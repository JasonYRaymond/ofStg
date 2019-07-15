#pragma once
#include <ofMain.h>

class Controller
{
public:
	float start_time;
	float previous_time;
	float interval_time;
	//int spawn_times[26] = { 7380, 9230, 11070, 14760, 16610, 18460, 22150, 24000, 25840, 29530, 31380, 33230, 36920, 66460, 68300, 70150, 73840, 75690, 77530, 81230, 83070, 84920, 88610, 90460, 92300, 96000 };;
	int spawn_times[25] = { 7380, 1850, 1840 , 3630 , 1850 , 1850 , 3690 , 1850 , 1840 , 3690 , 1850 , 1850 , 33230, 1840 , 1850 , 3690 , 1850 , 1840 , 3700 , 1840 , 1850 , 3690 , 1850 , 1840 , 3700};
	int counter;

	void setup(float e);
	bool should_spawn();
	bool should_enter_midway();
	bool should_destroy_midway();
	bool should_enter_dialog();
};

