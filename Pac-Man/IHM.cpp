/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.12

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

using namespace std;

///////////////////////////// IHM //////////////////////////////

IHM::~IHM() {

}

void IHM::initfile(sysinfo& information) {
	ofstream log(information.files.log);
	if (log) {}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " + information.files.log;
}
void IHM::logfileconsole(const std::string &msg) {
	const std::string logtxt = "log.txt";
	ofstream log(logtxt, ios::app);

	//std::time_t result = std::time(nullptr);
	//<< std::asctime(std::localtime(&result))

	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}

void IHM::logSDLError(std::ostream &os, const std::string &msg) {
	const std::string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		os << msg << " error: " << SDL_GetError() << std::endl;
		log << msg << " error: " << SDL_GetError() << std::endl;
	}
	else
		cout << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt << endl;
}

void IHM::initsdl(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font* font[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cout << endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	else {
		window = SDL_CreateWindow("Pacman",
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (window == nullptr) {
			logSDLError(cout, "CreateWindow");
			SDL_Quit();
		}
		else
			logfileconsole("CreateWindow Success");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//| SDL_RENDERER_PRESENTVSYNC
		if (renderer == nullptr) {
			logSDLError(cout, "CreateRenderer");
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

		for (unsigned int i = 1; i < FONTMAX; i++)
			font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
	}
}
void IHM::initTile(tile& map, bool wall, unsigned int entity) {
	map.wall = wall; map.entity = entity;
}
void IHM::forme(tile map[], unsigned int length, unsigned int height, unsigned int space) {
	for (unsigned int i = 0; i < length; i++) {
		for (unsigned int j = 0; j < height; j++) {
			initTile(map[space], true, nothing);
			space++;
		}
		space += (mapHeight - height);
	}
}
void IHM::initGrid(sysinfo& information) {
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
void IHM::calculimage(sysinfo& information) {
	logfileconsole("_calculimage Start_");

	string IPath = "image/";

	information.variable.statescreen = STATEplay;
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "tile32/Black.bmp", "Black.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "tile32/White.bmp", "White.bmp", (Uint8)255, -1, -1, tileSize, tileSize);
	Texture::loadImage(information.ecran.renderer, information.allTextures.ground, information.variable.statescreen, information.variable.select,
		IPath + "map.png", "map.png", (Uint8)255, -1, -1, NULL, NULL);



	vector<string> ghostName, Pos;
	ghostName.push_back("Red"); ghostName.push_back("Blue"); ghostName.push_back("Yellow"); ghostName.push_back("Pink");
	Pos.push_back("U"); Pos.push_back("L"); Pos.push_back("D"); Pos.push_back("R");


	for (unsigned int i = 0; i < Pos.size(); i++) {
		for (unsigned int j = 1; j < 3; j++)
			Texture::loadImage(information.ecran.renderer, information.allTextures.pacman, information.variable.statescreen, information.variable.select,
				IPath + "pacman/pacman_" + Pos[i] + "_" + to_string(j) + ".png", "pacman_" + Pos[i] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
	}

	for (unsigned int i = 0; i < ghostName.size(); i++) {
		for (unsigned int j = 1; j < 3; j++) {
			for (unsigned int k = 0; k < Pos.size(); k++) {
				switch (i) {
				case 0:
					Texture::loadImage(information.ecran.renderer, information.allTextures.red, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
					break;
				case 1:
					Texture::loadImage(information.ecran.renderer, information.allTextures.blue, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
					break;
				case 2:
					Texture::loadImage(information.ecran.renderer, information.allTextures.yellow, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
					break;
				case 3:
					Texture::loadImage(information.ecran.renderer, information.allTextures.pink, information.variable.statescreen,
						information.variable.select, IPath + "Ghost/" + ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png",
						ghostName[i] + "_" + Pos[k] + "_" + to_string(j) + ".png", (Uint8)255, -1, -1, tileSize, tileSize);
					break;
				}


			}
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
		"Return to Title Screen", WriteColorButton, BackColorButton, 32, 0, 0);
	Buttons::createbutton(information, information.allButton.buttonplay, shaded,
		"Pause", WriteColorButton, BackColorButton, 32, SCREEN_WIDTH / 2, 0, center_x);
	Buttons::createbutton(information, information.allButton.buttonplay, shaded,
		"Initial Grid", WriteColorButton, BackColorButton, 32, 0, 64);

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

	information.variable.statescreen = STATEplay;
	Texture::loadwritetxt(information, information.allTextures.txtplay, blended,
		"Your Score", { 0, 64, 255, 255 }, NoColor, 26, SCREEN_WIDTH / 2, 50, center_x);
	Texture::loadwritetxt(information, information.allTextures.txtplay, blended,
		"YOU DIED", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, center);
	Texture::loadwritetxt(information, information.allTextures.txtplay, blended,
		"YOU WIN", { 255, 0, 0, 255 }, NoColor, 140, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, center);

	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "100", { 255, 0, 0, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "200", { 0, 64, 255, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "400", { 0, 255, 0, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "800", { 255, 0, 255, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "1600", { 255, 0, 255, 255 }, NoColor, 26, -1, -1);
	Texture::loadwritetxt(information, information.allTextures.scoreValue, blended, "5000", { 0, 64, 255, 255 }, NoColor, 26, -1, -1);


	logfileconsole("_calculimage End_");
}


void IHM::mouse(sysinfo& information, SDL_Event event) {
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT

	*/

	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(information, event);


}
void IHM::cliqueGauche(sysinfo& information, SDL_Event event) {
	// recherche du bouton par comparaison de string et des positions x et y du clic

	switch (information.variable.statescreen) {
	case STATEplay:
		for (unsigned int i = 0; i < information.allButton.buttonplay.size(); i++) { // recherche si une bouton est dans ces coordonnées
			if (information.allButton.buttonplay[i]->searchButton((string)"Return to Title Screen", information.variable.statescreen, event.button.x, event.button.y)) {
				ecrantitre(information);
				return;
			}
			if (information.allButton.buttonplay[i]->searchButton((string)"Pause", information.variable.statescreen, event.button.x, event.button.y)) {
				information.allButton.buttonplay[i]->changeOn();
				if (information.allButton.buttonplay[i]->GETon())
					information.variable.select = pause;
				else
					information.variable.select = selectnothing;
				return;
			}
			if (information.allButton.buttonplay[i]->searchButton((string)"Initial Grid", information.variable.statescreen, event.button.x, event.button.y)) {
				initGrid(information);
				return;
			}
		}

		break;
	case STATEecrantitre:
		for (unsigned int i = 0; i < information.allButton.buttonecrantitre.size(); i++) {
			if (information.allButton.buttonecrantitre[i]->searchButton((string)"New Game", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.statescreen = STATEplay;
				return;
			}
			else if (information.allButton.buttonecrantitre[i]->searchButton((string)"Reload", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.continuer = false;
				return;
			}
			else if (information.allButton.buttonecrantitre[i]->searchButton((string)"Option", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.continuer = false;
				return;
			}
			else if (information.allButton.buttonecrantitre[i]->searchButton((string)"Quit", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.continuer = false;
				return;
			}
		}
		break;
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
		information.allTextures.txtecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen);

	for (unsigned int i = 0; i < information.allTextures.imgecrantitre.size(); i++)
		information.allTextures.imgecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen);

	for (unsigned int i = 0; i < information.allButton.buttonecrantitre.size(); i++)
		information.allButton.buttonecrantitre[i]->renderButton(information.ecran.renderer, information.variable.statescreen);


	SDL_RenderPresent(information.ecran.renderer);

	logfileconsole("_Ecrantitres End_");
}


void IHM::alwaysrender(sysinfo& information, Pacman& player) {
	//clock_t t1, t2;
	//t1 = clock();



	switch (information.variable.statescreen) {
	case STATEplay:

		/*
			fond gris et affichage de la map avec les couloirs et murs
		*/
		SDL_RenderClear(information.ecran.renderer);
		SDL_SetRenderDrawColor(information.ecran.renderer, 128, 128, 128, 0xFF);
		afficherMap(information);

		/*
			changement de skin toutes 10 boucles
		*/
		information.variable.modulo = (information.variable.modulo + 1) % 10;
		if (information.variable.modulo == 0) {
			player.SETalternateSkin(!player.GETalternateSkin());
			for (unsigned int i = 0; i < information.ghost.size(); i++)
				information.ghost[i]->SETalternateSkin(!information.ghost[i]->GETalternateSkin());
		}


		for (unsigned int i = 0; i < information.allTextures.txtplay.size(); i++) {
			information.allTextures.txtplay[i]->renderTextureTestString(information.ecran.renderer, "Your Score");
			if (player.GETlife() == 0)
				information.allTextures.txtplay[i]->renderTextureTestString(information.ecran.renderer, "YOU DIED");
			if (information.variable.win)
				information.allTextures.txtplay[i]->renderTextureTestString(information.ecran.renderer, "YOU WIN");
		}


		//
		player.afficherStats(information);
		player.afficher(information.ecran.renderer, information.allTextures.pacman);
		for (unsigned int i = 0; i < information.ghost.size(); i++) {
			if (i == red) {
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.red, information.allTextures.miscGhost);
			}
			else if (i == blue)
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.blue, information.allTextures.miscGhost);
			else if (i == yellow)
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.yellow, information.allTextures.miscGhost);
			else
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.pink, information.allTextures.miscGhost);
		}





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
		à utiliser si besoin de changer la map
		screenshot de l'ecran et rogner sous paint pour n'utiliser que la map -> map.png à mettre dans le dossier image

	unsigned int k = 0;
	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			if (information.map[k].wall)
				information.allTextures.ground[blackTile]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
			else {
				information.allTextures.ground[whiteTile]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
				if(information.map[k].entity != nothing)
					information.allTextures.collectibles[information.map[k].entity - 1]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
			}
			k++;
		}
	}
	*/


	unsigned int k = 0;
	information.allTextures.ground[mapTile]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);

	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			if (!information.map[k].wall && information.map[k].entity != nothing)
				information.allTextures.collectibles[information.map[k].entity - 1]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
			k++;
		}
	}

}


void IHM::deleteAll(sysinfo& information) {
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
	deleteDyTabPlayerAndTextures(information.allTextures.txtecrantitre, "txtecrantitre Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtplay, "txtplay Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.imgecrantitre, "imgecrantitre Texture");

	deleteDyTabPlayerAndTextures(information.allButton.buttonecrantitre, "Button ecrantitre");
	deleteDyTabPlayerAndTextures(information.allButton.buttonplay, "Button play");

	SDL_DestroyRenderer(information.ecran.renderer);
	SDL_DestroyWindow(information.ecran.window);
	information.ecran.renderer = nullptr;
	information.ecran.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}


///////////////////////////// Texture //////////////////////////////

Texture::Texture(SDL_Texture* image, const std::string& msg, unsigned int statescreen, unsigned int select, unsigned int x, unsigned int y, int w, int h)
	: _texture(image), _dst(rectangle(x,y,w,h)),_name(msg), _statescreen(statescreen), _select(select)
{
}

Texture::~Texture() {
	if (_texture != nullptr){
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}


SDL_Rect Texture::rectangle(int x, int y, int w, int h){
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	return rectangle;
}



SDL_Texture* Texture::renderText(SDL_Renderer*& renderer, unsigned int type, const std::string &message, SDL_Color color, SDL_Color colorback, TTF_Font* font) {
	SDL_Surface *surf = nullptr;

	if (type == blended)
		surf = TTF_RenderText_Blended(font, message.c_str(), color);
	else if (type == shaded)
		surf = TTF_RenderText_Shaded(font, message.c_str(), color, colorback);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		IHM::logfileconsole("___________ERROR : renderTextShaded nullptr for : " + message);
	SDL_FreeSurface(surf);
	return texture;
}

void Texture::loadImage(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, unsigned int statescreen, unsigned int select,
	const std::string &path, const std::string &msg, Uint8 alpha, int x, int y, unsigned int w, unsigned int h, int cnt) {


	int xt = 0, yt = 0, wt = 0, ht = 0;
	if (x != -1 && y != -1)
		xt = x, yt = y;

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (w == 0 && h == 0) {
		wt = loadedSurface->w;
		ht = loadedSurface->h;
	}
	else {
		wt = w;
		ht = h;
	}

	if (loadedSurface != NULL) {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL) {
			if (alpha != (Uint8)255) {
				if (SDL_SetTextureAlphaMod(newTexture, alpha) != 0)
					IHM::logSDLError(cout, "alpha : ");
			}
			centrage(xt, yt, wt, ht, cnt);
			tabTexture.push_back(new Texture(newTexture, msg, statescreen, select, xt, yt, wt, ht));
		}
		else
			IHM::logfileconsole("___________ERROR : loadImage : cannot create Texture from : " + path);
		SDL_FreeSurface(loadedSurface);
	}
	else
		IHM::logfileconsole("___________ERROR : loadImage : path or image are corrupt : " + path);
}

void Texture::loadwritetxt(sysinfo& information, std::vector<Texture*>& tabTexture, unsigned int type, const std::string &msg,
	SDL_Color color, SDL_Color backcolor, unsigned int size, int x, int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, type, msg, color, backcolor, information.allTextures.font[size]);
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);
	tabTexture.push_back(new Texture(image, msg, information.variable.statescreen, information.variable.select, xc, yc, iW, iH));
}


void Texture::writetxt(sysinfo& information, unsigned int type, const std::string &msg, SDL_Color color, SDL_Color backcolor, unsigned int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, type, msg, color, backcolor, information.allTextures.font[size]);
	loadAndWriteImage(information.ecran.renderer, image, x, y, cnt);
	SDL_DestroyTexture(image);
}

void Texture::loadAndWriteImage(SDL_Renderer*& renderer, SDL_Texture *image, unsigned int x, unsigned int y, int cnt) {
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);

	SDL_Rect dst;
	dst.x = xc;
	dst.y = yc;
	dst.w = iW;
	dst.h = iH;
	SDL_RenderCopy(renderer, image, NULL, &dst);
}


void Texture::centrage(int& xc, int& yc, int iW, int iH, int cnt) {
	switch (cnt) {
	case nocenter:
		break;
	case center_x:
		xc = xc - (iW / 2);
		break;
	case center_y:
		yc = yc - (iH / 2);
		break;
	case center:
		xc = xc - (iW / 2);
		yc = yc - (iH / 2);
		break;
	}
}


void Texture::render(SDL_Renderer*& renderer, int x, int y) {
	if (x != -1 && y != -1) {
		_dst.x = x;
		_dst.y = y;
	}
	SDL_RenderCopy(renderer, _texture, NULL, &_dst);
}

void Texture::renderTexture(SDL_Renderer*& renderer, int x, int y) {
	render(renderer, x, y);
}

void Texture::renderTextureTestStates(SDL_Renderer*& renderer, unsigned int statescreen, int x, int y) {
	if (_statescreen == statescreen)
		render(renderer, x, y);
}

void Texture::renderTextureTestStatesAngle(SDL_Renderer*& renderer, unsigned int statescreen, int x, int y, unsigned int angle) {
	if (_statescreen == statescreen) {
		if (x != -1 && y != -1) {
			_dst.x = x;
			_dst.y = y;
		}
		SDL_RenderCopyEx(renderer, _texture, NULL, &_dst, angle, NULL, SDL_FLIP_NONE);
	}
}

void Texture::renderTextureTestString(SDL_Renderer*& renderer, const std::string& msg, int xc, int yc) {
	if (_name.compare(msg) == 0)
		render(renderer, xc, yc);
}

bool Texture::renderTextureTestStringAndStates(SDL_Renderer*& renderer, const std::string& msg, unsigned int statescreen, int xc, int yc) {
	if (_name.compare(msg) == 0 && _statescreen == statescreen){
		render(renderer, xc, yc);
		return true;
	}
	return false;	
}
bool Texture::TextureTestString(const std::string& msg) {
	if (_name.compare(msg) == 0)
		return true;
	return false;
}



void Texture::changeAlpha(Uint8 alpha) {
	if (SDL_SetTextureAlphaMod(_texture, alpha) != 0)
		IHM::logSDLError(cout, "alpha : ");
}




SDL_Texture* Texture::GETtexture() const{
	return _texture;
}
SDL_Rect Texture::GETdst()const {
	return _dst;
}
int Texture::GETdstx()const {
	return _dst.x;
}
int Texture::GETdsty()const {
	return _dst.y;
}
int Texture::GETdstw()const {
	return _dst.w;
}
int Texture::GETdsth()const {
	return _dst.h;
}
string Texture::GETname() const{
	return _name;
}
unsigned int Texture::GETstatescreen() const {
	return _statescreen;
}
unsigned int Texture::GETselect() const {
	return _select;
}


void Texture::SETdstx(int x) {
	_dst.x = x;
}
void Texture::SETdsty(int y) {
	_dst.y = y;
}
void Texture::SETdstw(int w) {
	_dst.w = w;
}
void Texture::SETdsth(int h) {
	_dst.h = h;
}





///////////////////////////// Button //////////////////////////////


Buttons::Buttons(SDL_Texture* image, const std::string& msg, unsigned int statescreen, unsigned int select, int x, int y, int w, int h,
	SDL_Texture* imageOn, SDL_Color txtcolor, SDL_Color backcolor, bool on)
	: Texture(image, msg, statescreen, select, x, y, w, h),
	_imageOn(imageOn), _txtcolor(txtcolor), _backcolor(backcolor), _on(on)
{

}

Buttons::~Buttons() {
	if (_imageOn != nullptr) {
		SDL_DestroyTexture(_imageOn);
		_imageOn = nullptr;
	}
}

void Buttons::createbutton(sysinfo& information, std::vector<Buttons*>& tabbutton, unsigned int type, const std::string& msg, SDL_Color color, SDL_Color backcolor, unsigned int size, int x, int y, int cnt) {
	int iW = 0, iH = 0;
	unsigned int i = 0;

	SDL_Texture *image = nullptr;
	SDL_Texture *imageOn = nullptr;

	if (tabbutton.size() > 0) {
		i++;
	}
	for (i; i <= tabbutton.size(); i++) {
		if (i == tabbutton.size()) {
			image = renderText(information.ecran.renderer, type, msg, color, backcolor, information.allTextures.font[size]);
			imageOn = renderText(information.ecran.renderer, type, msg, color, { 64,128,64,255 }, information.allTextures.font[size]);
			SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
			centrage(x, y, iW, iH, cnt);
			tabbutton.push_back(new Buttons(image, msg, information.variable.statescreen, information.variable.select, x, y, iW, iH, imageOn, color, backcolor));

			IHM::logfileconsole("Create Button n:" + to_string(i) + " msg = " + tabbutton[i]->GETname() + " Success");
			break;
		}
	}
}


unsigned int Buttons::testcolor(SDL_Color txt, SDL_Color back) const {
	if (_txtcolor.a != txt.a || _txtcolor.b != txt.b || _txtcolor.g != txt.g || _txtcolor.r != txt.r ||
		_backcolor.a != back.a || _backcolor.b != back.b || _backcolor.g != back.g || _backcolor.r != back.r)
		return 1;
	else
		return 0;
}

unsigned int Buttons::searchButton(string msg, unsigned int statescreen, signed int x, signed int y) {
	if (statescreen == this->GETstatescreen()) {
		if (x >= this->GETdstx() && x <= this->GETdstx() + this->GETdstw()) {
			if (y >= this->GETdsty() && y <= this->GETdsty() + this->GETdsth()) {
				if (this->GETname().compare(msg) == 0)
					return 1;
			}
		}
	}
	return 0;
}
unsigned int Buttons::searchButtonName(string& msg, unsigned int statescreen) {
	if (statescreen == this->GETstatescreen()) {
		if (this->GETname().compare(msg) == 0)
			return 1;
	}
	return 0;
}




void Buttons::resetOnStatescreen(unsigned int select, unsigned int selectnothing) {
	if (this->GETselect() != select && this->GETselect() != selectnothing)
		_on = false;
}

void Buttons::resetOnPlayer(unsigned int selectplayer, std::vector<std::string> tabPlayerName) {
	for (unsigned int i = 0; i < tabPlayerName.size(); i++) {
		if (i != selectplayer && this->GETname().compare(tabPlayerName[i]) == 0)
			_on = false;
	}
}

bool Buttons::renderButton(SDL_Renderer*& renderer, unsigned int statescreen) {
	if (this->GETstatescreen() == statescreen) {
		if (_on)
			SDL_RenderCopy(renderer, _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(renderer, this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}

bool Buttons::renderButtonTestString(SDL_Renderer*& renderer, unsigned int statescreen, std::string& msg, int newx, int newy, int cnt) {
	if (this->GETstatescreen() == statescreen && this->GETname().compare(msg) == 0) {
		if (newx != -1 && newy != -1) {
			centrage(newx, newy, this->GETdstw(), this->GETdsth(), cnt);
			this->SETdstx(newx);
			this->SETdstx(newx);
		}
		if (_on)
			SDL_RenderCopy(renderer, _imageOn, NULL, &this->GETdst());
		else
			SDL_RenderCopy(renderer, this->GETtexture(), NULL, &this->GETdst());
		return true;
	}
	return false;
}


void Buttons::changeOn() {
	_on = !_on;
}





SDL_Texture* Buttons::GETimageOn() const {
	return _imageOn;
}
SDL_Color Buttons::GETtxtcolor() const {
	return _txtcolor;
}
SDL_Color Buttons::GETbackcolor() const {
	return _backcolor;
}
bool Buttons::GETon() const {
	return _on;
}






void Buttons::SETon(bool state) {
	_on = state;
}
