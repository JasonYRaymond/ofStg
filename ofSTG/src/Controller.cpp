#include "Controller.h"

void Controller::setup(float s) {
	start_time = s;
	previous_time = s;
	interval_time = 200;
	counter = 0;
}
bool Controller::should_spawn() {
	/*
	if (ofGetElapsedTimeMillis() - start_time > interval_time) {
		start_time = ofGetElapsedTimeMillis();
		return true;
	}
	*/
	/*
	for (int i = 0; i < 26; i++) {
		if ((int) ofGetElapsedTimeMillis() - (int) start_time == spawn_times[i]) {
			return true;
		}
	}
	*/
	if (counter >= 25) {
		return false;
	}

	if (ofGetElapsedTimeMillis() - previous_time > spawn_times[counter]) {
		counter += 1;
		previous_time = ofGetElapsedTimeMillis();
		return true;
	}
	return false;
}

bool Controller::should_enter_midway() {
	if (ofGetElapsedTimeMillis() - start_time > 36920 && ofGetElapsedTimeMillis() - start_time < 66360) {
		return true;
	}
	return false;
}

bool Controller::should_destroy_midway() {
	if (ofGetElapsedTimeMillis() - start_time > 66360) {
		return true;
	}
	return false;
}

bool Controller::should_enter_dialog() {
	//100200
	if (ofGetElapsedTimeMillis() - start_time > 100200) {
		return true;
	}
	return false;
}