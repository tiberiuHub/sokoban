// Copyright Tiberiu 2025

#pragma once

#include <vector>
#include <tiage/Position.h>
#include <tiage/Matrix.h>
#include "Object.h"
#include "Floor.h"

namespace sokoban {

class Warehouse {
public:

	Warehouse(uint32_t width, uint32_t height);

	const std::vector<tiage::Position>& getDeliveryPositions() const;

	int getPlayerIndex() const;

	uint32_t nRows() const;

	uint32_t nCols() const;

	void parseFromFile(const std::string& filePath);//within files f means floor and o means object

	Floor getFloor(tiage::Position pos) const;
	
	const std::vector<Object>& getObjects() const;

	bool isObjectAtPos(tiage::Position pos) const;

	int getObjectAtPosIndex(tiage::Position pos) const;

	const std::vector<tiage::Position>& getTargetPositions() const;

	void moveObject(size_t index, tiage::Position newPos);

private:

	Floor::Type charToFloor(char c);

	Object::Type charToObject(char c);

	void calculateDeliveryPositions();

	void ensureUniquePlayer() const;//stop program and throw error if player not found

	tiage::Matrix<Floor> floor_;

	std::vector<Object> objects_;

	std::vector<tiage::Position> targetPositions_;

};

} // sokoban