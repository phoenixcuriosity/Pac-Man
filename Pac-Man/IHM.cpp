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


		const std::string fontFile = "arial.ttf";

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

	std::string IPath = "image/";
	sysinfo.var.statescreen = STATEplay;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "tile32/Black.bmp", "Black.bmp", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "tile32/White.bmp", "White.bmp", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.ground, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "map.png", "map.png", (Uint8)255, -1, -1, NULL, NULL);

	std::string ghostName[MAX_GHOST] = { "Red", "Blue", "Yellow", "Pink" }, Pos[MAX_POS] = { "U", "L", "D", "R" };
	for (unsigned int i = 0; i < MAX_POS; i++) {
		for (unsigned int j = 1; j < 3; j++)
			Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.pacman, sysinfo.var.statescreen, sysinfo.var.select,
				IPath + "pacman/pacman_" + Pos[i] + "_" + std::to_string(j) + ".png", "pacman_" + Pos[i] + "_" + std::to_string(j) + ".png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	}

	// permet de charger les 32 Textures des Ghost (8 par Ghost, dont 4 pour les position avec le 1er skin et les 4 autres pour l'autre skin(alternateskin))
	std::vector<Texture*>* ghostTab[MAX_GHOST] = { &sysinfo.allTextures.red, &sysinfo.allTextures.blue,
		&sysinfo.allTextures.yellow, &sysinfo.allTextures.pink };
	for (unsigned int i = 0; i < MAX_GHOST; i++) { // nb de ghost
		for (unsigned int j = 1; j < 3; j++) { // skin or alternate skin
			for (unsigned int k = 0; k < MAX_POS; k++) // UP, LEFT, DOWN, RIGHT
				Texture::loadImage(sysinfo.screen.renderer, *ghostTab[i], sysinfo.var.statescreen,
						sysinfo.var.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + std::to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + std::to_string(j) + ".png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
		}
	}
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.miscGhost, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "Ghost/not_Invincible_B.png", "not_Invincible_B.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.miscGhost, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "Ghost/not_Invincible_W.png", "not_Invincible_W.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.miscGhost, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "Ghost/goHome.png", "goHome.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);

	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "collectibles/gold.png", "gold.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "collectibles/cherry.png", "cherry.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "collectibles/strawberry.png", "strawberry.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "collectibles/lemon.png", "lemon.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "collectibles/pear.png", "pear.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.collectibles, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "collectibles/key.png", "key.png", (Uint8)255, -1, -1, TILE_SIZE, TILE_SIZE);


	sysinfo.var.statescreen = STATEecrantitre;
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecrantitre, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ecrantitre/linux.jpg", "linux.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2, NULL, NULL, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecrantitre, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ecrantitre/c++.jpg", "c++.jpg", (Uint8)255, SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 400, NULL, NULL, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecrantitre, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ecrantitre/sudo.jpg", "sudo.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2, NULL, NULL, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecrantitre, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ecrantitre/PC_master_Race.jpg", "PC_master_Race.jpg", (Uint8)255, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 + 400, NULL, NULL, center);
	Texture::loadImage(sysinfo.screen.renderer, sysinfo.allTextures.imgecrantitre, sysinfo.var.statescreen, sysinfo.var.select,
		IPath + "ecrantitre/matlab.jpg", "matlab.jpg", (Uint8)255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350, NULL, NULL, center);
	int spacemenu = 64, initspacemenu = 400;

	// ______Buttons_____
	sysinfo.var.statescreen = STATEecrantitre;
	Button::createbutton(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButtons.buttonEcrantitre,
		shaded, "New Game", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu, nonTransparent, center);
	Button::createbutton(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButtons.buttonEcrantitre,
		shaded, "Reload", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	Button::createbutton(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButtons.buttonEcrantitre,
		shaded, "Option", { 128, 128, 128, 255 }, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	Button::createbutton(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButtons.buttonEcrantitre,
		shaded, "Quit", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);

	sysinfo.var.statescreen = STATEplay;
	Button::createbutton(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButtons.buttonPlay,
		shaded, "Pause", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);
	Button::createbutton(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButtons.buttonPlay,
		shaded, "Go to leader board (END GAME)", WriteColorButton, BackColorButton, 32, 0, 0, nonTransparent);
	Button::createbutton(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButtons.buttonPlay,
		shaded, "Save and Quit", WriteColorButton, BackColorButton, 32, 0, 64, nonTransparent);

	sysinfo.var.statescreen = STATEscore;
	Button::createbutton(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allButtons.buttonScore,
		shaded, "Return to Title Screen", WriteColorButton, BackColorButton, 32, 0, 0, nonTransparent);

	// ______writeTexte_____ 
	sysinfo.var.statescreen = STATEecrantitre;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtEcrantitre,
		blended, "Game dev in C++ and with SDL2.0.8", { 255, 127, 127, 255 }, NoColor, 18, 0, 0, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtEcrantitre,
		blended, "Developed by Joeffrey VILLERONCE and Robin SAUTER", { 127, 255, 127, 255 }, NoColor, 18, 0, 30, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtEcrantitre,
		blended, "New Super Pac-Man Plus DELUX Pro Turbo Edition", { 0, 64, 255, 255 }, NoColor, 50, SCREEN_WIDTH / 2, 100, nonTransparent, center_x);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtEcrantitre,
		blended, "With ALL DLC For Only 99.99$ what a deal !!!", { 255, 255, 0, 255 }, NoColor, 25, SCREEN_WIDTH / 2, 160, nonTransparent, center_x);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtEcrantitre,
		blended, "Use your mouse to select", { 0, 255, 0, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 350, nonTransparent, center_x);


	sysinfo.var.statescreen = STATEplay;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtPlay,
		blended, "Your Score", { 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, 50, nonTransparent, center_x);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtPlay,
		blended, "You can move Pacman", { 0, 255, 0, 255 }, NoColor, 24, 100, 500, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtPlay,
		blended, "by pressing arrows on your keyboard", { 0, 255, 0, 255 }, NoColor, 24, 100, 524, nonTransparent);
	sysinfo.var.select = lost;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtPlay,
		blended, "YOU DIED", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, nonTransparent, center);
	sysinfo.var.select = win;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtPlay, 
		blended, "YOU WIN", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, nonTransparent, center);

	sysinfo.var.select = selectnothing;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "100", { 255, 0, 0, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "200", { 0, 64, 255, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "400", { 0, 255, 0, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "800", { 255, 0, 255, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "1600", { 255, 0, 255, 255 }, NoColor, 26, -1, -1, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.scoreValue,
		blended, "5000", { 0, 64, 255, 255 }, NoColor, 26, -1, -1, nonTransparent);

	sysinfo.var.statescreen = STATEscore;
	sysinfo.var.select = pause;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "TOP 10 SCORES", { 255, 0, 0, 255 }, NoColor, 50, SCREEN_WIDTH / 2, 100, nonTransparent, center_x);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "Enter your name", { 0, 255, 0, 255 }, NoColor, 24, 100, 200, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "with your keyboard", { 0, 255, 0, 255 }, NoColor, 24, 100, 224, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "Remove last letter with backspace", { 0, 255, 0, 255 }, NoColor, 24, 100, 248, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.txtScore,
		blended, "Press return when finish", { 0, 255, 0, 255 }, NoColor, 24, 100, 272, nonTransparent);

	sysinfo.var.select = selectnothing;
	logfileconsole("_calculimage End_");
}
void IHM::mouse(Sysinfo& sysinfo, SDL_Event event) {
	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(sysinfo, event);
}
void IHM::cliqueGauche(Sysinfo& sysinfo, SDL_Event event) {
	switch (sysinfo.var.statescreen) {
	case STATEplay:
		for (unsigned int i = 0; i < sysinfo.allButtons.buttonPlay.size(); i++) { // recherche si une bouton est dans ces coordonnées
			if (sysinfo.allButtons.buttonPlay[i]->searchButton((std::string)"Pause", sysinfo.var.statescreen, event.button.x, event.button.y)) {
				sysinfo.allButtons.buttonPlay[i]->changeOn();
				if (sysinfo.allButtons.buttonPlay[i]->GETon())
					sysinfo.var.select = pause;
				else
					sysinfo.var.select = selectnothing;
				return;
			}
			else if (sysinfo.allButtons.buttonPlay[i]->searchButton((std::string)"Save and Quit", sysinfo.var.statescreen, event.button.x, event.button.y)) {
				SaveReload::save(sysinfo);
				sysinfo.var.continuer = false;
				return;
			}
			else if (sysinfo.allButtons.buttonPlay[i]->searchButton((std::string)"Go to leader board (END GAME)", sysinfo.var.statescreen, event.button.x, event.button.y)) {
				sysinfo.var.statescreen = STATEscore;
				sysinfo.var.select = pause;
				ecranScore(sysinfo);
				return;
			}
		}
		break;
	case STATEecrantitre:
		for (unsigned int i = 0; i < sysinfo.allButtons.buttonEcrantitre.size(); i++) {
			if (sysinfo.allButtons.buttonEcrantitre[i]->searchButton((std::string)"New Game", sysinfo.var.statescreen, event.button.x, event.button.y)) {
				sysinfo.var.statescreen = STATEplay;
				Entity::initEntity(sysinfo.pacman, sysinfo.ghost);
				initGrid(sysinfo.map);
				return;
			}
			else if (sysinfo.allButtons.buttonEcrantitre[i]->searchButton((std::string)"Reload", sysinfo.var.statescreen, event.button.x, event.button.y)) {
				Entity::initEntity(sysinfo.pacman, sysinfo.ghost);
				initGrid(sysinfo.map);
				if(SaveReload::reload(sysinfo))
					sysinfo.var.statescreen = STATEplay;
				else
					sysinfo.var.continuer = false;
				return;
			}
			else if (sysinfo.allButtons.buttonEcrantitre[i]->searchButton((std::string)"Option", sysinfo.var.statescreen, event.button.x, event.button.y)) {
				sysinfo.var.continuer = false;
				return;
			}
			else if (sysinfo.allButtons.buttonEcrantitre[i]->searchButton((std::string)"Quit", sysinfo.var.statescreen, event.button.x, event.button.y)) {
				sysinfo.var.continuer = false;
				return;
			}
		}
		break;
	case STATEscore:
		for (unsigned int i = 0; i < sysinfo.allButtons.buttonScore.size(); i++) {
			if (sysinfo.allButtons.buttonScore[i]->searchButton((std::string)"Return to Title Screen", sysinfo.var.statescreen, event.button.x, event.button.y)) {
				sysinfo.var.select = selectnothing;
				ecrantitre(sysinfo);
				return;
			}
		}
		break;
	}
}
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
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
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
				if(validCharacter)
					name += (char)event.key.keysym.sym;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				tabScore[position]->SETname(name + "      " + std::to_string(var.saveReload.GETtabScorePlayer()[position].score),
					renderer, font);
				tabScore[position]->SETtxtcolor(Yellow, renderer, font);
				
				for (unsigned int i = 0; i < tabScore.size(); i++)
					tabScore[i]->renderTextureTestStates(renderer, var.statescreen, var.select);
				for (unsigned int i = 0; i < txtScore.size(); i++)
					txtScore[i]->renderTextureTestStates(renderer, var.statescreen, var.select);
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
void IHM::ecrantitre(Sysinfo& sysinfo) {
	logfileconsole("_Ecrantitres Start_");

	sysinfo.var.statescreen = STATEecrantitre;
	SDL_SetRenderDrawColor(sysinfo.screen.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sysinfo.screen.renderer);

	for (unsigned int i = 0; i < sysinfo.allTextes.txtEcrantitre.size(); i++)
		sysinfo.allTextes.txtEcrantitre[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.statescreen, sysinfo.var.select);

	for (unsigned int i = 0; i < sysinfo.allTextures.imgecrantitre.size(); i++)
		sysinfo.allTextures.imgecrantitre[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.statescreen, sysinfo.var.select);

	for (unsigned int i = 0; i < sysinfo.allButtons.buttonEcrantitre.size(); i++)
		sysinfo.allButtons.buttonEcrantitre[i]->renderButton(sysinfo.screen.renderer, sysinfo.var.statescreen);


	SDL_RenderPresent(sysinfo.screen.renderer);

	logfileconsole("_Ecrantitres End_");
}
void IHM::ecranScore(Sysinfo& sysinfo) {
	logfileconsole("_Ecrantitres Start_");

	sysinfo.var.statescreen = STATEscore;
	int8_t position = 0;
	ScorePlayer p; p.name = ""; p.score = sysinfo.pacman->GETvalue();
	sysinfo.var.saveReload.GETtabScorePlayerNONCONST().push_back(p);
	position = topScore(sysinfo.var.saveReload.GETtabScorePlayerNONCONST(), p.score);
	
	for (unsigned int i = 0; i < sysinfo.allTextes.tabScore.size(); i++)
		delete sysinfo.allTextes.tabScore[i];
	sysinfo.allTextes.tabScore.clear();
	unsigned int initspacemenu = 200;
	for (unsigned int i = 0; i < sysinfo.var.saveReload.GETtabScorePlayer().size(); i++)
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.statescreen, sysinfo.var.select, sysinfo.allTextes.tabScore,
			blended, sysinfo.var.saveReload.GETtabScorePlayer()[i].name + "      " + std::to_string(sysinfo.var.saveReload.GETtabScorePlayer()[i].score),
			{ 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, initspacemenu += 32, nonTransparent, center_x);


	SDL_SetRenderDrawColor(sysinfo.screen.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sysinfo.screen.renderer);
	for (unsigned int i = 0; i < sysinfo.allTextes.tabScore.size(); i++)
		sysinfo.allTextes.tabScore[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.statescreen, sysinfo.var.select);
	for (unsigned int i = 0; i < sysinfo.allTextes.txtScore.size(); i++) {
		if (sysinfo.allTextes.txtScore[i]->renderTextureTestString(sysinfo.screen.renderer, "TOP 10 SCORES"))
			break;
	}
		

	if (position != -1) { // si dans le top 10
		for (unsigned int i = 0; i < sysinfo.allTextes.txtScore.size(); i++)
			sysinfo.allTextes.txtScore[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.statescreen, sysinfo.var.select);
		SDL_RenderPresent(sysinfo.screen.renderer);
		sysinfo.var.saveReload.GETtabScorePlayerNONCONST()[position].name = getName(sysinfo.screen.renderer,sysinfo.allTextes.font,
			sysinfo.var, sysinfo.allTextes.txtScore, sysinfo.allTextes.tabScore, position);
	}

	SDL_SetRenderDrawColor(sysinfo.screen.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sysinfo.screen.renderer);
	for (unsigned int i = 0; i < sysinfo.allTextes.tabScore.size(); i++)
		sysinfo.allTextes.tabScore[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.statescreen, sysinfo.var.select);
	for (unsigned int i = 0; i < sysinfo.allTextes.txtScore.size(); i++) {
		if (sysinfo.allTextes.txtScore[i]->renderTextureTestString(sysinfo.screen.renderer, "TOP 10 SCORES"))
			break;
	}
	for (unsigned int i = 0; i < sysinfo.allButtons.buttonScore.size(); i++)
		sysinfo.allButtons.buttonScore[i]->renderButton(sysinfo.screen.renderer, sysinfo.var.statescreen);
	SDL_RenderPresent(sysinfo.screen.renderer);

	logfileconsole("_Ecrantitres End_");
}
void IHM::alwaysrender(Sysinfo& sysinfo) {
	//clock_t t1, t2;
	//t1 = clock();

	switch (sysinfo.var.statescreen) {
	case STATEplay:
		/*
			fond gris et affichage de la map avec les couloirs et murs
		*/
		SDL_RenderClear(sysinfo.screen.renderer);
		SDL_SetRenderDrawColor(sysinfo.screen.renderer, 128, 128, 128, 0xFF);
		afficherMap(sysinfo);
		calculTime(sysinfo.var.gameTime);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended,
			std::to_string(sysinfo.var.gameTime.hours) + ":"+ std::to_string(sysinfo.var.gameTime.minutes) + ":"
			+ std::to_string(sysinfo.var.gameTime.seconds), Black, NoColor, 24, SCREEN_WIDTH - 300, 0, center_x);

		/*
			changement de skin toutes 10 boucles (10 frames)
		*/
		sysinfo.var.modulo = (sysinfo.var.modulo + 1) % 10;
		if (sysinfo.var.modulo == 0) {
			sysinfo.pacman->SETalternateSkin(!sysinfo.pacman->GETalternateSkin());
			for (unsigned int i = 0; i < sysinfo.ghost.size(); i++)
				sysinfo.ghost[i]->SETalternateSkin(!sysinfo.ghost[i]->GETalternateSkin());
		}


		for (unsigned int i = 0; i < sysinfo.allTextes.txtPlay.size(); i++) {
			sysinfo.allTextes.txtPlay[i]->renderTextureTestStates(sysinfo.screen.renderer, sysinfo.var.statescreen, sysinfo.var.select);
		}

		//
		std::vector<Texture*> pacmanTab[1] = { sysinfo.allTextures.pacman };
		sysinfo.pacman->afficherStats(sysinfo.screen.renderer, sysinfo.allTextes.font);
		sysinfo.pacman->afficher(sysinfo.screen.renderer, pacmanTab);

		
		std::vector<Texture*> ghostTab[MAX_GHOST + 1] = { sysinfo.allTextures.red, sysinfo.allTextures.blue,
		sysinfo.allTextures.yellow, sysinfo.allTextures.pink , sysinfo.allTextures.miscGhost };
		for (unsigned int i = 0; i < sysinfo.ghost.size(); i++)
			sysinfo.ghost[i]->afficher(sysinfo.screen.renderer, ghostTab);


		sysinfo.var.moduloScore = (sysinfo.var.moduloScore + 1) % 30;
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

		for (unsigned int i = 0; i < sysinfo.allButtons.buttonPlay.size(); i++)
			sysinfo.allButtons.buttonPlay[i]->renderButton(sysinfo.screen.renderer, sysinfo.var.statescreen);


		SDL_RenderPresent(sysinfo.screen.renderer);
		break;
	}

	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}
