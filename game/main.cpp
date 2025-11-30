// Copyright Tiberiu 2025






#include <tiage/WinConsole.h>
#include <tiage/WinFileSystem.h>
#include "Game.h"

//int 
//main() {
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
    //tiage::WinConsole renderer;//(5, 5);
    sokoban::Game game(cc);
    cc.setCursorVisible(false);
    game.loadLevel(R"(C:\Users\root\Desktop\1.lvl)");
    game.runGame();
    return 0;
}