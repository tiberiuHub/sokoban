// Copyright Tiberiu 2025

#pragma once

#include "Object.h"

namespace sokoban {

// --------------------------------------------------------------------------------------------------

Object::Object(Type type, tiage::Vec2 <uint32_t> pos) :
    type_(type),
    pos_(pos) {
    // the default look for a sokoban object
    static const std::unordered_map<Type, std::pair<char, tiage::Color>> defaults = {
        { Type::Player , { '@', tiage::Color::Red } },
        { Type::Box, { '#', tiage::Color::Brown} },
    };
    asciiCode_ = defaults.at(type).first;
    color_ = defaults.at(type).second;
}

// --------------------------------------------------------------------------------------------------

void
Object::setPos(tiage::Vec2 <uint32_t> pos) {
    pos_ = pos;
}

// --------------------------------------------------------------------------------------------------

tiage::Color
Object::color() const {
    return color_;
}

// --------------------------------------------------------------------------------------------------

char
Object::asciiCode() const {
    return asciiCode_;
}

// --------------------------------------------------------------------------------------------------

Object::Type
Object::type() const {
    return type_;
}

// --------------------------------------------------------------------------------------------------

tiage::Vec2 <uint32_t>
Object::pos() const {
    return pos_;
}

// --------------------------------------------------------------------------------------------------

} // sokoban
