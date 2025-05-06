#pragma once
#include <iostream>
#include "conio.h"
#include <windows.h>

#define UP 72 // 위
#define DOWN 80 // 아래


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
    gotoxy(x, y);
    printf("아무튼 말달리자 게임임\n");

    gotoxy(x - 4, y + 2);
    cout << "계속하려면 아무 키나 누르세요...";

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


/*
참고사이트
https://geundung.dev/14?category=699626 => 화면 메뉴란 구성
https://geundung.dev/15?category=699626 =>키보드 이벤트 처리
*/