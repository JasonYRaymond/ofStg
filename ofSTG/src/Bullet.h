#pragma once
#include "ofMain.h"
#include "ofxAnimatableOfPoint.h"

class Bullet
{
public:
	ofPoint pos;
	float speed;
	float width;
	string from;
	int spawn_time;
	int max_stay_time;
	ofxAnimatableOfPoint boss_bullet_tracker;

	void setup(string set_from, ofPoint p, float s, ofImage *bullet_image, int spawn);
	void set_tracker(ofxAnimatableOfPoint& set_tracker);
	void update();
	void draw();
	bool should_be_destroyed();

	ofImage *img;
};