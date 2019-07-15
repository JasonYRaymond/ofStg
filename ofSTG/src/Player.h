#pragma once
#include "ofMain.h"
#include <math.h>

class Player
{
public:

	ofPoint pos;
	float width, height;
	float speed;
	int lives;
	bool left_pressed, right_pressed, up_pressed, down_pressed;
	
	void initialize(ofImage *img);
	void update();
	void draw();
	
	float start_shoot;
	float shoot_interval;

	bool can_shoot;
	bool is_shooting;

	ofImage *img;
};

