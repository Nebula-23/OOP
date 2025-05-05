#include "horse.h"
#include "training.h"

#include <iostream>
#include <ctime>
#include <Windows.h>

const int MAX_MONTH = 36;
const int startStat = 100.0;

using namespace std;

horse select_horse();
void print_basic(int month, horse* player, training& trainer);

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    horse player = select_horse();
    // 트레이너 객체 생성
    training trainer(player);

    Sleep(500);
    system("cls");

    for (int i = 0; i < MAX_MONTH; i++) {
        print_basic(i,&player,trainer);
        Sleep(500);
        system("cls");
    }

    return 0;
}

horse select_horse() {
    cout << "1. 도주마 세크리테리엇\n" 
        << "2. 선행마 트리플 크라운\n" //이름확인필요 
        << "3. 선입마 오르페브르\n"
        << "4. 추입마 골드 쉽\n"
        << "시작마를 고르시오 (1 ~ 4): ";

    while (true) {
        int n;
        cin >> n;
        if (cin.fail()) {
            cin.clear(); // fail 플래그 초기화
            cin.ignore(1000, '\n'); // 버퍼 비우기 (엔터까지 무시)
            cout << "숫자만 입력해주세요: ";
            continue;
        }
        switch (n) {
        case 1: return horse("aaa",0, startStat, startStat, startStat, startStat);
        case 2: return horse("aaa", 1, startStat, startStat, startStat, startStat);
        case 3: return horse("aaa", 2, startStat, startStat, startStat, startStat);
        case 4: return horse("aaa", 3, startStat, startStat, startStat, startStat);
        default:
            cout << "잘못된 선택입니다. 다시 입력해주세요: ";
            continue;
        }
    }
}

void print_basic(int month, horse* player, training& trainer) {
    cout << "=============================================\n"
        << "Month " << month << " / " << MAX_MONTH << "\n";
    cout << "=============================================\n\n";

    cout << "부상확률 : " << trainer.injury_percent(*player) << "%\n\n";

    cout << "1) 스피드 훈련\t2) 파워 훈련\t3) 근성 훈련\t4) 지구력 훈련\t5) 휴식\n";
    while (true) {
        int n;
        cin >> n;
        if (cin.fail()) {
            cin.clear(); // fail 플래그 초기화
            cin.ignore(1000, '\n'); // 버퍼 비우기 (엔터까지 무시)
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
            continue;
        }
    }
}
