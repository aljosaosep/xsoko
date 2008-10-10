
#include "win.h"

#include "win.h"
#include <iostream>
#include <stdlib.h>

    struct Mouse {
        int x, y;
    //    int button; // 1=left, 2=right, 3=middle
    };

    struct MouseDrag{
        bool drag;     // window draggin enabled
        int x,y;   // X and Y coords when drag started
        Window* window;
    };

    Component* compPressed;
    MouseDrag mouseDrag;
    GLuint fontList;          // font display list
    
    GLuint guiTexture;      // the GUI texture
    GLuint fontTexture;      // the font texture
    Mouse wmouse;
    
    int mWidth, mHeight;
    Window* mainWin = NULL;
    

    using namespace std;
    
    void DestroyGUI(){
        glDeleteLists(fontList,256);
        GLuint tex[2];
        tex[0] = guiTexture;
        tex[1] = fontTexture;
        glDeleteTextures(2, tex);
        fontTexture = guiTexture = 0;
    }
    
// Write

void glWrite(int x,int y, string text)
{
  glBindTexture(GL_TEXTURE_2D, fontTexture);
  glPushMatrix();
    glTranslatef(x, y, 0.02);
    glListBase(fontList);
    glCallLists(text.length(), GL_BYTE, text.c_str());
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, guiTexture);
}
    
// Window 

/*------------------------------------------------------------------*
 *  Procedure to create the font display list                       *
 *------------------------------------------------------------------*/
bool BuildFont()
{
  FILE *fontFile = fopen("data/font.fnt","rb");
  if(fontFile == NULL)
    return false;
  
  unsigned char fontWidth[256];
  if(fread(fontWidth,1,sizeof(fontWidth),fontFile)!=sizeof(fontWidth)){
      fclose(fontFile);
      return false;
  }
  fclose(fontFile);

  // create the font display list
  fontList = glGenLists(256);               // Storage For 128 Characters
  for(int i=0;i<256;i++)
  {
    GLfloat x = (float)(i % 16) / 16;	     		// X Position Of Current Character
    GLfloat y = (float)(i / 16) / 16;	     		// Y Position Of Current Character
    glNewList(fontList+i, GL_COMPILE);       // Start Building A List
    glBegin(GL_QUADS);
      GLfloat xs = (16.0f-fontWidth[i])/2.0f/256.0f;
      glTexCoord2f(x+xs,1.0f-y-0.0625f);                                            glVertex2i(0, 0);
      glTexCoord2f(x+xs + (GLfloat)fontWidth[i]/256.0f + 1.0f/512.0f, 1.0f-y-0.0625f);  glVertex2i(fontWidth[i], 0);
      glTexCoord2f(x+xs + (GLfloat)fontWidth[i]/256.0f + 1.0f/512.0f, 1.0f-y);         glVertex2i(fontWidth[i], 16);
      glTexCoord2f(x+xs,1.0f-y);                                                   glVertex2i(0, 16);
    glEnd();
    glTranslatef(fontWidth[i], 0, 0);
    glEndList();
  }
  return true;
}

    bool InitGUI(const char* guiTextureFileName,const char* fontTextureFileName){
          glClearColor(0.0, 0.0, 0.0, 0.0); 	   // Black Background
          glShadeModel(GL_SMOOTH);                 // Enables Smooth Color Shading
          glClearDepth(1.0);                       // Depth Buffer Setup
          glEnable(GL_DEPTH_TEST);                 // Enable Depth Buffer
          glDepthFunc(GL_LESS);		           // The Type Of Depth Test To Do

          glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   //Realy Nice perspective calculations

          glEnable(GL_TEXTURE_2D);

        glGenTextures(1,&guiTexture);
        glBindTexture(GL_TEXTURE_2D,guiTexture);
        if(glfwLoadTexture2D(guiTextureFileName, GLFW_ORIGIN_UL_BIT)){
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
           glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        } else
            return false;
        glGenTextures(1,&fontTexture);
        glBindTexture(GL_TEXTURE_2D,fontTexture);
        if(glfwLoadTexture2D(fontTextureFileName, GLFW_ORIGIN_UL_BIT)){
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
           glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
           return BuildFont();
        } else
            return false;
    }

// Component

Component::Component(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->visible = true;
    this->parent = NULL;
}

Position Component::getPosition(){
    Position pos;
    pos.x = this->x;
    pos.y = this->y;
    return pos;
}

Size Component::getSize(){
    Size size;
    size.width = this->width;
    size.height = this->height;
    return size;
}

Component* Component::getParent(){
    return parent;
}

void Component::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Component::setSize(int width, int height){
    this->width = width;
    this->height = height;
}

bool Component::isVisible(){
    return this->visible;
}

void Component::setVisible(bool visible){
    this->visible = visible;
}

void Component::setParent(Component* parent){
    this->parent = parent;
}

//Container

Container::Container(int x, int y, int width, int height) :
Component(x,y,width,height) {}

