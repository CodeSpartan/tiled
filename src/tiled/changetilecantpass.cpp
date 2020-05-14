/*
 * changetilecantpass.cpp
 * Copyright 2020, CodeSpartan
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "changetilecantpass.h"

#include "tilesetdocument.h"
#include "tile.h"

#include <QCoreApplication>

namespace Tiled {

ChangeTileCantPass::ChangeTileCantPass(TilesetDocument *tilesetDocument,
                                             const QList<Tile*>& tiles,
                                             bool cantPass)
    : mTilesetDocument(tilesetDocument)
    , mTiles(tiles)
{
    mCantPasses.reserve(tiles.size());
    for (int i = 0; i < tiles.size(); ++ i)
        mCantPasses.append(cantPass);

    setText(QCoreApplication::translate("Undo Commands",
                                        "Change Tile CantPass"));
}

ChangeTileCantPass::ChangeTileCantPass(TilesetDocument *tilesetDocument,
                                             const QList<Tile *> &tiles,
                                             const QList<bool> &cantPasses,
                                             QUndoCommand *parent)
    : QUndoCommand(parent)
    , mTilesetDocument(tilesetDocument)
    , mTiles(tiles)
    , mCantPasses(cantPasses)
{
    Q_ASSERT(mTiles.size() == mCantPasses.size());
    setText(QCoreApplication::translate("Undo Commands",
                                        "Change Tile CantPasses"));
}

void ChangeTileCantPass::swap()
{
    for (int i = 0; i < mTiles.size(); ++ i) {
        Tile *tile = mTiles[i];
        bool cantPass = tile->cantPass();
        mTilesetDocument->setTileCantPass(tile, mCantPasses[i]);
        mCantPasses[i] = cantPass;
    }
}

} // namespace Tiled

