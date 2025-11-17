// Copyright Tiberiu 2025

#include <tiage/WinConsole.h>
#include "Game.h"

int main() {
    tiage::WinConsole renderer(3,3);
    sokoban::Game game(renderer);
    renderer.setCursorVisible(false);
    game.loadLevel("C:/Users/oana/Desktop/debug.lvl");
    game.runGame();
    //std::cout << 111;
    //game.loadLevel("C:/Users/oana/Desktop/1.lvl");
    //game.runGame();
    return 0;
}