/**
 * \file GrassTile.h
 *
 * \author Jered Brophy
 *
 * 
 */

#pragma once

#include "Tile.h"


 /**
 *  A grass tile
 */
class CGrassTile :
    public CTile
{
public:
    CGrassTile(CGrid* grid);

    ///  Default constructor (disabled)
    CGrassTile() = delete;

    ///  Copy constructor (disabled)
    CGrassTile(const CGrassTile&) = delete;

    ~CGrassTile();

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Accept function for item visitors, overrides CItem's accept
    * \param visitor pointer to visitor being accepted */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitGrassTile(this); }
};

