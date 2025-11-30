// Copyright Tiberiu 2025

#pragma once

#include "Game.h"
#include <iostream>
#include <conio.h>

namespace sokoban {

// -------------------------------------------------------------------------------------------------

Game::Game(Warehouse warehouse, tiage::IConsole& renderer):
    currentWarehouse_(std::move(warehouse)),
    renderer_(renderer) {
}

// -------------------------------------------------------------------------------------------------

Game::Game(tiage::IConsole& renderer) :
    currentWarehouse_(Warehouse(5, 5)),
    renderer_(renderer) {
}

// -------------------------------------------------------------------------------------------------

bool
Game::posIsInvalid(tiage::V2i32 pos) const {
    return    (pos.x() < 0 or pos.x() >= currentWarehouse_.nCols()) or
        (pos.y() < 0 or pos.y() >= currentWarehouse_.nRows());
}

// -------------------------------------------------------------------------------------------------

void
Game::runGame() {
    gameRunning_ = true;
    
    //renderer_.create(currentWarehouse_.nCols(), currentWarehouse_.nRows() * 2 - 1);

    while (gameRunning_) {

        renderCurrentWarehouse();

        if (_kbhit()) {
            char key = _getch();

            handleInput(key);
        }
        if (checkVictory() == true) {
            renderCurrentWarehouse();
            gameRunning_ = false;
        }

        Sleep(50);

      /*  renderer_.move(tiage::V2i32{ rand() % 100, rand() % 100 },
                       tiage::V2i32{ 100, 100 });*/
    }
}

// -------------------------------------------------------------------------------------------------

void
Game::handleInput(char key) {
    if (key == 'w' or key == 'a' or key == 's' or key == 'd') {
        attemptPlayerMove(key);
    }
}

// -------------------------------------------------------------------------------------------------

void
Game::attemptPlayerMove(char key) {

    auto dir = dirFromKey(key);

    if (dir.x() == 0 and dir.y() == 0) {
        return;
    }

    auto playerIndex = currentWarehouse_.getPlayerIndex();

    auto playerPos = currentWarehouse_.getObjects()[playerIndex].pos();

    auto movePos = playerPos + dir;

    if (posIsInvalid(movePos) or currentWarehouse_.getFloor(movePos).type() == Floor::Type::Wall) {
        return;
    }

    if (currentWarehouse_.isObjectAtPos(movePos)) {


        auto objectIndex = currentWarehouse_.getObjectAtPosIndex(movePos);

        if (currentWarehouse_.getObjects()[objectIndex].type() == Object::Type::Box) {

            tiage::Vec2 nextMovePos =
                currentWarehouse_.getObjects()[objectIndex].pos() + dir;

            if (posIsInvalid(nextMovePos) or
                currentWarehouse_.isObjectAtPos(nextMovePos) or
                currentWarehouse_.getFloor(nextMovePos).type() == Floor::Type::Wall) {
                return;
            }

            currentWarehouse_.moveObject(objectIndex, nextMovePos);

        }
    }
    currentWarehouse_.moveObject(playerIndex, movePos);

}

// -------------------------------------------------------------------------------------------------

tiage::Vec2<int>
Game::dirFromKey(char key) {
    if (key == 'w') {
        return { -1, 0 };
    } else if (key == 's') {
        return { 1, 0 };
    } else if (key == 'a') {
        return { 0, -1 };
    } else if (key == 'd') {
        return { 0, 1 };
    } else {
        //unreacheable
        throw std::runtime_error("impossible error");
    }
}

// -------------------------------------------------------------------------------------------------

bool
Game::checkVictory() {
    for (auto& object : currentWarehouse_.getObjects()) {
        if (object.type() == Object::Type::Box and !objectIsCrateOnDelivery(object)) {
            return false;
        }
    }
    
    return true;
}

// -------------------------------------------------------------------------------------------------

void
Game::loadLevel(const std::string& filePath) {
    currentWarehouse_.parseFromFile(filePath);
}

// -------------------------------------------------------------------------------------------------

bool
Game::objectIsCrateOnDelivery(const Object& obj) const {
    return obj.type() == Object::Type::Box and currentWarehouse_.getFloor(obj.pos()).type() == Floor::Type::Storage;
}

// -------------------------------------------------------------------------------------------------

void
Game::renderCurrentWarehouse() const {
    auto rows = currentWarehouse_.nRows();
    auto cols = currentWarehouse_.nCols();

    for (int32_t row = 0; row < rows; row++) {
        for (int32_t col = 0; col < cols; col++) {
            auto floor = currentWarehouse_.getFloor({ col, row });
            renderer_.putChar(row * 2, col, floor.color(), floor.chr());
        }
    }

    for (auto& object : currentWarehouse_.getObjects()) {
        if (objectIsCrateOnDelivery(object)) {
            renderer_.putChar(2 * object.pos().y(), object.pos().x(), tiage::Color::Green, object.asciiCode());
        } else {
            renderer_.putChar(2 * object.pos().y(), object.pos().x(), object.color(), object.asciiCode());
        }
    }

    renderer_.flush();
}

// -------------------------------------------------------------------------------------------------

} // sokoban
