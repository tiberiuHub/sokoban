// Copyright Tiberiu 2025

#include <tiage/WinConsole.h>
#include "Game.h"

int main() {
    tiage::WinConsole renderer(50,50);
    sokoban::Game game(renderer);
    renderer.setCursorVisible(false);
    game.loadLevel("C:/Users/oana/Desktop/debug.lvl");
    game.runGame();
    game.loadLevel("C:/Users/oana/Desktop/1.lvl");
    game.runGame();
    return 0;
}