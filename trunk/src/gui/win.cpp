
#ifdef _WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glfw.h>
#include "win.h"
#include "fonts.h"
#include <stdlib.h>

using namespace std;

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

Container* Component::getParent(){
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

void Component::setParent(Container* parent){
    this->parent = parent;
}

void Component::setName(const string& name){
    this->name = name;
}

string Component::getName(){
    return name;
}

void Component::setSkin(GLuint texIndex){
    this->texIndex = texIndex;
}

//Container

Container::Container(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->visible = true;
    this->parent = NULL;
    compPressed = NULL;
}

void Container::AddComponent(Component* component){
    component->setParent(this);
    components.push_back(component);
}

void Container::AddContainer(Container* container){
    container->setParent(this);
    containers.push_back(container);
}

bool Container::isInArea(Position p, Size s, int x, int y){
    if ((x > p.x) && (x < p.x + s.width)&&
       (y > p.y) && (y < p.y + s.height))
        return true;
    else 
        return false;
}

void Container::setSkin(GLuint texIndex){
    this->texIndex = texIndex;
    for(unsigned i=0;i<components.size();i++)
        components[i]->setSkin(texIndex);
    for(unsigned i=0;i<containers.size();i++)
        containers[i]->setSkin(texIndex);
}

void Container::onMouseDown(int mx, int my){
    if(!visible)
        return;
    
    // recalculate coordinates relative to window
    int mouseX = mx - x;
    int mouseY = my - 26 - y;
    Container* parent = this->parent;
    while(parent != NULL){
        Position loc = parent->getPosition();
        mouseX -= loc.x;
        mouseY -= loc.y;
        parent = parent->getParent();
    }

    for(unsigned i=0;i<components.size();i++)
    {
        if (isInArea(components[i]->getPosition(),components[i]->getSize(),mouseX,mouseY))
        {
            compPressed = components[i];
            compPressed->onMouseDown(mx,my);
            break;
        }
    }
    for(unsigned i=0;i<containers.size();i++)
    {
        if (isInArea(containers[i]->getPosition(),containers[i]->getSize(),mouseX,mouseY))
        {
            containers[i]->onMouseDown(mx,my);
            break;
        }
    }
}

void Container::onMouseUp(int mx, int my){
    if(compPressed != NULL){
        compPressed->onMouseUp();
        compPressed = NULL;
    }
    for(unsigned i=0;i<containers.size();i++)
        containers[i]->onMouseUp(mx,my);
}

Position Container::getPosition(){
    Position pos;
    pos.x = this->x;
    pos.y = this->y;
    return pos;
}

Size Container::getSize(){
    Size size;
    size.width = this->width;
    size.height = this->height;
    return size;
}

Container* Container::getParent(){
    return parent;
}

void Container::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Container::setSize(int width, int height){
    this->width = width;
    this->height = height;
}

bool Container::isVisible(){
    return this->visible;
}

void Container::setVisible(bool visible){
    this->visible = visible;
}

void Container::setParent(Container* parent){
    this->parent = parent;
}

Container::~Container(){
    for(unsigned i=0;i<components.size();i++){
        delete components[i];
    }
    for(unsigned i=0;i<containers.size();i++){
        delete containers[i];
    }
}

/*------------------------------------------------------------------*
 *  initialise window and setup defaults                            *
 *------------------------------------------------------------------*/
Window::Window(int wX, int wY, int wWidth, int wHeight,string caption) : Container(wX,wY,wWidth,wHeight)
{
  zorder = 0;         // used if you specifically want to set a window higher
  visible = true;     // start off visible
  alpha = 0.9f;        // defult for alpha bl}ing
  onScreenResize();
  enableCloseButton = true;
  mouseDrag.drag = false;
  mouseDrag.x = 0;
  mouseDrag.y = 0;
  modal = false;
  this->caption = caption;
  fnt = new Font("font");
};

Window::~Window(){
    //Font::destroyInstance(fnt);
    delete fnt;
}

void Window::setVisible(bool visible){
    Container::setVisible(visible);
    
}

void Window::setModal(bool modal){
    this->modal = modal;
}

Font* Window::getFont(){
    return fnt;
}

/*------------------------------------------------------------------*
 *  Render the window. Calls render button, child windows ...       *
 *------------------------------------------------------------------*/
void Window::Render()
{
  if (visible)
  {
    glBindTexture(GL_TEXTURE_2D, texIndex);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glColor4f(1.0, 1.0, 1.0, alpha);

    glPushMatrix();
      glTranslatef((float)x, (float)screenHeight - 26 -y , zorder);
      glBegin(GL_QUADS);
        // top left corner of window.
        glTexCoord2f( 0, 1);							glVertex2i(0, 0);
        glTexCoord2f( 0, 1-(float)27/128);				glVertex2i(0, -27);
        glTexCoord2f((float)64/128, 1-(float)27/128);	glVertex2i(63, -27);
        glTexCoord2f((float)64/128, 1);					glVertex2i(63, 0);

        // top of window.
        glTexCoord2f((float)64/128, 1);					glVertex2i(63, 0);
        glTexCoord2f((float)64/128, 1-(float)27/128);	glVertex2i(63, -27);
        glTexCoord2f((float)96/128, 1-(float)27/128);	glVertex2i(width-32, -27);
        glTexCoord2f((float)96/128, 1);					glVertex2i(width-32, 0);

        // top right corder of window.
        glTexCoord2f((float)96/128, 1);					glVertex2i(width-32, 0);
        glTexCoord2f((float)96/128, 1-(float)27/128);	glVertex2i(width-32, -27);
        glTexCoord2f(1, 1-(float)27/128);				glVertex2i(width, -27);
        glTexCoord2f(1, 1);								glVertex2i(width, 0);

      
        // left side of window.
        glTexCoord2f(0, 1-(float)27/128);				glVertex2i(0, -27);
        glTexCoord2f(0, (float)27/128);					glVertex2i(0, -height+27);
        glTexCoord2f((float)6/128, (float)27/128);		glVertex2i(6,-height+27);
        glTexCoord2f((float)6/128, 1-(float)27/128);	glVertex2i(6, -27);

        // draw the main body of the window
        glTexCoord2f((float) 9/128, (float)96/128);     glVertex2i(6, -27);
        glTexCoord2f((float) 9/128, (float)64/128);     glVertex2i(6, 25-height);
        glTexCoord2f((float)39/128, (float)64/128);     glVertex2i(width-7, 25-height);
        glTexCoord2f((float)39/128, (float)96/128);     glVertex2i(width-7, -27);

        // right side of window.
        glTexCoord2f(1-(float)7/128, 1-(float)27/128);	glVertex2i(width-7, -27);
        glTexCoord2f(1-(float)7/128, (float)27/128);	glVertex2i(width-7, -height+27);
        glTexCoord2f(1,   (float)27/128);				glVertex2i(width,-height+27);
        glTexCoord2f(1, 1-(float)27/128);				glVertex2i(width, -27);

        // bottom left corner of window.
        glTexCoord2f( 0, (float)27/128);				glVertex2i(0, 27-height);
        glTexCoord2f( 0,  0);							glVertex2i(0, -height);
        glTexCoord2f((float)64/128,  0);				glVertex2i(63, -height);
        glTexCoord2f((float)64/128, (float)27/128);		glVertex2i(63, 27-height);

        // bottom of window.
        glTexCoord2f((float)64/128, (float)27/128);		glVertex2i(63, 27-height);
        glTexCoord2f((float)64/128, 0);					glVertex2i(63, -height);
        glTexCoord2f((float)96/128, 0);					glVertex2i(width-32, -height);
        glTexCoord2f((float)96/128, (float)27/128);		glVertex2i(width-32, 27-height);

        // bottom right corder of window.
        glTexCoord2f((float)96/128, (float)27/128);		glVertex2i(width-32, 27-height);
        glTexCoord2f((float)96/128, 0);					glVertex2i(width-32, -height);
        glTexCoord2f(1, 0);								glVertex2i(width, -height);
        glTexCoord2f(1, (float)27/128);					glVertex2i(width, 27-height);

        /*if(enableCloseButton){
            // window close button
            glTexCoord2f((float)104/128, (float)96/128); glVertex3i(width-22, -8,  0.01);
            glTexCoord2f((float)104/128, (float)80/128); glVertex3i(width-22, -24, 0.01);
            glTexCoord2f((float)120/128, (float)80/128); glVertex3i(width-6, -24, 0.01);
            glTexCoord2f((float)120/128, (float)96/128); glVertex3i(width-6, -8,  0.01);
        }*/
      glEnd();

      fnt->writeText((int)(width-fnt->stringWidth(caption))/2,-24,caption);
      glBindTexture(GL_TEXTURE_2D, texIndex);

      //glTranslatef(0, 0, 0.02);      
      for(unsigned i=0;i<components.size();i++){
		  glTranslatef(0, 0, 0.02f);      
        components[i]->Render();
      }
      for(unsigned i=0;i<containers.size();i++){
        containers[i]->Render();
      }

    glPopMatrix();
    glBlendFunc(GL_ONE,GL_ONE);
    glDisable(GL_BLEND);
  }
}

void Window::onMouseUp(int mx, int my){
    if(mouseDrag.drag){
        mouseDrag.drag = false;
        return;
    }
    Container::onMouseUp(mx,my);
}

void Window::onMouseMove(int mx, int my){
  if (mouseDrag.drag) 
  {
    x = mouseDrag.x + mx;
    y = mouseDrag.y + my;
  }
}

void Window::onMouseDown(int mx, int my){
    if(!visible)
        return;

    if(enableCloseButton){
        // Test to see if user clicked on window close icon
        if ((mx > x + width-22) && (mx < x + width-6))
          if ((my - 26 > y+8) && (my - 26 < y + 24)){
            setVisible(false);
            return;
          }
    }

    // Test to see if user clicked in caption bar
    if ((mx > x) && (mx < x + width))
      if ((my - 26 > y+1) && (my - 26 < y + 26))
      {
        mouseDrag.drag = true;
        mouseDrag.x    = x - mx;
        mouseDrag.y    = y - my;
        return;
      }
    
    Container::onMouseDown(mx,my);
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

void Window::onScreenResize(){
    int temp;
    glfwGetWindowSize(&temp,&screenHeight);
}

void Window::setEnableCloseButton(bool enabled){
    enableCloseButton = enabled;
}

// TButton 

/*------------------------------------------------------------------*
 *  initialise a button                                             *
 *------------------------------------------------------------------*/
Button::Button(int x, int y, int width, int height, string caption) : Component(x,y,width,height)
{
  this->pressed = false;
  this->caption = caption;
  this->action = NULL;
  fnt = new Font("font");
}

Button::~Button(){
    delete fnt;
}


/*------------------------------------------------------------------*
 *  Render the button                                               *
 *------------------------------------------------------------------*/
void Button::Render()
{
  if(!visible)
      return;
  
  glColor3f(1,1,1);
  if (pressed) 
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)57/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)57/128, (float)70/128); glVertex2i(x, -y-height);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6,-y-height);
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6, -y-height);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+width-6, -y-height);
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+width-6, -y);

      // right side
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+width-6, -y);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+width-6, -y-height);
      glTexCoord2f((float)71/128, (float)70/128); glVertex2i(x+width, -y-height);
      glTexCoord2f((float)71/128, (float)95/128); glVertex2i(x+width, -y);
    glEnd();

    fnt->writeText(x+1+(int)(width - fnt->stringWidth(caption))/2, -y-21, caption);
  }
  else
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)41/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)41/128, (float)70/128); glVertex2i(x, -y-height);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6,-y-height);
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6, -y-height);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+width-6, -y-height);
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+width-6, -y);

      // right side
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+width-6, -y);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+width-6, -y-height);
      glTexCoord2f((float)55/128, (float)70/128); glVertex2i(x+width, -y-height);
      glTexCoord2f((float)55/128, (float)95/128); glVertex2i(x+width, -y);
    glEnd();

    fnt->writeText(x + (int)(width-fnt->stringWidth(caption))/2, -y-20, caption);
  }
    glBindTexture(GL_TEXTURE_2D,texIndex);
}

