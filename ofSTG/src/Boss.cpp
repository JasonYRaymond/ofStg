#include "Boss.h"
#include "Bullet.h"

void Boss::setup(ofImage * enemy_image, string set_type, int x, int y) {
	pos.x = x;
	pos.y = y;
	start_pos.x = x;
	start_pos.y = y;
	img = enemy_image;
	width = img->getWidth();
	height = img->getHeight();
	start_shoot = ofGetElapsedTimef();
	type = set_type;
	if (set_type == "midway") {
		shoot_interval = 2;
		hp = 10000;
		life = 1;
	}
	else if (set_type == "last boss") {
		shoot_interval = 2;
		hp = 40;
		life = 4;
	}
}

void Boss::update(string mode) {
	if (mode == "enter") {
		if (type == "midway") {
			if (pos.y < ofGetHeight() / 6) {
				pos.y += 6;
			}
		}
		else if (type == "last boss") {
			pos.y += 10;
		}
	}
	if (mode == "exit") {
		if (type == "midway") {
			if (pos.y > -1 * height) {
				pos.y -= 2;
			}
		}
	}
}

bool Boss::time_to_shoot() {
	if ((pos.y >= ofGetHeight() / 6 || type == "last boss") && ofGetElapsedTimef() - start_shoot > shoot_interval) {
		start_shoot = ofGetElapsedTimef();
		return true;
	}
	return false;
}

void Boss::draw() {
	img->draw(pos.x - width / 2, pos.y - width / 2);
}
