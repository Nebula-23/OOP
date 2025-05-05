#include "horse.h"
#include "training.h"
#include "UI.h"
#include <iostream>
#include <ctime>
#include <Windows.h>

const int MAX_MONTH = 36;
const int startStat = 100.0;

using namespace std;

horse select_horse();
void print_basic(int month, horse* player, training& trainer);

int main() { //cols 가로 , lines 세로 cols=140 lines=30
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
        print_basic(i, &player, trainer);
        Sleep(500);
        system("cls");
    }

    return 0;
}

horse select_horse() {
    int x = 46;
   
    gotoxy(x,15);
    cout << "1. 도주마 세크리테리엇\n";
    gotoxy(x, 17);
    cout << "2. 선행마 트리플 크라운\n"; //이름확인필요
    gotoxy(x, 19);
    cout << "3. 선입마 오르페브르\n";
    gotoxy(x, 21);
    cout << "4. 추입마 골드 쉽\n";
    gotoxy(x, 23);
    cout << "시작마를 고르시오 (1 ~ 4): ";

    while (true) {
        int n;
        cin >> n;
        switch (n) {
        case 1: return horse("aaa", 0, startStat, startStat, startStat, startStat);
        case 2: return horse("aaa", 1, startStat, startStat, startStat, startStat);
        case 3: return horse("aaa", 2, startStat, startStat, startStat, startStat);
        case 4: return horse("aaa", 3, startStat, startStat, startStat, startStat);
        default:
            cout << "잘못된 선택입니다. 다시 입력해주세요: ";
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
