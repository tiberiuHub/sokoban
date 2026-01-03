// Copyright Tiberiu 2025



#include <chrono>
#include <thread>

#include <tiage/WinConsole.h>
#include <tiage/WinFileSystem.h>
#include "Game.h"
#include <iostream>

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
   tiage::WinConsole skbConsole;
   tiage::WinFileSystem fileSys;

    skbConsole.create(tiage::WinConsole::kWinDefaultCreateOptions |tiage::WinConsole::kDefaultCreateOptions );

   skbConsole.setCursorVisible(false);

   skbConsole.move(tiage::V2i32{ 500, 500 }, tiage::V2i32{ 50,50 });

   skbConsole.setTitle("Sokoban");

   std::string answer = fileSys.pickFile("lvl");
   sokoban::Game game(skbConsole);

   game.loadLevel(answer);
   game.runGame();

    return 0;
}