/**
 * \file Tower8Shot.h
 *
 * \author Connor Mears
 *
 * Derived Tower class for 8-Shot.
 */

#pragma once

#include "Tower.h"
#include "Projectile.h"
#include "ProjectileDart.h"
#include <vector>


/**
 * Derived Tower class for 8-Shot.
 */
class CTower8Shot : public CTower
{
public:

	/// Time in seconds between shots for this tower
	const static int TimeBetweenShots = 5;

	CTower8Shot() = delete;
	CTower8Shot(const CTower8Shot&) = delete;
	virtual ~CTower8Shot();

	CTower8Shot(CGame* game, int x, int y);

	/** Makes the 8shot shoot it's projectile(s), overrides CTower's function */
	virtual void Shoot() override;

	virtual void Update(double elapsed) override;

	/** Accept function for item visitors, overrides CItem's accept
	* \param visitor pointer to visitor being accepted */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTower8Shot(this); }

private:

	double mTimeTillFire = TimeBetweenShots; ///< Time until this tower should fire

};

