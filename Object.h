// Copyright Tiberiu 2025

#pragma once

#include <tiage/Color.h>
#include <tiage/Position.h>
#include <unordered_map>

namespace sokoban {

class Object {
public:

	enum class Type { Box, Player };

	Object(Type type, tiage::Position pos);

	void setPos(tiage::Position pos);

	Type type() const;

	tiage::Position pos() const;

	char asciiCode() const;

	tiage::Color color() const;

private:

	Type type_;

	tiage::Position pos_;

	char asciiCode_;
	
	tiage::Color color_;
};

} // sokoban