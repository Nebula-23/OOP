#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "horse.h"
#include "training.h"
#include "race.h"
#include "UI.h"

const int startStat = 100.0;

using namespace std;

horse select_horse();
//void print_basic(int month, horse* player, training& trainer);
void print_stat(int month, horse* player, training& trainer);

int main() { //cols 가로 , lines 세로 cols=140 lines=30
    // 콘솔 입출력 인코딩을 UTF-8로 설정
    SetConsoleOutputCP(CP_UTF8);  // 출력 인코딩
    SetConsoleCP(CP_UTF8);        // 입력 인코딩

    int start_format;
    init_console_size(); // 콘솔 크기 초기화
    //init_game_ui(); // UI 초기화
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

    horse player = select_horse();
    // 트레이너 객체 생성
    training trainer(player);

    Sleep(500);
    system("cls");

    for (int i = 0; i < MAX_MONTH; i++) {
        //레이스 함수 갈수록 말의 티어가 높아짐 1년차(6,5티어) 2년차(4,3티어) 3년차 (2,1티어)
        if (i != 0 && i % 6 == 0) {

            int tier = 1; // 기본값
            if (i <= 12)        tier = 6;
            else if (i <= 24)   tier = 5;
            else if (i <= 36)   tier = 4;
            else if (i <= 48)   tier = 3;
            else if (i <= 60)   tier = 2;
            else  tier = 1;

            Race race(player, tier);
            cout << "\n=== 레이스가 시작됩니다! ===\n";

            race.start();
            cout << "---------------------------------레이스 끝-----------------------\n";
            race.reward();
            getchar();
        }

        print_stat(i + 1, &player, trainer);
        Sleep(500);
        system("cls");
    }
    //최종레이스
    cout << "\n=== 최종 레이스가 시작됩니다! ===\n";
    Race race(player, 1);
    race.start();
    return 0;
}

horse select_horse() {
    int x = 46;

    gotoxy(x, 15);
    cout << "1. 도주마 사일런스 스즈카\n";
    gotoxy(x, 17);
    cout << "2. 선행마 마야노 탑건\n";
    gotoxy(x, 19);
    cout << "3. 선입마 오구리 캡\n";
    gotoxy(x, 21);
    cout << "4. 추입마 골드 쉽\n";
    gotoxy(x, 23);
    cout << "5. 커스텀 말 만들기\n";
    gotoxy(x, 25);
    cout << "시작마를 고르시오 (1 ~ 5): ";

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
        case 1: return horse("사일런스 스즈카", 0, startStat, startStat, startStat, startStat);
        case 2: return horse("마야노 탑건", 1, startStat, startStat, startStat, startStat);
        case 3: return horse("오구리 캡", 2, startStat, startStat, startStat, startStat);
        case 4: return horse("골드 쉽", 3, startStat, startStat, startStat, startStat);
        case 5: {//커스텀말 생성
            string name;
            int breed;

            cout << "\n[커스텀 말 생성]\n";
            cout << "이름을 입력하세요: ";
            cin.ignore(); // 버퍼 비우기
            getline(cin, name);

            cout << "경주 스타일을 선택하세요 (1: 도주, 2: 선행, 3: 선입, 4: 추입): ";
            while (!(cin >> breed) || breed < 1 || breed > 4) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "잘못된 선택입니다. 다시 입력해주세요 (1~4): ";
            }

            return horse(name, breed - 1, startStat, startStat, startStat, startStat);
        }
        default:
            cout << "잘못된 선택입니다. 다시 입력해주세요: ";
        }
    }
}

void print_stat(int month, horse* player, training& trainer);