//
//  Header.h
//  game_launcher
//
//  Created by Andy Wallace on 7/25/15.
//
//

#ifndef game_launcher_Header_h
#define game_launcher_Header_h

#include "SystemSpecificInfo.h"

//gamepad stuff

enum BUTTON_TYPE { BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, BUTTON_START, BUTTON_SELECT, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_UP, BUTTON_DOWN, BUTTON_L1, BUTTON_L2, BUTTON_R1, BUTTON_R2, NUM_BUTTONS};

enum GAME_STATE { STATE_HOME, STATE_OPTIONS };

#define MIN_TIME_BEFORE_CANCEL 0.3


#endif
