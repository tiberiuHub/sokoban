// Copyright Tiberiu 2025

#include <tiage/WinConsole.h>
#include "Game.h"

int main() {
    tiage::WinConsole renderer(50,100);
    sokoban::Game game(renderer);
    renderer.setCursorVisible(false);
    game.loadLevel("C:/Users/oana/Desktop/1.lvl");
    game.runGame();
    //renderer.create(50, 50);
    //renderer.putChar(0, 0, tiage::Color::Green, 'a');
    //renderer.putChar(0, 0, tiage::Color::Green, 'a');
   // renderer.putChar(1, 1, tiage::Color::Green, 'a');
    //renderer.putChar(1, 0, tiage::Color::Green, 'a');
   // renderer.flush();
    
    //renderer.flush();

    //game.loadLevel("C:/Users/oana/Desktop/1.lvl");
    //game.runGame();
    return 0;
}