void Button::onMouseDown(int mx, int my){
    pressed = true;
}

void Button::onMouseUp(){
    pressed = false;
    if(action != NULL)
        action->onAction(this);
}

string Button::getCaption(){
    return caption;
}

void Button::setCaption(const string& caption){
    this->caption = caption;
}

void Button::setAction(ButtonClick* action){
    this->action = action;
}

Font* Button::getFont(){
    return fnt;
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
      glTexCoord2f((float) 8/128, (float)64/128); glVertex2i(x, -y);
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2i(x, -y-10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);
      glTexCoord2f((float)18/128, (float)64/128); glVertex2i(x+10, -y);

      // top of panel.
      glTexCoord2f((float)18/128, (float)64/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+10+(width-20), -y-10);
      glTexCoord2f((float)30/128, (float)64/128); glVertex2i(x+10+(width-20), -y);

      // top right corder of panel.
      glTexCoord2f((float)30/128, (float)64/128); glVertex2i(x+width-10, -y);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+width-10, -y-10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2i(x+width, -y-10);
      glTexCoord2f((float)40/128, (float)64/128); glVertex2i(x+width, -y);

      // left side of panel.
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2i(x, -y-10);
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2i(x, -y-height+10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-height+10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);

      // middle of panel.
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-height+10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+10+(width-20), -y-height+10);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+10+(width-20), -y-10);

      // right side of panel.
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+width-10, -y-10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+width-10, -y-height+10);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2i(x+width, -y-height+10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2i(x+width, -y-10);

      // bottom left corner of panel.
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2i(x, -y-height+10);
      glTexCoord2f((float) 8/128, (float)32/128); glVertex2i(x, -y-height);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2i(x+10, -y-height);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-height+10);

      // bottom middle of panel.
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-height+10);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2i(x+10, -y-height);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2i(x+10+(width-20), -y-height);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+10+(width-20), -y-height+10);

      // bottom right corner of panel.
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+width-10, -y-height+10);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2i(x+width-10, -y-height);
      glTexCoord2f((float)40/128, (float)32/128); glVertex2i(x+width, -y-height);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2i(x+width, -y-height+10);

    glEnd();
    
    glPushMatrix();
    glTranslatef((float)x,(float)-y,0.02f);
    for(unsigned i=0;i<containers.size();i++){
        containers[i]->Render();
      }
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
    action = NULL;
    upPressed = false;
    downPressed = false;
    drawIndex = 0;
    canShow = (height-4) / 16;
    fnt = new Font("font");
}

