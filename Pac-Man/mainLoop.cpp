/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Pac-Man

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "mainLoop.h"

#include "sdl.h"
#include "renduecran.h"
#include "keyboardAndMouse.h"
#include "Entity.h"



using namespace std;

void mainLoop(sysinfo& information) {
	logfileconsole("_mainLoop Start_");
	SDL_Event event;

	Pacman player((string)"robin", 832, 512);
	information.ghost.push_back(new Ghost("Red", 640, 512, red));
	information.ghost.push_back(new Ghost("Blue", 1280, 512, blue));
	information.ghost.push_back(new Ghost("Yellow", 1280, 564, yellow));
	information.ghost.push_back(new Ghost("Pink", 1280, 596, pink));

	int SDL_EnableUNICODE(1); // on azerty

	unsigned int randomPos1 = 0, randomPos2 = 0, randomPos3 = 0, randomPos4 = 0;
	unsigned int moduloPos = 0;

	while (information.variable.continuer) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:	// permet de quitter le jeu
				information.variable.continuer = 0;
				break;
			case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					player.SETnextHeading(UP);
					break;
				case SDLK_DOWN:
					player.SETnextHeading(DOWN);
					break;
				case SDLK_RIGHT:
					player.SETnextHeading(RIGHT);
					break;
				case SDLK_LEFT:
					player.SETnextHeading(LEFT);
					break;
				case SDLK_ESCAPE:
					information.variable.continuer = 0;
					break;
				case SDLK_SPACE:

					break;
				}
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
				mouse(information, event);
				break;
			case SDL_MOUSEWHEEL:
				//wheel(information, event.wheel.y);
			break;
			}

		}

		if (information.variable.statescreen == STATEplay) {
			moduloPos = (moduloPos + 1) % 60;
			if (moduloPos == 0) {
				randomPos1 = rand() % 4; randomPos2 = rand() % 4; randomPos3 = rand() % 4; randomPos4 = rand() % 4;
				for (unsigned int i = 0; i < information.ghost.size(); i++) {
					switch (i) {
					case 0:
						information.ghost[i]->SETnextHeading(randomPos1);
						break;
					case 1:
						information.ghost[i]->SETnextHeading(randomPos2);
						break;
					case 2:
						information.ghost[i]->SETnextHeading(randomPos3);
						break;
					case 3:
						information.ghost[i]->SETnextHeading(randomPos4);
						break;
					}
				}
			}
			for (unsigned int i = 0; i < information.ghost.size(); i++)
				information.ghost[i]->move(information.map);
			player.move(information.map);
		}
		alwaysrender(information, player);
	}

	for (unsigned int i = 0; i < information.ghost.size(); i++)
		delete information.ghost[i];
	logfileconsole("_mainLoop End_");
}
	

