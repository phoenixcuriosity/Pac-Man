/*

	

*/

/*

	

*/

#ifndef Pac_Man_lib_H
#define Pac_Man_lib_H

#include "lib.h"

#include "Buttons.h"
#include "Texture.h"

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
const int tileSize = 64;

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris

enum { normal, shaded, normaltexture};
enum { nocenter, center_x, center_y, center };

enum { STATEnothing, STATEecrantitre, STATEecrannewgame, STATEreload, STATEmainmap, STATEscience, STATEcitiemap };  // différents état de l'écran
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
	
};

typedef struct map map;
struct map {
	
	
	//unsigned int selectsupertiles = ceil(float(SUPERTILES)/2);
};



typedef struct texture texture;
struct texture {
	std::vector<Texture*> tabTexture;
	TTF_Font *font[80];
};

typedef struct sysinfo sysinfo;
struct sysinfo {
	screen ecran;
	var variable;
	map maps;
	std::vector<Buttons*> tabbutton;
	texture allTextures;
};












#endif