#pragma once
#include <ofMain.h>

using std::string;

class Enemy
{
public:
	ofPoint pos;
	ofPoint start_pos;
	float speed;
	float width;
	float height;
	float angle;
	float start_angle;
	string type;

	float start_shoot;
	float shoot_interval;

	void setup(float max_enemy_shoot_interval, ofImage * enemy_image, string set_type, int x, int y, float set_angle);
	void update();
	void draw();
	bool time_to_shoot();

	ofImage * img;
};

