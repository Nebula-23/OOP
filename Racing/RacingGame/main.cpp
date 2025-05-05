#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "horse.h"
#include "training.h"
#include "race.h"
#include "UI.h"

const int MAX_MONTH = 72;
const int startStat = 100.0;

using namespace std;

horse select_horse();
void print_basic(int month, horse* player, training& trainer);

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    init_console_size();  // 콘솔 크기 초기화

    int menuChoice = menuDraw(); // 시작 화면 메뉴 표시
    if (menuChoice == 3) {
        cout << "게임을 종료합니다." << endl;
        return 0;
    }

    horse player = select_horse();
    training trainer(player);

    Sleep(500);
    system("cls");
    //6턴 진행후 레이스, 갈수록 CPU말의 티어가 상승
    for (int month = 0; month < MAX_MONTH; month++) {
        if (month != 0 && month % 6 == 0) {
            cout << "\n=== 레이스가 시작됩니다! ===\n";

            int tier = 1; // 기본값
            if (month <= 12)        tier = 6;
            else if (month <= 24)   tier = 5;
            else if (month <= 36)   tier = 4;
            else if (month <= 48)   tier = 3;
            else if (month <= 60)   tier = 2;
            else  tier = 1;

            Race race(player, tier);
            race.start();
        }

        print_basic(month + 1, &player, trainer);
        Sleep(1000);
        system("cls");
    }

    //최종레이스
    cout << "\n=== 최종 레이스가 시작됩니다! ===\n";
    Race race(player, 1);
    race.start();

    //게임 종료
    cout << "\n[ 게임이 종료되었습니다 ]\n";
    return 0;
}
 //말선택
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

//메인 게임 UI
void print_basic(int month, horse* player, training& trainer) {
    //년차 , D-Day, 말품종 표시 함수
    int display_year = (month % 24 == 0 && month != 0) ? month / 24 : month / 24 + 1;
    
    int d_day = (month % 6 == 0) ? 0 : 6 - (month % 6);
    
    string breed_str;
    switch (player->get_breed()) {
    case 0: breed_str = "도주마"; break;
    case 1: breed_str = "선행마"; break;
    case 2: breed_str = "선입마"; break;
    case 3: breed_str = "추입마"; break;
    default: breed_str = "알 수 없음"; break;
    }

    

    cout << "[ " << display_year << "년차 ]" << endl;
    cout << "===============================================\n"
        << player->get_name() << " | " << breed_str << " | " << month << " turn |" << " 레이스 D-" << d_day << "\n"
        << "===============================================\n";
    cout << "스피드: " << player->get_spd() << "  파워: " << player->get_pow()<<"\n";
    cout << "근성: " << player->get_guts() << " 지구력: " << player->get_sta() << "\n";
   

    cout <<"채력: "<< trainer.get_hp() << "  부상확률 : " << trainer.injury_percent(*player) << "%\n\n";

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
