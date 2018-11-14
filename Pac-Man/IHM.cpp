/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.16

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


/* *********************************************************
						 Init
  ********************************************************* */
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
bool IHM::initsdl(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font* font[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << std::endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		return false;
	}
	else {
		window = SDL_CreateWindow("Pacman",
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (window == nullptr) {
			logSDLError(std::cout, "CreateWindow");
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("CreateWindow Success");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//| SDL_RENDERER_PRESENTVSYNC
		if (renderer == nullptr) {
			logSDLError(std::cout, "CreateRenderer");
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0) {
			logSDLError(std::cout, "TTF_Init");
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("TTF_Init Success");


		for (Uint8 i = 1; i < MAX_FONT; i++)
			font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
		return true;
	}
}
void IHM::initTile(Tile& map, bool wall, Uint8 entity) {
	map.wall = wall; map.entity = entity;
}
void IHM::forme(Tile& tmap, std::vector<std::vector<Tile>>& map, Uint8 length, Uint8 height, bool wall) {
	for (Uint8 i = 0; i < length; i++) {
		for (Uint8 j = 0; j < height; j++) {
			if(wall)
				initTile(map[tmap.indexX + i][tmap.indexY + j], true, nothing);
			else
				initTile(map[tmap.indexX + i][tmap.indexY + j], false, nothing);
		}
	}
}
void IHM::initGrid(Map& map) {
	map.matriceMap.clear();
	Tile blankTile;
	std::vector<Tile> blank;
	for (Uint8 x = 0; x < map.map_length; x++) {
		map.matriceMap.push_back(blank);
		for (Uint8 y = 0; y < map.map_height; y++) {

			blankTile.indexX = x;
			blankTile.indexY = y;
			blankTile.tile_x = TILE_SIZE * x + (SCREEN_WIDTH / 2 - (map.map_length / 2 * TILE_SIZE));
			blankTile.tile_y = TILE_SIZE * y + (SCREEN_HEIGHT / 2 - (map.map_height / 2 * TILE_SIZE));
			if (x == 0 || x == map.map_length - 1 || y == 0 || y == map.map_height - 1) {
				blankTile.wall = true;
				blankTile.entity = nothing;
			}
			else {
				blankTile.wall = false;
				blankTile.entity = gold;
			}
			map.matriceMap[x].push_back(blankTile);
		}
	}
	// ouverture
	initTile(map.matriceMap[0][12], false, nothing);
	initTile(map.matriceMap[map.map_length - 1][12], false, nothing);

	// 
	initTile(map.matriceMap[1][1], false, cherry);
	initTile(map.matriceMap[1][map.map_height - 2], false, strawberry);
	initTile(map.matriceMap[map.map_length - 2][1], false, peach);
	initTile(map.matriceMap[map.map_length - 2][map.map_height - 2], false, apple);

	// ghost spawn
	forme(map.matriceMap[11][11], map.matriceMap, 3, 3, false);
	initTile(map.matriceMap[12][10], false, nothing);

	// blocs de murs
	forme(map.matriceMap[1][11], map.matriceMap, 4, 1); // 1
	forme(map.matriceMap[1][13], map.matriceMap, 4, 1); // 2
	forme(map.matriceMap[2][2], map.matriceMap, 4, 2); // 3
	forme(map.matriceMap[2][5], map.matriceMap, 2, 3); // 4
	forme(map.matriceMap[2][9], map.matriceMap, 2, 1); // 5
	forme(map.matriceMap[2][15], map.matriceMap, 4, 2); // 6
	forme(map.matriceMap[2][18], map.matriceMap, 1, 5); // 7
	forme(map.matriceMap[4][18], map.matriceMap, 2, 2); // 8
	forme(map.matriceMap[4][21], map.matriceMap, 2, 2); // 9
	forme(map.matriceMap[5][5], map.matriceMap, 1, 5); // 10
	initTile(map.matriceMap[6][11], true, nothing); // 11a
	initTile(map.matriceMap[6][13], true, nothing); // 12a
	forme(map.matriceMap[7][2], map.matriceMap, 1, 3); // 13
	forme(map.matriceMap[7][6], map.matriceMap, 1, 2); // 11b
	forme(map.matriceMap[7][8], map.matriceMap, 2, 4); // 11c
	forme(map.matriceMap[7][13], map.matriceMap, 2, 4); // 12b
	forme(map.matriceMap[7][18], map.matriceMap, 2, 3); // 14
	forme(map.matriceMap[7][22], map.matriceMap, 4, 1); // 15a
	forme(map.matriceMap[9][2], map.matriceMap, 2, 5); // 16
	forme(map.matriceMap[10][8], map.matriceMap, 5, 1); // 17a
	forme(map.matriceMap[10][10], map.matriceMap, 2, 1); // 18a
	forme(map.matriceMap[10][11], map.matriceMap, 1, 4); // 18b
	initTile(map.matriceMap[10][16], true, nothing); // 19
	forme(map.matriceMap[10][18], map.matriceMap, 5, 1); // 20a
	forme(map.matriceMap[10][20], map.matriceMap, 1, 2); // 15b
	forme(map.matriceMap[11][14], map.matriceMap, 3, 1); // 18c
	forme(map.matriceMap[12][1], map.matriceMap, 1, 4); // 21
	forme(map.matriceMap[12][6], map.matriceMap, 1, 2); // 17b
	forme(map.matriceMap[12][16], map.matriceMap, 1, 2); // 20b
	forme(map.matriceMap[12][20], map.matriceMap, 1, 4); // 22
	forme(map.matriceMap[13][10], map.matriceMap, 2, 1); // 18d
	forme(map.matriceMap[14][2], map.matriceMap, 2, 5); // 23
	forme(map.matriceMap[14][11], map.matriceMap, 1, 4); // 18e
	initTile(map.matriceMap[14][16], true, nothing); // 24
	forme(map.matriceMap[14][20], map.matriceMap, 1, 2); // 25a
	forme(map.matriceMap[14][22], map.matriceMap, 4, 1); // 25b
	forme(map.matriceMap[16][8], map.matriceMap, 2, 4); // 26a
	forme(map.matriceMap[16][13], map.matriceMap, 2, 4); // 27a
	forme(map.matriceMap[16][18], map.matriceMap, 2, 3); // 28
	forme(map.matriceMap[17][2], map.matriceMap, 1, 3); // 29
	forme(map.matriceMap[17][6], map.matriceMap, 1, 2); // 26b
	initTile(map.matriceMap[18][11], true, nothing); // 26c
	initTile(map.matriceMap[18][13], true, nothing); // 27b
	forme(map.matriceMap[19][2], map.matriceMap, 4, 2); // 30
	forme(map.matriceMap[19][5], map.matriceMap, 1, 5); // 31
	forme(map.matriceMap[19][15], map.matriceMap, 4, 2); // 32
	forme(map.matriceMap[19][18], map.matriceMap, 2, 2); // 33
	forme(map.matriceMap[19][21], map.matriceMap, 2, 2); // 34
	forme(map.matriceMap[20][11], map.matriceMap, 4, 1); // 35
	forme(map.matriceMap[20][13], map.matriceMap, 4, 1); // 36
	forme(map.matriceMap[21][5], map.matriceMap, 2, 3); // 37
	forme(map.matriceMap[21][9], map.matriceMap, 2, 1); // 38
	forme(map.matriceMap[22][18], map.matriceMap, 1, 5); // 39
}
void IHM::calculimage(Sysinfo& sysinfo) {
	logfileconsole("_calculimage Start_");

	/* *********************************************************
						 Textures
  ********************************************************* */
	std::string IPath = "image/";
	sysinfo.var.stateScreen = STATEplay;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "tile32/Black.bmp", "Black.bmp", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "tile32/White.bmp", "White.bmp", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "map.png", "map.png", (Uint8)255, -1, -1, NULL, NULL);

	std::string ghostName[MAX_GHOST] = { "Red", "Blue", "Yellow", "Pink" }, Pos[MAX_POS] = { "U", "L", "D", "R" };
	for (unsigned int i = 0; i < MAX_POS; i++) {
		for (unsigned int j = 1; j < 3; j++)
			Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.pacman, sysinfo.var.stateScreen, sysinfo.var.select,
				IPath + "pacman/pacman_" + Pos[i] + "_" + std::to_string(j) + ".png", "pacman_" + Pos[i] + "_" + std::to_string(j) + ".png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	}

	// permet de charger les 32 Textures des Ghost (8 par Ghost, dont 4 pour les position avec le 1er skin et les 4 autres pour l'autre skin(alternateskin))
	std::vector<Texture*>* ghostTab[MAX_GHOST] = { &sysinfo.allTextures.red, &sysinfo.allTextures.blue,
		&sysinfo.allTextures.yellow, &sysinfo.allTextures.pink };
	for (unsigned int i = 0; i < MAX_GHOST; i++) { // nb de ghost
		for (unsigned int j = 1; j < MAX_SKIN + 1; j++) { // skin or alternate skin
			for (unsigned int k = 0; k < MAX_POS; k++) // UP, LEFT, DOWN, RIGHT
				Texture::loadImage(sysinfo.screen.renderer, *ghostTab[i], sysinfo.var.stateScreen,
						sysinfo.var.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + std::to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + std::to_string(j) + ".png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
		}
	}
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.miscGhost, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "Ghost/not_Invincible_B.png", "not_Invincible_B.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.miscGhost, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "Ghost/not_Invincible_W.png", "not_Invincible_W.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.miscGhost, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "Ghost/goHome.png", "goHome.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);

	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "collectibles/gold.png", "gold.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "collectibles/cherry.png", "cherry.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "collectibles/strawberry.png", "strawberry.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "collectibles/lemon.png", "lemon.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "collectibles/pear.png", "pear.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "collectibles/key.png", "key.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);


	sysinfo.var.stateScreen = STATEecranTitre;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecranTitre, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "ecranTitre/linux.jpg", "linux.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2, NULL, NULL, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecranTitre, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "ecranTitre/c++.jpg", "c++.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 400, NULL, NULL, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecranTitre, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "ecranTitre/sudo.jpg", "sudo.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2, NULL, NULL, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecranTitre, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "ecranTitre/PC_master_Race.jpg", "PC_master_Race.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 400, NULL, NULL, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecranTitre, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "ecranTitre/matlab.jpg", "matlab.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350, NULL, NULL, center);
	


	/* *********************************************************
						 Buttons
  ********************************************************* */
	int spacemenu = 64, initspacemenu = 400;
	sysinfo.var.stateScreen = STATEecranTitre;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.buttonTexteEcranTitre,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.buttonTexteEcranTitre,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.buttonTexteEcranTitre,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.buttonTexteEcranTitre,
		shaded, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);

	ButtonImage::createButtonImage(sysinfo.screen.renderer, sysinfo.allButtons.buttonImageEcranTitre, sysinfo.var.stateScreen, sysinfo.var.select,
		IPath + "Boutons/EcranTitre/confirm.png", "confirm", nonTransparent, 1500, 0, 64, 64, center_x);




	sysinfo.var.stateScreen = STATEplay;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.buttonTextePlay,
		shaded, "Pause", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.buttonTextePlay,
		shaded, "Go to leader board (END GAME)", WriteColorButton, BackColorButton, 32, 0, 0, nonTransparent);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.buttonTextePlay,
		shaded, "Save and Quit", WriteColorButton, BackColorButton, 32, 0, 64, nonTransparent);

	sysinfo.var.stateScreen = STATEscore;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.buttonTexteScore,
		shaded, "Return to Title Screen", WriteColorButton, BackColorButton, 32, 0, 0, nonTransparent);


	/* *********************************************************
							Textes
  ********************************************************* */
	sysinfo.var.stateScreen = STATEecranTitre;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtecranTitre,
		blended, "Game dev in C++ and with SDL2.0.8", { 255, 127, 127, 255 }, NoColor, 18, 0, 0, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtecranTitre,
		blended, "Developed by Joeffrey VILLERONCE and Robin SAUTER", { 127, 255, 127, 255 }, NoColor, 18, 0, 30, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtecranTitre,
		blended, "New Super Pac-Man Plus DELUX Pro Turbo Edition", { 0, 64, 255, 255 }, NoColor, 50, SCREEN_WIDTH / 2, 100, nonTransparent, center_x);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtecranTitre,
		blended, "With ALL DLC For Only 99.99$ what a deal !!!", { 255, 255, 0, 255 }, NoColor, 25, SCREEN_WIDTH / 2, 160, nonTransparent, center_x);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtecranTitre,
		blended, "Use your mouse to select", { 0, 255, 0, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 350, nonTransparent, center_x);


	sysinfo.var.stateScreen = STATEplay;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtPlay,
		blended, "Your Score", { 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, 50, nonTransparent, center_x);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtPlay,
		blended, "You can move Pacman", { 0, 255, 0, 255 }, NoColor, 24, 100, 500, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtPlay,
		blended, "by pressing arrows on your keyboard", { 0, 255, 0, 255 }, NoColor, 24, 100, 524, nonTransparent);
	sysinfo.var.select = lost;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtPlay,
		blended, "YOU DIED", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, nonTransparent, center);
	sysinfo.var.select = win;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtPlay, 
		blended, "YOU WIN", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, nonTransparent, center);

	sysinfo.var.select = selectnothing;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "100", { 255, 0, 0, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "200", { 0, 64, 255, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "400", { 0, 255, 0, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "800", { 255, 0, 255, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "1600", { 255, 0, 255, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "5000", { 0, 64, 255, 255 }, NoColor, 26, -1, -1, nonTransparent);

	sysinfo.var.stateScreen = STATEscore;
	sysinfo.var.select = pause;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "TOP 10 SCORES", { 255, 0, 0, 255 }, NoColor, 50, SCREEN_WIDTH / 2, 100, nonTransparent, center_x);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "Enter your name", { 0, 255, 0, 255 }, NoColor, 24, 100, 200, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "with your keyboard", { 0, 255, 0, 255 }, NoColor, 24, 100, 224, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "Remove last letter with backspace", { 0, 255, 0, 255 }, NoColor, 24, 100, 248, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "Press return when finish", { 0, 255, 0, 255 }, NoColor, 24, 100, 272, nonTransparent);

	sysinfo.var.select = selectnothing;
	logfileconsole("_calculimage End_");
}


/* *********************************************************
						 In Game
  ********************************************************* */

//--- Evenements -------------------------------------------------------------------------------------------------------------------------------------

void IHM::eventSDL(Sysinfo& sysinfo) {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:	// permet de quitter le jeu
			sysinfo.var.continuer = 0;
			break;
		case SDL_KEYDOWN: // test sur le type d'�v�nement touche enfonc�
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				sysinfo.pacman->SETnextHeading(UP);
				break;
			case SDLK_DOWN:
				sysinfo.pacman->SETnextHeading(DOWN);
				break;
			case SDLK_RIGHT:
				sysinfo.pacman->SETnextHeading(RIGHT);
				break;
			case SDLK_LEFT:
				sysinfo.pacman->SETnextHeading(LEFT);
				break;
			case SDLK_ESCAPE:
				sysinfo.var.continuer = 0;
				break;
			case SDLK_SPACE:

				break;
			}
		case SDL_MOUSEBUTTONDOWN: // test sur le type d'�v�nement click souris (enfonc�)
			IHM::mouse(sysinfo, event);
			break;
		case SDL_MOUSEWHEEL:
			//wheel(sysinfo, event.wheel.y);
			break;
		}
	}
}
void IHM::mouse(Sysinfo& sysinfo, SDL_Event event) {
	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(sysinfo, event);
}
void IHM::cliqueGauche(Sysinfo& sysinfo, SDL_Event event) {
	switch (sysinfo.var.stateScreen) {
	case STATEplay:
		for (unsigned int i = 0; i < sysinfo.allButtons.buttonTextePlay.size(); i++) { // recherche si une bouton est dans ces coordonn�es
			if (sysinfo.allButtons.buttonTextePlay[i]->searchButtonTexte((std::string)"Pause", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				sysinfo.allButtons.buttonTextePlay[i]->changeOn();
				if (sysinfo.allButtons.buttonTextePlay[i]->GETon())
					sysinfo.var.select = pause;
				else
					sysinfo.var.select = selectnothing;
				return;
			}
			else if (sysinfo.allButtons.buttonTextePlay[i]->searchButtonTexte((std::string)"Save and Quit", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				SaveReload::save(sysinfo);
				sysinfo.var.continuer = false;
				return;
			}
			else if (sysinfo.allButtons.buttonTextePlay[i]->searchButtonTexte((std::string)"Go to leader board (END GAME)", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				sysinfo.var.stateScreen = STATEscore;
				sysinfo.var.select = pause;
				ecranScore(sysinfo);
				return;
			}
		}
		break;
	case STATEecranTitre:
		for (unsigned int i = 0; i < sysinfo.allButtons.buttonTexteEcranTitre.size(); i++) {
			if (sysinfo.allButtons.buttonTexteEcranTitre[i]->searchButtonTexte((std::string)"New Game", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				sysinfo.var.stateScreen = STATEplay;
				initGrid(sysinfo.map);
				Entity::initEntity(sysinfo.pacman, sysinfo.ghost, sysinfo.map.matriceMap);
				return;
			}
			else if (sysinfo.allButtons.buttonTexteEcranTitre[i]->searchButtonTexte((std::string)"Reload", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				initGrid(sysinfo.map);
				Entity::initEntity(sysinfo.pacman, sysinfo.ghost, sysinfo.map.matriceMap);
				if(SaveReload::reload(sysinfo))
					sysinfo.var.stateScreen = STATEplay;
				else
					sysinfo.var.continuer = false;
				return;
			}
			else if (sysinfo.allButtons.buttonTexteEcranTitre[i]->searchButtonTexte((std::string)"Option", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				sysinfo.var.continuer = false;
				return;
			}
			else if (sysinfo.allButtons.buttonTexteEcranTitre[i]->searchButtonTexte((std::string)"Quit", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				sysinfo.var.continuer = false;
				return;
			}
		}
		for (unsigned int i = 0; i < sysinfo.allButtons.buttonImageEcranTitre.size(); i++) {
			if (sysinfo.allButtons.buttonImageEcranTitre[i]->searchButtonImage((std::string)"confirm", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				sysinfo.allButtons.buttonImageEcranTitre[i]->changeOn();
				ecranTitre(sysinfo);
				return;
			}
		}
		break;
	case STATEscore:
		for (unsigned int i = 0; i < sysinfo.allButtons.buttonTexteScore.size(); i++) {
			if (sysinfo.allButtons.buttonTexteScore[i]->searchButtonTexte((std::string)"Return to Title Screen", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
				sysinfo.var.select = selectnothing;
				ecranTitre(sysinfo);
				return;
			}
		}
		break;
	}
}

//--- Affichage --------------------------------------------------------------------------------------------------------------------------------------

void IHM::ecranTitre(Sysinfo& sysinfo) {
	logfileconsole("_ecranTitres Start_");

	sysinfo.var.stateScreen = STATEecranTitre;
	SDL_SetRenderDrawColor(sysinfo.screen.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sysinfo.screen.renderer);

	for (unsigned int i = 0; i < sysinfo.allTextes.txtecranTitre.size(); i++)
		sysinfo.allTextes.txtecranTitre[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.stateScreen, sysinfo.var.select);

	for (unsigned int i = 0; i < sysinfo.allTextures.imgecranTitre.size(); i++)
		sysinfo.allTextures.imgecranTitre[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.stateScreen, sysinfo.var.select);

	for (unsigned int i = 0; i < sysinfo.allButtons.buttonTexteEcranTitre.size(); i++)
		sysinfo.allButtons.buttonTexteEcranTitre[i]->renderButtonTexte(sysinfo.screen.renderer, sysinfo.var.stateScreen);

	for (unsigned int i = 0; i < sysinfo.allButtons.buttonImageEcranTitre.size(); i++)
		sysinfo.allButtons.buttonImageEcranTitre[i]->renderButtonImage(sysinfo.screen.renderer, sysinfo.var.stateScreen);


	SDL_RenderPresent(sysinfo.screen.renderer);

	logfileconsole("_ecranTitres End_");
}
void IHM::ecranScore(Sysinfo& sysinfo) {
	logfileconsole("_ecranTitres Start_");

	sysinfo.var.stateScreen = STATEscore;
	int8_t position = 0;
	ScorePlayer p; p.name = ""; p.score = sysinfo.pacman->GETvalue();
	sysinfo.var.saveReload.GETtabScorePlayerNONCONST().push_back(p);
	position = topScore(sysinfo.var.saveReload.GETtabScorePlayerNONCONST(), p.score);
	
	for (unsigned int i = 0; i < sysinfo.allTextes.tabScore.size(); i++)
		delete sysinfo.allTextes.tabScore[i];
	sysinfo.allTextes.tabScore.clear();
	unsigned int initspacemenu = 200;
	for (unsigned int i = 0; i < sysinfo.var.saveReload.GETtabScorePlayer().size(); i++)
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.tabScore,
			blended, sysinfo.var.saveReload.GETtabScorePlayer()[i].name + "      " + std::to_string(sysinfo.var.saveReload.GETtabScorePlayer()[i].score),
			{ 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, initspacemenu += 32, nonTransparent, center_x);


	SDL_SetRenderDrawColor(sysinfo.screen.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sysinfo.screen.renderer);
	for (unsigned int i = 0; i < sysinfo.allTextes.tabScore.size(); i++)
		sysinfo.allTextes.tabScore[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.stateScreen, sysinfo.var.select);
	for (unsigned int i = 0; i < sysinfo.allTextes.txtScore.size(); i++) {
		if (sysinfo.allTextes.txtScore[i]->renderTextureTestString(sysinfo.screen.renderer, "TOP 10 SCORES"))
			break;
	}
		

	if (position != -1) { // si dans le top 10
		for (unsigned int i = 0; i < sysinfo.allTextes.txtScore.size(); i++)
			sysinfo.allTextes.txtScore[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.stateScreen, sysinfo.var.select);
		SDL_RenderPresent(sysinfo.screen.renderer);
		sysinfo.var.saveReload.GETtabScorePlayerNONCONST()[position].name = getName(sysinfo.screen.renderer,sysinfo.allTextes.font,
			sysinfo.var, sysinfo.allTextes.txtScore, sysinfo.allTextes.tabScore, position);
	}

	SDL_SetRenderDrawColor(sysinfo.screen.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sysinfo.screen.renderer);
	for (unsigned int i = 0; i < sysinfo.allTextes.tabScore.size(); i++)
		sysinfo.allTextes.tabScore[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.stateScreen, sysinfo.var.select);
	for (unsigned int i = 0; i < sysinfo.allTextes.txtScore.size(); i++) {
		if (sysinfo.allTextes.txtScore[i]->renderTextureTestString(sysinfo.screen.renderer, "TOP 10 SCORES"))
			break;
	}
	for (unsigned int i = 0; i < sysinfo.allButtons.buttonTexteScore.size(); i++)
		sysinfo.allButtons.buttonTexteScore[i]->renderButtonTexte(sysinfo.screen.renderer, sysinfo.var.stateScreen);
	SDL_RenderPresent(sysinfo.screen.renderer);

	logfileconsole("_ecranTitres End_");
}
void IHM::alwaysRender(Sysinfo& sysinfo) {
	//clock_t t1, t2;
	//t1 = clock();

	switch (sysinfo.var.stateScreen) {
	case STATEplay:
		/*
			fond gris et affichage de la map avec les couloirs et murs
		*/
		SDL_RenderClear(sysinfo.screen.renderer);
		SDL_SetRenderDrawColor(sysinfo.screen.renderer, 128, 128, 128, 0xFF);
		afficherMap(sysinfo);

		
		sysinfo.var.gameTime.t2RealTime = clock();
		calculTime(sysinfo.var.gameTime);
		if (!sysinfo.var.gameTime.startTimerRealTime) {
			sysinfo.var.gameTime.startTimerRealTime = true;
			sysinfo.var.gameTime.t1RealTime = clock();
		}
		
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended, "Run Time : " +
			std::to_string(sysinfo.var.gameTime.hoursRunTime) + ":"+ std::to_string(sysinfo.var.gameTime.minutesRunTime) + ":"
			+ std::to_string(sysinfo.var.gameTime.secondsRunTime), Black, NoColor, 24, SCREEN_WIDTH - 300, 0, center_x);

		std::ostringstream stream;
		stream << std::fixed << std::setprecision(0) << (((double)sysinfo.var.gameTime.t2RealTime - (double)sysinfo.var.gameTime.t1RealTime) / CLOCKS_PER_SEC);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended, "Real Time : " +
			stream.str() + " secondes", Black, NoColor, 24, SCREEN_WIDTH - 300, 50, center_x);

	

		/*
			changement de skin toutes 10 boucles (10 frames)
		*/
		sysinfo.var.modulo = (sysinfo.var.modulo + 1) % (SCREEN_REFRESH_RATE / 6);
		if (sysinfo.var.modulo == 0) {
			sysinfo.pacman->SETalternateSkin(!sysinfo.pacman->GETalternateSkin());
			for (unsigned int i = 0; i < sysinfo.ghost.size(); i++)
				sysinfo.ghost[i]->SETalternateSkin(!sysinfo.ghost[i]->GETalternateSkin());
		}


		for (unsigned int i = 0; i < sysinfo.allTextes.txtPlay.size(); i++) {
			sysinfo.allTextes.txtPlay[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.stateScreen, sysinfo.var.select);
		}

		//
		std::vector<Texture*> pacmanTab[1] = { sysinfo.allTextures.pacman };
		sysinfo.pacman->afficherStats(sysinfo.screen.renderer, sysinfo.allTextes.font);
		sysinfo.pacman->afficher(sysinfo.screen.renderer, pacmanTab);

		
		std::vector<Texture*> ghostTab[MAX_GHOST + 1] = { sysinfo.allTextures.red, sysinfo.allTextures.blue,
		sysinfo.allTextures.yellow, sysinfo.allTextures.pink , sysinfo.allTextures.miscGhost };
		for (unsigned int i = 0; i < sysinfo.ghost.size(); i++)
			sysinfo.ghost[i]->afficher(sysinfo.screen.renderer, ghostTab);


		sysinfo.var.moduloScore = (sysinfo.var.moduloScore + 1) % (SCREEN_REFRESH_RATE / 2);
		if (sysinfo.pacman->GETtypeOfValue() != 0 || sysinfo.var.tempoScore != 0) {
			if (sysinfo.pacman->GETtypeOfValue() != 0)
				sysinfo.var.tempoScore = sysinfo.pacman->GETtypeOfValue();
			switch (sysinfo.var.tempoScore) {
			case valuegold:
				sysinfo.allTextes.scoreValue[gold - 1]->render(sysinfo.screen.renderer, sysinfo.pacman->GETx() + TILE_SIZE, sysinfo.pacman->GETy() + TILE_SIZE);
				break;
			case valuecherry:
				sysinfo.allTextes.scoreValue[cherry - 1]->render(sysinfo.screen.renderer, sysinfo.pacman->GETx() + TILE_SIZE, sysinfo.pacman->GETy() + TILE_SIZE);
				break;
			case valuestrawberry:
				sysinfo.allTextes.scoreValue[strawberry - 1]->render(sysinfo.screen.renderer, sysinfo.pacman->GETx() + TILE_SIZE, sysinfo.pacman->GETy() + TILE_SIZE);
				break;
			case valuepeach:
				sysinfo.allTextes.scoreValue[peach - 1]->render(sysinfo.screen.renderer, sysinfo.pacman->GETx() + TILE_SIZE, sysinfo.pacman->GETy() + TILE_SIZE);
				break;
			case valueapple:
				sysinfo.allTextes.scoreValue[apple - 1]->render(sysinfo.screen.renderer, sysinfo.pacman->GETx() + TILE_SIZE, sysinfo.pacman->GETy() + TILE_SIZE);
				break;
			}

			if (sysinfo.var.moduloScore == 0)
				sysinfo.var.tempoScore = 0;
		}

		for (unsigned int i = 0; i < sysinfo.allButtons.buttonTextePlay.size(); i++)
			sysinfo.allButtons.buttonTextePlay[i]->renderButtonTexte(sysinfo.screen.renderer, sysinfo.var.stateScreen);


		SDL_RenderPresent(sysinfo.screen.renderer);
		break;
	}

	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysRender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}
void IHM::afficherMap(Sysinfo& sysinfo) {
	/*
		� utiliser si besoin de changer la map -> commenter l'autre partie du code
		screenshot de l'ecran et rogner sous paint pour n'utiliser que la map -> map.png � mettre dans le dossier image
	*/
	
	for (Uint8 i = 0; i < sysinfo.map.map_length; i++) {
		for (Uint8 j = 0; j < sysinfo.map.map_height; j++) {
			if (sysinfo.map.matriceMap[i][j].wall)
				sysinfo.allTextures.ground[blackTile]->render(sysinfo.screen.renderer, sysinfo.map.matriceMap[i][j].tile_x, sysinfo.map.matriceMap[i][j].tile_y);
			else {
				sysinfo.allTextures.ground[whiteTile]->render(sysinfo.screen.renderer, sysinfo.map.matriceMap[i][j].tile_x, sysinfo.map.matriceMap[i][j].tile_y);
				if (sysinfo.map.matriceMap[i][j].entity != nothing)
					sysinfo.allTextures.collectibles[sysinfo.map.matriceMap[i][j].entity - 1]->render(sysinfo.screen.renderer, sysinfo.map.matriceMap[i][j].tile_x, sysinfo.map.matriceMap[i][j].tile_y);
			}
		}
	}
	

	/*
	sysinfo.allTextures.ground[mapTile]->render(sysinfo.screen.renderer, sysinfo.map.matriceMap[0][0].tile_x, sysinfo.map.matriceMap[0][0].tile_y);
	for (Uint8 i = 0; i < sysinfo.map.map_length; i++) {
		for (Uint8 j = 0; j < sysinfo.map.map_height; j++) {
			if (!sysinfo.map.matriceMap[i][j].wall && sysinfo.map.matriceMap[i][j].entity != nothing)
				sysinfo.allTextures.collectibles[sysinfo.map.matriceMap[i][j].entity - 1]->render(sysinfo.screen.renderer,
					sysinfo.map.matriceMap[i][j].tile_x, sysinfo.map.matriceMap[i][j].tile_y);
		}
	}
	*/
}
void IHM::calculTime(GameTime& gameTime) {
	gameTime.frameRunTime = (gameTime.frameRunTime + 1) % 60;
	if (gameTime.frameRunTime == 0) {
		gameTime.secondsRunTime = (gameTime.secondsRunTime + 1) % 60;
		if (gameTime.secondsRunTime == 0) {
			gameTime.minutesRunTime = (gameTime.minutesRunTime + 1) % 60;
			if (gameTime.minutesRunTime == 0)
				gameTime.hoursRunTime++;
		}
	}
}

/* *********************************************************
						 End Game
  ********************************************************* */

std::string IHM::getName(SDL_Renderer*& renderer, TTF_Font* font[], Var& var,
	std::vector<Texte*> txtScore, std::vector<Texte*> tabScore, unsigned int position) {
	SDL_Event event;
	std::string name;
	bool validCharacter = false, validChange = false;

	while (true) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:	// permet de quitter le jeu
			var.continuer = 0;
			return "0";
			break;
		case SDL_KEYDOWN: // test sur le type d'�v�nement touche enfonc�
			switch (event.key.keysym.sym) {
			case SDLK_RETURN:
				return name;
				break;
			case SDLK_ESCAPE:
				var.continuer = 0;
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
				if (validCharacter)
					name += (char)event.key.keysym.sym;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				tabScore[position]->SETname(name + "      " + std::to_string(var.saveReload.GETtabScorePlayer()[position].score),
					renderer, font);
				tabScore[position]->SETtxtcolor(Yellow, renderer, font);

				for (unsigned int i = 0; i < tabScore.size(); i++)
					tabScore[i]->renderTextureTestStates(renderer, var.stateScreen, var.select);
				for (unsigned int i = 0; i < txtScore.size(); i++)
					txtScore[i]->renderTextureTestStates(renderer, var.stateScreen, var.select);
				SDL_RenderPresent(renderer);
			}
			validCharacter = false;
			validChange = false;
			break;
		}
	}

}
int8_t IHM::topScore(std::vector<ScorePlayer>& tabScorePlayer, unsigned int score) {
	std::vector<ScorePlayer> newTabScore;
	ScorePlayer player;
	unsigned int scoreToDestroy = 0, maxSize = 0;

	if (tabScorePlayer.size() > 10)
		maxSize = 10;
	else {
		maxSize = tabScorePlayer.size();
		if (score == 0)
			maxSize--;
	}
	while (newTabScore.size() < maxSize) { // TOP 10 SCORES
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

	int8_t positionToReturn = -1;
	for (unsigned int i = 0; i < tabScorePlayer.size(); i++) {
		if (tabScorePlayer[i].score == score)
			positionToReturn = (int8_t)i;
	}
	return positionToReturn;
}
void IHM::deleteAll(Sysinfo& sysinfo) {
	logfileconsole("*********_________ Start DeleteAll _________*********");

	Entity::destroyEntity(sysinfo.pacman, sysinfo.ghost);

	for (Uint8 i = 1; i < MAX_FONT; i++)
		TTF_CloseFont(sysinfo.allTextes.font[i]);

	deleteDyTabPlayerAndTextures(sysinfo.allTextures.ground, "ground Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.pacman, "pacman Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.red, "red Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.blue, "blue Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.yellow, "yellow Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.pink, "pink Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.miscGhost, "miscGhost Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.collectibles, "collectibles Texture");
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.imgecranTitre, "imgecranTitre Texture");

	deleteDyTabPlayerAndTextures(sysinfo.allTextes.txtecranTitre, "txtecranTitre Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.txtPlay, "txtplay Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.scoreValue, "scoreValue Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.txtScore, "txtscore Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.tabScore, "tabScore Texte");

	deleteDyTabPlayerAndTextures(sysinfo.allButtons.buttonTexteEcranTitre, "Button ecranTitre");
	deleteDyTabPlayerAndTextures(sysinfo.allButtons.buttonTextePlay, "Button play");
	deleteDyTabPlayerAndTextures(sysinfo.allButtons.buttonTexteScore, "Button score");

	deleteDyTabPlayerAndTextures(sysinfo.allButtons.buttonImageEcranTitre, "Button ecranTitre");

	SDL_DestroyRenderer(sysinfo.screen.renderer);
	SDL_DestroyWindow(sysinfo.screen.window);
	sysinfo.screen.renderer = nullptr;
	sysinfo.screen.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}

