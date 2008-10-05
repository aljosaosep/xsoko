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
