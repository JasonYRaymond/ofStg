#include "Enemy.h"

void Enemy::setup(float max_enemy_shoot_interval, ofImage * enemy_image, string set_type, int x, int y, float set_angle) {
	pos.x = x;
	pos.y = y;
	start_pos.x = x;
	start_pos.y = y;
	img = enemy_image;
	width = img->getWidth();
	height = img->getHeight();
	speed = ofRandom(2, 7);
	shoot_interval = ofRandom(1, max_enemy_shoot_interval) + 2;
	start_shoot = ofGetElapsedTimef();
	type = set_type;
	angle = set_angle;
	start_angle = set_angle;
}

void Enemy::update() {
	/*
	pos.y += speed;
	pos.x += amplitude * sin(ofGetElapsedTimef());
	*/
	int radius = (int)(2 * ofGetHeight() / 3);
	if (type == "top left circular") {
		angle -= 0.01;
		pos.x = 0 + (int)(radius * cos(angle));
		pos.y = 0 + (int)(radius * sin(angle));
	} else if (type == "top right circular") {
		angle += 0.01;
		pos.x = ofGetWidth() + (int)(radius * cos(angle));
		pos.y = 0 + (int)(radius * sin(angle));
	} else if (type == "top down") {
		pos.y += 4;
	} else if (type == "left right") {
		pos.x += 6;
	} else if (type == "right left") {
		pos.x -= 6;
	} else if (type == "parabola left right") {
		pos.x += 6;
		int x_coord = pos.x - (int)(ofGetWidth() / 2);
		pos.y = -0.0002 * pow(x_coord, 2) + 0.0002 * pow((int) (ofGetWidth() / 2), 2);
	} else if (type == "parabola right left") {
		pos.x -= 6;
		int x_coord = pos.x - (int)(ofGetWidth() / 2);
		pos.y = -0.0002 * pow(x_coord, 2) + 0.0002 * pow((int)(ofGetWidth() / 2), 2);
	}
}

void Enemy::draw() {
	img->draw(pos.x - width / 2, pos.y - width / 2);
}

bool Enemy::time_to_shoot() {
	if (ofGetElapsedTimef() - start_shoot > shoot_interval) {
		start_shoot = ofGetElapsedTimef();
		return true;
	}
	return false;
}
