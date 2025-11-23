// Copyright Tiberiu 2025

#include <tiage/WinConsole.h>
#include "Game.h"

int main() {
    tiage::WinConsole renderer(5,5);
    sokoban::Game game(renderer);
    renderer.setCursorVisible(false);
    //renderer.putChar(1, 1, tiage::Color::Green, 'A');
    //renderer.flush();
    game.loadLevel("C:/Users/oana/Desktop/1.lvl");
    game.runGame();
   
    //std::cout << 111;
    //game.loadLevel("C:/Users/oana/Desktop/1.lvl");
    //game.runGame();
    return 0;
}