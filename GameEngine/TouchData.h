//
//  TouchData.h
//  Gamerize
//
//  Created by Ho Thi Trang on 11/1/12.
//  Copyright (c) 2012 Ho Thi Trang. All rights reserved.
//

#ifndef Gamerize_TouchData_h
#define Gamerize_TouchData_h


#include "Geometry.h"

namespace gamerize
{
  // The touch state
	enum TouchState { TOUCH_DOWN, TOUCH_UP, TOUCH_MOVE, TOUCH_HANDLED };

  // The touch data
  struct TouchData {
    unsigned int touchId;
    Vector2 position;
    Vector2 originalPoint;
    TouchState state;
  };
};
#endif
