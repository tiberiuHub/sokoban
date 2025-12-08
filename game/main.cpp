// Copyright Tiberiu 2025



#include <chrono>
#include <thread>

#include <tiage/WinConsole.h>
#include <tiage/WinFileSystem.h>
#include "Game.h"
#include <iostream>


int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    tiage::WinConsole cc;

    cc.create(tiage::WinConsole::kDefaultCreateOptions | tiage::WinConsole::kWinDefaultCreateOptions);

    cc.setCursorVisible(false);

    cc.move(tiage::V2i32{ 500, 500 }, tiage::V2i32{ 29, 15 });

    

//    printf("ad");

    //for (int j = 0; j < 50; j++) {
    //    for (int i = 0; i < 50; i++) {
    //        printf("a");
    //    }        
    //    if (j < 49) {
    //        //SetConsoleCursorPosition()
    //    }
    //    //printf("%d\n", j);
    //}
    //printf("b");
  
    
  //  Sleep(10000);

    //return 0;
    
   

    tiage::WinFileSystem fileSys;
    //std::string answer = fileSys.pickFile("lvl");
    //std::string answer2 = fileSys.pickFolder();
    tiage::WinConsole console;//(5, 5);
    sokoban::Game game(cc);
    cc.setCursorVisible(false);
    //game.loadLevel(answer);
    //game.runGame();
    std::cout << console.getHostProcess();
    int screenW = 1920;
    int screenH = 1080;
    int centerX = screenW / 2;
    int centerY = screenH / 2;

    double angle = 0.0;
    double angularSpeed = 1.0;
    double radius = 200.0;

    auto lastTime = std::chrono::high_resolution_clock::now();
    HWND hwndConsole = GetConsoleWindow();
    DWORD consolePid = 0;
    
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt = now - lastTime;
        lastTime = now;

        angle += angularSpeed * dt.count();

        int x = static_cast<int>(centerX + radius * std::cos(angle));
        int y = static_cast<int>(centerY + radius * std::sin(angle));

        tiage::V2i32 pos(x, y);
        console.move(pos, std::nullopt);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}