/*------------------------------------------------------------------*
 *  Adds a new component onto container                             *
 *------------------------------------------------------------------*/

void Container::AddComponent(Component* component){
    component->setParent(this);
    components.push_back(component);
}

void Container::onMouseDown(){
    if(!visible)
        return;
    
    // recalculate coordinates relative to window
    int mouseX = wmouse.x - x;
    int mouseY = mHeight - wmouse.y - 26 - y;
    Component* parent = this->parent;
    while(parent != NULL){
        Position loc = parent->getPosition();
        mouseX -= loc.x;
        mouseY -= loc.y;
        parent = parent->getParent();
    }

    for(unsigned i=0;i<components.size();i++)
    {
      Size size = components[i]->getSize();
      Position pos = components[i]->getPosition();
      if ((mouseX > pos.x) && (mouseX < pos.x + size.width))
        if ((mouseY > pos.y) && (mouseY < pos.y + size.height))
        {
            compPressed = components[i];
            compPressed->onMouseDown();
        }
    }
}

Container::~Container(){
    for(int i=0;i<components.size();i++){
        delete components.at(i);
    }
}

/*------------------------------------------------------------------*
 *  initialise window and setup defaults                            *
 *------------------------------------------------------------------*/
Window::Window(int wX, int wY, int wWidth, int wHeight) : Container(wX,wY,wWidth,wHeight)
{
  zorder = 0;         // used if you specifically want to set a window higher
  visible = true;     // start off visible
  alpha = 0.9;        // defult for alpha bl}ing
};

/*------------------------------------------------------------------*
 *  Adds a new child window                                         *
 *------------------------------------------------------------------*/
void Window::AddChildWindow(Window* child)
{
    childwindows.push_back(child);
}

/*------------------------------------------------------------------*
 *  Render the window. Calls render button, child windows ...       *
 *------------------------------------------------------------------*/
void Window::Render()
{
  if (visible)
  {
    glBindTexture(GL_TEXTURE_2D, guiTexture);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glColor4f(1.0, 1.0, 1.0, alpha);

    glPushMatrix();
      glTranslatef(x, mHeight - 26 -y , zorder);
      glBegin(GL_QUADS);
        // top left corner of window.
        glTexCoord2f( 0, 1);        glVertex2f(0, 0);
        glTexCoord2f( 0, 1-(float)27/128); glVertex2f(0, -27);
        glTexCoord2f((float)64/128, 1-(float)27/128); glVertex2f(63, -27);
        glTexCoord2f((float)64/128, 1);        glVertex2f(63, 0);

        // top of window.
        glTexCoord2f((float)64/128, 1);        glVertex2f(63, 0);
        glTexCoord2f((float)64/128, 1-(float)27/128); glVertex2f(63, -27);
        glTexCoord2f((float)96/128, 1-(float)27/128); glVertex2f(width-32, -27);
        glTexCoord2f((float)96/128, 1);        glVertex2f(width-32, 0);

        // top right corder of window.
        glTexCoord2f((float)96/128, 1);        glVertex2f(width-32, 0);
        glTexCoord2f((float)96/128, 1-(float)27/128); glVertex2f(width-32, -27);
        glTexCoord2f(1, 1-(float)27/128);      glVertex2f(width, -27);
        glTexCoord2f(1, 1);             glVertex2f(width, 0);

      
        // left side of window.
        glTexCoord2f(0, 1-(float)27/128);  glVertex2f(0, -27);
        glTexCoord2f(0, (float)27/128);    glVertex2f(0, -height+27);
        glTexCoord2f((float)6/128, (float)27/128);    glVertex2f(6,-height+27);
        glTexCoord2f((float)6/128, 1-(float)27/128);  glVertex2f(6, -27);

        // draw the main body of the window
        glTexCoord2f((float) 9/128, (float)96/128);     glVertex2f(6, 0);
        glTexCoord2f((float) 9/128, (float)64/128);     glVertex2f(6, 25-height);
        glTexCoord2f((float)39/128, (float)64/128);     glVertex2f(width-7, 25-height);
        glTexCoord2f((float)39/128, (float)96/128);     glVertex2f(width-7, 0);

        // right side of window.
        glTexCoord2f(1-(float)7/128, 1-(float)27/128);glVertex2f(width-7, -27);
        glTexCoord2f(1-(float)7/128, (float)27/128);  glVertex2f(width-7, -height+27);
        glTexCoord2f(1,   (float)27/128);      glVertex2f(width,-height+27);
        glTexCoord2f(1, 1-(float)27/128);      glVertex2f(width, -27);

        // bottom left corner of window.
        glTexCoord2f( 0, (float)27/128);   glVertex2f(0, 27-height);
        glTexCoord2f( 0,  0);   glVertex2f(0, -height);
        glTexCoord2f((float)64/128,  0);   glVertex2f(63, -height);
        glTexCoord2f((float)64/128, (float)27/128);   glVertex2f(63, 27-height);

        // bottom of window.
        glTexCoord2f((float)64/128, (float)27/128);   glVertex2f(63, 27-height);
        glTexCoord2f((float)64/128, 0);    glVertex2f(63, -height);
        glTexCoord2f((float)96/128, 0);    glVertex2f(width-32, -height);
        glTexCoord2f((float)96/128, (float)27/128);   glVertex2f(width-32, 27-height);

        // bottom right corder of window.
        glTexCoord2f((float)96/128, (float)27/128);   glVertex2f(width-32, 27-height);
        glTexCoord2f((float)96/128, 0);    glVertex2f(width-32, -height);
        glTexCoord2f(1, 0);         glVertex2f(width, -height);
        glTexCoord2f(1, (float)27/128);        glVertex2f(width, 27-height);

        // window close button
        glTexCoord2f((float)104/128, (float)96/128); glVertex3f(width-22, -8,  0.01);
        glTexCoord2f((float)104/128, (float)80/128); glVertex3f(width-22, -24, 0.01);
        glTexCoord2f((float)120/128, (float)80/128); glVertex3f(width-6, -24, 0.01);
        glTexCoord2f((float)120/128, (float)96/128); glVertex3f(width-6, -8,  0.01);
      glEnd();

      glTranslatef(0, 0, 0.02);      
      for(unsigned i=0;i<components.size();i++){
        components[i]->Render();
      }

    glPopMatrix();
    glBlendFunc(GL_ONE,GL_ONE);
    glDisable(GL_BLEND);

    // draw the child windows
    glPushMatrix();
      glTranslatef(0, 0, 0.1);
      for(unsigned i=0;i<childwindows.size();i++)
        childwindows[i]->Render();
    glPopMatrix();
  }
}

