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

#ifndef Pac_Man_lib_H
#define Pac_Man_lib_H

#include "lib.h"  // include lib et typedef

#include "IHM.h"
#include "Entity.h"

const Uint16 SCREEN_WIDTH = 1920;
const Uint16 SCREEN_HEIGHT = 1088;
const int8_t TILE_SIZE = 32;
const Uint8 MAX_GHOST = 4;
const Uint8 MAX_POS = 4;
const Uint8 MAX_SKIN = 2;
const Uint8 MAX_FONT = 160;
const Uint16 TEMPO_INVINCIBLE = 600;
const Uint8 INITIAL_VELOCITY = 2;

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris
const SDL_Color NoColor = { 0, 0, 0, 0 };

enum : Uint8 { normal, blended, shaded};
enum : Uint8 { nocenter, center_x, center_y, center }; // centrage des textures et boutons
enum : Uint8 { blackTile, whiteTile, mapTile}; // allTexture.ground

enum : Uint8 { red, blue, yellow, pink};
enum : Uint8 { UP, LEFT, DOWN, RIGHT };
enum : Uint8 { Not_Valid, validCondition, validNextHeading};

enum : Uint8 { nothing, gold, cherry, strawberry, peach, apple, key};
enum { nothing1, valuegold = 100, valuecherry = 200, valuestrawberry = 400, valuepeach = 800, valueapple = 1600, ghost1 = 800, ghost2 = 1600, ghost3 = 3200, ghost4 = 10000,valuekey = 5000};

enum : Uint8 { STATEnothing, STATEecrantitre, STATEplay, STATEscore };  // différents état de l'écran
enum : Uint8 { selectnothing, pause, win, lost };	// spécifications de la séléction


//////////////////////// Structure niveau 2 ///////////////////////
/*
		structure contenant les données en rapport avec le temps du programme
*/
struct GameTime {
	
	Uint8 hours = 0;
	Uint8 minutes = 0;
	Uint8 seconds = 0;
	Uint8 frame = 0;
};
struct ScorePlayer {
	unsigned int score = 0;
	std::string name = "";
};
/*
		Structure décrivant une case dans la map
*/
struct Tile {
	
	Uint8 indexX = 0; // numéro de la case en x map[x][y]
	Uint8 indexY = 0; // numéro de la case en y map[x][y]
	unsigned int tile_x = 0;
	unsigned int tile_y = 0;

	bool wall = false;
	Uint8 entity = gold;
};
//////////////////////// Structure niveau 1 ///////////////////////
struct Screen {
	/*
		
	*/
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};
/*
		Structure contenant tous les noms des fichiers ainsi que leurs chemins
*/
struct File {
	const std::string log = "log.txt";
	const std::string score = "save/scores.txt";
	std::string saveMap = "save/saveMap.txt";
	std::string saveEntity = "save/saveEntity.txt";
};
struct Var {
	bool continuer = true;

	Uint8 select = selectnothing;
	Uint8 statescreen = 0; // selectnothing par défaut
	unsigned int score = 0;
	bool win = false;

	Uint8 modulo = 0;
	Uint8 moduloScore = 0;
	unsigned int tempoScore = 0;
	
	GameTime gameTime;
	std::vector<ScorePlayer> tabScorePlayer;
};
/*
		Contient toutes les Textures (images et textes)
*/
struct AllTextures {
	std::vector<Texture*> ground;

	std::vector<Texture*> pacman;
	std::vector<Texture*> red;
	std::vector<Texture*> blue;
	std::vector<Texture*> yellow;
	std::vector<Texture*> pink;
	std::vector<Texture*> miscGhost;
	std::vector<Texture*> collectibles;
	std::vector<Texture*> scoreValue;
	std::vector<Texture*> tabScore;

	std::vector<Texture*> imgecrantitre;
	std::vector<Texture*> txtecrantitre;
	std::vector<Texture*> txtplay;
	std::vector<Texture*> txtscore;

	TTF_Font *font[MAX_FONT];
};
/*
		Contient tous les boutons
*/
struct AllButtons {
	
	std::vector<Buttons*> buttonEcrantitre;
	std::vector<Buttons*> buttonPlay;
	std::vector<Buttons*> buttonScore;
};
struct Map {
	std::vector<std::vector<Tile>> matriceMap;
	Uint8 map_length = 25;
	Uint8 map_height = 25;
};
//////////////////////// Structure niveau 0 ///////////////////////
struct Sysinfo {
	Screen screen;
	File file;
	Var var;
	AllTextures allTextures;
	AllButtons allButtons;
	Map map;
	Pacman* pacman = nullptr;
	std::vector<Ghost*> ghost;
};

#endif