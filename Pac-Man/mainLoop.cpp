/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.3

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
	Pacman player((string)"robin", 1200, 500);

	int SDL_EnableUNICODE(1); // on azerty

	while (information.variable.continuer) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:	// permet de quitter le jeu
				information.variable.continuer = 0;
				break;
			case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					keySDLK_UP(player);
					break;
				case SDLK_DOWN:
					keySDLK_DOWN(player);
					break;
				case SDLK_RIGHT:
					keySDLK_RIGHT(player);
					break;
				case SDLK_LEFT:
					keySDLK_LEFT(player);
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
		alwaysrender(information, player);
	}
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
			if (i == 0 || i == mapLength - 1 || j == 0 || j == mapHeight - 1)
				information.map[k].wall = true;
			else
				information.map[k].wall = false;
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
		for(unsigned int j = 1; j < 3; j++)
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
	information.variable.statescreen = STATEecrantitre;
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/linux.jpg", "linux.jpg", (Uint8)255, SCREEN_WIDTH/2 + 500, SCREEN_HEIGHT/2, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/c++.jpg", "c++.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 400, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/sudo.jpg", "sudo.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2, center);
	loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select, IPath + "ecrantitre/PC_master_Race.jpg", "PC_master_Race.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 400, center);
	
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
	loadwritetxt(information, information.allTextures.txtecrantitre, "Well Well Well... Now let's play", { 0, 64, 255, 255 }, 26, SCREEN_WIDTH / 2, 100, center_x);

	t2 = clock();
	logfileconsole("temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC));
	logfileconsole("_calculimage End_");
}

void createbutton(sysinfo& information, std::vector<Buttons*>& tabbutton,const string& msg, SDL_Color color, SDL_Color backcolor, int size, int x, int y, int centerbutton) {
	int iW = 0, iH = 0;
	unsigned int i = 0;
	int xc = 0, yc = 0;
	SDL_Texture *image = nullptr;
	SDL_Texture *imageOn = nullptr;

	if (tabbutton.size() > 0) {
		i++;
	}
	for (i; i <= tabbutton.size(); i++) {
		if (i == tabbutton.size()) {
			image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font[size]);
			imageOn = renderTextShaded(information.ecran.renderer, msg, color, { 64,128,64,255 }, information.allTextures.font[size]);
			SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
			searchcenter(x, y, xc, yc, iW, iH, centerbutton);
			tabbutton.push_back(new Buttons(image, msg, information.variable.statescreen, information.variable.select, xc, yc, iW, iH, imageOn, x, y, size, color, backcolor));

			logfileconsole("Create Button n:" + to_string(i) + " msg = " + tabbutton[i]->GETname() + " Success");
			break;
		}
	}
}

void searchcenter(int &x, int &y, int &xc, int &yc, int iW, int iH, int centerbutton) {
	switch (centerbutton) {
	case nocenter:
		xc = x + iW / 2;
		yc = y + iH / 2;
		break;
	case center_x:
		xc = x;
		yc = y + iH / 2;
		x = x - iW / 2;
		break;
	case center_y:
		xc = x + iW / 2;
		yc = y;
		y = y - iH / 2;
		break;
	case center:
		xc = x;
		yc = y;
		x = x - iW / 2;
		y = y - iH / 2;
		break;
	}
}

