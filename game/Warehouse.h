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

	const std::vector<tiage::Vec2>& getDeliveryPositions() const;

	int getPlayerIndex() const;

	size_t nRows() const;

	size_t nCols() const;

	void parseFromFile(const std::string& filePath);//within files f means floor and o means object d means dimension

	Floor getFloor(tiage::Vec2 pos) const;
	
	const std::vector<Object>& getObjects() const;

	bool isObjectAtPos(tiage::Vec2 pos) const;

	int getObjectAtPosIndex(tiage::Vec2 pos) const;

	const std::vector<tiage::Vec2>& getTargetPositions() const;

	void moveObject(size_t index, tiage::Vec2 newPos);

private:

	Floor::Type charToFloor(char c);

	Object::Type charToObject(char c);

	void calculateDeliveryPositions();

	void ensureUniquePlayer() const;//stop program and throw error if player not found

	tiage::Matrix<Floor> floor_;

	std::vector<Object> objects_;

	std::vector<tiage::Vec2> targetPositions_;

};

} // sokoban