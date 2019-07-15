#pragma once
#include <ofMain.h>

class Boss
{
public:
	ofPoint pos;
	ofPoint start_pos;
	float width;
	float height;
	int hp;
	int life;
	string type;

	float start_shoot;
	float shoot_interval;

	void setup(ofImage * boss_image, string set_type, int x, int y);
	void update(string mode);
	bool time_to_shoot();
	void draw();

	ofImage * img;
};

