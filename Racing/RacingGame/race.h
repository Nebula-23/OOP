﻿#pragma once
#include "race_info.h"
#include "canvas.h"
#include "horse.h"
#include "horse_name.h"
#include <array>
#include <algorithm>
#include <random>
#include <iomanip>
#include <vector>
#include <Windows.h>
//최종등수 아스키아트 불러올때 필요해서 추가
#include "final_reward.h"

using namespace std;

class Race {
private:
	static const int HORSE_COUNT = 7;

	horse& player;    // 실제 플레이어 참조
	Canvas canvas;    // canvas 생성
	Horse_name name;  // Horse_name 생성

	int lane = rand() % HORSE_COUNT; // 플레이어 라인 추첨;
	array<int, 6> cpu_type = { 0, 1, 1, 2, 2, 3 }; //cpu 특성 배열
	string h_breed = "";
	string turn[7] = { "", "" , "" , "" , "" , "", "" }; // 도착 턴 저장 배열

	horse horses[HORSE_COUNT];       // 빈 말 배열 생성
	bool finished[HORSE_COUNT] = {}; // 말이 결승선에 도착여부 확인

public:
	Race(horse& player, int tier) : player(player) { // 플레이어 말 입력, 현재 레이스 티어 입력
		horses[lane] = player; // 화면 표시용 복사본
		horses[lane].reset();  // 복사본 초기화

		canvas.set_player(lane); // 플레이어 마크 ★ 수정

		// CPU 타입 셔플
		std::mt19937 g(std::random_device{}());
		std::shuffle(cpu_type.begin(), cpu_type.end(), g);

		for (int i = 0, j = 0; i < HORSE_COUNT; i++) { // 말 생성
			if (i != lane) {
				int type = cpu_type[j];
				horses[i] = horse(name.get_name(type), type, tier); // cpu이름 생성로직 만들기
				j++;
			}
		}
	}

	//레이스 이름 표시
	void print_race_name(int race_index) {
		const std::string names[] = {
			"아카데미 지역리그", "아카데미 플레이오프", "아카데미 파이널",
			"컨퍼런스 그룹 스테이지", "컨퍼런스 녹아웃 스테이지", "컨퍼런스 챔피언십",
			"챔피언스 디비전", "챔피언스 세미파이널", "챔피언스 결승"
		};
		if (race_index >= 0 && race_index < 9) {
			std::cout << "\n=================================================\n";
			std::cout << "\t\t" << names[race_index] << "\n";
			std::cout << "=================================================\n\n";
		}
	}

	void tie_breaker(int rank) {
		vector<pair<double, int>> list; // pair인 vector list(거리, 말번호)

		for (int i = 0; i < HORSE_COUNT; i++) {
			if (horses[i].get_rank() == 0 && finished[i]) {
				double total = horses[i].get_position() + horses[i].get_decimal_point();
				list.emplace_back(total, i);  // 거리, 말 번호
			}
		}

		sort(list.rbegin(), list.rend()); // 거리 내림차순

		for (int i = 0; i < list.size(); i++) {
			int num = list[i].second;
			int total_rank = rank + i + 1;
			horses[num].set_rank(total_rank);
		}
	}

	void show_race_summary() { // 레이스 사전 정보 출력
		using RI = RaceInfo;

		const int COL_NUM_WIDTH = 6;
		const int COL_NAME_WIDTH = 20;
		const int COL_BREED_WIDTH = 12;
		const int COL_STAT_WIDTH = 8;

		cout
			<< RI::pad("번호", COL_NUM_WIDTH)
			<< RI::pad("이름", COL_NAME_WIDTH)
			<< RI::pad("주행 특성", COL_BREED_WIDTH)
			<< RI::pad("스피드", COL_STAT_WIDTH)
			<< RI::pad("파워", COL_STAT_WIDTH)
			<< RI::pad("지구력", COL_STAT_WIDTH)
			<< RI::pad("근성", COL_STAT_WIDTH)
			<< "\n";

		for (int i = 0; i < HORSE_COUNT; ++i) {
			switch (horses[i].get_breed())
			{
			case 0:
				h_breed = "도주마";
				break;
			case 1:
				h_breed = "선행마";
				break;
			case 2:
				h_breed = "선입마";
				break;
			case 3:
				h_breed = "추입마";
				break;
			}

			cout
				<< RI::pad(to_string(i + 1) + "번마", COL_NUM_WIDTH)
				<< RI::pad(horses[i].get_name(), COL_NAME_WIDTH)
				<< RI::pad(h_breed, COL_BREED_WIDTH)
				<< RI::pad(to_string(horses[i].get_spd()), COL_STAT_WIDTH)
				<< RI::pad(to_string(horses[i].get_pow()), COL_STAT_WIDTH)
				<< RI::pad(to_string(horses[i].get_sta()), COL_STAT_WIDTH)
				<< RI::pad(to_string(horses[i].get_guts()), COL_STAT_WIDTH)
				<< "\n";
		}
	}