vector<Window*>* Window::getChildWindows(){
    return &childwindows;
}

void Window::onMouseDown(){
    if(!visible)
        return;
    
    int mouseX   = wmouse.x;
    int mouseY   = mHeight - wmouse.y - 26;
    
    // Test to see if user clicked on window close icon
    if ((mouseX > x + width-22) && (mouseX < x + width-6))
      if ((mouseY > y+8) && (mouseY < y + 24))
      {
        setVisible(false);
        return;
      }

    // Test to see if user clicked in caption bar
    if ((mouseX > x) && (mouseX < x + width))
      if ((mouseY > y+1) && (mouseY < y + 26))
      {
        mouseDrag.drag = true;
        mouseDrag.x    = x - wmouse.x;
        mouseDrag.y    = y - (mHeight - wmouse.y);
        mouseDrag.window =  this;
        return;
      }
    
    Container::onMouseDown();
}

float Window::getAlpha(){
    return alpha;
}

void Window::setAlpha(float alpha){
    this->alpha = (alpha < 1) ? alpha : 1;
    if(this->alpha < 0)
        alpha = 0;
}

float  Window::getZOrder(){
    return zorder;
}

void  Window::setZOrder(float zorder){
    this->zorder = zorder;
}

Window::~Window(){
    for(int i=0;i<childwindows.size();i++){
        delete childwindows.at(i);
    }
}

// TButton 

/*------------------------------------------------------------------*
 *  initialise a button                                             *
 *------------------------------------------------------------------*/
Button::Button(int x, int y, int width, int height, string caption) : Component(x,y,width,height)
{
  this->pressed = false;
  this->caption = caption;
  this->onClick = NULL;
}


/*------------------------------------------------------------------*
 *  Render the button                                               *
 *------------------------------------------------------------------*/
void Button::Render()
{
    if(!visible)
        return;
  if (pressed) 
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)57/128, (float)95/128); glVertex2f(x, -y);
      glTexCoord2f((float)57/128, (float)70/128); glVertex2f(x, -y-height);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2f(x+6,-y-height);
      glTexCoord2f((float)62/128, (float)95/128); glVertex2f(x+6, -y);

      // middle
      glTexCoord2f((float)62/128, (float)95/128); glVertex2f(x+6, -y);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2f(x+6, -y-height);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2f(x+width-6, -y-height);
      glTexCoord2f((float)66/128, (float)95/128); glVertex2f(x+width-6, -y);

      // right side
      glTexCoord2f((float)66/128, (float)95/128); glVertex2f(x+width-6, -y);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2f(x+width-6, -y-height);
      glTexCoord2f((float)71/128, (float)70/128); glVertex2f(x+width, -y-height);
      glTexCoord2f((float)71/128, (float)95/128); glVertex2f(x+width, -y);
    glEnd();

    glWrite(x + 1 + (width - caption.length()*6) / 2, -y-21, caption);
  }
  else
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)41/128, (float)95/128); glVertex2f(x, -y);
      glTexCoord2f((float)41/128, (float)70/128); glVertex2f(x, -y-height);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2f(x+6,-y-height);
      glTexCoord2f((float)46/128, (float)95/128); glVertex2f(x+6, -y);

      // middle
      glTexCoord2f((float)46/128, (float)95/128); glVertex2f(x+6, -y);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2f(x+6, -y-height);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2f(x+width-6, -y-height);
      glTexCoord2f((float)50/128, (float)95/128); glVertex2f(x+width-6, -y);

      // right side
      glTexCoord2f((float)50/128, (float)95/128); glVertex2f(x+width-6, -y);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2f(x+width-6, -y-height);
      glTexCoord2f((float)55/128, (float)70/128); glVertex2f(x+width, -y-height);
      glTexCoord2f((float)55/128, (float)95/128); glVertex2f(x+width, -y);
    glEnd();

    glWrite(x + (width-caption.length()*6) / 2, -y-20, caption);
  }
}

