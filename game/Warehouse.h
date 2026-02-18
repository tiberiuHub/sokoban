// Copyright Tiberiu 2025

#pragma once

#include <vector>
#include <tiage/Vec2.h>
#include <tiage/Matrix.h>
#include "Object.h"
#include "Floor.h"

namespace sokoban {

class Warehouse {
public:

    Warehouse(uint32_t width, uint32_t height);

    const std::vector<tiage::V2i32>& getDeliveryPositions() const;

    int getPlayerIndex() const;

    size_t nRows() const;

    size_t nCols() const;

    void parseFromFile(const std::string& filePath);//within files f means floor and o means object d means dimensions

    Floor getFloor(tiage::Vec2<size_t> pos) const;
    
    const std::vector<Object>& getObjects() const;

    bool isObjectAtPos(tiage::V2i32 pos) const;

    int getObjectAtPosIndex(tiage::V2i32 pos) const;

    const std::vector<tiage::V2i32>& getTargetPositions() const;

    void moveObject(size_t index, tiage::V2i32 newPos);

private:

    Floor::Type charToFloor(char c);

    Object::Type charToObject(char c);

    void calculateDeliveryPositions();

    void ensureUniquePlayer() const;//stop program and throw error if player not found

    tiage::Matrix<Floor> floor_;

    std::vector<Object> objects_;

    std::vector<tiage::V2i32> targetPositions_;

};

} // sokoban