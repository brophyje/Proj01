/**
 * \file AreaEffect.h
 *
 * \author Nicholas Aaltonen
 *
 * Base class for our explosions
 */

#pragma once

 /**
  * Base class for all of our various explosions.
  */
class CAreaEffect
{
public:
    /// Add to score on destruction
    virtual ~CAreaEffect();

    /**  The X location of the center of the tile
    * \returns X location in pixels */
    double GetX() const { return mX; }

    /**  The Y location of the center of the tile
    * \returns Y location in pixels */
    double GetY() const { return mY; }

protected:

    CAreaEffect(const double x, const double y);

private:

    // Starting explosion location on screen
    double   mX;  ///< X location for the center of the projectile
    double   mY;  ///< Y location for the center of the projectile
};

