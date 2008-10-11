#include "gui.h"
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

PGuiSession* guiSession;
PGameSession* gameSession;
string selectedLevel = "";

void SetGuiSession(PGuiSession* session){
    guiSession = session;
}

void SetGameSession(PGameSession* session){
    gameSession = session;
}


/*------------------------------------------------------------------*
 *  Custom button functions                                         *
 *------------------------------------------------------------------*/
void closeAction()
{
    if(guiSession != NULL)
        guiSession->Quit();
}

void runAction(){
    if(guiSession != NULL)
        guiSession->LoadLevel("data/testlevel.lvl");
}

void fpShow(){
    if(guiSession != NULL)
        guiSession->getMainWindow()->getChildWindows()->at(0)->setVisible(true);
}

void fpClose(){
    if(guiSession != NULL)
        guiSession->getMainWindow()->getChildWindows()->at(0)->setVisible(false);
}

void fpListBoxSelect(string selected){
    selectedLevel = selected;
}
void fpPlay(){
    if(guiSession != NULL && selectedLevel != ""){
        guiSession->LoadLevel("data/"+selectedLevel+".lvl");
    }
}

// main menu

Window* createMainMenu(){
    Window* mainWin = new Window(253, 158, 135, 165);
    Button* btn = new Button(30, 40, 75, 25, "Campaing");
    btn->onClick = &runAction;
    mainWin->AddComponent(btn);

    btn = new Button(30, 75, 75, 25, "Freeplay");
    btn->onClick = &fpShow;
    mainWin->AddComponent(btn);

    btn = new Button(30, 110, 75, 25, "Exit");
    btn->onClick = &closeAction;
    mainWin->AddComponent(btn);

    Window* fpWin = new Window(210, 158, 220, 141);
    fpWin->setVisible(false);

    ListBox* list = new ListBox(10,40,115,68);
    list->onClick = &fpListBoxSelect;

    path dir_path("data");
    directory_iterator end_itr; // default construction yields past-the-end
    for (directory_iterator itr(dir_path);itr != end_itr; ++itr )
    {
      if ( !is_directory(itr->status()) && extension(itr->path()) == ".lvl" )
      {
          string filename = itr->leaf();
          list->addItem(filename.substr(0,filename.find_last_of('.')));
      }
    }

    fpWin->AddComponent(list);
    btn = new Button(135,40,75,25,"Play");
    btn->onClick = &fpPlay;
    fpWin->AddComponent(btn);
    btn = new Button(135,70,75,25,"Back");
    btn->onClick = &fpClose;
    fpWin->AddComponent(btn);

    mainWin->AddChildWindow(fpWin);
    return mainWin;
}

void gmExit(){
    if(gameSession != NULL)
        gameSession->Quit();
}

void gmReset(){
    if(gameSession != NULL)
        gameSession->resetLevel();
}

Window* createGameMenu(){
    Window* mainWin = new Window(253, 158, 135, 165);
    
    Button* btn = new Button(30, 40, 75, 25, "Save");
    //btn->onClick = &runAction;
    mainWin->AddComponent(btn);

    btn = new Button(30, 75, 75, 25, "Reset");
    btn->onClick = &gmReset;
    mainWin->AddComponent(btn);

    btn = new Button(30, 110, 75, 25, "Exit");
    btn->onClick = &gmExit;
    mainWin->AddComponent(btn);

    return mainWin;
}
