/**
 * \file ProjectileCounter.h
 *
 * \author Connor Mears
 *
 * Derived visitor to count number of projectiles
 */


#pragma once
#include "ItemVisitor.h"
#include "Projectile.h"
#include "ProjectileDart.h"
#include "ProjectileSniper.h"
#include <vector>


/**
 * Derived visitor to count number of projectiles
 */
class CProjectileCounter : public CItemVisitor
{
public:

	virtual void VisitProjectileDart(CProjectileDart* projectile) override;

	virtual void VisitProjectileSniper(CProjectileSniper* projectile) override;

	/** Gets the number of projectiles
	* \returns Number of projectiles */
	int GetNumProjectiles() const { return mNumProjectiles; }

	/** Gets the last projectile found
	* \returns Last checked projectile */
	CProjectile* GetProjectile() { return mProjectile; }

	/** Gets the projectiles in the game
	* \returns List of projectiles */
	std::vector<CProjectile*> GetProjectiles() { return mProjectiles; }

private:
	/// Projectiles counter
	int mNumProjectiles = 0;

	/// Projectile checked
	CProjectile* mProjectile;

	/// Collection of all projectiles in game
	std::vector<CProjectile*> mProjectiles;
};

