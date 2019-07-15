#pragma once

#include "ofMain.h"
#include "ofxAnimatableOfPoint.h"
#include <Player.h>
#include <Bullet.h>
#include <Enemy.h>
#include <Controller.h>
#include <Boss.h>

class ofApp : public ofBaseApp{

	public:
		Controller controller;

		glm::vec2 background_pos;
		glm::vec2 credit_pos;

		ofSoundPlayer music;
		ofSoundPlayer boss_music;
		ofSoundPlayer credit_music;

		ofTrueTypeFont font;

		ofImage background;
		ofImage player_image;
		ofImage enemy_image;
		ofImage player_bullet_image;
		ofImage enemy_bullet_image;
		ofImage midway_boss_image;
		ofImage midway_boss_bullet_image;
		ofImage last_boss_image;
		ofImage last_boss_bullet_image;
		ofImage life;
		ofImage cai;
		ofImage start;
		ofImage dialog_background_student;
		ofImage dialog_background_boss;
		ofImage credit;
		vector<Bullet> bullets;
		vector<Enemy> enemies;
		vector<Boss> bosses;
		vector<string> dialog;
		int type_counter;
		int dialog_counter;
		vector<string> types;

		float max_enemy_amplitude;
		float max_enemy_shoot_interval;
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void update_bullets();
		void check_bullet_collisions();
		void spawn_enemies(string type);
		void change_stage();
		void end_game();
};
