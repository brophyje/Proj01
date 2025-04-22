/**
 * \file TowerWave.h
 *
 * \author Nicholas Aaltonen
 *
 * Derived class for Wave tower.
 */

#pragma once
#include "Tower.h"

 /**
  * Derived Tower class for Wave Tower.
  */
class CTowerWave :
    public CTower
{
public:

	/// Points for popping a balloon w/ this tower
	const static int Points = 3;

	/// Time in seconds between shots for this tower
	const static int TimeBetweenShots = 5;

	CTowerWave() = delete;
	CTowerWave(const CTowerWave&) = delete;
	virtual ~CTowerWave();

	CTowerWave(CGame* game, int x, int y);

	/** Makes the wave tower shoot a wave, overrides CItem's function
	* \param graphics pointer to graphics being drawn on */
	virtual void Draw(Gdiplus::Graphics* graphics) override;

	virtual void Update(double elapsed) override;

	/** Accept function for item visitors, overrides CItem's accept
	* \param visitor pointer to visitor being accepted
	*/
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerWave(this); }

private:

	double mTimeTillFire; ///< Time until this tower should fire
	bool mFiring = false; ///< Determines whether tower is in firing state
	int mDiameter = 20; ///< The current diameter of our ring
	int mSpeed = 200; ///< The speed our ring grows
};

