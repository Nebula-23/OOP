#pragma once
#include "race.h"
#include "training.h"
#include "UI.h"
#include "Sound.h"
#include <windows.h>

inline void play_game(horse& player) {
    training trainer(player);

    Sleep(500);
    system("cls");

    PlaySound(TEXT("BGM2.wav"), NULL, SND_ASYNC | SND_LOOP);

    for (int i = 0; i < MAX_MONTH; i++) {
        // 티어 계산
        if (i != 0 && i % 6 == 0) {
            //매경기마다 티어 1한단계씩 올라감
            int tier = 10 - (i / 6);
            // 최소 티어는 1로 보장
            if (tier < 1) tier = 1;

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