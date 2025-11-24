// Copyright Tiberiu 2025

#include <tiage/WinConsole.h>
#include "Game.h"

int 
main() {
    tiage::WinConsole renderer(5,5);
    sokoban::Game game(renderer);
    renderer.setCursorVisible(false);
    game.loadLevel("C:/Users/Oana/Desktop/1.lvl");
    game.runGame();
    return 0;
}