void Button::onMouseDown(){
    pressed = true;
}

void Button::onMouseUp(){
    pressed = false;
    if(onClick != NULL)
        onClick();
}

string Button::getCaption(){
    return caption;
}

void Button::setCaption(const string& caption){
    this->caption = caption;
}

// TPanel 

/*------------------------------------------------------------------*
 *  initialise a panel                                              *
 *------------------------------------------------------------------*/
Panel::Panel(int x, int y, int width, int height) : Container(x,y,width,height)
{
}


/*------------------------------------------------------------------*
 *  Render the Panel                                                *
 *------------------------------------------------------------------*/
void Panel::Render()
{
      //rendered = false;
  if(visible)
  {
    glBegin(GL_QUADS);
      // top left corner of panel.
      glTexCoord2f((float) 8/128, (float)64/128); glVertex2f(x, -y);
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2f(x, -y-10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2f(x+10, -y-10);
      glTexCoord2f((float)18/128, (float)64/128); glVertex2f(x+10, -y);

      // top of panel.
      glTexCoord2f((float)18/128, (float)64/128); glVertex2f(x+10, -y);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2f(x+10, -y-10);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2f(x+10+(width-20), -y-10);
      glTexCoord2f((float)30/128, (float)64/128); glVertex2f(x+10+(width-20), -y);

      // top right corder of panel.
      glTexCoord2f((float)30/128, (float)64/128); glVertex2f(x+width-10, -y);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2f(x+width-10, -y-10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2f(x+width, -y-10);
      glTexCoord2f((float)40/128, (float)64/128); glVertex2f(x+width, -y);

      // left side of panel.
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2f(x, -y-10);
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2f(x, -y-height+10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2f(x+10, -y-height+10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2f(x+10, -y-10);

      // middle of panel.
      glTexCoord2f((float)18/128, (float)54/128); glVertex2f(x+10, -y-10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2f(x+10, -y-height+10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2f(x+10+(width-20), -y-height+10);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2f(x+10+(width-20), -y-10);

      // right side of panel.
      glTexCoord2f((float)30/128, (float)54/128); glVertex2f(x+width-10, -y-10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2f(x+width-10, -y-height+10);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2f(x+width, -y-height+10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2f(x+width, -y-10);

      // bottom left corner of panel.
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2f(x, -y-height+10);
      glTexCoord2f((float) 8/128, (float)32/128); glVertex2f(x, -y-height);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2f(x+10, -y-height);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2f(x+10, -y-height+10);

      // bottom middle of panel.
      glTexCoord2f((float)18/128, (float)42/128); glVertex2f(x+10, -y-height+10);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2f(x+10, -y-height);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2f(x+10+(width-20), -y-height);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2f(x+10+(width-20), -y-height+10);

      // bottom right corner of panel.
      glTexCoord2f((float)30/128, (float)42/128); glVertex2f(x+width-10, -y-height+10);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2f(x+width-10, -y-height);
      glTexCoord2f((float)40/128, (float)32/128); glVertex2f(x+width, -y-height);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2f(x+width, -y-height+10);

    glEnd();
    
    glPushMatrix();
    glTranslatef(x,-y,0.02);
    for(unsigned i=0;i<components.size();i++){
        components[i]->Render();
      }
    glPopMatrix();
  }
}

// ListBox 

/*------------------------------------------------------------------*
 *  initialise a panel                                              *
 *------------------------------------------------------------------*/
ListBox::ListBox(int x, int y, int width, int height) : Component(x,y,width,height)
{
    selected = -1;
    onClick = NULL;
    upPressed = false;
    downPressed = false;
    drawIndex = 0;
    canShow = (height-4) / 16;
}


/*------------------------------------------------------------------*
 *  Render the Panel                                                *
 *------------------------------------------------------------------*/
void ListBox::Render()
{
  if(visible)
  {
    glBegin(GL_QUADS);
      // top of panel.
      glTexCoord2f((float)10/128, (float)33/128); glVertex2f(x+2, -y);
      glTexCoord2f((float)10/128, (float)32/128); glVertex2f(x+2, -y-2);
      glTexCoord2f((float)37/128, (float)32/128); glVertex2f(x+2+(width-4), -y-2);
      glTexCoord2f((float)37/128, (float)33/128); glVertex2f(x+2+(width-4), -y);

      // left side of panel.
      glTexCoord2f((float)38/128, (float)61/128); glVertex2f(x, -y);
      glTexCoord2f((float)38/128, (float)34/128); glVertex2f(x, -y-height+2);
      glTexCoord2f((float)39/128, (float)34/128); glVertex2f(x+2, -y-height+2);
      glTexCoord2f((float)39/128, (float)61/128); glVertex2f(x+2, -y);

      // middle of panel.
      glTexCoord2f((float)18/128, (float)54/128); glVertex2f(x+2, -y-2);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2f(x+2, -y-height+2);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2f(x+2+(width-4), -y-height+2);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2f(x+2+(width-4), -y-2);

      // right side of panel.
      glTexCoord2f((float) 8/128, (float)61/128); glVertex2f(x+width-2, -y);
      glTexCoord2f((float) 8/128, (float)34/128); glVertex2f(x+width-2, -y-height+2);
      glTexCoord2f((float) 9/128, (float)34/128); glVertex2f(x+width, -y-height+2);
      glTexCoord2f((float) 9/128, (float)61/128); glVertex2f(x+width, -y);

      // bottom middle of panel.
      glTexCoord2f((float)10/128, (float)62/128); glVertex2f(x+2, -y-height+2);
      glTexCoord2f((float)10/128, (float)63/128); glVertex2f(x+2, -y-height);
      glTexCoord2f((float)37/128, (float)63/128); glVertex2f(x+2+(width-2), -y-height);
      glTexCoord2f((float)37/128, (float)62/128); glVertex2f(x+2+(width-2), -y-height+2);      

    glEnd();
    
    glTranslatef(0,0,0.02);    
    int limit = (canShow<items.size()) ? canShow : items.size();
    for(unsigned i=0;i<limit;i++){
        if(selected == i+drawIndex)
            drawSelected(x+2,y+2+(i*16),width-20,items.at(i+drawIndex));
        else
            glWrite(x+5,-y-17-(i*16),items.at(i+drawIndex));
    }
    
    drawButton(x+width-18,y+2,upPressed,true);
    drawButton(x+width-18,y+height-18,downPressed,false);
    glBegin(GL_QUADS);
          glTexCoord2f((float) 8/128, (float)61/128); glVertex2f(x+width-10, -y-18);
          glTexCoord2f((float) 8/128, (float)34/128); glVertex2f(x+width-10, -y-height+18);
          glTexCoord2f((float) 9/128, (float)34/128); glVertex2f(x+width-9, -y-height+18);
          glTexCoord2f((float) 9/128, (float)61/128); glVertex2f(x+width-9, -y-18);
    glEnd();
    if(items.size() > canShow){
        float length = (float)(height - 34) / (items.size() - canShow + 1);
        float dy = length * drawIndex + length/2;
        glTranslatef(0,0,0.02);
        glBegin(GL_QUADS);
          glTexCoord2f((float)101/128, (float)63/128); glVertex2f(x+width-17, -y-dy-9);
          glTexCoord2f((float)101/128, (float)50/128); glVertex2f(x+width-17, -y-dy-25);
          glTexCoord2f((float)88/128, (float)50/128); glVertex2f(x+width-1,-y-dy-25);
          glTexCoord2f((float)88/128, (float)63/128); glVertex2f(x+width-1, -y-dy-9);
        glEnd();
    }
  }
}

void ListBox::onMouseDown(){
    // recalculate coordinates relative to window
    int mouseX = wmouse.x - x;
    int mouseY = mHeight - wmouse.y - 26 - y;
    Component* parent = this->parent;
    while(parent != NULL){
        Position loc = parent->getPosition();
        mouseX -= loc.x;
        mouseY -= loc.y;
        parent = parent->getParent();
    }
    
    if(mouseX >= 2 && mouseX <= width-18){
        int index = (mouseY-2) / 16 + drawIndex;
        if(index < items.size()){
            selected = index;
        }
    }
    if(mouseX >= width-18){
        if(mouseY >= 2 && mouseY <= 18){
            upPressed = true;
        }
        if(mouseY >= height-18){
            downPressed = true;
        }
    } else
        if(this->onClick != NULL){
            onClick(items.at(selected));
        }
}

void ListBox::onMouseUp(){
    if(upPressed){
        if(drawIndex > 0)
            drawIndex--;
        upPressed= false;
    }
    if(downPressed){
        if(drawIndex+canShow < items.size())
            drawIndex++;
        downPressed= false;
    }
}

string  ListBox::getSelectedItem(){
    return items.at(selected);
}

void ListBox::drawButton(int x, int y,bool pressed,bool upArrow)
{
  if (pressed) 
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)57/128, (float)95/128); glVertex2f(x, -y);
      glTexCoord2f((float)57/128, (float)70/128); glVertex2f(x, -y-16);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2f(x+6,-y-16);
      glTexCoord2f((float)62/128, (float)95/128); glVertex2f(x+6, -y);

      // middle
      glTexCoord2f((float)62/128, (float)95/128); glVertex2f(x+6, -y);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2f(x+6, -y-16);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2f(x+10, -y-16);
      glTexCoord2f((float)66/128, (float)95/128); glVertex2f(x+10, -y);

      // right side
      glTexCoord2f((float)66/128, (float)95/128); glVertex2f(x+10, -y);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2f(x+10, -y-16);
      glTexCoord2f((float)71/128, (float)70/128); glVertex2f(x+16, -y-16);
      glTexCoord2f((float)71/128, (float)95/128); glVertex2f(x+16, -y);
    glEnd();
    glTranslatef(0,0,0.2);
    if(upArrow){
        glBegin(GL_QUADS);
        glTexCoord2f((float)117/128, (float)63/128); glVertex2f(x+1, -y-1);
        glTexCoord2f((float)117/128, (float)50/128); glVertex2f(x+1, -y-17);
        glTexCoord2f((float)104/128, (float)50/128); glVertex2f(x+17,-y-17);
        glTexCoord2f((float)104/128, (float)63/128); glVertex2f(x+17, -y-1);
      glEnd();
    }
    else {
        glBegin(GL_QUADS);
          glTexCoord2f((float)104/128, (float)50/128); glVertex2f(x+1, -y-1);
          glTexCoord2f((float)104/128, (float)63/128); glVertex2f(x+1, -y-17);
          glTexCoord2f((float)117/128, (float)63/128); glVertex2f(x+17,-y-17);
          glTexCoord2f((float)117/128, (float)50/128); glVertex2f(x+17, -y-1);
        glEnd();
    }
  }
  else
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)41/128, (float)95/128); glVertex2f(x, -y);
      glTexCoord2f((float)41/128, (float)70/128); glVertex2f(x, -y-16);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2f(x+6,-y-16);
      glTexCoord2f((float)46/128, (float)95/128); glVertex2f(x+6, -y);

      // middle
      glTexCoord2f((float)46/128, (float)95/128); glVertex2f(x+6, -y);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2f(x+6, -y-16);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2f(x+10, -y-16);
      glTexCoord2f((float)50/128, (float)95/128); glVertex2f(x+10, -y);

      // right side
      glTexCoord2f((float)50/128, (float)95/128); glVertex2f(x+10, -y);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2f(x+10, -y-16);
      glTexCoord2f((float)55/128, (float)70/128); glVertex2f(x+16, -y-16);
      glTexCoord2f((float)55/128, (float)95/128); glVertex2f(x+16, -y);
    glEnd();
    glTranslatef(0,0,0.2);
    if(upArrow){
      glBegin(GL_QUADS);
        glTexCoord2f((float)117/128, (float)63/128); glVertex2f(x, -y);
        glTexCoord2f((float)117/128, (float)50/128); glVertex2f(x, -y-16);
        glTexCoord2f((float)104/128, (float)50/128); glVertex2f(x+16,-y-16);
        glTexCoord2f((float)104/128, (float)63/128); glVertex2f(x+16, -y);
      glEnd();
    } 
    else {
        glBegin(GL_QUADS);
          glTexCoord2f((float)104/128, (float)50/128); glVertex2f(x, -y);
          glTexCoord2f((float)104/128, (float)63/128); glVertex2f(x, -y-16);
          glTexCoord2f((float)117/128, (float)63/128); glVertex2f(x+16,-y-16);
          glTexCoord2f((float)117/128, (float)50/128); glVertex2f(x+16, -y);
        glEnd();
    }
  }
}

void ListBox::drawSelected(int x, int y,int width,string item){
    glTranslatef(0,0,0.02);
    glBegin(GL_QUADS);
      // top left corner of panel.
      glTexCoord2f((float) 8/128, (float)64/128); glVertex2f(x, -y);
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2f(x, -y-10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2f(x+10, -y-10);
      glTexCoord2f((float)18/128, (float)64/128); glVertex2f(x+10, -y);

      // top of panel.
      glTexCoord2f((float)18/128, (float)64/128); glVertex2f(x+10, -y);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2f(x+10, -y-10);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2f(x+10+(width-20), -y-10);
      glTexCoord2f((float)30/128, (float)64/128); glVertex2f(x+10+(width-20), -y);

      // top right corder of panel.
      glTexCoord2f((float)30/128, (float)64/128); glVertex2f(x+width-10, -y);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2f(x+width-10, -y-10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2f(x+width, -y-10);
      glTexCoord2f((float)40/128, (float)64/128); glVertex2f(x+width, -y);

      // left side of panel.
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2f(x, -y-10);
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2f(x, -y-16+10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2f(x+10, -y-16+10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2f(x+10, -y-10);

      // right side of panel.
      glTexCoord2f((float)30/128, (float)54/128); glVertex2f(x+width-10, -y-10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2f(x+width-10, -y-16+10);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2f(x+width, -y-16+10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2f(x+width, -y-10);

      // bottom left corner of panel.
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2f(x, -y-16+10);
      glTexCoord2f((float) 8/128, (float)32/128); glVertex2f(x, -y-16);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2f(x+10, -y-16);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2f(x+10, -y-16+10);

      // bottom middle of panel.
      glTexCoord2f((float)18/128, (float)42/128); glVertex2f(x+10, -y-16+10);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2f(x+10, -y-16);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2f(x+10+(width-20), -y-16);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2f(x+10+(width-20), -y-16+10);

      // bottom right corner of panel.
      glTexCoord2f((float)30/128, (float)42/128); glVertex2f(x+width-10, -y-16+10);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2f(x+width-10, -y-16);
      glTexCoord2f((float)40/128, (float)32/128); glVertex2f(x+width, -y-16);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2f(x+width, -y-16+10);

    glEnd();
    
    glWrite(x+4,-y-16,item);
}

void ListBox::addItem(string item){
    items.push_back(item);
    if(items.size() == 1){
        selected = 0;
        if(this->onClick != NULL){
            onClick(item);
        }
    }
}

// TCheckbox 

/*------------------------------------------------------------------*
 *  initialise a checkbox                                           *
 *------------------------------------------------------------------*/
CheckBox::CheckBox(int x,int y,bool checked) : Component(x,y,16,16)
{
  this->checked = false;
}


/*------------------------------------------------------------------*
 *  Render a Checkbox                                               *
 *------------------------------------------------------------------*/
void CheckBox::Render()
{
  if(visible)
  {
    glTranslatef(0, 0, 0.02);
    if (checked)
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)88/128, (float)96/128); glVertex2f(x, -y);
        glTexCoord2f((float)88/128, (float)80/128); glVertex2f(x, -y-16);
        glTexCoord2f((float)104/128, (float)80/128); glVertex2f(x+16,-y-16);
        glTexCoord2f((float)104/128, (float)96/128); glVertex2f(x+16, -y);
      glEnd();
    }
    else
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)72/128, (float)96/128); glVertex2f(x, -y);
        glTexCoord2f((float)72/128, (float)80/128); glVertex2f(x, -y-16);
        glTexCoord2f((float)88/128, (float)80/128); glVertex2f(x+16,-y-16);
        glTexCoord2f((float)88/128, (float)96/128); glVertex2f(x+16, -y);
      glEnd();
    }
  }
}

void CheckBox::onMouseDown(){
    checked = !checked;
}

bool CheckBox::isChecked(){
    return checked;
}

void CheckBox::setChecked(bool checked){
    this->checked = checked;
}

// TRadioButton

/*------------------------------------------------------------------*
 *  initialise a Radio Button                                       *
 *------------------------------------------------------------------*/
RadioButton::RadioButton(int x, int y,RadioButtonGroup* group,bool checked) : Component(x,y,16,16)
{
  this->group = group;
  group->addToGroup(this);
  setChecked(checked);
}


/*------------------------------------------------------------------*
 *  Render Radio Button                                             *
 *------------------------------------------------------------------*/
void RadioButton::Render()
{
  if(visible)
  {
    if(checked)
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)88/128, (float)80/128); glVertex2f(x, -y);
        glTexCoord2f((float)88/128, (float)64/128); glVertex2f(x, -y-16);
        glTexCoord2f((float)104/128, (float)64/128); glVertex2f(x+16,-y-16);
        glTexCoord2f((float)104/128, (float)80/128); glVertex2f(x+16, -y);
      glEnd();
    }
    else
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)72/128, (float)80/128); glVertex2f(x, -y);
        glTexCoord2f((float)72/128, (float)64/128); glVertex2f(x, -y-16);
        glTexCoord2f((float)88/128, (float)64/128); glVertex2f(x+16,-y-16);
        glTexCoord2f((float)88/128, (float)80/128); glVertex2f(x+16, -y);
      glEnd();
    }
  }
}