void initfile(sysinfo& information) {
	ofstream log("log.txt");
	if (log) {}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : log.txt";
}
void initGrid(sysinfo& information) {
	unsigned int k = 0;
	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			information.map[k].tile_nb = k;
			information.map[k].tile_x = tileSize * i + (SCREEN_WIDTH / 2 - (mapLength / 2 * tileSize));
			information.map[k].tile_y = tileSize * j + (SCREEN_HEIGHT / 2 - (mapHeight / 2 * tileSize));
			if (i == 0 || i == mapLength - 1 || j == 0 || j == mapHeight - 1 || i == 15 || i == 17 || j == 9) {
				information.map[k].wall = true;
				information.map[k].entity = false;
			}
				
			else {
				information.map[k].wall = false;
				information.map[k].entity = true;
			}
				
			if(k == 208)
				information.map[k].wall = true;
			else if (k == 311)
				information.map[k].wall = true;
			else if (k == 336)
				information.map[k].wall = true;
			else if (k == 361)
				information.map[k].wall = true;
			else if (k == 386)
				information.map[k].wall = true;
			else if (k == 385)
				information.map[k].wall = false;
			else if (k == 409)
				information.map[k].wall = false;
			else if (k == 436)
				information.map[k].wall = true;
			else if (k == 435)
				information.map[k].wall = false;
			else if (k == 461)
				information.map[k].wall = true;
			else if (k == 486)
				information.map[k].wall = true;
			else if (k == 287)
				information.map[k].wall = true;
			else if (k == 111)
				information.map[k].wall = true;
			else if (k == 215)
				information.map[k].wall = true;
			else if (k == 239)
				information.map[k].wall = true;
			k++;
		}
	}
}
void calculimage(sysinfo& information) {
	logfileconsole("_calculimage Start_");

	clock_t t1, t2;
	t1 = clock();

	string IPath = "image/";

	information.variable.statescreen = STATEplay;
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select, IPath + "tile32/White.bmp", "White.bmp", (Uint8)255, -1, -1);
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select, IPath + "tile32/Black.bmp", "Black.bmp", (Uint8)255, -1, -1);

	

	vector<string> ghostName, Pos;
	ghostName.push_back("Red"); ghostName.push_back("Blue"); ghostName.push_back("Yellow"); ghostName.push_back("Pink");
	Pos.push_back("U"); Pos.push_back("L"); Pos.push_back("D"); Pos.push_back("R");


	for (unsigned int i = 0; i < Pos.size(); i++) {
		for (unsigned int j = 1; j < 3; j++)
			loadImage(information.ecran.renderer, information.allTextures.pacman, information.variable.statescreen, information.variable.select, IPath + "pacman/pacman_" + Pos[i] + "_" + to_string(j) + ".png", "pacman_" + Pos[i] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1);
	}

	for (unsigned int i = 0; i < ghostName.size(); i++) {
		for (unsigned int j = 1; j < 3; j++) {
			for (unsigned int k = 0; k < Pos.size(); k++) {
				switch (i) {
				case 0:
					loadImage(information.ecran.renderer, information.allTextures.red, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1);
					break;
				case 1:
					loadImage(information.ecran.renderer, information.allTextures.blue, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1);
					break;
				case 2:
					loadImage(information.ecran.renderer, information.allTextures.yellow, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1);
					break;
				case 3:
					loadImage(information.ecran.renderer, information.allTextures.pink, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1);
					break;
				}


			}
		}
	}

	loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select, IPath + "collectibles/gold.bmp", "gold.bmp", (Uint8)255, -1, -1);

	information.variable.statescreen = STATEecrantitre;
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/linux.jpg", "linux.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/c++.jpg", "c++.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 400, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/sudo.jpg", "sudo.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/PC_master_Race.jpg", "PC_master_Race.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 400, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/matlab.jpg", "matlab.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350, center);
	int spacemenu = 64, initspacemenu = 400;

	// ______Buttons_____
	information.variable.statescreen = STATEecrantitre;
	createbutton(information, information.allButton.buttonecrantitre, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, center);
	createbutton(information, information.allButton.buttonecrantitre, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, information.allButton.buttonecrantitre, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, information.allButton.buttonecrantitre, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	information.variable.statescreen = STATEplay;
	createbutton(information, information.allButton.buttonplay, "Return to Title Screen", WriteColorButton, BackColorButton, 32, 0, 0);

	// ______Writetxt_____ 
	information.variable.statescreen = STATEecrantitre;
	loadwritetxt(information, information.allTextures.txtecrantitre, "Game dev in C++ and with SDL2.0.8", { 255, 127, 127, 255 }, 18, 0, 0);
	loadwritetxt(information, information.allTextures.txtecrantitre, "Developed by Joeffrey VILLERONCE and Robin SAUTER", { 127, 255, 127, 255 }, 18, 0, 30);
	loadwritetxt(information, information.allTextures.txtecrantitre, "New Super Pac-Man Plus DELUX Pro Turbo Edition", { 0, 64, 255, 255 }, 50, SCREEN_WIDTH / 2, 100, center_x);
	loadwritetxt(information, information.allTextures.txtecrantitre, "With ALL DLC For Only 99.99$ what a deal !!!", { 255, 255, 0, 255 }, 25, SCREEN_WIDTH / 2, 160, center_x);
	information.variable.statescreen = STATEplay;
	loadwritetxt(information, information.allTextures.txtplay, "Your Score", { 0, 64, 255, 255 }, 26, SCREEN_WIDTH / 2, 50, center_x);

	loadwritetxt(information, information.allTextures.scoreValue, "100", { 0, 64, 255, 255 }, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, "200", { 0, 64, 255, 255 }, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, "400", { 0, 64, 255, 255 }, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, "800", { 0, 64, 255, 255 }, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, "5000", { 0, 64, 255, 255 }, 26, -1, -1);


	t2 = clock();
	logfileconsole("temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));
	logfileconsole("_calculimage End_");
}

