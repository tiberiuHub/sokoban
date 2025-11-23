// Copyright Tiberiu 2025

#pragma once

#include <tiage/Color.h>
#include <unordered_map>

namespace sokoban {

class Floor {
public:

    enum class Type { Empty, Wall, Storage };

    Floor(Type type);

    Floor();

    Type type() const;

    tiage::Color color() const;

    char chr() const;

private:

    char asciiCode_;

    tiage::Color color_;

    Type type_;
};

} // sokoban