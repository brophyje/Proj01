/**
 * \file ProjectileSniper.h
 *
 * \author Jacob Theobald
 *
 * Derived sniper bullet class from CProjectile.
 */


#pragma once
#include "Projectile.h"

/**
 * Class for projectiles from sniper towers.
 */
class CProjectileSniper : public CProjectile
{
public:
    /// Amount of points for this projectile
    const static int Points = 15;

    CProjectileSniper(CGame* game, const double x, const double y, 
        double angle, double speedX, double speedY);

    ///  Copy constructor (disabled)
    CProjectileSniper(const CProjectileSniper&) = delete;

    /// Add to score on destruction
    virtual ~CProjectileSniper();

    virtual void Update(double elapsed);

    /** Accept function for item visitors, overrides CItem's accept
    * \param visitor pointer to visitor being accepted */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitProjectileSniper(this); }
};

