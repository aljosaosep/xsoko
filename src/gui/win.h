/* 
 * File:   win.h
 * Author: jernej
 * Based on delphi tutorial glWindows by Jan Horn
 *
 * Created on Nedelja, 28 september 2008, 10:49
 */

#ifndef _WIN_H
#define	_WIN_H

#include <string>
#include <vector>
#include <GL/glfw.h>
#include "fonts.h"

using namespace std;

struct Position{
    int x,y;
};

struct Size{
    int width, height;
};

class Container;

class Component {
protected:
    int x, y;
    int width, height;
    bool visible;
    Container* parent;
    string name;
    GLuint texIndex;
public:
    Component(int x, int y, int width, int height);
    virtual ~Component() {};
    Position getPosition();
    Size getSize();
    bool isVisible();
    Container* getParent();
    void setPosition(int x, int y);
    void setSize(int width, int height);
    virtual void setVisible(bool visible);
    void setParent(Container* parent);
    void setName(const string& name);
    void setSkin(GLuint texIndex);
    string getName();
    virtual void Render() = 0;
    virtual void onMouseDown(int mx, int my) {};
    virtual void onMouseUp() {};
};

class Container{
protected:
    int x, y;
    int width, height;
    bool visible;
    Container* parent;
    vector<Component*> components;
    vector<Container*> containers;
    bool isInArea(Position p, Size s, int x, int y);
    Component* compPressed;
    GLuint texIndex;
public:
    Container(int x, int y, int width, int height);
    void AddComponent(Component* component);
    void AddContainer(Container* container);
    ~Container();
    Position getPosition();
    Size getSize();
    bool isVisible();
    Container* getParent();
    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setVisible(bool visible);
    void setParent(Container* parent);
    void setSkin(GLuint texIndex);
    virtual void Render() = 0;
    void onMouseDown(int mx, int my);
    virtual void onMouseUp(int mx, int my);
    //virtual void onMouseMove(int mx, int my) {};
};

class ButtonClick{
public:
    virtual void onAction(Component* button) = 0;
};

class ListBoxClick{
public:
    virtual void onAction(Component* listBox, string selected) = 0;
};

class SelectionClick{
public:
    virtual void onAction(Component* c, bool selected) = 0;
};

class Button : public Component{
private:
    bool pressed;
    string caption;
    ButtonClick* action;
    Font* fnt;
public:
    Button(int x, int y, int width, int height, string caption);
    ~Button();
    string getCaption();
    Font* getFont();
    void setCaption(const string& caption);
    void setAction(ButtonClick* action);
    void Render();
    void onMouseDown(int mx, int my);
    void onMouseUp();
};

class Text : public Component{
private:
    string caption;
    Font* fnt;
public:
    Text(int x,int y,string text);
    ~Text();
    string getText();
    void setText(const string& text);
    void Render();
    Font* getFont();
};

class Panel: public Container{
public:
    Panel(int x, int y, int width, int height);
    void Render();
};

class ListBox: public Component{
private:
    vector<string> items;
    int selected;
    int drawIndex;
    unsigned canShow;
    bool upPressed;
    bool downPressed;
    void drawSelected(int x, int y,int width,string item);
    void drawButton(int x, int y,bool pressed,bool upArrow);
    ListBoxClick* action;
    Font* fnt;
public:
    ListBox(int x, int y, int width, int height);
    ~ListBox();
    void addItem(string item);
    string getSelectedItem();
    Font* getFont();
    void setAction(ListBoxClick* action);
    void Render();
    void onMouseDown(int mx, int my);
    void onMouseUp();
};

class CheckBox: public Component{
private:
    bool checked;
    SelectionClick* action;
public:
    CheckBox(int x, int y, bool checked);
    bool isChecked();
    void setChecked(bool checked);
    void setAction(SelectionClick* action);
    void Render();
    void onMouseDown(int mx, int my);
};

class RadioButton;

class RadioButtonGroup {
private:
    vector<RadioButton*> radioButtons;
public:
    void addToGroup(RadioButton* radioButton);
    void removeFromGroup(RadioButton* radioButton);
    vector<RadioButton*>* getRadioButtons();
};

class RadioButton : public Component{
private:
    RadioButtonGroup* group;
    bool checked;
    SelectionClick* action;
public:
    RadioButton(int x, int y,RadioButtonGroup* group,bool checked);
    RadioButtonGroup* getRadioButtonGroup();
    bool isChecked();
    void setChecked(bool checked);
    void setRadioButtonGroup(RadioButtonGroup* group);
    void setAction(SelectionClick* action);
    void Render();
    void onMouseDown(int mx, int my);
};

struct MouseDrag{
    bool drag;     // window draggin enabled
    int x,y;   // X and Y coords when drag started
};

class Window : public Container{
private:
    float alpha;
    float zorder;
    int screenHeight;
    MouseDrag mouseDrag;
    bool enableCloseButton;
    bool modal;
    string caption;
    Font* fnt;
public:
    Window(int wX, int wY, int wWidth, int wHeight, string caption);
    ~Window();
    float getAlpha();
    float getZOrder();
    void setZOrder(float zorder);
    void setAlpha(float alpha);
    void setEnableCloseButton(bool enabled);
    void setModal(bool modal);
    void setVisible(bool visible);
    void Render();
    void onMouseDown(int mx, int my);
    void onMouseMove(int mx, int my);
    void onMouseUp(int mx, int my);
    void onScreenResize();
    Font* getFont();
};

struct msgHandle {
    unsigned id;
    Window* ptr;
};

class Gui : public ButtonClick{
private:
    static int mouseX, mouseY;
    static int wndWidth, wndHeight;
    static int click;
    static bool processed;
    static bool sizeRefreshed;
    static bool moved;
    
    vector<Window*> windows;
    vector<Window*> modals;

    void onMouseDown();
    GLuint texIndex;
    bool mVisible;
    Font* fnt;
    //unordered_map<int,Window*> msgnum;
    vector<msgHandle*> msgnum;
    unsigned num;
public:
    static void onMouseClick(int button, int action);
    static void onMouseMove(int x, int y);
    static void glResizeWnd(int Width, int Height);
    
    Gui(const char* guiTextureFileName);
    ~Gui();
    void Render();
    void setMouseVisible(bool visible);
    GLuint getSkin();
    void addWindow(Window* win);
    unsigned showMessage(string title, string msg);
    bool isMessageActive(unsigned id);
    void onAction(Component* button);
    //void addModal(Window* win);
    Font* getFont();
};

#endif	/* _WIN_H */

