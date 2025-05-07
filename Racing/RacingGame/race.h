#pragma once
#include"canvas.h"
#include"horse.h"
#include"horse_name.h"
#include <array>
#include <algorithm>
#include <random>
#include <Windows.h>

class Race {
private:
    static const int HORSE_COUNT = 7;

    // canvas, Horse_name 생성
    Canvas canvas;
    Horse_name name;

    int lane = rand() % HORSE_COUNT; // 플레이어 라인 추첨;
    std::array<int, 6> cpu_type = { 0, 1, 1, 2, 2, 3 }; //cpu 특성 배열

    horse horses[HORSE_COUNT];       // 빈 말 배열 생성
    bool finished[HORSE_COUNT] = {}; // 말이 결승선에 도착여부 확인

public:
    Race(const horse& player, int tier) { // 플레이어 말 입력, 현재 레이스 티어 입력
        horses[lane] = player; // 플레이어 말 저장
        horses[lane].reset(); // 플레이어 등수 상태 초기화

        // CPU 타입 셔플
        std::mt19937 g(std::random_device{}());
        std::shuffle(cpu_type.begin(), cpu_type.end(), g);

        for (int i = 0, j = 0; i < HORSE_COUNT; i++) { // 말 생성
            if (i != lane)
                horses[i] = horse(name.get_name(cpu_type[j]), cpu_type[j++], tier); // cpu이름 생성로직 만들기
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

    void show_race_summary() {
        for (int i = 0; i < HORSE_COUNT; ++i) {
            std::cout << i + 1 << "레인 | " << horses[i].get_name();

            if (horses[i].get_rank() > 0) { // 등수가 있는 경우에만 등수 출력
                std::cout << " | 등수: " << horses[i].get_rank();
            }

            std::cout << '\n';
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

                std::cout << i << " 이전 위치: " << horses[i].get_prev_pos() << " | 이동한 위치 " << horses[i].get_position() << std::endl;

                if (curr_pos >= 60) {
                    canvas.set_tile(i, 60, prev_pos); // 결승선에 도달한 말 위치 고정
                    finished[i] = true;
                    ++finished_count;
                    tie_breaker();
                }

                else {
                    canvas.set_tile(i, curr_pos, prev_pos); // 일반 이동 처리
                }

                //보상 함수 만들어야함
            }

            canvas.printMap();
            show_race_summary();
            getchar();
            system("cls");
            //Sleep(500);

        }
    }
};
