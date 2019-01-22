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

#ifndef Pac_Man_lib_H
#define Pac_Man_lib_H

#include "lib.h"  // include lib et typedef

#include "IHM.h"
#include "Entity.h"
#include "SaveReload.h"
#include "Texture.h"

/* *********************************************************
						 Constantes
  ********************************************************* */

//--- Constantes concernant l'ecran et la dimension de la fenetre  -----------------------------------------------------------------------------------

// longueur et hauteur d'une case en pixel
const Uint8 TILE_SIZE = 32;

/*
	Pendant le développement du jeux, les parametres optimaux ont été:
	*	-> SCREEN_WIDTH = 1920 pixels 
	*	-> SCREEN_HEIGHT = 1088 pixels
	*	-> SCREEN_REFRESH_RATE = 60 Hz
	SCREEN_WIDTH et SCREEN_HEIGHT doivent etre des multiples de TILE_SIZE pour que le placement des objets Entity fonctionne bien
*/


Uint16 getHorizontal();
// longueur de la fenetre en pixel
const Uint16 SCREEN_WIDTH = getHorizontal();

Uint16 getVertical();
// hauteur de la fenetre en pixel
const Uint16 SCREEN_HEIGHT = getVertical();

Uint8 getRefreshRate();
// fréquence de rafraichissement de l'écran en Hz
const Uint8 SCREEN_REFRESH_RATE = getRefreshRate();

// nombre de musiques
const Uint8 MAX_MUSIC = 4;


/* *********************************************************
						 Enum
  ********************************************************* */

// contient les index concernant le tableau de Texture ground
enum Ground_Type: Uint8 { blackTile, whiteTile}; 

// contient les index concernant le tableau de Mix_Music*
enum Music_Type : Uint8 { music_intro, music_game, music_died, music_score};

//--- enum concernant l'état dans le quel ce trouve le programme  ----------------------------------------------------------------------------------

// différents état de l'écran
enum State_Type: Uint8 { STATEnothing, STATEecranTitre, STATEplay, STATEscore };  

// spécifications de la séléction
enum Select_Type: Uint8 { selectnothing, pause, win, lost };	



/* *********************************************************
						Structures
  ********************************************************* */
//---------------------- Structure niveau 2 ---------------------------------------------------------------------------------------------------------
/*
	*	Structure décrivant une case dans la map
*/
struct Tile {
	// numéro de la case en x map[x][y]
	Uint8 indexX = NULL; 

	// numéro de la case en y map[x][y]
	Uint8 indexY = NULL;

	// position en x sur l'écran
	unsigned int tile_x = NULL;

	// position en y sur l'écran
	unsigned int tile_y = NULL;

	// s'il y a un mur ou non
	bool wall = false;

	// bonus de la case, par défaut gold (1)
	Uint8 entity = gold;
};
//---------------------- Structure niveau 1 ---------------------------------------------------------------------------------------------------------
struct Screen {
	// ptr sur la fenetre crée par la SDL
	SDL_Window *window = nullptr;

	// ptr sur le renderer crée par la SDL
	SDL_Renderer *renderer = nullptr;
};
/*
	*	Structure contenant tous les noms des fichiers ainsi que leurs chemins
*/
struct File {
	const std::string log = "log.txt";
	const std::string score = "save/scores.save";
	const std::string saveMap = "save/saveMap.save";
	const std::string saveEntity = "save/saveEntity.save";
	const std::string levelMap = "save/levelMap.pacman";
};
struct Var {
	/*** type primitif	***/

	// variable permettant de quitter la boucle principale donc le jeu
	bool continuer = true;

	/*
		état de la sélection du joueur
		enum Select_Type: Uint8 { selectnothing, pause, win, lost };
	*/
	Uint8 select = selectnothing;

	/* 
		état de l'écran du joueur
		enum State_Type: Uint8 { STATEnothing, STATEecranTitre, STATEplay, STATEscore };
	*/
	Uint8 stateScreen = STATEnothing;

	// variable de victoire
	bool win = false;

	// modulo permettant de passer un nombre de fois pré-défini par seconde (max 60/s -> flag : SDL_RENDERER_PRESENTVSYNC)
	Uint8 modulo = 0;

	// nombre de cycles ou l'on affiche la valeur du bonus mangé par Pacman  
	Uint8 moduloScore = 0;

