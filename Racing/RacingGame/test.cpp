#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "horse.h"
#include "training.h"
#include "race.h"

const int MAX_MONTH = 36;
const int startStat = 100.0;

using namespace std;

horse select_horse();
void print_basic(int month, horse* player, training& trainer);

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    horse player = select_horse();
    training trainer(player);

    Sleep(500);
    system("cls");

    for (int month = 0; month < MAX_MONTH; month++) {
        cout << "[ " << month + 1 << "개월차 진행 중... ]" << endl;

        // 6개월마다 레이스
        if ((month + 1) % 6 == 0) {
            cout << "\n===  레이스가 시작됩니다!  ===\n";
            Race race(player, 1); // tier는 1로 예시
            race.start();
            Sleep(1000);
            system("cls");
        }

        // 훈련 루틴
        print_basic(month + 1, &player, trainer);
        Sleep(1000);
        system("cls");
    }

    cout << "\n[  36개월 간의 훈련 및 경주가 종료되었습니다! 수고하셨습니다  ]\n";
    return 0;
}

horse select_horse() {
    cout << "1. 도주마 사일런스 스즈카\n"
        << "2. 선행마 마야노 탑건\n"
        << "3. 선입마 오구리 캡\n"
        << "4. 추입마 골드 쉽\n"
        << "시작마를 고르시오 (1 ~ 4): ";

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
        default:
            cout << "잘못된 선택입니다. 다시 입력해주세요: ";
            continue;
        }
    }
}

void print_basic(int month, horse* player, training& trainer) {
    cout << "=============================================\n"
        << "Month " << month << " / " << MAX_MONTH << "\n"
        << "=============================================\n\n";

    cout << "부상확률 : " << trainer.injury_percent(*player) << "%\n\n";

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
        case 1: trainer.training_speed(*player);        return;
        case 2: trainer.training_power(*player);        return;
        case 3: trainer.training_perseverance(*player); return;
        case 4: trainer.training_endurance(*player);    return;
        case 5: trainer.rest(*player);                  return;
        default:
            cout << "잘못된 선택입니다. 다시 입력해주세요: ";
            continue;
        }
    }
}
