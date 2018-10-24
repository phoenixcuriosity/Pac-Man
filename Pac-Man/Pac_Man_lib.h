/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15

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

// ********* CONSTANTES ******** //
//--- Constantes concernant l'ecran et la dimension de la fenetre  -----------------------------------------------------------------------------------

const Uint16 SCREEN_WIDTH = 1920;
const Uint16 SCREEN_HEIGHT = 1088;
const Uint8 TILE_SIZE = 32;

//--- Constantes concernant la taille des différents tableaux  --------------------------------------------------------------------------------------

const Uint8 MAX_GHOST = 4;
const Uint8 MAX_POS = 4;
const Uint8 MAX_SKIN = 2;
const Uint8 MAX_FONT = 160;

//--- Constantes concernant les objets Entity  ------------------------------------------------------------------------------------------------------

const Uint16 TEMPO_INVINCIBLE = 600;
const Uint8 INITIAL_VELOCITY = 2;

//--- Constantes concernant les couleurs pour l'utilisation de la SDL  -------------------------------------------------------------------------------

// {Red, Green, Blue, Alpha (transparance)} codé sur 8 bit -> Uint8

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color Yellow = { 255, 255, 0, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris
const SDL_Color NoColor = { 0, 0, 0, 0 };

// ********* ENUM ******** //
//--- enum concernant les objets Texture  -----------------------------------------------------------------------------------------------------------

/*
	* type de texte :
	*	-> blended : sans couleur de fond
	*	-> shaded : avec une couleur de fond
*/
enum Texte_Type : Uint8 { NA, blended, shaded};

/*
	* type de transparance :
	*	-> 0 transparance totale
	*	-> 255 totalement visible
*/
enum Transparance_Type : Uint8 { transparent = 0, semiTransparent = 128, nonTransparent = 255 };

/*
	* type de centrage :	
	*	-> nocenter : les positions x et y ne changent pas
	*	-> center_x : la position y ne change pas et centre la position x en focntion de longueur du texte
	*	-> center_y : la position x ne change pas et centre la position y en focntion de hauteur du texte
	*	-> center : centre totalement le texte en fonction de sa longueur et de sa hauteur
*/
enum Center_Type: Uint8 { nocenter, center_x, center_y, center };

// contient les index concernant le tableau de Texture ground
enum Ground_Type: Uint8 { blackTile, whiteTile, mapTile}; 

//--- enum concernant les objets Entity  -----------------------------------------------------------------------------------------------------------

// contient les différents type de Ghost
enum Ghost_Type: Uint8 { red, blue, yellow, pink};

// type de directions
enum Heading_Type: Uint8 { UP, LEFT, DOWN, RIGHT };

/* 
	* type de retour des fonctions Pacman::move et Ghost::move
	*	-> Not_Valid : la condition de mouvement n'est pas validée
	*	-> validCondition : la contion de mouvement est validée tout de suite
	*	-> validNextHeading : la condition de mouvement n'est pas validée tout de suite mais est gardé en mémoire
*/
enum Validation_Type: Uint8 { Not_Valid, validCondition, validNextHeading};

//--- enum concernant les valeurs des bonus  -------------------------------------------------------------------------------------------------------

// type de bonus sur la map
enum Bonus_Type: Uint8 { nothing, gold, cherry, strawberry, peach, apple, key};

// type de valeur des bonus
enum BonusValue_Type{ nothing1, valuegold = 100, valuecherry = 200, valuestrawberry = 400, valuepeach = 800, valueapple = 1600, ghost1 = 800, ghost2 = 1600, ghost3 = 3200, ghost4 = 10000,valuekey = 5000};

//--- enum concernant l'état dans le quel ce trouve le programme  ----------------------------------------------------------------------------------

// différents état de l'écran
enum State_Type: Uint8 { STATEnothing, STATEecrantitre, STATEplay, STATEscore };  

// spécifications de la séléction
enum Select_Type: Uint8 { selectnothing, pause, win, lost };	



// ********* STRUCTURE ******** //
//---------------------- Structure niveau 2 ---------------------------------------------------------------------------------------------------------
/*
	*	structure contenant les données en rapport avec le temps du programme
*/
struct GameTime {
	// nombre d'heures de jeu
	Uint8 hours = 0;

	// nombre de minutes de jeu, modulo 60
	Uint8 minutes = 0;

	// nombre de seconde de jeu, modulo 60
	Uint8 seconds = 0;

	Uint8 frame = 0;
};
struct ScorePlayer {
	// score du joueur
	unsigned int score = 0;

	// nom du joueur
	std::string name = "";
};
/*
	*	Structure décrivant une case dans la map
*/
struct Tile {
	// numéro de la case en x map[x][y]
	Uint8 indexX = 0; 

	// numéro de la case en y map[x][y]
	Uint8 indexY = 0; 

	// position en x sur l'écran
	unsigned int tile_x = 0;

	// position en y sur l'écran
	unsigned int tile_y = 0;

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
	const std::string score = "save/scores.txt";
	std::string saveMap = "save/saveMap.txt";
	std::string saveEntity = "save/saveEntity.txt";
};
struct Var {
	/*** type primitif	***/

	// variable permettant de quitter la boucle principale donc le jeu
	bool continuer = true;

	// état de la sélection du joueur : selectnothing, pause, win, lost
	Uint8 select = selectnothing;

	// état de l'écran du joueur : STATEnothing, STATEecrantitre, STATEplay, STATEscore
	Uint8 statescreen = STATEnothing;

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

	// structure contenant les données en rapport avec le temps du programme
	GameTime gameTime;
};
/*
	*	Contient toutes les Textures images
*/
struct AllTextures {
	// tableau d'images contenu dans l'écran titre
	std::vector<Texture*> imgecrantitre;

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
	TTF_Font *font[MAX_FONT];

	// tableau de textes contenu dans l'écran titre
	std::vector<Texte*> txtEcrantitre;

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
	// tableau de boutons contenu dans l'écran titre
	std::vector<Button*> buttonEcrantitre;

	// tableau de boutons contenu dans l'écran play
	std::vector<Button*> buttonPlay;

	// tableau de boutons contenu dans l'écran Score
	std::vector<Button*> buttonScore;
};
struct Map {
	// Matrice contenant des structures Tile
	std::vector<std::vector<Tile>> matriceMap;

	// longueur de la map en TILE_SIZE
	Uint8 map_length = 25;

	// hauteur de la map en TILE_SIZE
	Uint8 map_height = 25;
};
//---------------------- Structure niveau 0 ---------------------------------------------------------------------------------------------------------
struct Sysinfo {
	// contient les données en rapport à la SDL 
	Screen screen;

	// contient les noms et le chemins des fichiers .txt 
	File file;

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