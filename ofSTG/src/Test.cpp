#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ofApp.h"

TEST_CASE("Player") {
	ofImage i;
	Player p;
	i.load("..\\img\\player.png");
	ofSetupOpenGL(1920, 1080, OF_WINDOW);

	SECTION("1") {
		p.initialize(&i);
		REQUIRE(p.speed == 9);
	}

	SECTION("2") {
		p.initialize(&i);
		REQUIRE(p.lives == 1);
	}

	SECTION("3") {
		p.initialize(&i);
		REQUIRE(p.width == i.getWidth());
	}

	SECTION("4") {
		p.initialize(&i);
		REQUIRE(p.height == i.getHeight());
	}

	SECTION("5") {
		p.initialize(&i);
		REQUIRE(p.pos.x == 960);
	}

	SECTION("6") {
		p.initialize(&i);
		REQUIRE(p.pos.y == (1080 - i.getHeight()) / 2);
	}
}