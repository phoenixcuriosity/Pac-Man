/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.2

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

#include "lib.h"

#include "Buttons.h"
#include "Texture.h"

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;
const int tileSize = 32;
const int mapHeight = 25;
const int mapLength = 25;

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris

enum { normal, shaded, normaltexture};
enum { nocenter, center_x, center_y, center };

enum { STATEnothing, STATEecrantitre, STATEplay };  // différents état de l'écran
enum { selectnothing, NotToSelect, selectcreate, selectinspect, selectmove, selectmoveCitizen };	// spécifications de la séléction



typedef struct screen screen;
struct screen {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	std::string stringTileSize = std::to_string(tileSize);


};

typedef struct subcatWheel subcatWheel;
struct subcatWheel {
	unsigned int mouse_x = 0;
	unsigned int mouse_y = 0;
	unsigned int ywheel = 0;
	unsigned int xwheel = 0;
};

typedef struct var var;
struct var {

	bool continuer = true;
	unsigned int nbturn = 0;
	unsigned int select = selectnothing;
	unsigned int statescreen = 0; // selectnothing par défaut

	subcatWheel s_wheel;
};


typedef struct tile tile;
struct tile{
	unsigned int tile_nb = 0;
	unsigned int tile_x = 0;
	unsigned int tile_y = 0;

	bool wall = false;
	bool entity = false;
	
};

typedef struct texture texture;
struct texture {
	std::vector<Texture*> tabTexture;
	TTF_Font *font[80];
	unsigned int indexGround = 0;
	unsigned int indexPacman = 0;
};

typedef struct sysinfo sysinfo;
struct sysinfo {
	screen ecran;
	var variable;
	tile map[mapHeight * mapLength];
	std::vector<Buttons*> tabbutton;
	texture allTextures;
};












#endif