void RadioButton::onMouseDown(){
    setChecked(true);
}

bool RadioButton::isChecked(){
    return checked;
}

void RadioButton::setChecked(bool checked){
    if(checked && group != NULL){
        vector<RadioButton*>* radioButtons = group->getRadioButtons();
        for(unsigned i=0;i<radioButtons->size();i++) {
            radioButtons->at(i)->checked = false;
        }
    }
    this->checked = checked;
}

RadioButtonGroup* RadioButton::getRadioButtonGroup(){
    return group;
}

void RadioButton::setRadioButtonGroup(RadioButtonGroup* group){
    if(this->group != NULL){
        this->group->removeFromGroup(this);
    }
    this->group = group;
    group->addToGroup(this);
}

// RadioButtonGroup

void RadioButtonGroup::addToGroup(RadioButton* radioButton){
    radioButtons.push_back(radioButton);
}

void RadioButtonGroup::removeFromGroup(RadioButton* radioButton){
    for(unsigned i=0;i<radioButtons.size();i++) {
        if(radioButtons[i] == radioButton)
            radioButtons.erase(radioButtons.begin() + i);
    }
}

vector<RadioButton*>* RadioButtonGroup::getRadioButtons(){
    return &radioButtons;
}

// TText 

/*------------------------------------------------------------------*
 *  initialise the Text                                             *
 *------------------------------------------------------------------*/
