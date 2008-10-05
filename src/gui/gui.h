/* 
 * File:   gui.h
 * Author: jernej
 *
 * Created on Ponedeljek, 29 september 2008, 15:30
 */

#ifndef _GUI_H
#define	_GUI_H

#include "win.h"
#include "../session.h"

using namespace PacGame::GameClasses;

  extern void SetGuiSession(PGuiSession* session);
  extern void closeAction();
  extern void runAction();

#endif	/* _GUI_H */

