/**
 * \file TowerSniper.h
 *
 * \author Jered Brophy
 *
 * Derived Tower class for Sniper.
 */


#pragma once

#include "Tower.h"
#include "Projectile.h"
#include "ProjectileSniper.h"
#include <vector>


/**
 * Derived Tower class for Sniper.
 */
class CTowerSniper : public CTower
{
public:

	/// Time in seconds between shots for this tower
	const static int TimeBetweenShots = 7;

	/// Time in seconds between shots for this tower
	const static int OverallSpeed = 1000;

	CTowerSniper() = delete;
	CTowerSniper(const CTowerSniper&) = delete;
	virtual ~CTowerSniper();

	CTowerSniper(CGame* game, int x, int y);

	/// Makes the sniper shoot it's projectile(s), overrides CTower's function
	virtual void Shoot() override;

	virtual void Update(double elapsed) override;

	virtual void Draw(Gdiplus::Graphics* graphics) override;

	/** Accept function for item visitors, overrides CItem's accept
	* \param visitor pointer to visitor being accepted */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerSniper(this); }

private:

	double mTimeTillFire = TimeBetweenShots; ///< Time until this tower should fire

	double mAngle = 0; ///< Rotation of tower in radians (default 0)

};

