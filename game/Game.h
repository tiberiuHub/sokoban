// Copyright Tiberiu 2025

#pragma once

#include <tiage/IConsole.h>
#include "Warehouse.h"
#include <Windows.h>
#include <stack>

namespace sokoban {

class Game {
public:

    Game(Warehouse warehouse, tiage::IConsole& renderer);

    Game(tiage::IConsole& renderer);

    void runGame();

    void loadLevel(const std::string& filePath);

private:

    struct Move {
        tiage::V2i32 from;
        tiage::V2i32 to;
    };

    bool objectIsCrateOnDelivery(const Object& obj) const;

    bool posIsInvalid(tiage::V2i32 pos) const;

    tiage::Vec2<int> dirFromKey(char key);

    void attemptPlayerMove(char key);

    void undoLastMove();

    bool checkVictory();

    void handleInput(char key);

    void renderCurrentWarehouse() const;

    Warehouse currentWarehouse_;

    tiage::IConsole& console_;

    bool gameRunning_ = false;

    std::stack<std::vector<Move>> movesMade_;

};

} // sokoban
