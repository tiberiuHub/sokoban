// Copyright Tiberiu 2025



#include <chrono>
#include <thread>

#include <tiage/WinConsole.h>
#include <tiage/WinFileSystem.h>
#include <tiage/Sprite.h>
#include <tiage/Renderer.h>
#include "Game.h"
#include <iostream>

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    tiage::WinConsole skbConsole({ 320,80 });
    skbConsole.create(tiage::WinConsole::kWinDefaultCreateOptions | tiage::WinConsole::kDefaultCreateOptions);
    skbConsole.setCursorVisible(false);

    skbConsole.move(tiage::V2i32{ 500,500 }, tiage::Vec2<size_t>{ 320,80 });
    skbConsole.resizeFont(6);
    skbConsole.setTitle("Sokoban");

   /*
     
   tiage::WinFileSystem fileSys;

   
 

   std::string answer = fileSys.pickFile("lvl");
   sokoban::Game game(skbConsole);

   game.loadLevel(answer);
   game.runGame();
   */
    tiage::Sprite sprt;
    tiage::Renderer rnd({ 320,80 });
    
    auto layer = rnd.addLayer(2);
    auto layer2 = rnd.addLayer(1);
    rnd.setLayer(layer);
    sprt.parseFromFile("C:/Users/oana/Desktop/Sokoban/Files/Sprite/test.sprt");
    rnd.drawChar({ 319,79 }, { ' ',tiage::Color::kWheat,tiage::Color::kWheat });
    rnd.setLayer(layer2);
    rnd.drawRect({ ' ',tiage::Color::kWhite,tiage::Color::kWhite }, { 0,0 }, { 320, 80 },true);
    rnd.drawSprite({ 60,30 }, sprt);
    rnd.present(skbConsole);
    skbConsole.flush();
    while (true) {
        Sleep(2222);
    }
    

    return 0;
}