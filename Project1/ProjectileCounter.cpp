/**
 * \file ProjectileCounter.cpp
 *
 * \author Connor Mears
 */

#include "pch.h"
#include "ProjectileCounter.h"

 /** Visit a CProjectileDart object
 * \param projectile Projectile we are visiting
 */
void CProjectileCounter::VisitProjectileDart(CProjectileDart* projectile)
{
	mNumProjectiles++;
	mProjectile = projectile;
	mProjectiles.push_back(projectile);
}

/** Visit a CProjectileSniper object
* \param projectile Projectile we are visiting
*/
void CProjectileCounter::VisitProjectileSniper(CProjectileSniper* projectile)
{
	mNumProjectiles++;
	mProjectile = projectile;
	mProjectiles.push_back(projectile);
}
