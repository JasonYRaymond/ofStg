#include "ofApp.h"

string game_state;
bool boss_should_enter = false;
int score;
Player player;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	game_state = "start";

	max_enemy_amplitude = 3.0;
	max_enemy_shoot_interval = 1.5;

	background_pos = glm::vec2(0, 0);
	credit_pos = glm::vec2(0, 0);

	font.load("C:\\Windows\\Fonts\\arial.ttf", 32);

	//dialog_background_boss.load("..\img\dialog_background_boss.png");
	dialog_background_student.load("..\\..\\img\\dialog_background_student.png");
	dialog_background_boss.load("..\\..\\img\\dialog_background_boss.png");
	cai.load("..\\..\\img\\cai.png");
	start.load("..\\..\\img\\start.png");
	start.load("..\\..\\img\\start.png");
	midway_boss_image.load("..\\..\\img\\enemy.png");
	midway_boss_bullet_image.load("..\\..\\img\\player_bullet.png");
	last_boss_image.load("..\\..\\img\\last_boss.png");
	last_boss_bullet_image.load("..\\..\\img\\player_bullet.png");
	life.load("..\\..\\img\\life.png");
	background.load("..\\..\\img\\background.jpg");
	music.load("..\\..\\ost\\Midway.mp3");
	boss_music.load("..\\..\\ost\\last boss.mp3");
	credit_music.load("..\\..\\ost\\credit.mp3");
	boss_music.setLoop(true);
	player_image.load("..\\..\\img\\player.png");
	player_bullet_image.load("..\\..\\img\\enemy_bullet.png");
	enemy_image.load("..\\..\\img\\enemy.png");
	enemy_bullet_image.load("..\\..\\img\\player_bullet.png");
	credit.load("..\\..\\img\\credit.png");

	types.push_back("top left circular");
	types.push_back("top right circular");
	types.push_back("top down");
	types.push_back("left right");
	types.push_back("parabola right left");
	types.push_back("right left");
	types.push_back("parabola left right");

	dialog.push_back("So many bugs around here...\nI wonder what happened?");
	dialog.push_back("Mwahahahaha! \nPathetic human, looks like you finally found out what's been going on.");
	dialog.push_back("...Who are you?");
	dialog.push_back("I am the Bug King! Lord of the bugs! Bane of the programs!");
	dialog.push_back("So it's you who's destroying my code?");
	dialog.push_back("Precisely.\nToday, we shall revenge for our dead brothers, \nand punish you for your unforgivable crime!");
	dialog.push_back("What?");
	dialog.push_back("Do you remember how many bugs you've destroyed during this semester?\nEvery single time you run your cursed debugger, some of our kin dies!\nYou dirty murder!");
	dialog.push_back("But they were bugs...I can't just leave them like that.");
	dialog.push_back("Well then we won't leave you like this either!\nPrepare yourself, and then face the fury of the almighty Bug King!");

	player.initialize(&player_image);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (game_state == "start") {
	}
	else if (game_state == "game" || game_state == "boss") {
		if (game_state == "game") {
			background_pos.y += 50 * ofGetLastFrameTime();
			if (background_pos.y >= ofGetHeight()) {
				background_pos.y = 0;
			}
			if (controller.should_enter_dialog()) {
				enemies.clear();
				game_state = "dialog";
			}
		}

		if (game_state == "boss") {

		}

		player.update();

		update_bullets();

		if (player.is_shooting && ofGetElapsedTimef() - player.start_shoot > player.shoot_interval) {
			player.start_shoot = ofGetElapsedTimef();
			Bullet bullet;
			ofPoint *bulletPos = new ofPoint(player.pos.x, player.pos.y - player.height);
			bullet.setup("player", *bulletPos, player.speed, &player_bullet_image, ofGetElapsedTimeMillis());
			bullets.push_back(bullet);
		}

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].update();
			
			if (abs(enemies[i].angle - enemies[i].start_angle) > PI) {
				enemies.erase(enemies.begin() + i);
			}
		}

		for (int i = 0; i < bosses.size(); i++) {
			if (ofGetElapsedTimeMillis() - controller.start_time >= 36920 && ofGetElapsedTimeMillis() - controller.start_time < 62760 && bosses[i].type == "midway") {
				bosses[i].update("enter");
			} 
			if (ofGetElapsedTimeMillis() - controller.start_time >= 62760 && ofGetElapsedTimeMillis() - controller.start_time < 66460) {
				bosses[i].update("exit");
			}
			if (bosses[i].type == "midway" && controller.should_destroy_midway()) {
				bosses.erase(bosses.begin() + i);
			}
		}

		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].time_to_shoot()) {
				Bullet bullet;
				ofPoint *bulletPos = new ofPoint(enemies[i].pos.x, enemies[i].pos.y + enemies[i].height);
				bullet.setup("enemy", *bulletPos, enemies[i].speed, &enemy_bullet_image, ofGetElapsedTimeMillis());
				bullets.push_back(bullet);
			}
		}

		for (int i = 0; i < bosses.size(); i++) {
			if (bosses[i].time_to_shoot()) {
				if (bosses[i].type == "midway") {
					int radius = 0.5 * bosses[i].width;
					int direction_const = rand() % 360;
					float angular_direction_const = direction_const * PI / 180;
					for (int j = 0; j < 16; j++) {
						Bullet bullet;
						ofPoint *bulletPos = new ofPoint((int)(ofGetWidth() / 2) + radius * cos(angular_direction_const + j * PI / 8), (int)(ofGetHeight() / 6) + radius * sin(angular_direction_const + j * PI / 8));
						bullet.setup("midway", *bulletPos, 10, &midway_boss_bullet_image, ofGetElapsedTimeMillis());
						bullets.push_back(bullet);
					}
				}
				else if (bosses[i].type == "last boss") {
					if (bosses[i].life == 4) {
						for (int j = 0; j < 8; j++) {
							Bullet bullet;
							ofPoint destination;
							destination.x = rand() % ofGetWidth();
							destination.y = ofGetHeight() + enemy_bullet_image.getHeight();

							ofxAnimatableOfPoint pt;
							pt.reset();
							pt.setPositionX(bosses[i].pos.x);
							pt.setPositionY(bosses[i].pos.y);
							pt.setRepeatType(PLAY_ONCE);
							pt.setCurve(CUBIC_EASE_IN);
							pt.animateTo(destination);

							bullet.setup("last boss", bosses[i].pos, 5, &last_boss_bullet_image, ofGetElapsedTimeMillis());
							bullet.set_tracker(pt);
							bullets.push_back(bullet);
						}
					} else if (bosses[i].life == 3) {
						for (int j = 0; j < 4; j++) {
							Bullet bullet;
							ofPoint destination;
							destination.x = player.pos.x;
							destination.y = player.pos.y;

							ofxAnimatableOfPoint pt;
							pt.reset();
							if (j == 0) {
								pt.setPositionX(enemy_bullet_image.getHeight());
								pt.setPositionY(enemy_bullet_image.getHeight());
							} else if (j == 1) {
								pt.setPositionX(ofGetWidth() - enemy_bullet_image.getHeight());
								pt.setPositionY(bullet.width);
							} else if (j == 2) {
								pt.setPositionX(ofGetWidth() - enemy_bullet_image.getHeight());
								pt.setPositionY(ofGetHeight() - enemy_bullet_image.getHeight());
							} else if (j == 3) {
								pt.setPositionX(enemy_bullet_image.getHeight());
								pt.setPositionY(ofGetHeight() - enemy_bullet_image.getHeight());
							}
							pt.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
							pt.setCurve(CUBIC_EASE_IN);
							pt.animateTo(destination);

							bullet.setup("last boss", bosses[i].pos, 5, &last_boss_bullet_image, ofGetElapsedTimeMillis());
							bullet.set_tracker(pt);
							bullets.push_back(bullet);
						}
					} else if (bosses[i].life == 2) {
						for (int j = 0; j < 3; j++) {
							Bullet bullet;
							ofPoint destination;
							destination.x = player.pos.x;
							destination.y = ofGetHeight();

							ofxAnimatableOfPoint pt;
							pt.reset();
							pt.setPositionX(player.pos.x);
							pt.setPositionY(j * ofGetHeight() / 10);
							pt.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
							pt.setCurve(EASE_OUT_BOUNCE);
							pt.animateTo(destination);

							bullet.setup("last boss", bosses[i].pos, 5, &last_boss_bullet_image, ofGetElapsedTimeMillis());
							bullet.set_tracker(pt);
							bullets.push_back(bullet);
						}

						for (int j = 0; j < 3; j++) {
							Bullet bullet;
							ofPoint destination;
							destination.x = ofGetWidth();
							destination.y = player.pos.y;

							ofxAnimatableOfPoint pt;
							pt.reset();
							pt.setPositionX(j * ofGetHeight() / 10);
							pt.setPositionY(player.pos.y);
							pt.setRepeatType(PLAY_ONCE);
							pt.setCurve(EASE_IN);
							pt.animateTo(destination);

							bullet.setup("last boss", bosses[i].pos, 5, &last_boss_bullet_image, ofGetElapsedTimeMillis());
							bullet.set_tracker(pt);
							bullets.push_back(bullet);
						}

					} else if (bosses[i].life == 1 || bosses[i].life == 0) {
						int index = rand() % 2;
						spawn_enemies(types[index]);
						for (int j = 0; j < 5; j++) {
							Bullet bullet;
							ofPoint destination;
							destination.x = ofGetWidth() + 2 * enemy_bullet_image.getWidth();
							destination.y = j * ofGetHeight() / 5;

							ofxAnimatableOfPoint pt;
							pt.reset();
							pt.setPositionX(0);
							pt.setPositionY(j * ofGetHeight() / 5);
							pt.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
							pt.setCurve(EASE_IN_EASE_OUT);
							pt.animateTo(destination);

							bullet.setup("last boss", bosses[i].pos, 5, &last_boss_bullet_image, ofGetElapsedTimeMillis());
							bullet.set_tracker(pt);
							bullets.push_back(bullet);
						}
						for (int j = 0; j < 5; j++) {
							Bullet bullet;
							ofPoint destination;
							destination.x = 0;
							destination.y = ofGetHeight() / 10 + j * ofGetHeight() / 5;

							ofxAnimatableOfPoint pt;
							pt.reset();
							pt.setPositionX(ofGetWidth());
							pt.setPositionY(ofGetHeight() / 10 + j * ofGetHeight() / 5);
							pt.setRepeatType(PLAY_ONCE);
							pt.setCurve(EASE_IN_EASE_OUT);
							pt.animateTo(destination);

							bullet.setup("last boss", bosses[i].pos, 5, &last_boss_bullet_image, ofGetElapsedTimeMillis());
							bullet.set_tracker(pt);
							bullets.push_back(bullet);
						}

						if (bosses[i].life == 0) {
							int left_diff = rand() % 10;
							for (int j = 0; j < 10; j++) {
								Bullet bullet;
								ofPoint destination;
								destination.x = (left_diff * ofGetWidth() / 100) + (j * ofGetWidth() / 10);
								destination.y = ofGetHeight() + enemy_bullet_image.getHeight();

								ofxAnimatableOfPoint pt;
								pt.reset();
								pt.setPositionX((left_diff * ofGetWidth() / 100) + (j * ofGetWidth() / 10));
								pt.setPositionY(0);
								pt.setRepeatType(PLAY_ONCE);
								pt.setCurve(EASE_IN_EASE_OUT);
								pt.animateTo(destination);

								bullet.setup("last boss", bosses[i].pos, 5, &last_boss_bullet_image, ofGetElapsedTimeMillis());
								bullet.set_tracker(pt);
								bullets.push_back(bullet);
							}
						}
					}
				}
			}
		}

		if (controller.should_spawn() == true && game_state == "game") {
			int type_index = type_counter % types.size();
			spawn_enemies(types[type_index]);
			type_counter += 1;
		}
		if (controller.should_enter_midway() && bosses.size() == 0 && game_state == "game") {
			Boss midway;
			midway.setup(&midway_boss_image, "midway", ofGetWidth() / 2, 0);
			bosses.push_back(midway);
		}

	}
	else if (game_state == "dialog") {
		if (boss_should_enter && bosses.size() == 0) {
			Boss last_boss;
			last_boss.setup(&last_boss_image, "last boss", ofGetWidth() / 2, 0);
			bosses.push_back(last_boss);
		}

		for (int i = 0; i < bosses.size(); i++) {
			if (bosses[i].pos.y < bosses[i].height) {
				bosses[i].update("enter");
			}
		}
	}
	else if (game_state == "credit") {
		if (credit_pos.y + credit.getHeight() > ofGetHeight()) {
			credit_pos.y -= 150 * ofGetLastFrameTime();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (game_state == "start") {
		start.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	else if (game_state == "game" || game_state == "boss") {
		background.draw(background_pos.x, background_pos.y, ofGetWidth(), ofGetHeight());
		background.draw(background_pos.x, background_pos.y - ofGetHeight(), ofGetWidth(), ofGetHeight());

		player.draw();

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].draw();
		}
		for (int i = 0; i < bosses.size(); i++) {
			bosses[i].draw();
			if (game_state == "boss") {
				font.drawString("BUG KING", 30, 60);
				ofDrawRectangle(30, 90, ((float)bosses[i].hp / 40) * (ofGetWidth() - 60), 30);
				for (int j = 0; j < bosses[i].life; j++) {
					life.draw(30 + j * life.getWidth(), 150, life.getWidth(), life.getHeight());
				}
			}
		}
		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].draw();
		}
	}
	else if (game_state == "dialog") {
		if (dialog_counter < 10) {
			background.draw(background_pos.x, background_pos.y, ofGetWidth(), ofGetHeight());
			background.draw(background_pos.x, background_pos.y - ofGetHeight(), ofGetWidth(), ofGetHeight());
			if (dialog_counter % 2 == 0) {
				dialog_background_student.draw(0, 0, ofGetWidth(), ofGetHeight());
				font.drawString(dialog[dialog_counter], ofGetWidth() / 8, ofGetHeight() * 2 / 3);
			}
			else {
				dialog_background_boss.draw(0, 0, ofGetWidth(), ofGetHeight());
				font.drawString(dialog[dialog_counter], ofGetWidth() / 8, ofGetHeight() * 2 / 3);
			}
		}

		for (int i = 0; i < bosses.size(); i++) {
			bosses[i].draw();
		}
	}
	else if (game_state == "ending dialog") {
		background.draw(background_pos.x, background_pos.y, ofGetWidth(), ofGetHeight());
		background.draw(background_pos.x, background_pos.y - ofGetHeight(), ofGetWidth(), ofGetHeight());
		dialog_background_boss.draw(0, 0, ofGetWidth(), ofGetHeight());
		font.drawString("Ahh...Well fought...\nYou...You won this one......\nBut we...shall...return......", ofGetWidth() / 8, ofGetHeight() * 2 / 3);
	}
	else if (game_state == "credit") {
		background.draw(background_pos.x, background_pos.y, ofGetWidth(), ofGetHeight());
		background.draw(background_pos.x, background_pos.y - ofGetHeight(), ofGetWidth(), ofGetHeight());
		credit.draw(credit_pos.x, credit_pos.y, ofGetWidth(), credit.getHeight());
	}
	else if (game_state == "end") {
		cai.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (game_state == "game" || game_state == "boss") {

		if (key == OF_KEY_LEFT) {
			player.left_pressed = true;
		}

		if (key == OF_KEY_RIGHT) {
			player.right_pressed = true;
		}

		if (key == OF_KEY_UP) {
			player.up_pressed = true;
		}

		if (key == OF_KEY_DOWN) {
			player.down_pressed = true;
		}

		if (key == 'z' || key == 'Z') {
			player.is_shooting = true;
		}
	}
	else if (game_state == "ending dialog") {
		game_state = "credit";
		boss_music.stop();
		credit_music.play();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (game_state == "start") {
		game_state = "game";

		controller.setup(ofGetElapsedTimeMillis());
		music.play();
	}
	else if (game_state == "game" || game_state == "boss") {
		if (key == OF_KEY_LEFT) {
			player.left_pressed = false;
		}

		if (key == OF_KEY_RIGHT) {
			player.right_pressed = false;
		}

		if (key == OF_KEY_UP) {
			player.up_pressed = false;
		}

		if (key == OF_KEY_DOWN) {
			player.down_pressed = false;
		}

		if (key == 'z' || key == 'Z') {
			player.is_shooting = false;
		}
	}
	else if (game_state == "dialog") {
		if (dialog_counter < 10) {
			dialog_counter++;
			if (dialog_counter == 1) {
				boss_should_enter = true;
			}
			if (dialog_counter >= 10) {
				game_state = "boss";
				change_stage();
				boss_music.play();
				if (music.isPlaying()) {
					music.stop();
				}
			}
		}
	}
	else if (game_state == "credit") {
		if (key == 'r' || key == 'R') {
			game_state = "start";
		}
	}
	else if (game_state == "end") {
		if (key == 'r' || key == 'R') {
			controller.setup(ofGetElapsedTimeMillis());
			game_state = "game";
			music.play();
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::update_bullets() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].update();

		if (bullets[i].pos.y + bullets[i].width < 0 || bullets[i].pos.y > ofGetHeight() || bullets[i].pos.x + bullets[i].width < 0 || bullets[i].pos.x > ofGetWidth()
			|| bullets[i].should_be_destroyed()) {
			bullets.erase(bullets.begin() + i);
		}
	}

	check_bullet_collisions();
}

void ofApp::check_bullet_collisions() {
	for (int i = bullets.size() - 1; i >= 0; i--) {
		if (bullets[i].from == "player") {
			for (int e = bosses.size() - 1; e >= 0; e--) {
				if (ofDist(bullets[i].pos.x, bullets[i].pos.y, bosses[e].pos.x, bosses[e].pos.y) < (bosses[e].width + bullets[i].width) / 2) {
					bullets.erase(bullets.begin() + i);
					bosses[e].hp -= 1;
					if (bosses[e].hp <= 0) {
						bosses[e].hp = 40;
						bosses[e].life -= 1;
					}
					if (bosses[e].life < 0) {
						bosses.erase(bosses.begin() + e);
						game_state = "ending dialog";
						end_game();
					}
					score += 10000;
					break;
				}
			}

			if (game_state == "ending dialog") {
				break;
			}

			for (int e = enemies.size() - 1; e >= 0; e--) {
				if (ofDist(bullets[i].pos.x, bullets[i].pos.y, enemies[e].pos.x, enemies[e].pos.y) < (enemies[e].width + bullets[i].width) / 2) {
					enemies.erase(enemies.begin() + e);
					bullets.erase(bullets.begin() + i);
					score += 100;
					break;
				}
			}
		}

		else {
			if (ofDist(bullets[i].pos.x, bullets[i].pos.y, player.pos.x, player.pos.y) < (bullets[i].width + player.width) / 2) {
				bullets.erase(bullets.begin() + i);
				player.lives--;
				if (player.lives <= 0) {
					game_state = "end";
					end_game();
					break;
				}
			}
		}
	}
}

void ofApp::spawn_enemies(string type) {
	int start_time = ofGetElapsedTimeMillis();
	int spawn_interval = 500;
	int i = 0;
	if (type == "top left circular") {
		int radius = (int) (2 * ofGetHeight() / 3);
		for (int i = 0; i < 6; i++) {
			Enemy e;
			e.setup(max_enemy_shoot_interval, &enemy_image, "top left circular", 0, 0, (0.5 + 0.1 * i) * PI);
			enemies.push_back(e);
		}
	} else if (type == "top right circular") {
		int radius = (int)(2 * ofGetHeight() / 3);
		for (int i = 0; i < 6; i++) {
			Enemy e;
			e.setup(max_enemy_shoot_interval, &enemy_image, "top right circular", 0, 0, (0.5 - 0.1 * i) * PI);
			enemies.push_back(e);
		}
	} else if (type == "top down") {
		for (int i = 0; i < 6; i++) {
			Enemy e;
			e.setup(max_enemy_shoot_interval, &enemy_image, "top down", (int) (ofGetWidth() / 2), 0 - 2 * i * enemy_image.getHeight(), 0);
			enemies.push_back(e);
		}
	} else if (type == "left right") {
		for (int i = 0; i < 6; i++) {
			Enemy e;
			e.setup(max_enemy_shoot_interval, &enemy_image, "left right", 0 - 2 * i * enemy_image.getWidth(), (int) (ofGetHeight() / 3), 0);
			enemies.push_back(e);
		}
	} else if (type == "right left") {
		for (int i = 0; i < 6; i++) {
			Enemy e;
			e.setup(max_enemy_shoot_interval, &enemy_image, "right left", ofGetWidth() + 2 * i * enemy_image.getWidth(), (int) (ofGetHeight() / 3), 0);
			enemies.push_back(e);
		}
	} else if (type == "parabola left right") {
		for (int i = 0; i < 6; i++) {
			Enemy e;
			e.setup(max_enemy_shoot_interval, &enemy_image, "parabola left right", 0 - 2 * i * enemy_image.getWidth(), 0, 0);
			enemies.push_back(e);
		}
	} else if (type == "parabola right left") {
		for (int i = 0; i < 6; i++) {
			Enemy e;
			e.setup(max_enemy_shoot_interval, &enemy_image, "parabola right left", ofGetWidth() + 2 * i * enemy_image.getWidth(), 0, 0);
			enemies.push_back(e);
		}
	}
}

void ofApp::change_stage() {
	player.down_pressed = false;
	player.up_pressed = false;
	player.left_pressed = false;
	player.right_pressed = false;
	player.is_shooting = false;
}

void ofApp::end_game() {
	music.stop();
	boss_music.stop();
	bullets.clear();
	enemies.clear();
	bosses.clear();
	controller.counter = 0;
	dialog_counter = 0;
	player.initialize(&player_image);
	change_stage();
}