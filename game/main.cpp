// Copyright Tiberiu 2025

#include <tiage/WinConsole.h>
#include <tiage/WinFileSystem.h>
#include "Game.h"

int 
main() {
    tiage::WinFileSystem fileSys;
    std::string answer = fileSys.pickFile("lvl");
    std::string answer2 = fileSys.pickFolder();
    tiage::WinConsole renderer(5,5);
    sokoban::Game game(renderer);
    renderer.setCursorVisible(false);
    return 0;
}