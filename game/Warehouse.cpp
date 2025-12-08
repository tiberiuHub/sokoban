// Copyright Tiberiu 2025

#pragma once

#include "Warehouse.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace sokoban {

// -------------------------------------------------------------------------------------------------

Warehouse::Warehouse(uint32_t width, uint32_t height) : floor_(width, height) {}

// -------------------------------------------------------------------------------------------------

int
Warehouse::getPlayerIndex() const {
    for (size_t i = 0; i < objects_.size(); i++) {
        if (objects_[i].type() == Object::Type::Player) {
            return i;
        }
    }
    throw std::runtime_error("Player not found in warehouse");
}

// -------------------------------------------------------------------------------------------------

const std::vector<tiage::V2i32>&
Warehouse::getDeliveryPositions() const {
    return targetPositions_;
}

// -------------------------------------------------------------------------------------------------

void
Warehouse::moveObject(size_t index, tiage::V2i32 newPos) {
    objects_[index].setPos(newPos);
}

// -------------------------------------------------------------------------------------------------

bool
Warehouse::isObjectAtPos(tiage::V2i32 pos) const {
    for (size_t i = 0; i < objects_.size(); i++) {
        if (objects_[i].pos() == pos) {
                return true;
        }
    }
    return false;
}

// -------------------------------------------------------------------------------------------------

int
Warehouse::getObjectAtPosIndex(tiage::V2i32 pos) const {
    for (size_t i = 0; i < objects_.size(); i++) {
        if (objects_[i].pos() == pos) {
            return i;
        }
    }
    throw std::runtime_error("you forgot to use isObjectAtPos to check if pos is valid first!");
}

// -------------------------------------------------------------------------------------------------

void
Warehouse::calculateDeliveryPositions() {

    targetPositions_.clear();

    for (int32_t i = 0; i < floor_.nRows(); i++) {
        for (int32_t j = 0; j < floor_.nCols(); j++) {
            if (floor_.get(i, j).type() == Floor::Type::Storage) {
                targetPositions_.push_back({ i, j });
            }
        }
    }

}

// -------------------------------------------------------------------------------------------------

void
Warehouse::parseFromFile(const std::string& filePath) {

    objects_.clear();

    std::ifstream file(filePath);
    std::string line;

    int32_t floorLineCount = 0;
    int32_t objectLineCount = 0;

    uint32_t width = 0;
    uint32_t height = 0;

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }



    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        char id = line[0];
        line = line.substr(1);

        if (id == 'd') {
            std::istringstream iss(line);
            if (!(iss >> width >> height))
                throw std::runtime_error("Invalid dimensions");
            floor_ = tiage::Matrix<Floor>(height, width);

        } else if (id == 'f') {

            for (size_t i = 0; i < line.size(); i++) {

                auto floorType = charToFloor(line[i]);
                
                floor_.set(i, floorLineCount, Floor(floorType));

            }

            floorLineCount++;

        } else if (id == 'o') {

            for (int32_t i = 0; i < line.size(); i++) {
                if (line[i] == '.') {
                    continue;
                }
                auto objectType = charToObject(line[i]);
                objects_.emplace_back(Object( objectType, { objectLineCount, i }));
            }

            objectLineCount++;

        }
    }


    ensureUniquePlayer();

    if (floorLineCount != objectLineCount) {
        throw std::runtime_error("file written wrong");
    }

}

// -------------------------------------------------------------------------------------------------

Floor::Type
Warehouse::charToFloor(char c) {
    switch (c) {
    case '#': return Floor::Type::Wall;
    case '.': return Floor::Type::Empty;
    case 'x': return Floor::Type::Storage;
    default: throw std::runtime_error(std::string("Unknown floor char: ") + c);
    }
}

// -------------------------------------------------------------------------------------------------

Object::Type
Warehouse::charToObject(char c) {
    switch (c) {
    case '@': return Object::Type::Player;
    case 'b': return Object::Type::Box;
    default: throw std::runtime_error(std::string("Unknown object char: ") + c);
    }
}

// -------------------------------------------------------------------------------------------------

void
Warehouse::ensureUniquePlayer() const {
    uint32_t count = 0;

    for (const auto& object : objects_) {
        if (object.type() == Object::Type::Player) {
            count++;
        }
    }

    if (count == 0 or count > 1) {
        throw std::runtime_error("invalid player amount");
    }
}

// -------------------------------------------------------------------------------------------------

size_t
Warehouse::nRows() const {
    return floor_.nRows();
}

// -------------------------------------------------------------------------------------------------

size_t
Warehouse::nCols() const {
    return floor_.nCols();
}

// -------------------------------------------------------------------------------------------------

Floor
Warehouse::getFloor(tiage::V2i32 pos) const {
    return floor_.get(pos.y(), pos.x());
}

// -------------------------------------------------------------------------------------------------

const std::vector<Object>&
Warehouse::getObjects() const {
    return objects_;
}

// -------------------------------------------------------------------------------------------------

const std::vector<tiage::V2i32>&
Warehouse::getTargetPositions() const {
    return targetPositions_;
}

// -------------------------------------------------------------------------------------------------

} // sokoban
