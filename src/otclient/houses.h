/*
 * Copyright (c) 2010-2012 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef HOUSES_H
#define HOUSES_H

#include "declarations.h"
#include "tile.h"

#include <framework/luaengine/luaobject.h>
#include <framework/util/attribstorage.h>

enum HouseAttributes
{
    HouseAttribId,
    HouseAttribName,
    HouseAttribTown,
    HouseAttribEntry,
    HouseAttribSize,
    HouseAttribRent
};

class House : public LuaObject
{
public:
    House() { }
    House(uint32 hId, const std::string& name = "", const Position& pos=Position());
    ~House() { m_tiles.clear(); }

    void setTile(const TilePtr& tile);
    void setId(uint32 hId) { m_attribs.set(HouseAttribId, hId); }
    void setName(const std::string& name) { m_attribs.set(HouseAttribName, name); }
    void setTownId(uint32 tid) { m_attribs.set(HouseAttribTown, tid); }
    void setSize(uint32 s) { m_attribs.set(HouseAttribSize, s); }
    void setRent(uint32 r) { m_attribs.set(HouseAttribRent, r); }
    void setEntry(const Position& p) { m_attribs.set(HouseAttribEntry, p); }

    uint32 getId() { return m_attribs.get<uint32>(HouseAttribId); }
    std::string getName() { return m_attribs.get<std::string>(HouseAttribName); }
    uint32 getRent() { return m_attribs.get<uint32>(HouseAttribRent); }
    uint32 getSize() { return m_attribs.get<uint32>(HouseAttribSize); }

protected:
    void load(const TiXmlElement* elem);
    void save(TiXmlElement &elem) { } // TODO

private:
    AttribStorage m_attribs;
    TileMap m_tiles;
    Boolean<false> m_isGuildHall;

    friend class Houses;
};

class Houses {
public:
    void addHouse(const HousePtr& house);
    void removeHouse(uint32 houseId);
    void load(const std::string& fileName);

    HouseList houseList() const { return m_houses; }
    HousePtr getHouse(uint32 houseId);

    // Fix to segfault on exit.
    void clear() { m_houses.clear(); }

private:
    HouseList m_houses;

protected:
    HouseList::iterator findHouse(uint32 houseId);
};

#endif
