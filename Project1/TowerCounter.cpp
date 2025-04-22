/**
 * \file TowerCounter.cpp
 *
 * \author Connor Mears
 */

#include "pch.h"
#include "TowerCounter.h"


void CTowerCounter::VisitTower8Shot(CTower8Shot* tower)
{
	mTowers.push_back(tower);
}

void CTowerCounter::VisitTowerBomb(CTowerBomb* tower)
{
	mTowers.push_back(tower);
}

void CTowerCounter::VisitTowerSniper(CTowerSniper* tower)
{
	mTowers.push_back(tower);
}

void CTowerCounter::VisitTowerWave(CTowerWave* tower)
{
	mTowers.push_back(tower);
}
