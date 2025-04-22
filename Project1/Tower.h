/**
 * \file Tower.h
 *
 * \author Zachary Morris
 *
 * Base class for Tower item
 */

#pragma once

#include <memory>
#include <string>
#include "Tile.h"
#include "Item.h"


/**
 * Base class for Tower item
 */
class CTower : public CItem
{
public:

	/// How much we offset drawing the tile to the left of the center
	const static int OffsetLeft = 32;

	/// How much we offset drawing the tile above the center
	const static int OffsetDown = 32;

	CTower() = delete;
	CTower(const CTower&) = delete;
	virtual ~CTower();

	void Add(int dX, int dY);



	/**  Get the tile the tower is on
	* \returns Tile the tower is on 
	*/
	std::shared_ptr<CTile> GetTile() { return mTile; }

	/**  Set the tile the tower is on
	* \param tile Tile tower is on 
	*/
	void SetTile(std::shared_ptr<CTile> tile) { mTile = tile; }


	/**  Handle updates for animation
	* \param elapsed The time since the last update
	*/
	virtual void Update(double elapsed) = 0;

	/// Makes the tower shoot it's projectile(s)
	virtual void Shoot() {};

protected:

	/** Constructor
	* \param game pointer to game tower is in
	* \param x X location
	* \param y Y location */
	CTower(CGame* game, int x, int y) : CItem(game, x, y) {};

private:
	/// The tile that this tower is on
	std::shared_ptr<CTile> mTile = nullptr;
};