ListBox::~ListBox(){
    delete fnt;
}

void ListBox::setAction(ListBoxClick* action){
    this->action = action;
}

Font* ListBox::getFont(){
    return fnt;
}

/*------------------------------------------------------------------*
 *  Render the Panel                                                *
 *------------------------------------------------------------------*/
void ListBox::Render()
{
  if(visible)
  {
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
      // top of panel.
      glTexCoord2f((float)10/128, (float)33/128); glVertex2i(x+2, -y);
      glTexCoord2f((float)10/128, (float)32/128); glVertex2i(x+2, -y-2);
      glTexCoord2f((float)37/128, (float)32/128); glVertex2i(x+2+(width-4), -y-2);
      glTexCoord2f((float)37/128, (float)33/128); glVertex2i(x+2+(width-4), -y);

      // left side of panel.
      glTexCoord2f((float)38/128, (float)61/128); glVertex2i(x, -y);
      glTexCoord2f((float)38/128, (float)34/128); glVertex2i(x, -y-height+2);
      glTexCoord2f((float)39/128, (float)34/128); glVertex2i(x+2, -y-height+2);
      glTexCoord2f((float)39/128, (float)61/128); glVertex2i(x+2, -y);

      // middle of panel.
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+2, -y-2);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+2, -y-height+2);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+2+(width-4), -y-height+2);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+2+(width-4), -y-2);

      // right side of panel.
      glTexCoord2f((float) 8/128, (float)61/128); glVertex2i(x+width-2, -y);
      glTexCoord2f((float) 8/128, (float)34/128); glVertex2i(x+width-2, -y-height+2);
      glTexCoord2f((float) 9/128, (float)34/128); glVertex2i(x+width, -y-height+2);
      glTexCoord2f((float) 9/128, (float)61/128); glVertex2i(x+width, -y);

      // bottom middle of panel.
      glTexCoord2f((float)10/128, (float)62/128); glVertex2i(x+2, -y-height+2);
      glTexCoord2f((float)10/128, (float)63/128); glVertex2i(x+2, -y-height);
      glTexCoord2f((float)37/128, (float)63/128); glVertex2i(x+2+(width-2), -y-height);
      glTexCoord2f((float)37/128, (float)62/128); glVertex2i(x+2+(width-2), -y-height+2);      

    glEnd();
    
    glTranslatef(0,0,0.02f);    
    unsigned limit = (canShow<items.size()) ? canShow : items.size();
    for(unsigned i=0;i<limit;i++){
        if(selected == i+drawIndex)
            drawSelected(x+2,y+2+(i*16),width-20,items.at(i+drawIndex));
        else {
            fnt->writeText(x+5,-y-17-(i*16),items.at(i+drawIndex));
            glBindTexture(GL_TEXTURE_2D,texIndex);
        }
    }

    glColor3f(1,1,1);
    drawButton(x+width-18,y+2,upPressed,true);
    drawButton(x+width-18,y+height-18,downPressed,false);
	glColor3f(1,1,1);
    glBegin(GL_QUADS);
          glTexCoord2f((float) 8/128, (float)61/128); glVertex2i(x+width-10, -y-18);
          glTexCoord2f((float) 8/128, (float)34/128); glVertex2i(x+width-10, -y-height+18);
          glTexCoord2f((float) 9/128, (float)34/128); glVertex2i(x+width-9, -y-height+18);
          glTexCoord2f((float) 9/128, (float)61/128); glVertex2i(x+width-9, -y-18);
    glEnd();
    if(items.size() > canShow){
        float length = (float)(height - 34) / (items.size() - canShow + 1);
        float dy = length * drawIndex + length/2;
        glTranslatef(0,0,0.02f);
        glBegin(GL_QUADS);
          glTexCoord2f((float)101/128, (float)63/128);	glVertex2f((float)x+width-17, -y-dy-9);
          glTexCoord2f((float)101/128, (float)50/128);	glVertex2f((float)x+width-17, -y-dy-25);
          glTexCoord2f((float)88/128, (float)50/128);	glVertex2f((float)x+width-1,-y-dy-25);
          glTexCoord2f((float)88/128, (float)63/128);	glVertex2f((float)x+width-1, -y-dy-9);
        glEnd();
    }
  }
}