	void show_race_rank() { // 레이스 등수 ui 출력
		using RI = RaceInfo;

		const int COL_NUM_WIDTH = 6;
		const int COL_NAME_WIDTH = 20;
		const int COL_BREED_WIDTH = 10;
		const int COL_RANK_WIDTH = 8;
		const int COL_TURN_WIDTH = 8;
		const int COL_ARRIVAL_WIDTH = 10;

		cout
			<< RI::pad("번호", COL_NUM_WIDTH)
			<< RI::pad("이름", COL_NAME_WIDTH)
			<< RI::pad("주행 특성", COL_BREED_WIDTH)
			<< RI::pad("등수", COL_RANK_WIDTH)
			//<< RI::pad("도착 턴", COL_TURN_WIDTH)
			//<< RI::pad("도착 거리", COL_ARRIVAL_WIDTH)
			<< "\n";

		for (int i = 0; i < HORSE_COUNT; ++i) {
			string h_num = to_string(i + 1) + "번마";
			string h_name = horses[i].get_name();

			switch (horses[i].get_breed())
			{
			case 0:
				h_breed = "도주마";
				break;
			case 1:
				h_breed = "선행마";
				break;
			case 2:
				h_breed = "선입마";
				break;
			case 3:
				h_breed = "추입마";
				break;
			}

			string h_rank = horses[i].get_rank() > 0
				? to_string(horses[i].get_rank()) + "등"
				: "";

			string h_turn = turn[i]; 

			string h_arrival = horses[i].get_rank() > 0
				? to_string(horses[i].get_position() + horses[i].get_decimal_point())
				: "";


			cout
				<< RI::pad(h_num, COL_NUM_WIDTH)
				<< RI::pad(h_name, COL_NAME_WIDTH)
				<< RI::pad(h_breed, COL_BREED_WIDTH)
				<< RI::pad(h_rank, COL_RANK_WIDTH)
				//<< RI::pad(h_turn, COL_TURN_WIDTH)
				//<< RI::pad(h_arrival, COL_ARRIVAL_WIDTH)
				<< "\n";
		}
	}

	void cpu_check() { // 사전 정보 출력
		canvas.printMap();   // 맵 출력
		show_race_summary(); // 레인별 능력치 보여주기
		cout << "\n레이스를 시작하려면 엔터를 눌러주세요.\n";
		getchar();
	}

	void restart_game() {//4등이하면 재시작하게 예외처리
		cout << "\n목표 등수에 도달하지 못했습니다...\n";
		cout << "게임을 다시 시작합니다...\n";
		getchar();
		throw std::runtime_error("RESTART");  // 예외로 재시작을 알림
	}

	void reward() { // 등수 보상 함수
		int rank = horses[lane].get_rank();
		player.set_rank(rank);  // player에 등수 기록

		switch (rank)
		{
		case 1:
			cout << "1등을 달성했습니다! (모든 능력치 +50)\n";
			player.set_spd(50);
			player.set_pow(50);
			player.set_sta(50);
			player.set_guts(50);
			break;

		case 2:
			cout << "2등을 달성했습니다! (모든 능력치 +30)\n";
			player.set_spd(30);
			player.set_pow(30);
			player.set_sta(30);
			player.set_guts(30);
			break;

		case 3:
			cout << "3등을 달성했습니다! (모든 능력치 +10)\n";
			player.set_spd(10);
			player.set_pow(10);
			player.set_sta(10);
			player.set_guts(10);
			break;

		default:
			restart_game();
			break;
		}

		cout << "시상식이 종료되었습니다.\n";
		cout << "훈련장으로 복귀합니다.\n";
		getchar();
		system("cls");
	}

	// 일차 받아와서 print_race_name에 넘겨주게 변경
	void start(int month) {
		system("cls");
		PlaySound(TEXT("BGM3.wav"), NULL, SND_ASYNC | SND_LOOP);
		print_race_name(month / 6 - 1);
		cpu_check();

		int finished_count = 0;
		int finished_turn = 0;

		while (finished_count < HORSE_COUNT) {
			finished_turn++;
			int rank = finished_count;

			system("cls");

			for (int i = 0; i < HORSE_COUNT; i++) {
				if (finished[i]) { continue; }

				horses[i].move(); // 말 이동

				int prev_pos = horses[i].get_prev_pos(); // 이전 위치
				int curr_pos = horses[i].get_position(); // 이동한 위치

				if (curr_pos >= 60) {
					canvas.set_tile(i, 60, prev_pos); // 결승선에 도달한 말 위치 고정
					finished[i] = true;
					turn[i] = to_string(finished_turn); // 도착 턴수 저장
					++finished_count;
				}

				else { canvas.set_tile(i, curr_pos, prev_pos); } // 일반 이동

				//cout << i + 1 << "이전 위치: " << horses[i].get_prev_pos() << " | 이동한 위치 " << horses[i].get_position() << " | 소수점 " << horses[i].get_decimal_point() << std::endl;

			}

			if (finished_count > rank) { tie_breaker(rank); }; //결승선을 넘은 말이 있을때만 실행.

			canvas.printMap();
			show_race_rank();
			getchar(); // sleep or getchar로 진행
			//Sleep(500);
		}
	}

	void final_reward() {//최종 등수 아스키아트 불러오기
		int rank = horses[lane].get_rank();
		player.set_rank(rank);  

		switch (rank) {
		case 1:
			show_win();
			break;
		case 2:
			show_se();
			break;
		case 3:
			show_th();
			break;
		default:
			show_go();
			break;
		}
	}
};