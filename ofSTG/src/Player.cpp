#include "Player.h"

void Player::initialize(ofImage *img) {
	this->img = img;
	width = img->getWidth();
	height = img->getHeight();
	pos.x = ofGetWindowWidth() / 2;
	pos.y = ofGetWindowHeight() - height / 2;
	speed = 9;
	lives = 1;
	is_shooting = false;
	start_shoot = ofGetElapsedTimef();
	shoot_interval = 0.3;
	left_pressed = false;
	right_pressed = false;
	up_pressed = false;
	down_pressed = false;
}

void Player::update() {
	if (left_pressed) {
		if (up_pressed) {
			if (pos.x - speed * sqrt(2) * 0.5 >= 0)
			{
				pos.x -= speed * sqrt(2) * 0.5;
			}
			if (pos.y - speed * sqrt(2) * 0.5 >= 0) 
			{
				pos.y -= speed * sqrt(2) * 0.5;
			}
		}
		else if (down_pressed) {
			if (pos.x - speed * sqrt(2) * 0.5 >= 0)
			{
				pos.x -= speed * sqrt(2) * 0.5;
			}
			if (pos.y + speed * sqrt(2) * 0.5 <= ofGetWindowHeight())
			{
				pos.y += speed * sqrt(2) * 0.5;
			}
		}
		else {
			if (pos.x - speed >= 0)
			{
				pos.x -= speed;
			}
		}
	}
	else if (right_pressed) {
		if (up_pressed) {
			if (pos.x + speed * sqrt(2) * 0.5 <= ofGetWindowWidth())
			{
				pos.x += speed * sqrt(2) * 0.5;
			}
			if (pos.y - speed * sqrt(2) * 0.5 >= 0)
			{
				pos.y -= speed * sqrt(2) * 0.5;
			}
		}
		else if (down_pressed) {
			if (pos.x + speed * sqrt(2) * 0.5 <= ofGetWindowWidth())
			{
				pos.x += speed * sqrt(2) * 0.5;
			}
			if (pos.y + speed * sqrt(2) * 0.5 <= ofGetWindowHeight())
			{
				pos.y += speed * sqrt(2) * 0.5;
			}
		}
		else {
			if (pos.x + speed <= ofGetWindowWidth())
			{
				pos.x += speed;
			}
		}
	}
	else if (up_pressed) {
		if (pos.y - speed >= 0)
		{
			pos.y -= speed;
		}
	}
	else if (down_pressed) {
		if (pos.y + speed <= ofGetWindowHeight())
		{
			pos.y += speed;
		}
	}
}
void Player::draw() {
	this->img->draw(pos.x - width / 2, pos.y - height / 2);
}
