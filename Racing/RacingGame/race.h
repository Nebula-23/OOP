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
    
    horse& player;    // ���� �÷��̾� ����
    Canvas canvas;    // canvas ����
    Horse_name name;  // Horse_name ����

    int lane = rand() % HORSE_COUNT; // �÷��̾� ���� ��÷;
    std::array<int, 6> cpu_type = { 0, 1, 1, 2, 2, 3 }; //cpu Ư�� �迭

    horse horses[HORSE_COUNT];       // �� �� �迭 ����
    bool finished[HORSE_COUNT] = {}; // ���� ��¼��� �������� Ȯ��

public:
    Race(horse& player, int tier) : player(player) { // �÷��̾� �� �Է�, ���� ���̽� Ƽ�� �Է�
        horses[lane] = player; // ȭ�� ǥ�ÿ� ���纻
        horses[lane].reset();  // ���纻 �ʱ�ȭ

        // CPU Ÿ�� ����
        std::mt19937 g(std::random_device{}());
        std::shuffle(cpu_type.begin(), cpu_type.end(), g);

        for (int i = 0, j = 0; i < HORSE_COUNT; i++) { // �� ����
            if (i != lane){
                int type = cpu_type[j];
                horses[i] = horse(name.get_name(type), type, tier); // cpu�̸� �������� �����
                j++;
            }
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

    void show_race_summary() { //���� �� ��� ���
        for (int i = 0; i < HORSE_COUNT; ++i) {
            std::cout << i + 1 << "���� | " << horses[i].get_name();

            if (horses[i].get_rank() > 0) { // ����� �ִ� ��쿡�� ��� ���
                std::cout << " | ���: " << horses[i].get_rank();
            }

            std::cout << '\n';
        }
    }

    void reward() { // ��� ���� �Լ� -> ��ġ�� ���߿� �뷱��
        int rank = horses[lane].get_rank();
        player.set_rank(rank);  // player�� ��� ���

        switch (rank)
        {
        case 1:
            std::cout << "1���� �޼��߽��ϴ�! (��� �ɷ�ġ +100)\n";
            player.set_spd(100);
            player.set_pow(100);
            player.set_sta(100);
            player.set_guts(100);
            break;

        case 2:
            std::cout << "2���� �޼��߽��ϴ�! (��� �ɷ�ġ +70)\n";
            player.set_spd(70);
            player.set_pow(70);
            player.set_sta(70);
            player.set_guts(70);
            break;

        case 3:
            std::cout << "3���� �޼��߽��ϴ�! (��� �ɷ�ġ +40)\n";
            player.set_spd(40);
            player.set_pow(40);
            player.set_sta(40);
            player.set_guts(40);
            break;

        case 4:
            std::cout << "4���� �޼��߽��ϴ�! (��� �ɷ�ġ +10)\n";
            player.set_spd(10);
            player.set_pow(10);
            player.set_sta(10);
            player.set_guts(10);
            break;

        default:
            std::cout << "��ǥ ����� �������� ���߽��ϴ�...\n";
            // �������� �Լ� ����?
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

                horses[i].move(); // �� �̵�

                int prev_pos = horses[i].get_prev_pos(); // ���� ��ġ
                int curr_pos = horses[i].get_position(); // �̵��� ��ġ

                std::cout << i << "���� ��ġ: " << horses[i].get_prev_pos() << " | �̵��� ��ġ " << horses[i].get_position() << std::endl;

                if (curr_pos >= 60) {
                    canvas.set_tile(i, 60, prev_pos); // ��¼��� ������ �� ��ġ ����
                    finished[i] = true;
                    ++finished_count;
                    tie_breaker();
                }

                else {
                    canvas.set_tile(i, curr_pos, prev_pos); // �Ϲ� �̵� ó��
                }
            }

            canvas.printMap();
            show_race_summary();
            getchar(); // ����׿�
            //system("cls");
            //Sleep(500);

        }
    }
};