void ListBox::onMouseDown(int mx, int my){
    // recalculate coordinates relative to window
    int mouseX = mx - x;
    int mouseY = my - 26 - y;
    Container* parent = this->parent;
    while(parent != NULL){
        Position loc = parent->getPosition();
        mouseX -= loc.x;
        mouseY -= loc.y;
        parent = parent->getParent();
    }
    
    if(mouseX >= 2 && mouseX <= width-18){
        unsigned index = (mouseY-2) / 16 + drawIndex;
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
        if(action != NULL){
            action->onAction(this,items.at(selected));
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
      glTexCoord2f((float)57/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)57/128, (float)70/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6,-y-16);
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6, -y-16);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+10, -y);

      // right side
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)71/128, (float)70/128); glVertex2i(x+16, -y-16);
      glTexCoord2f((float)71/128, (float)95/128); glVertex2i(x+16, -y);
    glEnd();
    glTranslatef(0,0,0.2f);
    if(upArrow){
        glBegin(GL_QUADS);
        glTexCoord2f((float)117/128, (float)63/128); glVertex2i(x+1, -y-1);
        glTexCoord2f((float)117/128, (float)50/128); glVertex2i(x+1, -y-17);
        glTexCoord2f((float)104/128, (float)50/128); glVertex2i(x+17,-y-17);
        glTexCoord2f((float)104/128, (float)63/128); glVertex2i(x+17, -y-1);
      glEnd();
    }
    else {
        glBegin(GL_QUADS);
          glTexCoord2f((float)104/128, (float)50/128); glVertex2i(x+1, -y-1);
          glTexCoord2f((float)104/128, (float)63/128); glVertex2i(x+1, -y-17);
          glTexCoord2f((float)117/128, (float)63/128); glVertex2i(x+17,-y-17);
          glTexCoord2f((float)117/128, (float)50/128); glVertex2i(x+17, -y-1);
        glEnd();
    }
  }
  else
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)41/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)41/128, (float)70/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6,-y-16);
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6, -y-16);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+10, -y);

      // right side
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)55/128, (float)70/128); glVertex2i(x+16, -y-16);
      glTexCoord2f((float)55/128, (float)95/128); glVertex2i(x+16, -y);
    glEnd();
    glTranslatef(0,0,0.2f);
    if(upArrow){
      glBegin(GL_QUADS);
        glTexCoord2f((float)117/128, (float)63/128); glVertex2i(x, -y);
        glTexCoord2f((float)117/128, (float)50/128); glVertex2i(x, -y-16);
        glTexCoord2f((float)104/128, (float)50/128); glVertex2i(x+16,-y-16);
        glTexCoord2f((float)104/128, (float)63/128); glVertex2i(x+16, -y);
      glEnd();
    } 
    else {
        glBegin(GL_QUADS);
          glTexCoord2f((float)104/128, (float)50/128); glVertex2i(x, -y);
          glTexCoord2f((float)104/128, (float)63/128); glVertex2i(x, -y-16);
          glTexCoord2f((float)117/128, (float)63/128); glVertex2i(x+16,-y-16);
          glTexCoord2f((float)117/128, (float)50/128); glVertex2i(x+16, -y);
        glEnd();
    }
  }
}

