/**
 * \file Explosive.h
 *
 * \author Zach Morris
 *
 * Derived class for Bomb from Explosions base class
 */

#pragma once
#include "AreaEffect.h"

 /**
  * Derived class for Bomb from Explosions base class
  */
class CExplosive : public CAreaEffect
{
public:
	/// Constructor
	CExplosive(const double x, const double y, const double time, const double radius);

	/// Disabling default constructor
	CExplosive() = delete;

	void Draw(Gdiplus::Graphics* graphics);

	void Explode(Gdiplus::Graphics* graphics);

private:
	/// The time it takes to complete the full explosion
	double mTime;

	/// The full radius 
	double mRadius;

	/// Start explosive time
	double mStartTime = 0;
};