void IHM::afficherMap(Sysinfo& sysinfo) {
	/*
		à utiliser si besoin de changer la map -> commenter l'autre partie du code
		screenshot de l'ecran et rogner sous paint pour n'utiliser que la map -> map.png à mettre dans le dossier image
	*/
	/*
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
	*/

	
	sysinfo.allTextures.ground[mapTile]->render(sysinfo.screen.renderer, sysinfo.map.matriceMap[0][0].tile_x, sysinfo.map.matriceMap[0][0].tile_y);
	for (Uint8 i = 0; i < sysinfo.map.map_length; i++) {
		for (Uint8 j = 0; j < sysinfo.map.map_height; j++) {
			if (!sysinfo.map.matriceMap[i][j].wall && sysinfo.map.matriceMap[i][j].entity != nothing)
				sysinfo.allTextures.collectibles[sysinfo.map.matriceMap[i][j].entity - 1]->render(sysinfo.screen.renderer,
					sysinfo.map.matriceMap[i][j].tile_x, sysinfo.map.matriceMap[i][j].tile_y);
		}
	}
}
void IHM::calculTime(GameTime& gameTime) {
	gameTime.frame = (gameTime.frame + 1) % 60;
	if (gameTime.frame == 0) {
		gameTime.seconds = (gameTime.seconds + 1) % 60;
		if (gameTime.seconds == 0) {
			gameTime.minutes = (gameTime.minutes + 1) % 60;
			if (gameTime.minutes == 0)
				gameTime.hours++;
		}
	}
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
	deleteDyTabPlayerAndTextures(sysinfo.allTextures.imgecrantitre, "imgecrantitre Texture");

	deleteDyTabPlayerAndTextures(sysinfo.allTextes.txtEcrantitre, "txtecrantitre Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.txtPlay, "txtplay Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.scoreValue, "scoreValue Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.txtScore, "txtscore Texte");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.tabScore, "tabScore Texte");

	deleteDyTabPlayerAndTextures(sysinfo.allButtons.buttonEcrantitre, "Button ecrantitre");
	deleteDyTabPlayerAndTextures(sysinfo.allButtons.buttonPlay, "Button play");
	deleteDyTabPlayerAndTextures(sysinfo.allButtons.buttonScore, "Button score");

	SDL_DestroyRenderer(sysinfo.screen.renderer);
	SDL_DestroyWindow(sysinfo.screen.window);
	sysinfo.screen.renderer = nullptr;
	sysinfo.screen.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}

