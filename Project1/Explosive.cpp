#include "pch.h"
#include "Explosive.h"

/** The constructor
* \param x The x location
* \param y The y location
* \param time How long it takes to complete the full explosion
* \param radius How big the radius is
*/
CExplosive::CExplosive(const double x, const double y, const double time, const double radius)
	: CAreaEffect(x, y)
{
	mTime = time;
	mRadius = radius;
}

/** The draw function
* \param graphics The Graphics the function is drawn on
*/
void CExplosive::Draw(Gdiplus::Graphics* graphics)
{
	Gdiplus::Pen pen(Gdiplus::Color().Red, Gdiplus::REAL());
	graphics->DrawEllipse(&pen, int(GetX()), int(GetY()), int(mRadius), int(mRadius));
}

/**
* The function that will check for ballons and destroy them
* \param graphics pointer to graphics being drawn on
*/
void CExplosive::Explode(Gdiplus::Graphics* graphics)
{
	Draw(graphics);
}
