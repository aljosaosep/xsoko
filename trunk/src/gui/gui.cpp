#include "gui.h"

PGuiSession* guiSession;

void SetGuiSession(PGuiSession* session){
    guiSession = session;
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
