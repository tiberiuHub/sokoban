// Copyright Tiberiu 2025

#pragma once

#include "Game.h"
#include <iostream>
#include <conio.h>

namespace sokoban {

// -------------------------------------------------------------------------------------------------

Game::Game(Warehouse warehouse, tiage::IConsole& renderer):
    currentWarehouse_(std::move(warehouse)),
    console_(renderer) {
}

// -------------------------------------------------------------------------------------------------

Game::Game(tiage::IConsole& renderer) :
    currentWarehouse_(Warehouse(5, 5)),
    console_(renderer) {
}

// -------------------------------------------------------------------------------------------------

bool
Game::posIsInvalid(tiage::V2i32 pos) const {
    return    (pos.x() < 0 || pos.x() >= currentWarehouse_.nCols()) ||
        (pos.y() < 0 || pos.y() >= currentWarehouse_.nRows());
}

// -------------------------------------------------------------------------------------------------

void
Game::runGame() {
    gameRunning_ = true;

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

    }
}

// -------------------------------------------------------------------------------------------------

void
Game::handleInput(char key) {
    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        attemptPlayerMove(key);
    } else if (key == 'r') {
        undoLastMove();
    }
}

// -------------------------------------------------------------------------------------------------

void
Game::attemptPlayerMove(char key) {

    auto dir = dirFromKey(key);

    if (dir.x() == 0 && dir.y() == 0) {
        return;
    }

    auto playerIndex = currentWarehouse_.getPlayerIndex();

    auto playerPos = currentWarehouse_.getObjects()[playerIndex].pos();

    auto movePos = playerPos + dir;

    if (posIsInvalid(movePos) || currentWarehouse_.getFloor(movePos).type() == Floor::Type::Wall) {
        return;
    }

    std::vector<Move> movesThisTurn;

    if (currentWarehouse_.isObjectAtPos(movePos)) {


        auto objectIndex = currentWarehouse_.getObjectAtPosIndex(movePos);

        if (currentWarehouse_.getObjects()[objectIndex].type() == Object::Type::Box) {

            tiage::Vec2 nextMovePos = currentWarehouse_.getObjects()[objectIndex].pos() + dir;

            if (posIsInvalid(nextMovePos) ||
                currentWarehouse_.isObjectAtPos(nextMovePos) || 
                currentWarehouse_.getFloor(nextMovePos).type() == Floor::Type::Wall) {
                return;
            }

            currentWarehouse_.moveObject(objectIndex, nextMovePos);

            movesThisTurn.push_back({ movePos, nextMovePos });
        }
    }
    currentWarehouse_.moveObject(playerIndex, movePos);

    movesThisTurn.push_back({ playerPos,movePos });
    movesMade_.push(movesThisTurn);
}

// -------------------------------------------------------------------------------------------------

void
Game::undoLastMove() {
    if (movesMade_.empty()) { 
        return; 
    }
    auto lastMove = movesMade_.top();
    movesMade_.pop();
    for (auto move : lastMove) {
        auto objectIndex = currentWarehouse_.getObjectAtPosIndex(move.to);
        currentWarehouse_.moveObject(objectIndex, move.from);
    }
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
        if (object.type() == Object::Type::Box && !objectIsCrateOnDelivery(object)) {
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
    return obj.type() == Object::Type::Box && currentWarehouse_.getFloor(obj.pos()).type() == Floor::Type::Storage;
}

// -------------------------------------------------------------------------------------------------

void
Game::renderCurrentWarehouse() const {
    auto rows = currentWarehouse_.nRows();
    auto cols = currentWarehouse_.nCols();

    for (int32_t row = 0; row < rows; row++) {
        for (int32_t col = 0; col < cols; col++) {
            auto floor = currentWarehouse_.getFloor({ col, row });
            console_.putChar(row * 2, col, {  floor.chr(),floor.color(),floor.color(), });
        }
    }

    console_.move(std::nullopt, tiage::V2i32{ static_cast<int>(rows) * 2 - 1, static_cast<int>(cols) });

    for (auto& object : currentWarehouse_.getObjects()) {
        if (objectIsCrateOnDelivery(object)) {
            console_.putChar(2 * object.pos().y(), object.pos().x(), {  object.asciiCode(), tiage::Color::kGreen, tiage::Color::kGreen });
        } else {
            console_.putChar(2 * object.pos().y(), object.pos().x(), {  object.asciiCode(), object.color(), object.color() });
        }
    }

    console_.flush();
}

// -------------------------------------------------------------------------------------------------

} // sokoban
