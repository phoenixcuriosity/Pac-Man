/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.8a

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


#include "init.h"

#include "Pac_Man_lib.h"
#include "sdl.h"

using namespace std;

void initfile(sysinfo& information) {
	ofstream log(information.files.log);
	if (log) {}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " + information.files.log;
}
void initTile(tile& map, bool wall, unsigned int entity) {
	map.wall = wall; map.entity = entity;
}
void forme(tile map[], unsigned int length, unsigned int height, unsigned int space) {
	for (unsigned int i = 0; i < length; i++) {
		for (unsigned int j = 0; j < height; j++) {
			initTile(map[space], true, nothing);
			space++;
		}
		space += (mapHeight - height);
	}
}
void initGrid(sysinfo& information) {
	unsigned int k = 0;
	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			information.map[k].tile_nb = k;
			information.map[k].tile_x = tileSize * i + (SCREEN_WIDTH / 2 - (mapLength / 2 * tileSize));
			information.map[k].tile_y = tileSize * j + (SCREEN_HEIGHT / 2 - (mapHeight / 2 * tileSize));
			if (i == 0 || i == mapLength - 1 || j == 0 || j == mapHeight - 1) {
				information.map[k].wall = true;
				information.map[k].entity = nothing;
			}
			else {
				information.map[k].wall = false;
				information.map[k].entity = gold;
			}
			k++;
		}
	}
	unsigned int space = 0;
	// ouverture
	initTile(information.map[12], false, nothing);
	initTile(information.map[612], false, nothing);

	// 
	initTile(information.map[26], false, cherry);
	initTile(information.map[48], false, strawberry);
	initTile(information.map[576], false, peach);
	initTile(information.map[598], false, apple);

	// blocs de murs
	forme(information.map, 4, 2, 52); // 1
	forme(information.map, 2, 3, 55); // 2 
	forme(information.map, 2, 1, 59); // 3 
	forme(information.map, 4, 1, 36); // 4
	forme(information.map, 4, 1, 38); // 5
	forme(information.map, 4, 2, 65); // 6
	forme(information.map, 1, 5, 68); // 7
	forme(information.map, 1, 5, 130); // 8
	forme(information.map, 2, 2, 118); // 9
	forme(information.map, 2, 2, 121); // 10
	forme(information.map, 1, 3, 177); // 11
	initTile(information.map[space = 161], true, nothing); // 12a
	forme(information.map, 1, 2, 181); // 12b
	forme(information.map, 2, 4, 183); // 12c
	initTile(information.map[space = 163], true, nothing); // 13a
	forme(information.map, 2, 4, 188); // 13b
	forme(information.map, 2, 3, 193); // 14
	forme(information.map, 4, 1, 197); // 15a
	forme(information.map, 1, 3, 270); // 15b
	forme(information.map, 2, 5, 227); // 16
	forme(information.map, 5, 1, 258); // 17a
	forme(information.map, 1, 2, 306); // 17b
	forme(information.map, 2, 1, 260); // 18a
	forme(information.map, 1, 4, 261); // 18b
	forme(information.map, 3, 1, 289); // 18c
	forme(information.map, 2, 1, 335); // 18d
	forme(information.map, 1, 4, 361); // 18e
	initTile(information.map[space = 266], true, nothing); // 19
	forme(information.map, 5, 1, 268); // 20a
	forme(information.map, 1, 2, 316); // 20b
	forme(information.map, 1, 4, 301); // 21
	forme(information.map, 1, 4, 320); // 22
	forme(information.map, 2, 5, 352); // 23
	initTile(information.map[space = 366], true, nothing); // 24
	forme(information.map, 1, 2, 370); // 25a
	forme(information.map, 4, 1, 372); // 25b
	forme(information.map, 2, 4, 408); // 26a
	forme(information.map, 1, 2, 431); // 26b
	initTile(information.map[space = 461], true, nothing); // 26c
	forme(information.map, 2, 4, 413); // 27a
	initTile(information.map[space = 463], true, nothing); // 27b
	forme(information.map, 2, 3, 418); // 28
	forme(information.map, 1, 3, 427); // 29
	forme(information.map, 4, 2, 477); // 30
	forme(information.map, 1, 5, 480); // 31
	forme(information.map, 4, 2, 490); // 32
	forme(information.map, 2, 2, 493); // 33
	forme(information.map, 2, 2, 496); // 34
	forme(information.map, 4, 1, 511); // 35
	forme(information.map, 4, 1, 513); // 36
	forme(information.map, 2, 3, 530); // 37
	forme(information.map, 2, 1, 534); // 38
	forme(information.map, 1, 5, 568); // 39

}
void calculimage(sysinfo& information) {
	logfileconsole("_calculimage Start_");

	clock_t t1, t2;
	t1 = clock();

	string IPath = "image/";

	information.variable.statescreen = STATEplay;
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "tile32/Black.bmp", "Black.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "tile32/White.bmp", "White.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "map.png", "map.png", (Uint8)255, -1, -1, NULL, NULL);



	vector<string> ghostName, Pos;
	ghostName.push_back("Red"); ghostName.push_back("Blue"); ghostName.push_back("Yellow"); ghostName.push_back("Pink");
	Pos.push_back("U"); Pos.push_back("L"); Pos.push_back("D"); Pos.push_back("R");


	for (unsigned int i = 0; i < Pos.size(); i++) {
		for (unsigned int j = 1; j < 3; j++)
			loadImage(information.ecran.renderer, information.allTextures.pacman, information.variable.statescreen, information.variable.select,
				IPath + "pacman/pacman_" + Pos[i] + "_" + to_string(j) + ".png", "pacman_" + Pos[i] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
	}

	for (unsigned int i = 0; i < ghostName.size(); i++) {
		for (unsigned int j = 1; j < 3; j++) {
			for (unsigned int k = 0; k < Pos.size(); k++) {
				switch (i) {
				case 0:
					loadImage(information.ecran.renderer, information.allTextures.red, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
					break;
				case 1:
					loadImage(information.ecran.renderer, information.allTextures.blue, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
					break;
				case 2:
					loadImage(information.ecran.renderer, information.allTextures.yellow, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
					break;
				case 3:
					loadImage(information.ecran.renderer, information.allTextures.pink, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
					break;
				}


			}
		}
	}
	loadImage(information.ecran.renderer, information.allTextures.miscGhost, information.variable.statescreen, information.variable.select,
		IPath + "Ghost/not_Invincible.png", "not_Invincible.png", (Uint8)255, -1, -1, tileSize, tileSize);

	loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/gold.png", "gold.png", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/cherry.png", "cherry.png", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/strawberry.png", "strawberry.png", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/lemon.png", "lemon.png", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/pear.png", "pear.png", (Uint8)255, -1, -1, tileSize, tileSize);
	loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/key.png", "key.png", (Uint8)255, -1, -1, tileSize, tileSize);


	information.variable.statescreen = STATEecrantitre;
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, 
		IPath + "ecrantitre/linux.jpg", "linux.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2, NULL, NULL, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/c++.jpg", "c++.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 400, NULL, NULL, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/sudo.jpg", "sudo.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2, NULL, NULL, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/PC_master_Race.jpg", "PC_master_Race.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 400, NULL, NULL, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/matlab.jpg", "matlab.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350, NULL, NULL, center);
	int spacemenu = 64, initspacemenu = 400;

	// ______Buttons_____
	information.variable.statescreen = STATEecrantitre;
	createbutton(information, information.allButton.buttonecrantitre,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, center);
	createbutton(information, information.allButton.buttonecrantitre,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, information.allButton.buttonecrantitre,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, information.allButton.buttonecrantitre, 
		shaded, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	
	information.variable.statescreen = STATEplay;
	createbutton(information, information.allButton.buttonplay, shaded,
		"Return to Title Screen", WriteColorButton, BackColorButton, 32, 0, 0);
	createbutton(information, information.allButton.buttonplay, shaded,
		"Pause", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, 0, center_x);
	createbutton(information, information.allButton.buttonplay, shaded,
		"Initial Grid", WriteColorButton, BackColorButton, 32, 0, 64);

	// ______Writetxt_____ 
	information.variable.statescreen = STATEecrantitre;
	loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "Game dev in C++ and with SDL2.0.8", { 255, 127, 127, 255 }, NoColor, 18, 0, 0);
	loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "Developed by Joeffrey VILLERONCE and Robin SAUTER", { 127, 255, 127, 255 }, NoColor, 18, 0, 30);
	loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "New Super Pac-Man Plus DELUX Pro Turbo Edition", { 0, 64, 255, 255 }, NoColor, 50, SCREEN_WIDTH / 2, 100, center_x);
	loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "With ALL DLC For Only 99.99$ what a deal !!!", { 255, 255, 0, 255 }, NoColor, 25, SCREEN_WIDTH / 2, 160, center_x);
	
	information.variable.statescreen = STATEplay;
	loadwritetxt(information, information.allTextures.txtplay, blended,
		"Your Score", { 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, 50, center_x);
	loadwritetxt(information, information.allTextures.txtplay, blended,
		"YOU DIED", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, center);

	loadwritetxt(information, information.allTextures.scoreValue, blended, "100", { 255, 0, 0, 255 }, NoColor, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, blended, "200", { 0, 64, 255, 255 }, NoColor, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, blended, "400", { 0, 255, 0, 255 }, NoColor, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, blended, "800", { 255, 0, 255, 255 }, NoColor, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, blended, "1600", { 255, 0, 255, 255 }, NoColor, 26, -1, -1);
	loadwritetxt(information, information.allTextures.scoreValue, blended, "5000", { 0, 64, 255, 255 }, NoColor, 26, -1, -1);


	t2 = clock();
	logfileconsole("temps d'execution de calculimage : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));
	logfileconsole("_calculimage End_");
}