#pragma once
#include <iostream>
#include <windows.h>

#include "conio.h"
#include "training.h"
#define UP 72 // 위
#define DOWN 80 // 아래
const int MAX_MONTH = 36;

//#define LEFT 2 
//#define RIGHT 3
using namespace std;


void init_console_size() {
    system("mode con:cols=124 lines=35");
}

void init_game_ui() { // 게임맨처음 킬때 TItle 현재는 사용 안함

    cout << " 말달리자 게임 " << endl;

}

void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 커서 핸들가져오기
    COORD pos;
    pos.X = x; // x좌표
    pos.Y = y; // y좌표	
    SetConsoleCursorPosition(consoleHandle, pos); // 커서 위치 설정
}



int keyControl() {
    char temp = _getch();

    if (temp == 72) // 위
        return UP;
    else if (temp == 80) // 아래
        return DOWN;
    else if (temp == 27) // ESC
        return 27;
    else if (temp == 13) // Enter
        return 13;
    else
        return -1; // 잘못된 입력
}

void drawArrow(int x, int y) {
    gotoxy(x, y);
    printf(">");
}

void clearArrow(int x, int y) {
    gotoxy(x, y);
    printf(" "); // 이전 위치의 '>'를 지움
}

int menuDraw() {
    
   
    int x = 50;
    int y = 15;
    int arrowX = x + 4; // '>' 기호 위치
    int currentY = y + 10; // 현재 선택된 항목의 y좌표
    
    cout << "===========================================================================================================================\n" << endl;
    gotoxy(x - 48, y - 6);
    printf("      :::::::::::   ::::    :::   :::::::::::   :::::::::::   :::::::::::         :::        :::               :::    ::: \n");//1

    gotoxy(x - 48, y - 5);
    printf("         :+:       :+:+:   :+:       :+:           :+:           :+:           :+: :+:      :+:               :+:    :+:  \n");//2

    gotoxy(x - 48, y - 4);
    printf("        +:+       :+:+:+  +:+       +:+           +:+           +:+          +:+   +:+     +:+               +:+    +:+   \n");//3

    gotoxy(x - 48, y - 3);
    printf("       +#+       +#+ +:+ +#+       +#+           +#+           +#+         +#++:++#++:    +#+               +#++:++#++    \n");//4

    gotoxy(x - 48, y - 2);
    printf("      +#+       +#+  +#+#+#       +#+           +#+           +#+         +#+     +#+    +#+               +#+    +#+      \n");//5

    gotoxy(x - 48, y - 1);
    printf("    #+#       #+#   #+#+#       #+#           #+#           #+#         #+#     #+#    #+#        #+#     #+#    #+#      \n");

    gotoxy(x - 48, y);
    //gotoxy(x-50, y );
    printf("###########  ###    ####   ###########       ###       ###########     ###     ###    ########## ###     ###    ###       ");

    /*gotoxy(x - 4, y + 2);
    cout << "계속하려면 아무 키나 누르세요...";*/

    gotoxy(x + 4, y + 10);
    printf("  게임시작 ");

    gotoxy(x + 6, y + 12);
    printf("이어하기 ");

    gotoxy(x + 6, y + 14);
    printf("  종료	\n\n");
    cout << "==========================================================================================================================\n" << endl;

    // 처음에 '>' 표시를 바로 그리기
    drawArrow(arrowX, currentY);

    while (1) {
        int n = keyControl();
        switch (n) {
        case UP:
            if (currentY > y + 10) { // 최소 위치 제한
                clearArrow(arrowX, currentY);
                currentY -= 2; // 한 줄 위로 이동
                drawArrow(arrowX, currentY);
            }
            break;
        case DOWN:
            if (currentY < y + 14) { // 최대 위치 제한
                clearArrow(arrowX, currentY);
                currentY += 2; // 한 줄 아래로 이동
                drawArrow(arrowX, currentY);
            }
            break;
        case 13: // Enter
            system("cls");
            if (currentY == y + 10) return 1; // 게임시작
            else if (currentY == y + 12) return 2; // 이어하기
            else if (currentY == y + 14) return 3; // 종료
            break;
        }
    }
}