void ListBox::drawSelected(int x, int y,int width,string item){
    glTranslatef(0,0,0.02f);
	glColor3f(1,1,1);
    glBegin(GL_QUADS);
      // top left corner of panel.
      glTexCoord2f((float) 8/128, (float)64/128); glVertex2i(x, -y);
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2i(x, -y-10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);
      glTexCoord2f((float)18/128, (float)64/128); glVertex2i(x+10, -y);

      // top of panel.
      glTexCoord2f((float)18/128, (float)64/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+10+(width-20), -y-10);
      glTexCoord2f((float)30/128, (float)64/128); glVertex2i(x+10+(width-20), -y);

      // top right corder of panel.
      glTexCoord2f((float)30/128, (float)64/128); glVertex2i(x+width-10, -y);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+width-10, -y-10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2i(x+width, -y-10);
      glTexCoord2f((float)40/128, (float)64/128); glVertex2i(x+width, -y);

      // left side of panel.
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2i(x, -y-10);
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2i(x, -y-16+10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-16+10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);

      // right side of panel.
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+width-10, -y-10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+width-10, -y-16+10);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2i(x+width, -y-16+10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2i(x+width, -y-10);

      // bottom left corner of panel.
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2i(x, -y-16+10);
      glTexCoord2f((float) 8/128, (float)32/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-16+10);

      // bottom middle of panel.
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-16+10);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2i(x+10+(width-20), -y-16);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+10+(width-20), -y-16+10);

      // bottom right corner of panel.
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+width-10, -y-16+10);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2i(x+width-10, -y-16);
      glTexCoord2f((float)40/128, (float)32/128); glVertex2i(x+width, -y-16);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2i(x+width, -y-16+10);

    glEnd();
    
    fnt->writeText(x+4,-y-16,item);
    glBindTexture(GL_TEXTURE_2D,texIndex);
}

