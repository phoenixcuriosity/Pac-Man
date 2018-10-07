/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.13

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


#include "IHM.h"
#include "Pac_Man_lib.h"
#include "Texture.h"
#include "SaveReload.h"


///////////////////////////// IHM //////////////////////////////
void IHM::initfile(const std::string& log) {
	std::ofstream logtxt(log);
	if (logtxt) {}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " + log;
}
void IHM::logfileconsole(const std::string &msg) {
	const std::string logtxt = "log.txt";
	std::ofstream log(logtxt, std::ios::app);

	//std::time_t result = std::time(nullptr);
	//<< std::asctime(std::localtime(&result))

	if (log) {
		std::cout << std::endl << msg;
		log << std::endl << msg;
	}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}
void IHM::logSDLError(std::ostream &os, const std::string &msg) {
	const std::string logtxt = "bin/log/log.txt";
	std::ofstream log(logtxt, std::ios::app);
	if (log) {
		os << msg << " error: " << SDL_GetError() << std::endl;
		log << msg << " error: " << SDL_GetError() << std::endl;
	}
	else
		std::cout << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt << std::endl;
}
void IHM::initsdl(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font* font[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << std::endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	else {
		window = SDL_CreateWindow("Pacman",
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (window == nullptr) {
			logSDLError(std::cout, "CreateWindow");
			SDL_Quit();
		}
		else
			logfileconsole("CreateWindow Success");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//| SDL_RENDERER_PRESENTVSYNC
		if (renderer == nullptr) {
			logSDLError(std::cout, "CreateRenderer");
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0) {
			logSDLError(std::cout, "TTF_Init");
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
		else
			logfileconsole("TTF_Init Success");


		const std::string fontFile = "arial.ttf";

		for (Uint8 i = 1; i < FONTMAX; i++)
			font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
	}
}
void IHM::initTile(tile& map, bool wall, Uint8 entity) {
	map.wall = wall; map.entity = entity;
}
void IHM::forme(tile& tmap, std::vector<std::vector<tile>>& map, unsigned int length, unsigned int height) {
	for (unsigned int i = 0; i < length; i++) {
		for (unsigned int j = 0; j < height; j++)
			initTile(map[tmap.tile_nbx + i][tmap.tile_nby + j], true, nothing);
	}
}
void IHM::initGrid(std::vector<std::vector<tile>>& map) {
	/*
		Initialisation d'un niveau unique de Pacman
	*/
	tile kTile;
	map.clear();
	std::vector<tile> blank;
	for (unsigned int x = 0; x < MAP_LENGTH; x++) {
		map.push_back(blank);
		for (unsigned int y = 0; y < MAP_HEIGHT; y++) {

			kTile.tile_nbx = x;
			kTile.tile_nby = y;
			kTile.tile_x = tileSize * x + (SCREEN_WIDTH / 2 - (MAP_LENGTH / 2 * tileSize));
			kTile.tile_y = tileSize * y + (SCREEN_HEIGHT / 2 - (MAP_HEIGHT / 2 * tileSize));
			if (x == 0 || x == MAP_LENGTH - 1 || y == 0 || y == MAP_HEIGHT - 1) {
				kTile.wall = true;
				kTile.entity = nothing;
			}
			else {
				kTile.wall = false;
				kTile.entity = gold;
			}
			map[x].push_back(kTile);
		}
	}
	// ouverture
	initTile(map[0][12], false, nothing);
	initTile(map[MAP_LENGTH - 1][12], false, nothing);

	// 
	initTile(map[1][1], false, cherry);
	initTile(map[1][MAP_HEIGHT - 2], false, strawberry);
	initTile(map[MAP_LENGTH - 2][1], false, peach);
	initTile(map[MAP_LENGTH - 2][MAP_HEIGHT - 2], false, apple);

	// blocs de murs
	forme(map[1][11], map, 4, 1); // 1
	forme(map[1][13], map, 4, 1); // 2
	forme(map[2][2], map, 4, 2); // 3
	forme(map[2][5], map, 2, 3); // 4
	forme(map[2][9], map, 2, 1); // 5
	forme(map[2][15], map, 4, 2); // 6
	forme(map[2][18], map, 1, 5); // 7
	forme(map[4][18], map, 2, 2); // 8
	forme(map[4][21], map, 2, 2); // 9
	forme(map[5][5], map, 1, 5); // 10
	initTile(map[6][11], true, nothing); // 11a
	initTile(map[6][13], true, nothing); // 12a
	forme(map[7][2], map, 1, 3); // 13
	forme(map[7][6], map, 1, 2); // 11b
	forme(map[7][8], map, 2, 4); // 11c
	forme(map[7][13], map, 2, 4); // 12b
	forme(map[7][18], map, 2, 3); // 14
	forme(map[7][22], map, 4, 1); // 15a
	forme(map[9][2], map, 2, 5); // 16
	forme(map[10][8], map, 5, 1); // 17a
	forme(map[10][10], map, 2, 1); // 18a
	forme(map[10][11], map, 1, 4); // 18b
	initTile(map[10][16], true, nothing); // 19
	forme(map[10][18], map, 5, 1); // 20a
	forme(map[10][20], map, 1, 2); // 15b
	forme(map[11][14], map, 3, 1); // 18c
	forme(map[12][1], map, 1, 4); // 21
	forme(map[12][6], map, 1, 2); // 17b
	forme(map[12][16], map, 1, 2); // 20b
	forme(map[12][20], map, 1, 4); // 22
	forme(map[13][10], map, 2, 1); // 18d
	forme(map[14][2], map, 2, 5); // 23
	forme(map[14][11], map, 1, 4); // 18e
	initTile(map[14][16], true, nothing); // 24
	forme(map[14][20], map, 1, 2); // 25a
	forme(map[14][22], map, 4, 1); // 25b
	forme(map[16][8], map, 2, 4); // 26a
	forme(map[16][13], map, 2, 4); // 27a
	forme(map[16][18], map, 2, 3); // 28
	forme(map[17][2], map, 1, 3); // 29
	forme(map[17][6], map, 1, 2); // 26b
	initTile(map[18][11], true, nothing); // 26c
	initTile(map[18][13], true, nothing); // 27b
	forme(map[19][2], map, 4, 2); // 30
	forme(map[19][5], map, 1, 5); // 31
	forme(map[19][15], map, 4, 2); // 32
	forme(map[19][18], map, 2, 2); // 33
	forme(map[19][21], map, 2, 2); // 34
	forme(map[20][11], map, 4, 1); // 35
	forme(map[20][13], map, 4, 1); // 36
	forme(map[21][5], map, 2, 3); // 37
	forme(map[21][9], map, 2, 1); // 38
	forme(map[22][18], map, 1, 5); // 39

	
}
void IHM::calculimage(sysinfo& information) {
	logfileconsole("_calculimage Start_");

	std::string IPath = "image/";
	information.variable.statescreen = STATEplay;
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "tile32/Black.bmp", "Black.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "tile32/White.bmp", "White.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "map.png", "map.png", (Uint8)255, -1, -1, NULL, NULL);

	std::string ghostName[MAXGHOST] = { "Red", "Blue", "Yellow", "Pink" }, Pos[MAXPOS] = { "U", "L", "D", "R" };
	for (unsigned int i = 0; i < MAXPOS; i++) {
		for (unsigned int j = 1; j < 3; j++)
			Texture::loadImage(information.ecran.renderer, information.allTextures.pacman, information.variable.statescreen, information.variable.select,
				IPath + "pacman/pacman_" + Pos[i] + "_" + std::to_string(j) + ".png", "pacman_" + Pos[i] + "_" + std::to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
	}

	// permet de charger les 32 Textures des Ghost (8 par Ghost, dont 4 pour les position avec le 1er skin et les 4 autres pour l'autre skin(alternateskin))
	std::vector<Texture*>* ghostTab[MAXGHOST] = { &information.allTextures.red, &information.allTextures.blue,
		&information.allTextures.yellow, &information.allTextures.pink };
	for (unsigned int i = 0; i < MAXGHOST; i++) { // nb de ghost
		for (unsigned int j = 1; j < 3; j++) { // skin or alternate skin
			for (unsigned int k = 0; k < MAXPOS; k++) // UP, LEFT, DOWN, RIGHT
				Texture::loadImage(information.ecran.renderer, *ghostTab[i], information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + std::to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + std::to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
		}
	}
	Texture::loadImage(information.ecran.renderer, information.allTextures.miscGhost, information.variable.statescreen, information.variable.select,
		IPath + "Ghost/not_Invincible.png", "not_Invincible.png", (Uint8)255, -1, -1, tileSize, tileSize);

	Texture::loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/gold.png", "gold.png", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/cherry.png", "cherry.png", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/strawberry.png", "strawberry.png", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/lemon.png", "lemon.png", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/pear.png", "pear.png", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.collectibles, information.variable.statescreen, information.variable.select,
		IPath + "collectibles/key.png", "key.png", (Uint8)255, -1, -1, tileSize, tileSize);


	information.variable.statescreen = STATEecrantitre;
	Texture::loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/linux.jpg", "linux.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2, NULL, NULL, center);
	Texture::loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/c++.jpg", "c++.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 400, NULL, NULL, center);
	Texture::loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/sudo.jpg", "sudo.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2, NULL, NULL, center);
	Texture::loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/PC_master_Race.jpg", "PC_master_Race.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 400, NULL, NULL, center);
	Texture::loadImage(information.ecran.renderer, information.allTextures.imgecrantitre, information.variable.statescreen, information.variable.select,
		IPath + "ecrantitre/matlab.jpg", "matlab.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350, NULL, NULL, center);
	int spacemenu = 64, initspacemenu = 400;

	// ______Buttons_____
	information.variable.statescreen = STATEecrantitre;
	Buttons::createbutton(information, information.allButton.buttonecrantitre,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, center);
	Buttons::createbutton(information, information.allButton.buttonecrantitre,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButton.buttonecrantitre,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButton.buttonecrantitre,
		shaded, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.variable.statescreen = STATEplay;
	Buttons::createbutton(information, information.allButton.buttonplay, shaded,
		"Pause", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, 0, center_x);
	Buttons::createbutton(information, information.allButton.buttonplay, shaded,
		"Initial Grid", WriteColorButton, BackColorButton, 32, 0, 128);
	Buttons::createbutton(information, information.allButton.buttonplay, shaded,
		"Go to leader board (END GAME)", WriteColorButton, BackColorButton, 32, 0, 0);
	Buttons::createbutton(information, information.allButton.buttonplay, shaded,
		"Save and Quit", WriteColorButton, BackColorButton, 32, 0, 64);

	information.variable.statescreen = STATEscore;
	Buttons::createbutton(information, information.allButton.buttonscore, shaded,
		"Return to Title Screen", WriteColorButton, BackColorButton, 32, 0, 0);

	// ______Writetxt_____ 
	information.variable.statescreen = STATEecrantitre;
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "Game dev in C++ and with SDL2.0.8", { 255, 127, 127, 255 }, NoColor, 18, 0, 0);
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "Developed by Joeffrey VILLERONCE and Robin SAUTER", { 127, 255, 127, 255 }, NoColor, 18, 0, 30);
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "New Super Pac-Man Plus DELUX Pro Turbo Edition", { 0, 64, 255, 255 }, NoColor, 50, SCREEN_WIDTH / 2, 100, center_x);
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "With ALL DLC For Only 99.99$ what a deal !!!", { 255, 255, 0, 255 }, NoColor, 25, SCREEN_WIDTH / 2, 160, center_x);
	Texture::loadwritetxt(information, information.allTextures.txtecrantitre,
		blended, "Use your mouse to select", { 0, 255, 0, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 350, center_x);


	information.variable.statescreen = STATEplay;
	Texture::loadwritetxt(information, information.allTextures.txtplay, blended,
		"Your Score", { 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, 50, center_x);
	Texture::loadwritetxt(information, information.allTextures.txtplay, blended,
		"You can move Pacman", { 0, 255, 0, 255 }, NoColor, 24, 100, 500);
	Texture::loadwritetxt(information, information.allTextures.txtplay, blended,
		"by pressing arrows on your keyboard", { 0, 255, 0, 255 }, NoColor, 24, 100, 524);
	information.variable.select = lost;
	Texture::loadwritetxt(information, information.allTextures.txtplay, blended,
		"YOU DIED", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, center);
	information.variable.select = win;
	Texture::loadwritetxt(information, information.allTextures.txtplay, blended,
		"YOU WIN", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, center);

	information.variable.select = selectnothing;
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "100", { 255, 0, 0, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "200", { 0, 64, 255, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "400", { 0, 255, 0, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "800", { 255, 0, 255, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "1600", { 255, 0, 255, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "5000", { 0, 64, 255, 255 }, NoColor, 26, -1, -1);

	information.variable.statescreen = STATEscore;
	information.variable.select = pause;
	Texture::loadwritetxt(information, information.allTextures.txtscore,
		blended, "TOP 10 SCORES", { 255, 0, 0, 255 }, NoColor, 50, SCREEN_WIDTH / 2, 100, center_x);
	Texture::loadwritetxt(information, information.allTextures.txtscore,
		blended, "Enter your name", { 0, 255, 0, 255 }, NoColor, 24, 100, 200);
	Texture::loadwritetxt(information, information.allTextures.txtscore,
		blended, "with your keyboard", { 0, 255, 0, 255 }, NoColor, 24, 100, 224);
	Texture::loadwritetxt(information, information.allTextures.txtscore,
		blended, "Remove last letter with backspace", { 0, 255, 0, 255 }, NoColor, 24, 100, 248);
	Texture::loadwritetxt(information, information.allTextures.txtscore,
		blended, "Press return when finish", { 0, 255, 0, 255 }, NoColor, 24, 100, 272);

	information.variable.select = selectnothing;
	logfileconsole("_calculimage End_");
}
void IHM::mouse(sysinfo& information, Pacman& Player, SDL_Event event) {
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT

	*/

	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(information, Player, event);


}
void IHM::cliqueGauche(sysinfo& information, Pacman& Player,SDL_Event event) {
	// recherche du bouton par comparaison de string et des positions x et y du clic

	switch (information.variable.statescreen) {
	case STATEplay:
		for (unsigned int i = 0; i < information.allButton.buttonplay.size(); i++) { // recherche si une bouton est dans ces coordonnées
			if (information.allButton.buttonplay[i]->searchButton((std::string)"Pause", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.buttonplay[i]->changeOn();
				if (information.allButton.buttonplay[i]->GETon())
					information.variable.select = pause;
				else
					information.variable.select = selectnothing;
				return;
			}
			else if (information.allButton.buttonplay[i]->searchButton((std::string)"Initial Grid", information.variable.statescreen, event.button.x, event.button.y)) {
				initGrid(information.map);
				return;
			}
			else if (information.allButton.buttonplay[i]->searchButton((std::string)"Save and Quit", information.variable.statescreen, event.button.x, event.button.y)) {
				SaveReload::save(information, Player);
				information.variable.continuer = false;
				return;
			}
			else if (information.allButton.buttonplay[i]->searchButton((std::string)"Go to leader board (END GAME)", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.statescreen = STATEscore;
				information.variable.select = pause;
				ecranScore(information, Player);
				return;
			}
		}
		break;
	case STATEecrantitre:
		for (unsigned int i = 0; i < information.allButton.buttonecrantitre.size(); i++) {
			if (information.allButton.buttonecrantitre[i]->searchButton((std::string)"New Game", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.statescreen = STATEplay;
				return;
			}
			else if (information.allButton.buttonecrantitre[i]->searchButton((std::string)"Reload", information.variable.statescreen, event.button.x, event.button.y)) {
				SaveReload::reload(information, Player);
				information.variable.statescreen = STATEplay;
				return;
			}
			else if (information.allButton.buttonecrantitre[i]->searchButton((std::string)"Option", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.continuer = false;
				return;
			}
			else if (information.allButton.buttonecrantitre[i]->searchButton((std::string)"Quit", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.continuer = false;
				return;
			}
		}
		break;
	case STATEscore:
		for (unsigned int i = 0; i < information.allButton.buttonscore.size(); i++) {
			if (information.allButton.buttonscore[i]->searchButton((std::string)"Return to Title Screen", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.select = selectnothing;
				ecrantitre(information);
				return;
			}
		}
		break;
	}
}
std::string IHM::getName(sysinfo& information, unsigned int position) {
	/*
		Demande au joueur son pseudo pour etre placé dans le tableau des scores
		Ne gère que les minuscules et les chiffres 0 à 9 qui ne sont pas sur le pavé numérique
		Fonctionne par cast avec le tableau ASCII
	*/
	SDL_Event event;
	std::string name;
	bool validCharacter = false, validChange = false;
	unsigned int initspacemenu = 200;
	while (true) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:	// permet de quitter le jeu
			information.variable.continuer = 0;
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym) {
			case SDLK_RETURN:
				return name;
				break;
			case SDLK_ESCAPE:
				return name;
			case SDLK_BACKSPACE:
				if (name.size() > 0) {
					name.pop_back();
					validChange = true;
				}
				break;
			}

			// lettre minuscule et chiffre clavier ascii
			if ((event.key.keysym.sym >= 97 && event.key.keysym.sym <= 122) || (event.key.keysym.sym >= 48 && event.key.keysym.sym <= 57)) {
				validCharacter = true;
				validChange = true;
			}
				
			if (validChange) {
				if(validCharacter)
					name += (char)event.key.keysym.sym;

				SDL_SetRenderDrawColor(information.ecran.renderer, 0, 0, 0, 255);
				SDL_RenderClear(information.ecran.renderer);
				information.allTextures.tabScore[position]->changeTextureMsg(information, blended,
					name + "      " + std::to_string(information.variable.tabScorePlayer[position].score),
					{ 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, initspacemenu += ((1 + position) * 32), center_x);
				initspacemenu = 200;
				for (unsigned int i = 0; i < information.allTextures.tabScore.size(); i++)
					information.allTextures.tabScore[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
				for (unsigned int i = 0; i < information.allTextures.txtscore.size(); i++)
					information.allTextures.txtscore[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
				SDL_RenderPresent(information.ecran.renderer);
			}
			validCharacter = false;
			validChange = false;
			break;
		}
	}

}
void IHM::ecrantitre(sysinfo& information) {
	/*

		affiche toutes les textures ainsi que les boutons ayant l'attribut _statescreen == STATEecrantitre

	*/
	logfileconsole("_Ecrantitres Start_");

	information.variable.statescreen = STATEecrantitre;
	SDL_SetRenderDrawColor(information.ecran.renderer, 0, 0, 0, 255);
	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allTextures.txtecrantitre.size(); i++)
		information.allTextures.txtecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);

	for (unsigned int i = 0; i < information.allTextures.imgecrantitre.size(); i++)
		information.allTextures.imgecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);

	for (unsigned int i = 0; i < information.allButton.buttonecrantitre.size(); i++)
		information.allButton.buttonecrantitre[i]->renderButton(information.ecran.renderer, information.variable.statescreen);


	SDL_RenderPresent(information.ecran.renderer);

	logfileconsole("_Ecrantitres End_");
}
void IHM::ecranScore(sysinfo& information, Pacman& player) {
	logfileconsole("_Ecrantitres Start_");

	information.variable.statescreen = STATEscore;
	int position = 0;
	scorePlayer p; p.name = ""; p.score = player.GETvalue();
	information.variable.tabScorePlayer.push_back(p);
	position = topScore(information.variable.tabScorePlayer, p.score);
	
	for (unsigned int i = 0; i < information.allTextures.tabScore.size(); i++)
		delete information.allTextures.tabScore[i];
	information.allTextures.tabScore.clear();
	unsigned int initspacemenu = 200;
	for (unsigned int i = 0; i < information.variable.tabScorePlayer.size(); i++)
		Texture::loadwritetxt(information, information.allTextures.tabScore,
			blended, information.variable.tabScorePlayer[i].name + "      " + std::to_string(information.variable.tabScorePlayer[i].score),
			{ 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, initspacemenu += 32, center_x);


	SDL_SetRenderDrawColor(information.ecran.renderer, 0, 0, 0, 255);
	SDL_RenderClear(information.ecran.renderer);
	for (unsigned int i = 0; i < information.allTextures.tabScore.size(); i++)
		information.allTextures.tabScore[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
	for (unsigned int i = 0; i < information.allTextures.txtscore.size(); i++) {
		if (information.allTextures.txtscore[i]->renderTextureTestString(information.ecran.renderer, "TOP 10 SCORES"))
			break;
	}
		

	if (position != -1) { // si dans le top 10
		for (unsigned int i = 0; i < information.allTextures.txtscore.size(); i++)
			information.allTextures.txtscore[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
		SDL_RenderPresent(information.ecran.renderer);
		information.variable.tabScorePlayer[position].name = getName(information, position);
	}

	SDL_SetRenderDrawColor(information.ecran.renderer, 0, 0, 0, 255);
	SDL_RenderClear(information.ecran.renderer);
	for (unsigned int i = 0; i < information.allTextures.tabScore.size(); i++)
		information.allTextures.tabScore[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
	for (unsigned int i = 0; i < information.allTextures.txtscore.size(); i++) {
		if (information.allTextures.txtscore[i]->renderTextureTestString(information.ecran.renderer, "TOP 10 SCORES"))
			break;
	}
	for (unsigned int i = 0; i < information.allButton.buttonscore.size(); i++)
		information.allButton.buttonscore[i]->renderButton(information.ecran.renderer, information.variable.statescreen);
	SDL_RenderPresent(information.ecran.renderer);

	logfileconsole("_Ecrantitres End_");
}
void IHM::alwaysrender(sysinfo& information, Pacman& player) {
	//clock_t t1, t2;
	//t1 = clock();
	std::vector<Texture*>* ghostTab[MAXGHOST] = { &information.allTextures.red, &information.allTextures.blue,
		&information.allTextures.yellow, &information.allTextures.pink };

	switch (information.variable.statescreen) {
	case STATEplay:
		/*
			fond gris et affichage de la map avec les couloirs et murs
		*/
		SDL_RenderClear(information.ecran.renderer);
		SDL_SetRenderDrawColor(information.ecran.renderer, 128, 128, 128, 0xFF);
		afficherMap(information);
		calculTime(information);

		/*
			changement de skin toutes 10 boucles (10 frames)
		*/
		information.variable.modulo = (information.variable.modulo + 1) % 10;
		if (information.variable.modulo == 0) {
			player.SETalternateSkin(!player.GETalternateSkin());
			for (unsigned int i = 0; i < information.ghost.size(); i++)
				information.ghost[i]->SETalternateSkin(!information.ghost[i]->GETalternateSkin());
		}


		for (unsigned int i = 0; i < information.allTextures.txtplay.size(); i++) {
			information.allTextures.txtplay[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
		}

		//
		player.afficherStats(information);
		player.afficher(information.ecran.renderer, information.allTextures.pacman);

		
		for (unsigned int i = 0; i < information.ghost.size(); i++)
			information.ghost[i]->afficher(information.ecran.renderer, *ghostTab[i], information.allTextures.miscGhost);


		information.variable.moduloScore = (information.variable.moduloScore + 1) % 30;
		if (player.GETtypeOfValue() != 0 || information.variable.tempoScore != 0) {
			if (player.GETtypeOfValue() != 0)
				information.variable.tempoScore = player.GETtypeOfValue();
			switch (information.variable.tempoScore) {
			case valuegold:
				information.allTextures.scoreValue[0]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			case valuecherry:
				information.allTextures.scoreValue[1]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			case valuestrawberry:
				information.allTextures.scoreValue[2]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			case valuepeach:
				information.allTextures.scoreValue[3]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			case valueapple:
				information.allTextures.scoreValue[4]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			}

			if (information.variable.moduloScore == 0)
				information.variable.tempoScore = 0;
		}

		for (unsigned int i = 0; i < information.allButton.buttonplay.size(); i++)
			information.allButton.buttonplay[i]->renderButton(information.ecran.renderer, information.variable.statescreen);


		SDL_RenderPresent(information.ecran.renderer);
		break;
	}

	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}
void IHM::afficherMap(sysinfo& information) {
	/*
		à utiliser si besoin de changer la map -> commenter l'autre partie du code
		screenshot de l'ecran et rogner sous paint pour n'utiliser que la map -> map.png à mettre dans le dossier image


	for (unsigned int i = 0; i < information.map.size(); i++) {
		if (information.map[i].wall)
			information.allTextures.ground[blackTile]->render(information.ecran.renderer, information.map[i].tile_x, information.map[i].tile_y);
		else {
			information.allTextures.ground[whiteTile]->render(information.ecran.renderer, information.map[i].tile_x, information.map[i].tile_y);
			if(information.map[i].entity != nothing)
				information.allTextures.collectibles[information.map[i].entity - 1]->render(information.ecran.renderer, information.map[i].tile_x, information.map[i].tile_y);
		}
	}
	*/

	information.allTextures.ground[mapTile]->render(information.ecran.renderer, information.map[0][0].tile_x, information.map[0][0].tile_y);
	for (unsigned int i = 0; i < MAP_LENGTH; i++) {
		for (unsigned int j = 0; j < MAP_HEIGHT; j++) {
			if (!information.map[i][j].wall && information.map[i][j].entity != nothing)
				information.allTextures.collectibles[information.map[i][j].entity - 1]->render(information.ecran.renderer,
					information.map[i][j].tile_x, information.map[i][j].tile_y);
		}
	}
}
void IHM::calculTime(sysinfo& information) {
	information.variable.onTime.frame = (information.variable.onTime.frame + 1) % 60;
	if (information.variable.onTime.frame == 0) {
		information.variable.onTime.seconds = (information.variable.onTime.seconds + 1) % 60;
		if (information.variable.onTime.seconds == 0) {
			information.variable.onTime.minutes = (information.variable.onTime.minutes + 1) % 60;
			if (information.variable.onTime.minutes == 0)
				information.variable.onTime.hours++;
		}
	}
	Texture::writetxt(information, blended,
		std::to_string(information.variable.onTime.hours) + ":"
		+ std::to_string(information.variable.onTime.minutes) + ":"
		+ std::to_string(information.variable.onTime.seconds),
		Black, NoColor, 24, SCREEN_WIDTH - 300, 0, center_x);
}
int IHM::topScore(std::vector<scorePlayer>& tabScorePlayer, unsigned int score) {
	/*
		Tri du tableau des scores dans le sens décroissant
		recherche si le score fait lors de cette partie est dans le TOP10
	*/
	std::vector<scorePlayer> newTabScore;
	scorePlayer player;
	unsigned int scoreToDestroy = 0, maxSize = 0;
	
	if (tabScorePlayer.size() > 10)
		maxSize = 10;
	else {
		maxSize = tabScorePlayer.size();
		if (score == 0)
			maxSize--;
	}
	while(newTabScore.size() < maxSize){ // TOP 10 SCORES
		for (unsigned int i = 0; i < tabScorePlayer.size(); i++) {
			if (tabScorePlayer[i].score > player.score) {
				scoreToDestroy = i;
				player.score = tabScorePlayer[i].score;
				player.name = tabScorePlayer[i].name;
			}
		}
		tabScorePlayer.erase(tabScorePlayer.begin() + scoreToDestroy);
		newTabScore.push_back(player);
		player.score = 0;
	}
	tabScorePlayer = newTabScore;

	int positionToReturn = -1;
	for (unsigned int i = 0; i < tabScorePlayer.size(); i++) {
		if (tabScorePlayer[i].score == score)
			positionToReturn = i;
	}
	return positionToReturn;
}
void IHM::deleteAll(sysinfo& information) {
	/*
		Destruction des allocations dynamiques et de la fenetre
	*/
	logfileconsole("*********_________ Start DeleteAll _________*********");

	for (unsigned int i = 1; i < FONTMAX; i++)
		TTF_CloseFont(information.allTextures.font[i]);

	deleteDyTabPlayerAndTextures(information.allTextures.ground, "ground Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.pacman, "pacman Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.red, "red Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.blue, "blue Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.yellow, "yellow Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.pink, "pink Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.miscGhost, "miscGhost Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.collectibles, "collectibles Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.scoreValue, "scoreValue Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.tabScore, "tabScore Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtecrantitre, "txtecrantitre Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtplay, "txtplay Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtplay, "txtscore Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.imgecrantitre, "imgecrantitre Texture");

	deleteDyTabPlayerAndTextures(information.allButton.buttonecrantitre, "Button ecrantitre");
	deleteDyTabPlayerAndTextures(information.allButton.buttonplay, "Button play");
	deleteDyTabPlayerAndTextures(information.allButton.buttonscore, "Button score");

	SDL_DestroyRenderer(information.ecran.renderer);
	SDL_DestroyWindow(information.ecran.window);
	information.ecran.renderer = nullptr;
	information.ecran.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}
bool IHM::assertIndexMap(int nbx, int nby) {
	if (nbx >= 0 && nby >= 0) {
		if (nbx < MAP_LENGTH && nby < MAP_HEIGHT)
			return true;
	}
	return false;
}

