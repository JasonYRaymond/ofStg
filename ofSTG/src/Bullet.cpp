#include "Bullet.h"

void Bullet::setup(string set_from, ofPoint p, float s, ofImage * bullet_image, int spawn) {
	from = set_from;
	pos = p;
	speed = s + 3;
	img = bullet_image;
	width = img->getWidth();
	spawn_time = spawn;
	max_stay_time = 3500;
}

void Bullet::set_tracker(ofxAnimatableOfPoint& set_tracker) {
	boss_bullet_tracker = set_tracker;
}

void Bullet::update() {
	if (from == "player") {
		pos.y -= speed;
	}
	else if (from == "enemy") {
		pos.y += speed;
	}
	else if (from == "midway") {
		float xdiff = pos.x - ofGetWidth() / 2;
		float ydiff = pos.y- ofGetHeight() / 6;
		float angle = atan(ydiff / xdiff);
		pos.x += (int)((xdiff / abs(xdiff)) * 10 * abs(cos(angle)));
		pos.y += (int)((ydiff / abs(ydiff)) * 10 * abs(sin(angle)));
	}
	else if (from == "last boss") {
		boss_bullet_tracker.update(1.0f / 100.0f);
		pos.x = boss_bullet_tracker.getCurrentPosition().x;
		pos.y = boss_bullet_tracker.getCurrentPosition().y;
	}
}
void Bullet::draw() {
	img->draw(pos.x - width / 2, pos.y - width / 2);
}

bool Bullet::should_be_destroyed() {
	if (from == "last boss" && ofGetElapsedTimeMillis() - spawn_time >= max_stay_time) {
		return true;
	}
	return false;
}