void ListBox::addItem(string item){
    items.push_back(item);
    if(items.size() == 1){
        selected = 0;
        if(this->action != NULL){
            action->onAction(this,item);
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
  action = NULL;
}

void CheckBox::setAction(SelectionClick* action){
    this->action = action;
}


/*------------------------------------------------------------------*
 *  Render a Checkbox                                               *
 *------------------------------------------------------------------*/
void CheckBox::Render()
{
  if(visible)
  {
    glColor3f(1,1,1);
    //glTranslatef(0, 0, 0.02); //FIXME:
    if (checked)
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)88/128, (float)96/128);		glVertex2i(x, -y);
        glTexCoord2f((float)88/128, (float)80/128);		glVertex2i(x, -y-16);
        glTexCoord2f((float)104/128, (float)80/128);	glVertex2i(x+16,-y-16);
        glTexCoord2f((float)104/128, (float)96/128);	glVertex2i(x+16, -y);
      glEnd();
    }
    else
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)72/128, (float)96/128); glVertex2i(x, -y);
        glTexCoord2f((float)72/128, (float)80/128); glVertex2i(x, -y-16);
        glTexCoord2f((float)88/128, (float)80/128); glVertex2i(x+16,-y-16);
        glTexCoord2f((float)88/128, (float)96/128); glVertex2i(x+16, -y);
      glEnd();
    }
  }
}

void CheckBox::onMouseDown(int mx, int my){
    checked = !checked;
    if(action != NULL)
        action->onAction(this,checked);
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
  action = NULL;
}

void RadioButton::setAction(SelectionClick* action){
    this->action = action;
}

/*------------------------------------------------------------------*
 *  Render Radio Button                                             *
 *------------------------------------------------------------------*/