void print_stat(int month, horse* player, training& trainer) {
    int display_year = (month % 24 == 0 && month != 0) ? month / 24 : month / 24 + 1;
    int d_day = (month % 6 == 0) ? 0 : 6 - (month % 6);

    string brred_str;
    switch (player->get_breed()) {
    case 0: brred_str = "도주마"; break;
    case 1: brred_str = "선행마"; break;
    case 2: brred_str = "선입마"; break;
    case 3: brred_str = "추입마"; break;
    default: brred_str = "알 수 없음"; break;
    }
   
    
    cout << "===========================================================================================================================\n"
        << "\t\t\t\t\t\t\t" << display_year << "(년차)\n\n" //<< month << " / " << MAX_MONTH << "\n\n"
        << "\t\t\t\t\t" << player->get_name() << " | " << brred_str << " | " << month << "turn |" << "레이스 D-" << d_day << "\n";
    cout << "===========================================================================================================================\n\n";
    cout << "\t\t\t    ,\n";
    cout << "\t\t\t    _,,).~,,._   /====================================================== \n";
    cout << "\t\t\t    (()`  ``)))),,_                                                   /| \n";
    cout << "\t\t\t    |      ''(()))),,_          ____                                 / | \n";
    cout << "\t\t\t    |6`   |   ''((\$))) \" - \".____. - \"    `-.-,                     /  | \n";
    cout << "\t\t\t    |    .'    ''))))'                  \$))                        /   | \n";
    cout << "\t\t\t    |   |  /`.     ''                     ((((                    /    | \n";
    cout << "\t\t\t    , _)  /  /                          |))))                    /     | \n";
    cout << "\t\t\t    `'   /    |                          (((((                  /     /| \n";
    cout << "\t\t\t         ========================================================    / | \n";
    cout << "\t\t\t         |      `|    |           ,\\     /((((((               |    /  | \n";            
    cout << "\t\t\t         |       |   / `-.______.&lt;  \\   |  )))))            |   /   | \n";
    cout << "\t\t\t         |       |   |  /         `. \\  \\  ((((                |  /    | \n";
    cout << "\t\t\t         |       |  / \\ |           `./  | (((                 | /     | \n";
    cout << "\t\t\t         ========================================================      | \n";
    cout << "\t\t\t         |        | | | |            / | |  '                   |        \n";    
    cout << "\t\t\t         |        | | /_(           /_(/ /                      |        \n";
    cout << "\t\t\t         |        /_(/__]           \\_/(_)                      |        \n";
    cout << "\t\t\t         |       /__]                /__]                       |        \n";
    cout << "\t\t\t\t\t\t\n";
    cout << "===========================================================================================================================\n";
    cout << "현능력치\n";
    cout << "스피드 : " << player->get_spd() << "\t파워 : " << player->get_pow() << "\t근성 : " << player->get_guts() << "\t지구력 : " << player->get_sta() << "\n";
    cout << "부상확률 : " << trainer.injury_percent(*player) << "%\t" << "체력: " << trainer.get_hp() << "\n";
    cout << "===========================================================================================================================\n";
    cout << "1) 스피드 훈련\t2) 파워 훈련\t3) 근성 훈련\t4) 지구력 훈련\t5) 휴식\n";
    while (true) {
        int n;
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "숫자만 입력해주세요: ";
            continue;
        }
        switch (n) {
        case 1: trainer.training_speed(*player);      return;
        case 2: trainer.training_power(*player);      return;
        case 3: trainer.training_perseverance(*player); return;
        case 4: trainer.training_endurance(*player);  return;
        case 5: trainer.rest(*player);                return;
        default:
            cout << "잘못된 선택입니다. 다시 입력해주세요: ";
        }
    }
}

/*
참고사이트
https://geundung.dev/14?category=699626 => 화면 메뉴란 구성
https://geundung.dev/15?category=699626 =>키보드 이벤트 처리
*/