Text::Text(int x,int y,string text) : Component(x,y,6*text.length(),16)
{
  caption = text;
}

/*------------------------------------------------------------------*
 *  Render Radio Text                                               *
 *------------------------------------------------------------------*/
void Text::Render()
{
    if(visible)
        glWrite(x, -y-16, caption);
}

string Text::getText(){
    return caption;
}

void Text::setText(const string& text){
    caption = text;
}

/*------------------------------------------------------------------*
 *  Procedure to render the GUI                                     *
 *------------------------------------------------------------------*/
void RenderGUI()
{
  if(mainWin == NULL)
      return;

  glMatrixMode(GL_PROJECTION);  // Change Matrix Mode to Projection
  glLoadIdentity();             // Reset View
  glOrtho(0, mWidth, 0, mHeight, 0, 100);
  glMatrixMode(GL_MODELVIEW);   // Change Projection to Matrix Mode
  glLoadIdentity();
          
  glTranslatef(0, 0, -1);
  glEnable(GL_TEXTURE_2D);
  mainWin->Render();                 // draw the main window and it will draw child windows
  
  //draw the mouse
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glColor4f(1,1,1,1);
  glBegin(GL_QUADS);
    glTexCoord2f((float)41/128, (float)64/128); glVertex3i(wmouse.x,    wmouse.y, 1);
    glTexCoord2f((float)72/128, (float)64/128); glVertex3i(wmouse.x+32, wmouse.y, 1);
    glTexCoord2f((float)72/128, (float)32/128); glVertex3i(wmouse.x+32, wmouse.y-32, 1);
    glTexCoord2f((float)41/128, (float)32/128); glVertex3i(wmouse.x,    wmouse.y-32, 1);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

  /*glMatrixMode(GL_PROJECTION);  // Change Matrix Mode to Projection
  glLoadIdentity();             // Reset View
  gluPerspective(45.0, mWidth/mHeight, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);   // Change Projection to Matrix Mode
  glLoadIdentity();*/
}

