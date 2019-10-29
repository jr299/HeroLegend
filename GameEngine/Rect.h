//
//  Rect.h
//  Gamerize
//
//  Created by Ho Thi Trang on 11/1/12.
//  Copyright (c) 2012 Ho Thi Trang. All rights reserved.
//

#ifndef __Gamerize__Rect__
#define __Gamerize__Rect__

#include "Geometry.h"

namespace gamerize
{
    
    class Rect
    {
    public:
        Rect();
        Rect(const Vector2 &position, const Vector2 &size);
        Rect(float x, float y, float w, float h);
        
        bool Contains(const Vector2 &point) const;
        Vector2 position;
        Vector2 size;
    };
}

#endif /* defined(__Gamerize__Rect__) */
