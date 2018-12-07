/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17

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

#ifndef lib_H
#define lib_H


#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include "wtypes.h"

#include "SDL2-2.0.8/include/SDL.h"
#include "SDL2-2.0.8/include/SDL_ttf.h"
#include "SDL2-2.0.8/include/SDL_image.h"
#include "SDL2-2.0.8/include/SDL_mixer.h"

typedef struct Node Node;
typedef struct NodeA NodeA;
typedef struct ScorePlayer ScorePlayer;
typedef struct Screen Screen;
typedef struct File File;
typedef struct Var Var;
typedef struct Tile Tile;
typedef struct AllTextures AllTextures;
typedef struct AllTextes AllTextes;
typedef struct AllButtons AllButtons;
typedef struct Map Map;
typedef struct Sysinfo Sysinfo;

class IHM;
class GameTime;
class Texture;
class Texte;
class ButtonImage;
class ButtonTexte;
class Entity;
class Pacman;
class Ghost;
class SaveReload;

#endif