/*------------------------------------------------------------------*
 *  Procedure to check if the user clicked in a window or object    *
 *------------------------------------------------------------------*/
bool onMouseDown(Window* wnd)
{
  if(wnd == NULL)
      return true;
  
  if (wnd->isVisible() == false )
      return false;

  bool wndClick = false;

  // First check child windows since they can be on top.
  vector<Window*>* chWins = wnd->getChildWindows();
  for(unsigned i=0;i<chWins->size();i++)
      if (chWins->at(i)->isVisible()){
        wndClick = onMouseDown(chWins->at(i));
        if (wndClick)
            return true;
      }

  // test to see if user clicked in a window
  int mouseX   = wmouse.x;
  int mouseY   = mHeight - wmouse.y - 26;
  Position winPos = wnd->getPosition();
  Size winSize = wnd->getSize();
  if ((mouseX > winPos.x) && (mouseX < winPos.x + winSize.width))
      if ((mouseY > winPos.y) && (mouseY < winPos.y + winSize.height)){
          wndClick = true;
          wnd->onMouseDown();
      }

  return wndClick;
}


void onMouseMove(int x, int y){
  wmouse.x = x > 0 ? x : 0;
  if(x > mWidth)
      wmouse.x = mWidth;
  wmouse.y = y > 0 ? mHeight-y : mHeight;
  if(y>mHeight)
      wmouse.y = 0;
  if (mouseDrag.drag) 
  {
    mouseDrag.window->setPosition(mouseDrag.x + wmouse.x,mouseDrag.y - wmouse.y + mHeight);
  }
}

/*------------------------------------------------------------------*
 *  Event that runs when mouse button is released                   *
 *------------------------------------------------------------------*/
void onMouseUp()
{
  mouseDrag.drag = false;
//  wmouse.button = 0;  
  if(compPressed != NULL){
      compPressed->onMouseUp();
      compPressed = NULL;
  }
}

void onMouseClick(int button, int action){
    if(action == GLFW_PRESS){
        onMouseDown(mainWin);
    }
    if(action == GLFW_RELEASE)
        onMouseUp();
}

/*{------------------------------------------------------------------}
{  Handle window resize                                            }
{------------------------------------------------------------------}*/
void glResizeWnd(int Width, int Height){
  if (Height == 0)               // prevent divide by zero exception
    Height = 1;
  glViewport(0, 0, Width, Height);    // Set the viewport for the OpenGL window
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
  gluPerspective(45.0, Width/Height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth
  mWidth = Width;
  mHeight = Height;
  
  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View                  // Reset View
}

void setMainWindow(Window* mWin){
    mainWin = mWin;
}
