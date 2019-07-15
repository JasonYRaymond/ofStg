// Comment out main.cpp and uncomment this file to run tests.
/*
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ofApp.h"

TEST_CASE("Player") {
	ofImage i;
	Player p;
	i.load("..\\..\\img\\player.png");
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
		REQUIRE(p.pos.y == 1080 - i.getHeight() / 2);
	}
}

TEST_CASE("Bullet") {
	ofImage i;
	Bullet b;
	i.load("..\\..\\img\\enemy_bullet.png");
	ofPoint p;
	p.x = 0;
	p.y = 0;

	SECTION("1") {
		b.setup("player", p, 10, &i, 0);
		REQUIRE(b.from == "player");
	}

	SECTION("2") {
		b.setup("player", p, 10, &i, 0);
		REQUIRE(b.pos.x == 0);
	}

	SECTION("3") {
		b.setup("player", p, 10, &i, 0);
		REQUIRE(b.pos.y == 0);
	}

}

TEST_CASE("Enemy") {
	ofImage i;
	Enemy e;
	i.load("..\\..\\img\\enemy.png");

	SECTION("1") {
		e.setup(3, &i, "top right circular", 0, 0, 0);
		REQUIRE(e.shoot_interval <= 5);
		REQUIRE(e.shoot_interval >= 3);
	}

	SECTION("2") {
		e.setup(3, &i, "top right circular", 0, 0, 0);
		REQUIRE(e.pos.x == 0);
	}

	SECTION("3") {
		e.setup(3, &i, "top right circular", 0, 0, 0);
		REQUIRE(e.pos.y == 0);
	}
}

TEST_CASE("Boss") {
	ofImage i;
	Boss b;
	i.load("..\\..\\img\\enemy.png");
	
	SECTION("1") {
		b.setup(&i, "midway", 0, 0);
		REQUIRE(b.hp == 10000);
	}

	SECTION("2") {
		b.setup(&i, "midway", 0, 0);
		REQUIRE(b.life == 1);
	}

	SECTION("3") {
		b.setup(&i, "midway", 0, 0);
		REQUIRE(b.shoot_interval == 2);
	}

	SECTION("4") {
		b.setup(&i, "last boss", 0, 0);
		REQUIRE(b.hp == 40);
	}

	SECTION("5") {
		b.setup(&i, "last boss", 0, 0);
		REQUIRE(b.life == 4);
	}

	SECTION("6") {
		b.setup(&i, "last boss", 0, 0);
		REQUIRE(b.shoot_interval == 2);
	}
}
*/