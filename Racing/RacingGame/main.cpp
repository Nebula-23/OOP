#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "horse.h"
#include "training.h"
#include "race.h"
#include "UI.h"
#include "game.h"
#include "tutorial.h"
#include <mmsystem.h> 
#pragma comment(lib,"winmm.lib")

const int startStat = 10.0;

using namespace std;

//void print_basic(int month, horse* player, training& trainer);
void print_stat(int month, horse* player, training& trainer);

int main() { //cols 가로 , lines 세로 cols=140 lines=30
    // 콘솔 입출력 인코딩을 UTF-8로 설정
    SetConsoleOutputCP(CP_UTF8);  // 출력 인코딩
    SetConsoleCP(CP_UTF8);        // 입력 인코딩

    int start_format;
    init_console_size(); // 콘솔 크기 초기화
    //init_game_ui(); // UI 초기화
    PlaySound(TEXT("BGM1.wav"), NULL, SND_ASYNC | SND_LOOP);
    start_format = menuDraw();
    if (start_format == 1)
    {
        system("cls");
    }
    else if (start_format == 2) {
        //save&load
    }
    else
        exit(1);

    srand(static_cast<unsigned>(time(nullptr)));

    // 말생성 함수 UI.h에서 처리
    horse player = select_horse();
    
    // 튜토리얼 실행
    tutorial();

    //게임 진행 함수 game,h에서 처리
    play_game(player);

    return 0;
}

void print_stat(int month, horse* player, training& trainer);