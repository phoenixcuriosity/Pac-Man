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

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1088;
const int tileSize = 32;
const int mapHeight = 25;
const int mapLength = 25;
const unsigned int FONTMAX = 160;
const unsigned int vitesse = 2;
const unsigned int tempoInvincible = 600;
const unsigned int MAXGHOST = 4;
const unsigned int MAXPOS = 4;
const unsigned int MAXSKIN = 2;

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris
const SDL_Color NoColor = { 0, 0, 0, 0 };

enum { normal, blended, shaded};
enum { nocenter, center_x, center_y, center }; // centrage des textures et boutons
enum { blackTile, whiteTile, mapTile}; // allTexture.ground

enum { red, blue, yellow, pink};
enum { UP, LEFT, DOWN, RIGHT };
enum { Not_Valid, validCondition, validNextHeading};

enum { nothing, gold, cherry, strawberry, peach, apple, key};
enum { nothing1, valuegold = 100, valuecherry = 200, valuestrawberry = 400, valuepeach = 800, valueapple = 1600, ghost1 = 800, ghost2 = 1600, ghost3 = 3200, ghost4 = 10000,valuekey = 5000};

enum { STATEnothing, STATEecrantitre, STATEplay, STATEscore };  // différents état de l'écran
enum { selectnothing, pause, win, lost };	// spécifications de la séléction

struct scorePlayer {
	unsigned int score = 0;
	std::string name = "";
};
struct screen {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};
struct file {
	const std::string log = "log.txt";
	const std::string score = "save/scores.txt";
};
struct var {
	bool continuer = true;
	
	unsigned int select = selectnothing;
	unsigned int statescreen = 0; // selectnothing par défaut
	unsigned int score = 0;
	bool win = false;

	unsigned int modulo = 0;
	unsigned int moduloScore = 0;
	unsigned int tempoScore = 0;

	std::vector<scorePlayer> tabScorePlayer;
};
struct tile{
	unsigned int tile_nb = 0;
	unsigned int tile_x = 0;
	unsigned int tile_y = 0;

	bool wall = false;
	unsigned int entity = gold;
	
};
struct texture {
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

	TTF_Font *font[FONTMAX];
};
struct button {
	std::vector<Buttons*> buttonecrantitre;
	std::vector<Buttons*> buttonplay;
	std::vector<Buttons*> buttonscore;
};
struct sysinfo {
	screen ecran;
	file files;
	var variable;
	std::vector<tile> map;
	button allButton;
	texture allTextures;
	std::vector<Ghost*> ghost;
};

#endif