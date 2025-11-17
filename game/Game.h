// Copyright Tiberiu 2025

#pragma once

#include <tiage/IConsole.h>
#include "Warehouse.h"
#include <Windows.h>

namespace sokoban {

class Game {
public:

	Game(Warehouse warehouse, tiage::IConsole& renderer);

	Game(tiage::IConsole& renderer);

	void runGame();

	void loadLevel(const std::string& filePath);

private:

	bool objectIsCrateOnDelivery(const Object& obj) const;

	bool posIsInvalid(tiage::Vec2 Pos) const;

	tiage::Vec2 dirFromKey(char key);

	void attemptPlayerMove(char key);

	bool checkVictory();

	void handleInput(char key);

	void renderCurrentWarehouse() const;

	Warehouse currentWarehouse_;

	tiage::IConsole& renderer_;

	bool gameRunning_ = false;

};

} // sokoban
