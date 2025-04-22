/**
 * \file BalloonCounter.cpp
 *
 * \author Zach Morris
 */

#include "pch.h"
#include "BalloonCounter.h"

/** Visit a CBalloon object
* \param balloon Balloon we are visiting
*/
void CBalloonCounter::VisitBalloon(CBalloon* balloon)
{
	mNumBalloons++;
	mBalloon = balloon;
	mBalloons.push_back(balloon);
}
