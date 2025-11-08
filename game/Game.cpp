// Copyright Tiberiu 2025

#pragma once

#include "Game.h"
#include <iostream>
#include <conio.h>

namespace sokoban {

// -------------------------------------------------------------------------------------------------

Game::Game(Warehouse warehouse, tiage::IAsciiRenderer& renderer):
	currentWarehouse_(std::move(warehouse)),
	renderer_(renderer) {
}

// -------------------------------------------------------------------------------------------------

Game::Game(tiage::IAsciiRenderer& renderer) :
	currentWarehouse_(Warehouse(5, 5)),
	renderer_(renderer) {
}

// -------------------------------------------------------------------------------------------------

bool
Game::posIsInvalid(tiage::Position pos) const {
	return	(pos.x < 0 or pos.x >= currentWarehouse_.nCols()) or
		(pos.y < 0 or pos.y >= currentWarehouse_.nRows());
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
	if (key == 'w' or key == 'a' or key == 's' or key == 'd') {
		attemptPlayerMove(key);
	}
}

// -------------------------------------------------------------------------------------------------

void
Game::attemptPlayerMove(char key) {

	auto dir = dirFromKey(key);

	if (dir.x == 0 and dir.y == 0) {
		return;
	}

	auto playerIndex = currentWarehouse_.getPlayerIndex();

	auto playerPos = currentWarehouse_.getObjects()[playerIndex].pos();

	tiage::Position movePos = { playerPos.x + dir.x, playerPos.y + dir.y };

	if (posIsInvalid(movePos) or currentWarehouse_.getFloor(movePos).type() == Floor::Type::Wall) {
		return;
	}
	//std::cout << currentWarehouse_.isObjectAtPos(movePos);




	if (currentWarehouse_.isObjectAtPos(movePos)) {


		auto objectIndex = currentWarehouse_.getObjectAtPosIndex(movePos);

		if (currentWarehouse_.getObjects()[objectIndex].type() == Object::Type::Box) {

			tiage::Position nextMovePos = { currentWarehouse_.getObjects()[objectIndex].pos().x + dir.x, currentWarehouse_.getObjects()[objectIndex].pos().y + dir.y };


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

tiage::Position
Game::dirFromKey(char key) {
	if (key == 'w') {
		return { -1,0 };
	} else if (key == 's') {
		return { 1,0 };
	} else if (key == 'a') {
		return { 0,-1 };
	} else if (key == 'd') {
		return { 0,1 };
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

	renderer_.resizeDesiredCanvas(currentWarehouse_.nRows() * 2 - 1, currentWarehouse_.nCols());

	renderer_.beginFrame();


	for (uint32_t row = 0; row < rows; row++) {
		for (uint32_t col = 0; col < cols; col++) {
			auto floor = currentWarehouse_.getFloor({ static_cast<int>(col), static_cast<int>(row) });
			renderer_.putChar(col, row * 2, floor.color(), floor.chr());
		}
	}


	for (auto& object : currentWarehouse_.getObjects()) {
		if (objectIsCrateOnDelivery(object)) {
			renderer_.putChar(object.pos().x, object.pos().y * 2, tiage::Color::Green, object.asciiCode());
		} else {
			renderer_.putChar(object.pos().x, object.pos().y * 2, object.color(), object.asciiCode());
		}
			
			
	}

	renderer_.render();
}

// -------------------------------------------------------------------------------------------------

} // sokoban