void RadioButton::Render()
{
  if(visible)
  {
    glColor3f(1,1,1);
    if(checked)
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)88/128, (float)80/128);		glVertex2i(x, -y);
        glTexCoord2f((float)88/128, (float)64/128);		glVertex2i(x, -y-16);
        glTexCoord2f((float)104/128, (float)64/128);	glVertex2i(x+16,-y-16);
        glTexCoord2f((float)104/128, (float)80/128);	glVertex2i(x+16, -y);
      glEnd();
    }
    else
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)72/128, (float)80/128); glVertex2i(x, -y);
        glTexCoord2f((float)72/128, (float)64/128); glVertex2i(x, -y-16);
        glTexCoord2f((float)88/128, (float)64/128); glVertex2i(x+16,-y-16);
        glTexCoord2f((float)88/128, (float)80/128); glVertex2i(x+16, -y);
      glEnd();
    }
  }
}

void RadioButton::onMouseDown(int mx, int my){
    setChecked(true);
    if(action != NULL){
        action->onAction(this,true);
    }
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
  fnt = new Font("font");
}

Text::~Text(){
    delete fnt;
}

/*------------------------------------------------------------------*
 *  Render Radio Text                                               *
 *------------------------------------------------------------------*/
void Text::Render()
{
    if(visible){
        fnt->writeText(x, -y-16, caption);
        glBindTexture(GL_TEXTURE_2D,texIndex);
    }
}

string Text::getText(){
    return caption;
}

void Text::setText(const string& text){
    caption = text;
}

Font* Text::getFont(){
    return fnt;
}

Gui::~Gui(){
    glDeleteTextures(1,&texIndex);
    delete fnt;
    texIndex = 0;
}

Gui::Gui(const char* guiTextureFileName) : mVisible(true), num(0) {
      //glClearColor(0.0, 0.0, 0.0, 0.0); 	   // Black Background
      //glShadeModel(GL_SMOOTH);                 // Enables Smooth Color Shading
      glClearDepth(1.0);                       // Depth Buffer Setup
      glEnable(GL_DEPTH_TEST);                 // Enable Depth Buffer
      //glDepthFunc(GL_LESS);		           // The Type Of Depth Test To Do

      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   //Realy Nice perspective calculations

      //glEnable(GL_TEXTURE_2D);

    glGenTextures(1,&texIndex);
    glBindTexture(GL_TEXTURE_2D,texIndex);
    if(glfwLoadTexture2D(guiTextureFileName, GLFW_ORIGIN_UL_BIT)){
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }

    fnt = new Font("font");

    glfwGetWindowSize(&wndWidth,&wndHeight);
}

/*------------------------------------------------------------------*
 *  Procedure to render the GUI                                     *
 *------------------------------------------------------------------*/
void Gui::Render()
{
    if(mVisible){
      if(!processed){
          switch(click){
            case GLFW_PRESS:
                onMouseDown();
                break;
            case GLFW_RELEASE:
                for(unsigned i=0;i<windows.size();i++)
                    windows[i]->onMouseUp(mouseX,mouseY);
                break;
          }
          processed = true;
      }
      if(moved){
          for(unsigned i=0;i<windows.size();i++)
              windows[i]->onMouseMove(mouseX,mouseY);
          moved = false;
      }
    }

  glMatrixMode(GL_PROJECTION);  // Change Matrix Mode to Projection
  glLoadIdentity();             // Reset View
  glOrtho(0, wndWidth, 0, wndHeight, 0, 100);
  glMatrixMode(GL_MODELVIEW);   // Change Projection to Matrix Mode
  glLoadIdentity();
          
  glTranslatef(0, 0, -1);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texIndex);
  for(unsigned i=0;i<windows.size();i++)
          windows[i]->Render();

  if(mVisible){
      //draw the mouse
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_TEXTURE_2D);
      glColor4f(1,1,1,1);
      glBegin(GL_QUADS);
        glTexCoord2f((float)41/128, (float)64/128); glVertex3i(mouseX,    wndHeight - mouseY, 1);
        glTexCoord2f((float)72/128, (float)64/128); glVertex3i(mouseX+32, wndHeight - mouseY, 1);
        glTexCoord2f((float)72/128, (float)32/128); glVertex3i(mouseX+32, wndHeight - mouseY-32, 1);
        glTexCoord2f((float)41/128, (float)32/128); glVertex3i(mouseX,    wndHeight - mouseY-32, 1);
      glEnd();
      glDisable(GL_BLEND);
  }
}

