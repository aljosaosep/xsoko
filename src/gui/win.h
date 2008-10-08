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

using namespace std;

struct Position{
    int x,y;
};

struct Size{
    int width, height;
};

class Component {
protected:
    int x, y;
    int width, height;
    bool visible;
    Component* parent;
public:
    Component(int x, int y, int width, int height);
    Position getPosition();
    Size getSize();
    bool isVisible();
    Component* getParent();
    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setVisible(bool visible);
    void setParent(Component* parent);
    virtual void Render() = 0;
    virtual void onMouseDown() {};
    virtual void onMouseUp() {};
};

class Container : public Component{
protected:
    vector<Component*> components;
public:
    Container(int x, int y, int width, int height);
    void AddComponent(Component* component);
    void onMouseDown();
};

class Button : public Component{
private:
    bool pressed;
    string caption;
public:
    void (*onClick)();
    Button(int x, int y, int width, int height, string caption);
    string getCaption();
    void setCaption(const string& caption);
    void Render();
    void onMouseDown();
    void onMouseUp();
};

class Text : public Component{
private:
    string caption;
public:
    Text(int x,int y,string text);
    string getText();
    void setText(const string& text);
    void Render();
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
    int canShow;
    bool upPressed;
    bool downPressed;
    void drawSelected(int x, int y,int width,string item);
    void drawButton(int x, int y,bool pressed,bool upArrow);
public:
    void (*onClick)(string selectedItem);
    ListBox(int x, int y, int width, int height);
    void addItem(string item);
    string getSelectedItem();
    void Render();
    void onMouseDown();
    void onMouseUp();
};

class CheckBox: public Component{
private:
    bool checked;
public:
    void (*onClick)(bool checked);
    CheckBox(int x, int y, bool checked);
    bool isChecked();
    void setChecked(bool checked);
    void Render();
    void onMouseDown();
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
public:
    void (*onClick)(bool checked);
    RadioButton(int x, int y,RadioButtonGroup* group,bool checked);
    RadioButtonGroup* getRadioButtonGroup();
    bool isChecked();
    void setChecked(bool checked);
    void setRadioButtonGroup(RadioButtonGroup* group);
    void Render();
    void onMouseDown();
};

class Window : public Container{
private:
    float alpha;
    float zorder;
    vector<Window*> childwindows;
public:
    Window(int wX, int wY, int wWidth, int wHeight);
    void AddChildWindow(Window* child);
    float getAlpha();
    float getZOrder();
    vector<Window*>* getChildWindows();
    void setZOrder(float zorder);
    void setAlpha(float alpha);
    void Render();
    void onMouseDown();
};

extern  bool InitGUI(const char* guiTextureFileName,const char* fontTextureFileName);
extern  void RenderGUI();
extern  void DestroyGUI();
extern  void onMouseClick(int button, int action);
extern  void onMouseMove(int x, int y);
extern  void glResizeWnd(int Width, int Height);
extern  void setMainWindow(Window* mWin);

#endif	/* _WIN_H */

