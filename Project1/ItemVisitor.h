/**
 * \file ItemVisitor.h
 *
 * \author Zachary Morris
 *
 * Item visitor base class visits towers, balloons, and projectiles
 */

#pragma once

 //Forward references to all item types
class CBalloon;
class CProjectile;
class CProjectileDart;
class CProjectileSniper;
class CTower;
class CTower8Shot;
class CTowerBomb;
class CTowerSniper;
class CTowerWave;
class CGrid;
class CTile;
class CRoadTile;
class CSceneryTile;
class CGrassTile;


/**
 * Item visitor base class visits towers, balloons, and projectiles
 */
class CItemVisitor
{
public:
	virtual ~CItemVisitor() {}

	/** Visit a CTower object
	\param tower Tower we are visiting */
	virtual void VisitTower(CTower* tower) {}

	/** Visit a CTower8Shot object
	\param tower Tower we are visiting */
	virtual void VisitTower8Shot(CTower8Shot* tower) {}

	/** Visit a CTowerBomb object
	\param tower Tower we are visiting */
	virtual void VisitTowerBomb(CTowerBomb* tower) {}

	/** Visit a CTowerSniper object
	\param tower Tower we are visiting */
	virtual void VisitTowerSniper(CTowerSniper* tower) {}

	/** Visit a CTowerWave object
	\param tower Tower we are visiting */
	virtual void VisitTowerWave(CTowerWave* tower) {}

	/** Visit a CBalloon object
	\param balloon Balloon we are visiting */
	virtual void VisitBalloon(CBalloon* balloon) {}

	/** Visit a CProjectileDart object
	\param projectile Projectile we are visiting */
	virtual void VisitProjectileDart(CProjectileDart* projectile) {}

	/** Visit a CProjectileSniper object
	\param projectile Projectile we are visiting */
	virtual void VisitProjectileSniper(CProjectileSniper* projectile) {}

	/** Visit a CRoadTile object
	\param tile Tile we are visiting */
	virtual void VisitRoadTile(CRoadTile* tile) {}

	/** Visit a CGrassTile object
	\param tile Tile we are visiting */
	virtual void VisitGrassTile(CGrassTile* tile) {}

	/** Visit a CSceneryTile object
	\param tile Tile we are visiting */
	virtual void VisitSceneryTile(CSceneryTile* tile) {}
};