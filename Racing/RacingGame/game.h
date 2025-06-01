#pragma once
#include "race.h"
#include "training.h"
#include "UI.h"
#include <windows.h>

inline void play_game(horse& player) {
    training trainer(player);
    const string names[] = {
    "아카데미 지역리그", "아카데미 플레이오프", "아카데미 파이널",
    "컨퍼런스 그룹 스테이지", "컨퍼런스 녹아웃 스테이지", "컨퍼런스 챔피언십",
    "챔피언스 디비전", "챔피언스 세미파이널", "챔피언스 결승전"
    };

    Sleep(500);
    system("cls");
    //첫 레이스 전 훈련BGM 실행
    PlaySound(TEXT("BGM2.wav"), NULL, SND_ASYNC | SND_LOOP);

    for (int i = 0; i < MAX_MONTH; i++) {
        if ((i != 0 && i % 6 == 0) || (i == MAX_MONTH - 1)) {
            int tier = 10 - (i / 6);
            if (tier < 1) tier = 1;

            int race_index = 9 - tier;

            Race race(player, tier);
            if (race_index >= 0 && race_index < 9) {
                cout << "=================================================\n";
                if (tier == 1 && i == MAX_MONTH - 1) {
                    cout << "\n=== 최종 레이스가 시작됩니다! ===\n";
                }
                cout << "\t\t" << names[race_index] << "\n";
                cout << "=================================================\n\n";
            }

            race.start(tier);
            cout << "-----------------------레이스 종료-----------------------\n";

            if (tier == 1 && i == MAX_MONTH - 1) {
                race.final_reward();
            }
            else {
                race.reward();
            }

            PlaySound(TEXT("BGM2.wav"), NULL, SND_ASYNC | SND_LOOP);
        }

        print_stat(i + 1, &player, trainer);
        Sleep(1000);
        system("cls");
    }


}
