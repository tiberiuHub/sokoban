// Copyright Tiberiu 2025

#pragma once

#include <tiage/Color.h>
#include <unordered_map>
#include "Floor.h"

namespace sokoban {

// --------------------------------------------------------------------------------------------------

Floor::Floor(Type type) :type_(type) {
	//default sokoban floors
	static const std::unordered_map<Floor::Type, std::pair<char, tiage::Color>> defaults = {
		{ Floor::Type::Wall , {'#', tiage::Color::Gray} },
		{ Floor::Type::Storage, {'X', tiage::Color::Purple} },
		{ Floor::Type::Empty,  {'=', tiage::Color::DarkGray} }
	};
	asciiCode_ = defaults.at(type).first;
	color_ = defaults.at(type).second;

}

// --------------------------------------------------------------------------------------------------

Floor::Floor() :type_(Type::Empty),
				color_(tiage::Color::White),
				asciiCode_(' ') { }

// --------------------------------------------------------------------------------------------------

tiage::Color
Floor::color() const {
	return color_;
}

// --------------------------------------------------------------------------------------------------

char 
Floor::chr() const {
	return asciiCode_;
}

// --------------------------------------------------------------------------------------------------

Floor::Type 
Floor::type() const {
	return type_;
}

// --------------------------------------------------------------------------------------------------

} // sokoban