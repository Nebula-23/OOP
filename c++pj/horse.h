#pragma once
#ifndef HORSE_H
#define HORSE_H
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

#define BASELINE 1000 

enum HorseType {PLAYER, CPU};

class horse {
private:
	HorseType type;
	int spd = 0;
	int pow = 0;
	int sta = 0;
	int guts = 0;

	std::string name;
	int breed;

	int prev_pos = 0;
	int curr_pos = 0;
	double decimal_point = 0.0;

protected:
	double breed_mod[3];
	double stat_mod[3];

public:

	horse(std::string name, int breed, int tier)
		: type(CPU), name(name), breed(breed) {
		set_ai_stats(breed, tier);
		set_modifiers(breed);
	}

	horse(std::string name, int breed, int spd, int pow, int sta, int guts)
		: type(PLAYER), name(name), breed(breed), spd(spd), pow(pow), sta(sta), guts(guts) {
		set_modifiers(breed);
	}

	void set_ai_stats(int breed, int tier) {
		switch (breed)
		{
		case 0: spd = (1100 + rand() % 101) / tier;
			pow = (1000 + rand() % 101) / tier;
			sta = (750 + rand() % 101) / tier;
			guts = (650 + rand() % 101) / tier;
			break;
		case 1: spd = (1050 + rand() % 101) / tier;
			pow = (900 + rand() % 101) / tier;
			sta = (950 + rand() % 101) / tier;
			guts = (800 + rand() % 101) / tier; break;
		case 2: spd = (950 + rand() % 101) / tier;
			pow = (850 + rand() % 101) / tier;
			sta = (1000 + rand() % 101) / tier;
			guts = (850 + rand() % 101) / tier; break;
		case 3: spd = (900 + rand() % 101) / tier;
			pow = (800 + rand() % 101) / tier;
			sta = (900 + rand() % 101) / tier;
			guts = (1100 + rand() % 101) / tier; break;
		}

	} //

	void set_modifiers(int breed)
	{
		static double s_mod[4][3] =
		{
			{1.5, 1.3, 1.2},
			{1.4, 1.4, 1.2},
			{1.3, 1.4, 1.3},
			{1.2, 1.3, 1.5}
		};
		static double b_mod[4][3] =
		{
			{1.9, 1.7, 1.4},
			{1.8, 1.8, 1.6},
			{1.6, 1.8, 1.8},
			{1.4, 1.7, 1.9}
		};
		for (int i = 0; i < 3; ++i) {
			stat_mod[i] = s_mod[breed][i];
			breed_mod[i] = b_mod[breed][i];
		}
	}


	//getter
	std::string get_name() { return name; }
	int get_spd() { return spd; }
	int get_pow() { return pow; }
	int get_sta() { return sta; }
	int get_guts() { return guts; }
	int get_breed() { return breed; }

	//setter
	void set_spd(int n) { this->spd += n; }
	void set_pow(int n) { this->pow += n; }
	void set_sta(int n) { this->sta += n; }
	void set_guts(int n) { this->guts += n; }

	int position() const {
		if (curr_pos <= 19) return 0;
		else if (curr_pos <= 39) return 1;
		else return 2;
	}

	void move()
	{
		int stat_by_section[3] = { pow, sta, guts };

		int seg = position();

		double base_speed = static_cast<double>(stat_by_section[seg]) / BASELINE;
		double random_factor = 2.5 + (rand() % 11) / 10.0;

		double stat_ratio = static_cast<double>(stat_by_section[seg]) / BASELINE;
		double stat_bonus = stat_ratio * stat_mod[seg];
		double breed_bonus = breed_mod[seg] * stat_bonus;

		double move_distance = base_speed * random_factor + breed_bonus + decimal_point;

		decimal_point = fmod(move_distance, 1.0); // 소수점 이하를 저장	

		prev_pos = curr_pos; // 이전 위치 저장
		curr_pos += static_cast<int>(move_distance); // 현재 위치 업데이트	


	}

	int get_position() const { return curr_pos; }
};


#endif // !PHORSE_H
