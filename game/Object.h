// Copyright Tiberiu 2025

#pragma once

#include <tiage/Color.h>
#include <tiage/Vec2.h>
#include <unordered_map>

namespace sokoban {

class Object {
public:

    enum class Type { Box, Player };

    Object(Type type, tiage::Vec2<uint32_t> pos);

    void setPos(tiage::Vec2<uint32_t> pos);

    Type type() const;

    tiage::Vec2<uint32_t> pos() const;

    char asciiCode() const;

    tiage::Color color() const;

private:

    Type type_;

    tiage::Vec2<uint32_t> pos_;

    char asciiCode_;
    
    tiage::Color color_;
};

} // sokoban