Font* Gui::getFont(){
    return fnt;
}

/*------------------------------------------------------------------*
 *  Procedure to check if the user clicked in a window or object    *
 *------------------------------------------------------------------*/
void Gui::onMouseDown()
{
  // test to see if user clicked in a window
    if(!modals.empty()){
        Position winPos = modals.back()->getPosition();
        Size winSize = modals.back()->getSize();
        if ((mouseX > winPos.x) && (mouseX < winPos.x + winSize.width))
            if ((mouseY - 26 > winPos.y) && (mouseY - 26 < winPos.y + winSize.height))
                modals.back()->onMouseDown(mouseX, mouseY);
        return;
    }
  for(unsigned i=0;i<windows.size();i++){
      if(windows[i]->isVisible()){
          Position winPos = windows[i]->getPosition();
          Size winSize = windows[i]->getSize();
          if ((mouseX > winPos.x) && (mouseX < winPos.x + winSize.width))
              if ((mouseY - 26 > winPos.y) && (mouseY - 26 < winPos.y + winSize.height)){
                  windows[i]->onMouseDown(mouseX, mouseY);
                  break;
              }
      }
  }
}

int Gui::mouseX = 0;
int Gui::mouseY = 0;
int Gui::wndWidth = 0;
int Gui::wndHeight = 0;
int Gui::click = GLFW_RELEASE;
bool Gui::processed = true;
bool Gui::sizeRefreshed = false;
bool Gui::moved = false;

void Gui::setMouseVisible(bool visible){
    mVisible = visible;
}

void Gui::onMouseMove(int x, int y){
  mouseX = x > 0 ? x : 0;
  if(x > wndWidth)
      mouseX = wndWidth;
  mouseY = y > 0 ? y : 0;
  if(y>wndHeight)
      mouseY = wndHeight;
  moved = true;
}

void Gui::onMouseClick(int button, int action){
    click = action;
    processed = false;
}

/*{------------------------------------------------------------------}
{  Handle window resize                                            }
{------------------------------------------------------------------}*/
void Gui::glResizeWnd(int Width, int Height){
  if (Height == 0)               // prevent divide by zero exception
    Height = 1;
  glViewport(0, 0, Width, Height);    // Set the viewport for the OpenGL window
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
  gluPerspective(45.0, Width/Height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth
  wndWidth = Width;
  wndHeight = Height;
  sizeRefreshed = true;
  
  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View                  // Reset View
}

GLuint Gui::getSkin(){
    return texIndex;
}

unsigned Gui::showMessage(string title, string msg){
    int width = (int)fnt->stringWidth(msg)+50;
    Window* dlg = new Window(wndWidth/2-width/2,wndHeight/2-64,width,100,title);
    dlg->AddComponent(new Text(25,35,msg));
    Button* btn = new Button(width/2-25,60,50,25,"OK");
    btn->setAction(this);
    dlg->AddComponent(btn);
    dlg->setSkin(texIndex);
    windows.push_back(dlg);
    //FIX: this...
    modals.push_back(dlg);
    if(!++num)  //ok, it could be if(num+1 == 0) num += 2 else ++num;
        ++num;
    msgHandle* hnd = new msgHandle;
    hnd->id = num;
    hnd->ptr = dlg;
    msgnum.push_back(hnd);
    return num;
}

void Gui::onAction(Component* button){
    Container* wnd = button->getParent();
    wnd->setVisible(false);
    for(unsigned i=0;i<modals.size();i++)
        if(modals[i] == wnd)
            modals.erase (modals.begin()+i);
    for(unsigned i=0;i<windows.size();i++)
        if(windows[i] == wnd){
            delete windows[i];
            windows.erase (windows.begin()+i);
        }
    for(unsigned i=0;i<msgnum.size();i++)
        if(msgnum[i]->ptr == wnd){
            delete msgnum[i];
            msgnum.erase(msgnum.begin()+i);
        }
}

bool Gui::isMessageActive(unsigned id){
    for(unsigned i=0;i<msgnum.size();i++){
        if(msgnum[i]->id == id)
            return true;
    }
    return false;
}

void Gui::addWindow(Window* win){
    windows.push_back(win);
    win->setSkin(texIndex);
}
    

