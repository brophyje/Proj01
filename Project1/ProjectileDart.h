/**
 * \file ProjectileDart.h
 *
 * \author Nicholas Aaltonen
 *
 * Derived dart class from CProjectile.
 */

#pragma once
#include "Projectile.h"

 /**
  * Class for dart projectiles.
  */
class CProjectileDart :
    public CProjectile
{
public:
    
    /// Amount of points for this projectile
    const static int Points = 10;

    CProjectileDart(CGame* game, const double x, const double y, 
        double angle, double speedX, double speedY);

    ///  Copy constructor (disabled)
    CProjectileDart(const CProjectileDart&) = delete;

    /// Add to score on destruction
    virtual ~CProjectileDart();

    virtual void Update(double elapsed);

    /** Accept function for item visitors, overrides CItem's accept
    * \param visitor pointer to visitor being accepted */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitProjectileDart(this); }

private:

    int mXStart; ///< The starting X location of our dart
    int mYStart; ///< The starting Y location of our dart

};