	// garde la dernier valeur du bonus mangé par Pacman  
	unsigned int tempoScore = 0;

	
	/*** type personnalisé	***/

	// classe permettant la sauvegarde et le chargement
	SaveReload saveReload;

	/*
		classe contenant les données en rapport avec le temps du programme
		*	-> RunTime : dépend du nombre de cycle de la boucle prinicpale par seconde
		*	-> RealTime : temps calculé par le système
	*/
	GameTime gameTime;
};
/*
	*	Contient toutes les Textures images
*/
struct AllTextures {
	// tableau d'images contenu dans l'écran titre
	std::vector<Texture*> imgecranTitre;

	// tableau d'images contenu dans le sol de la map
	std::vector<Texture*> ground;

	// tableau d'images concernant Pacman, 2 skins par position cardinale
	std::vector<Texture*> pacman;

	// tableau d'images concernant Red, 2 skins par position cardinale
	std::vector<Texture*> red;

	// tableau d'images concernant Blue, 2 skins par position cardinale
	std::vector<Texture*> blue;

	// tableau d'images concernant Yellow, 2 skins par position cardinale
	std::vector<Texture*> yellow;

	// tableau d'images concernant Pink, 2 skins par position cardinale
	std::vector<Texture*> pink;

	// tableau d'images concernant la texture lorsque les Ghost ne sont plus invincible
	std::vector<Texture*> miscGhost;

	// tableau d'images concernant les bonus
	std::vector<Texture*> collectibles;
};
/*
	*	Contient toutes les Textes
*/
struct AllTextes {
	// tableau de polices de la font arial
	TTF_Font *font[MAX_FONT] = {};

	// tableau de textes contenu dans l'écran titre
	std::vector<Texte*> txtecranTitre;

	// tableau de textes contenu dans l'écran play
	std::vector<Texte*> txtPlay;

	// tableau de textes contenu dans l'écran play pour les valeurs des bonus
	std::vector<Texte*> scoreValue;

	// tableau de textes contenu dans l'écran play pour l'affichage du score du joueur
	std::vector<Texte*> txtScore;

	// tableau de textes contenu dans l'écran Score
	std::vector<Texte*> tabScore;
};
/*
	*	Contient tous les boutons
*/
struct AllButtons {
	// tableau de boutonsTexte contenu dans l'écran titre
	std::vector<ButtonTexte*> buttonTexteEcranTitre;

	// tableau de boutonsImage contenu dans l'écran titre
	std::vector<ButtonImage*> buttonImageEcranTitre;

	// tableau de boutons contenu dans l'écran play
	std::vector<ButtonTexte*> buttonTextePlay;

	// tableau de boutonsImage contenu dans l'écran play
	std::vector<ButtonImage*> buttonImagePlay;

	// tableau de boutons contenu dans l'écran Score
	std::vector<ButtonTexte*> buttonTexteScore;
};
struct Map {

	// Matrice contenant les murs de la map -> donné par save/levelMap.txt
	std::vector<std::vector<bool>> matriceMapWall;

	// Matrice contenant des structures Tile
	std::vector<std::vector<Tile>> matriceMap;

	// longueur de la map en TILE_SIZE -> donné par save/levelMap.txt
	Uint8 map_length = NULL;

	// hauteur de la map en TILE_SIZE -> donné par save/levelMap.txt
	Uint8 map_height = NULL;

	// valeur courante du niveau chargé
	Uint8 levelMap = 0;
};
//---------------------- Structure niveau 0 ---------------------------------------------------------------------------------------------------------
struct Sysinfo {
	// contient les données en rapport à la SDL 
	Screen screen;

	// contient les noms et le chemins des fichiers .txt 
	File file;

	// Musiques du jeu
	Mix_Music *music[MAX_MUSIC] = {};

	// contient des variables non organisées
	Var var;

	// contient toutes les images
	AllTextures allTextures;

	// contient tous les textes
	AllTextes allTextes;

	// contient tous les boutons
	AllButtons allButtons;

	// contient les données en rapport à la map
	Map map;

	// ptr sur l'objet Pacman (classe fille de Entity)
	Pacman* pacman = nullptr;

	// tableau de ptr sur les objets Ghost (classe fille de Entity)
	std::vector<Ghost*> ghost;
};

#endif