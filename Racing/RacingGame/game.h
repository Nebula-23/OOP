#pragma once
#include "race.h"
#include "training.h"
#include "UI.h"
#include <windows.h>

inline void play_game(horse& player) {
    training trainer(player);

    Sleep(500);
    system("cls");

    PlaySound(TEXT("BGM2.wav"), NULL, SND_ASYNC | SND_LOOP);

    for (int i = 0; i < MAX_MONTH; i++) {
        // 티어 계산
        if (i != 0 && i % 6 == 0) {
            int tier;
            if (i <= 12)        tier = 6;
            else if (i <= 24)   tier = 5;
            else if (i <= 36)   tier = 4;
            else if (i <= 48)   tier = 3;
            else if (i <= 60)   tier = 2;
            else                tier = 1;

            Race race(player, tier);
            std::cout << "\n=== 레이스가 시작됩니다! ===\n";
            race.start();
            std::cout << "-----------------------레이스 종료-----------------------\n";
            race.reward();
        }

        print_stat(i + 1, &player, trainer);
        Sleep(500);
        system("cls");
    }

    std::cout << "\n=== 최종 레이스가 시작됩니다! ===\n";
    Race race(player, 1);
    race.start();
}