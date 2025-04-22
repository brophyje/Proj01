/**
 * \file AreaEffect.cpp
 *
 * \author Nicholas Aaltonen
 */

#include "pch.h"
#include "AreaEffect.h"

using namespace std;
using namespace Gdiplus;


/** Constructor
* \param x X position
* \param y Y position
*/
CAreaEffect::CAreaEffect(const double x, const double y)
{
    mX = x;
    mY = y;
}

/**
*  Destructor
*/
CAreaEffect::~CAreaEffect()
{
}
