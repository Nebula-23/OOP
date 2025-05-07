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

    // canvas, Horse_name ����
    Canvas canvas;
    Horse_name name;

    int lane = rand() % HORSE_COUNT; // �÷��̾� ���� ��÷;
    std::array<int, 6> cpu_type = { 0, 1, 1, 2, 2, 3 }; //cpu Ư�� �迭

    horse horses[HORSE_COUNT];       // �� �� �迭 ����
    bool finished[HORSE_COUNT] = {}; // ���� ��¼��� �������� Ȯ��

public:
    Race(const horse& player, int tier) { // �÷��̾� �� �Է�, ���� ���̽� Ƽ�� �Է�
        horses[lane] = player; // �÷��̾� �� ����
        horses[lane].reset(); // �÷��̾� ��� ���� �ʱ�ȭ

        // CPU Ÿ�� ����
        std::mt19937 g(std::random_device{}());
        std::shuffle(cpu_type.begin(), cpu_type.end(), g);

        for (int i = 0, j = 0; i < HORSE_COUNT; i++) { // �� ����
            if (i != lane)
                horses[i] = horse(name.get_name(cpu_type[j]), cpu_type[j++], tier); // cpu�̸� �������� �����
        }
    }

    void tie_breaker() { // ������ �˻�
        for (int i = 0; i < HORSE_COUNT; i++) {
            if (finished[i]) { // ��¼��� ������ ���� ��� ���
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
            std::cout << i + 1 << "���� | " << horses[i].get_name();

            if (horses[i].get_rank() > 0) { // ����� �ִ� ��쿡�� ��� ���
                std::cout << " | ���: " << horses[i].get_rank();
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

                horses[i].move(); // �� �̵�

                int prev_pos = horses[i].get_prev_pos(); // ���� ��ġ
                int curr_pos = horses[i].get_position(); // �̵��� ��ġ

                std::cout << i << " ���� ��ġ: " << horses[i].get_prev_pos() << " | �̵��� ��ġ " << horses[i].get_position() << std::endl;

                if (curr_pos >= 60) {
                    canvas.set_tile(i, 60, prev_pos); // ��¼��� ������ �� ��ġ ����
                    finished[i] = true;
                    ++finished_count;
                    tie_breaker();
                }

                else {
                    canvas.set_tile(i, curr_pos, prev_pos); // �Ϲ� �̵� ó��
                }

                //���� �Լ� ��������
            }

            canvas.printMap();
            show_race_summary();
            getchar();
            system("cls");
            //Sleep(500);

        }
    }
};
