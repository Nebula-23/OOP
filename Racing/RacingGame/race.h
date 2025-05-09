#pragma once
#include "canvas.h"
#include "horse.h"
#include "horse_name.h"
#include <array>
#include <algorithm>
#include <random>
#include <Windows.h>

class Race {
private:
    static const int HORSE_COUNT = 7;
    
    horse& player;    // 실제 플레이어 참조
    Canvas canvas;    // canvas 생성
    Horse_name name;  // Horse_name 생성

    int lane = rand() % HORSE_COUNT; // 플레이어 라인 추첨;
    std::array<int, 6> cpu_type = { 0, 1, 1, 2, 2, 3 }; //cpu 특성 배열

    horse horses[HORSE_COUNT];       // 빈 말 배열 생성
    bool finished[HORSE_COUNT] = {}; // 말이 결승선에 도착여부 확인

public:
    Race(horse& player, int tier) : player(player) { // 플레이어 말 입력, 현재 레이스 티어 입력
        horses[lane] = player; // 화면 표시용 복사본
        horses[lane].reset();  // 복사본 초기화

        // CPU 타입 셔플
        std::mt19937 g(std::random_device{}());
        std::shuffle(cpu_type.begin(), cpu_type.end(), g);

        for (int i = 0, j = 0; i < HORSE_COUNT; i++) { // 말 생성
            if (i != lane){
                int type = cpu_type[j];
                horses[i] = horse(name.get_name(type), type, tier); // cpu이름 생성로직 만들기
                j++;
            }
        }
    }

    void tie_breaker() { // 동석차 검사
        for (int i = 0; i < HORSE_COUNT; i++) {
            if (finished[i]) { // 결승선에 도달한 말만 등수 계산
                int rank = 1;
                for (int j = 0; j < HORSE_COUNT; j++) {
                    if (finished[j] && horses[i].get_position() < horses[j].get_position()) {
                        rank++;
                    }
                }
                horses[i].set_rank(rank);
            }
        }
    }

    void show_race_summary() { //레인 및 등수 출력
        for (int i = 0; i < HORSE_COUNT; ++i) {
            std::cout << i + 1 << "레인 | " << horses[i].get_name();

            if (horses[i].get_rank() > 0) { // 등수가 있는 경우에만 등수 출력
                std::cout << " | 등수: " << horses[i].get_rank();
            }

            std::cout << '\n';
        }
    }

    void reward() { // 등수 보상 함수 -> 수치는 나중에 밸런싱
        int rank = horses[lane].get_rank();
        player.set_rank(rank);  // player에 등수 기록

        switch (rank)
        {
        case 1:
            std::cout << "1등을 달성했습니다! (모든 능력치 +100)\n";
            player.set_spd(100);
            player.set_pow(100);
            player.set_sta(100);
            player.set_guts(100);
            break;

        case 2:
            std::cout << "2등을 달성했습니다! (모든 능력치 +70)\n";
            player.set_spd(70);
            player.set_pow(70);
            player.set_sta(70);
            player.set_guts(70);
            break;

        case 3:
            std::cout << "3등을 달성했습니다! (모든 능력치 +40)\n";
            player.set_spd(40);
            player.set_pow(40);
            player.set_sta(40);
            player.set_guts(40);
            break;

        case 4:
            std::cout << "4등을 달성했습니다! (모든 능력치 +10)\n";
            player.set_spd(10);
            player.set_pow(10);
            player.set_sta(10);
            player.set_guts(10);
            break;

        default:
            std::cout << "목표 등수에 도달하지 못했습니다...\n";
            // 게임종료 함수 실행?
            break;
        }
    }

    void start() {
        int finished_count = 0;

        while (finished_count < HORSE_COUNT) {
            for (int i = 0; i < HORSE_COUNT; ++i) {
                if (finished[i]) {
                    horses[i].add_position(100);
                    continue;
                }

                horses[i].move(); // 말 이동

                int prev_pos = horses[i].get_prev_pos(); // 이전 위치
                int curr_pos = horses[i].get_position(); // 이동한 위치

                std::cout << i << "이전 위치: " << horses[i].get_prev_pos() << " | 이동한 위치 " << horses[i].get_position() << std::endl;

                if (curr_pos >= 60) {
                    canvas.set_tile(i, 60, prev_pos); // 결승선에 도달한 말 위치 고정
                    finished[i] = true;
                    ++finished_count;
                    tie_breaker();
                }

                else {
                    canvas.set_tile(i, curr_pos, prev_pos); // 일반 이동 처리
                }
            }

            canvas.printMap();
            show_race_summary();
            getchar(); // 디버그용
            //system("cls");
            //Sleep(500);

        }
    }
};

