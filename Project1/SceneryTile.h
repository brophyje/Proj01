/**
 * \file SceneryTile.h
 *
 * \author Nicholas Aaltonen
 *
 *  Class that implements a scenery tile in our grid
 */

#pragma once
#include "Tile.h"
#include "ItemVisitor.h"

 /**
  *  A scenery tile
  */
class CSceneryTile :
    public CTile
{
public:
    CSceneryTile(CGrid* grid);

    ///  Default constructor (disabled)
    CSceneryTile() = delete;

    ///  Copy constructor (disabled)
    CSceneryTile(const CSceneryTile&) = delete;

    ~CSceneryTile();

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Accept function for item visitors, overrides CItem's accept
    * \param visitor pointer to visitor being accepted */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitSceneryTile(this); }
};

