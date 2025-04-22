/**
 * \file Projectile.h
 *
 * \author Connor Mears
 *
 * Base Projectile class.
 * Derived classes: CDart, CSniper
 */


#pragma once
#include <string>
#include <memory>
#include "Item.h"

/**
 * Base Projectile class.
 */
class CProjectile : public CItem
{
public:

    ///  Copy constructor (disabled)
    CProjectile(const CProjectile&) = delete;

    /// Add to score on destruction
    virtual ~CProjectile();

    /**  The angle of the projectile
    * \returns rotation angle in degrees */
    double GetAngle() { return mAngle; }

    /**  The points of the projectile
    * \returns Number of points for projectile */
    int GetPoints() { return mPoints; }

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    virtual void Update(double elapsed) = 0;

protected:

    CProjectile(CGame* game, int points, const double x, const double y, 
        double angle, double speedX, double speedY);

private:

    double mAngle; ///< Rotation of projectile in radians

    double mSpeedX; ///< Projectile speed in the X direction
    double mSpeedY; ///< Projectile speed in the Y direction

    int mPoints; ///< How much points the projectile is worth

};

