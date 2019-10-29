//
//  Rect.cpp
//  Gamerize
//
//  Created by Ho Thi Trang on 11/1/12.
//  Copyright (c) 2012 Ho Thi Trang. All rights reserved.
//

#include "Rect.h"
#include <math.h>

namespace gamerize
{
 
    Rect::Rect()
    {
        
    }
    
    Rect::Rect(const Vector2 &position, const Vector2 &size)
    {
        this->position = position;
        this->size = size;
    }
    
    Rect::Rect(float x, float y, float w, float h)
    {
        position.Set(x, y);
        size.Set(w, h);
    }
    
    bool Rect::Contains(const Vector2 &point) const
    {
        return (fabsf(point.x - position.x) <= size.x * 0.5f &&
                fabsf(point.y - position.y) <= size.y * 0.5f);
    }
}