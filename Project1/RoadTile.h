/**
 * \file RoadTile.h
 *
 * \author Jered Brophy
 *
 *
 */

#pragma once

#include <string>
#include "Tile.h"
#include "Balloon.h"


 /**
  *  A road tile
  */
class CRoadTile :
    public CTile
{
public:
    CRoadTile(CGrid* grid);

    ///  Default constructor (disabled)
    CRoadTile() = delete;

    ///  Copy constructor (disabled)
    CRoadTile(const CRoadTile&) = delete;

    /// Destructor
    ~CRoadTile();

    /** Getter for Road Type
    * \return Type of RoadTile */
    std::wstring GetType() { return mType; }

    /** Setter for Next Road for Balloons to travel to
    * \param tile Next Road Tile */
    void SetNext(CRoadTile* tile) { mNext = tile; }

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Add Balloon to this Tile
    * \param balloon Balloon to add to tile */
    void AddBalloon(CBalloon* balloon) { mBalloons.push_back(balloon); 
                                         balloon->SetTileOn(this); }

    void DeleteBalloon(CBalloon* balloon);

    void PlaceBalloonNW(CBalloon* balloon);
    void PlaceBalloonSW(CBalloon* balloon);
    void PlaceBalloonEW(CBalloon* balloon);
    void PlaceBalloonNS(CBalloon* balloon);
    void PlaceBalloonNE(CBalloon* balloon);
    void PlaceBalloonSE(CBalloon* balloon);

    virtual void Update(double elapsed) override;

    /** Accept function for item visitors, overrides CItem's accept
    * \param visitor pointer to visitor being accepted */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitRoadTile(this); }

private:
    std::wstring mType; ///< Road type - "EW", "NS", "SE", "SW", "NE", or "NW"

    CRoadTile* mNext = nullptr; ///< Linked List. Pointer to next RoadTile

    std::vector<CBalloon*> mBalloons; ///< Current Balloons on Tile
};
