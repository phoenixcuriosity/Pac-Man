/*

   Pac-Man
   Copyright SAUTER Robin (robin.sauter@orange.fr)
   last modification on this file on version : 0.17
   file version : 1.0

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

#ifndef Entity_H
#define Entity_H

#include "lib.h"


/* *********************************************************
	*					 Constantes
  ********************************************************* */

//--- Constantes concernant la taille des diff�rents tableaux  --------------------------------------------------------------------------------------

// nombre maximal d'objets Ghost dans les tableau (peut servir d'index) 
const Uint8 MAX_GHOST = 4;

// nombre maximal de positions cardinales, li� � -> enum Heading_Type: Uint8 { UP, LEFT, DOWN, RIGHT };
const Uint8 MAX_POS = 4;

// nombre maximal d'animations par position cardinal
const Uint8 MAX_SKIN = 2;

//--- Constantes concernant les objets Entity  ------------------------------------------------------------------------------------------------------

// temps en nombre de cycle de la boucle principale (60 boucles/s -> 600 boucles = 10s)
const Uint16 TEMPO_INVINCIBLE = 600;

// vitesse des objets Entity en pixel
const Uint8 INITIAL_VELOCITY = 2;



/* *********************************************************
	*					 Enum
  ********************************************************* */

//--- enum concernant les objets Entity  -----------------------------------------------------------------------------------------------------------

// contient les diff�rents type de Ghost
enum Ghost_Type : Uint8 { red, blue, yellow, pink };

// type de directions
enum Heading_Type : Uint8 { UP, LEFT, DOWN, RIGHT };

/*
	* type de retour des fonctions Pacman::move et Ghost::move
	*	-> Not_Valid : la condition de mouvement n'est pas valid�e
	*	-> validCondition : la contion de mouvement est valid�e tout de suite
	*	-> validNextHeading : la condition de mouvement n'est pas valid�e tout de suite mais est gard� en m�moire
*/
enum Validation_Type : Uint8 { Not_Valid, validCondition, validNextHeading, trySecondTime };

//--- enum concernant les valeurs des bonus  -------------------------------------------------------------------------------------------------------

// type de bonus sur la map
enum Bonus_Type : Uint8 { nothing, gold, cherry, strawberry, peach, apple, key };

// type de valeur des bonus
enum BonusValue_Type { nothing1, valuegold = 100, valuecherry = 200, valuestrawberry = 400, valuepeach = 800, valueapple = 1600, ghost1 = 800, ghost2 = 1600, ghost3 = 3200, ghost4 = 10000, valuekey = 5000 };





/* *********************************************************
	*					Structures
  ********************************************************* */


// structure repr�sentant une case de la grille pour etre utilis�e dans findAPath()
struct Node 
{
	Uint8 indexX = NULL;
	Uint8 indexY = NULL;
};
struct NodeA
{
	Uint8 indexX = NULL;
	Uint8 indexY = NULL;
	unsigned int cost = NULL;
};


/* *********************************************************
	*					Classes
  ********************************************************* */

//--- Entity -------------------------------------------------------------------------------------------------------------------------------------

// classe abstraite
class Entity
{ 

	/* *********************************************************
		*				STATIC
	 ********************************************************* */
public:
	// demande un mouvement de tous les objets Entity, conditions de victoire et de d�faite
	static void move(Sysinfo& sysinfo);

public:
	// initialisation des objets Entity au positions et param�tres pr�-d�finis
	static void initEntity(Pacman*& pacman, std::vector<Ghost*>& ghost, std::vector<std::vector<Tile>>& map);

	// destruction de tous les objets Entity
	static void destroyEntity(Pacman*& pacman, std::vector<Ghost*>& ghost);


	/* *********************************************************
		*				METHODES
	 ********************************************************* */
public: // constructeurs et destructeur
	Entity(std::string name, unsigned int x, unsigned int y, Uint8 currentHeading, Uint8 nextHeading, unsigned int value = 0);
	~Entity();


public: // Algorithme

	/*
		Algorithme de recherche : 
		*	-> actuellement implent� : glouton
		*	-> futur version : A*
	*/
	void findAPath(std::vector<std::vector<Tile>>& map, Uint8 indexX, Uint8 indexY);

	/*
		recherche si la case avec les indexX et indexY est d�j� dans le chemin
		*	-> retorune false si la case se trouve d�j� dans le chemin
		*	-> retourne true si la case ne fait pas encore parti du chemin
	*/
	bool notPreviousTile(std::vector<Node>& path, Uint8 newIndexX, Uint8 newIndexY);

public: // op�rations sur l'objet
	/*
		test la future position de l'objet
		*	-> retourne Not_Valid (false) si la future position est bloqu�e
		*	-> retourne validCondition (true) si l'objet peut effectuer le mouvement vers la future position
	*/
	bool tryToMove(std::vector<std::vector<Tile>>& map, unsigned int pos);

	/* 
		cherche si l'objet est pleinement sur la case
		*	-> retourne vrai si l'objet est effectivement pleinement la case
		*	-> retourne faux sinon
	*/
	bool isOnFullTile(std::vector<std::vector<Tile>>& map, unsigned int i, unsigned int j);

	/*
		cherche si l'objet (centre) est sur la case
		*	-> retourne vrai si l'objet est effectivement la case
		*	-> retourne faux sinon
	*/
	bool isOnTile(std::vector<std::vector<Tile>>& map, unsigned int i, unsigned int j);

	// change les coordonn�es de l'objet
	void makeTheMove(bool validMove, unsigned int pos);

	// test de la position sp�cifique de t�l�poration
	void teleport(std::vector<std::vector<Tile>>& map);

	virtual void goHomeGhost();

public: // affichage
	virtual void afficher(std::vector<Texture*> tabTexture[]) = 0;

public: // assesseurs
	inline std::string GETname()const { return _name; };
	inline unsigned int GETx()const { return _x; };
	inline unsigned int GETy()const { return _y; };
	// d�duis de x
	inline unsigned int GETxc()const { return _x + TILE_SIZE / 2; };
	// d�duis de y
	inline unsigned int GETyc()const { return _y + TILE_SIZE / 2; };
	inline Uint8 GETindexX()const { return _indexX; };
	inline Uint8 GETindexY()const { return _indexY; };
	inline Uint8 GETcurrentHeading()const { return _currentHeading; };
	inline Uint8 GETnextHeading()const { return _nextHeading; };
	inline bool GETalternateSkin()const { return _alternateSkin; };
	inline bool GETinvincible()const { return _invincible; };
	inline unsigned int GETtimeInvincible()const { return _timeInvincible; };
	inline unsigned int GETvalue()const { return _value; };
	inline Uint8 GETvelocity()const { return _velocity; };
	inline std::vector<std::vector<Node>> GETtabPath()const { return _tabPath; };
	inline std::vector<std::vector<Node>>& GETtabPathNONCONST() { return _tabPath; };

	inline void SETname(std::string name) { _name = name; };
	inline void SETx(unsigned int x) { _x = x; };
	inline void SETy(unsigned int y) { _y = y; };
	inline void SETindexX(Uint8 indexX) { _indexX = indexX; };
	inline void SETindexY(Uint8 indexY) { _indexY = indexY; };
	inline void SETcurrentHeading(Uint8 currentHeading) { _currentHeading = currentHeading; };
	inline void SETnextHeading(Uint8 nextHeading) { _nextHeading = nextHeading; };
	inline void SETalternateSkin(bool alternateSkin) { _alternateSkin = alternateSkin; };
	inline void SETinvincible(bool invincible) { _invincible = invincible; };
	inline void SETtimeInvincible(unsigned int timeInvincible) { _timeInvincible = timeInvincible; };
	inline void SETvalue(unsigned int value) { _value = value; };
	inline void SETvelocity(Uint8 velocity) { _velocity = velocity; };
	inline void SETtabPath(std::vector<std::vector<Node>>& tabPath) { _tabPath = tabPath; };


	/* *********************************************************
		*				ATTRIBUTS
	 ********************************************************* */
private: 
	// nom de l'objet Entity
	std::string _name;

	// position en x sur la fenetre
	unsigned int _x;

	// position en y sur la fenetre
	unsigned int _y;

	// index de la case en x map[x][y]
	Uint8 _indexX;

	// index de la case en y map[x][y]
	Uint8 _indexY;

private:
	// direction cardinal courante
	Uint8 _currentHeading;

	// direction cardinal futur
	Uint8 _nextHeading;

	// permet d'alterner le skin pour cr�er une animation
	bool _alternateSkin;

	// invincibilit� de l'objet Entity
	bool _invincible;

	// temps restant de l'invincibilit�
	unsigned int _timeInvincible;

	// valeur ou score de l'objet
	unsigned int _value;

	// vitesse en pixel de l'objet, par d�faut INITIAL_VELOCITY = 2
	Uint8 _velocity;

	// tableau des differents chemins pour aller � la cible
	std::vector<std::vector<Node>> _tabPath;

};

//--- Pacman ------------------------------------------------------------------------------------------------------------------------------------

class Pacman : public Entity
{
public: // constructeurs et destructeur
	Pacman(std::string name, unsigned int x, unsigned int y, unsigned int value = 0);
	Pacman(const Pacman& player);
	~Pacman();

public: // op�rations sur l'objet
	/*
		boucle pouvant etre parcouru au maximum 2 fois
		permet d'�valuer et de tester le mouvement possible
		en fonction des murs et des objets Ghost
		*	-> retourne 0 si la foncton ne rencontre pas d'erreur
		*	-> retourne -1 si la fonction rencontre une erreur
	*/
	int8_t move(Map& map, std::vector<Ghost*>& ghost, unsigned int secondLoop = -1);
	
	/*
		cherche la position de Pacman 
		*	-> retourne Not_Valid (0) si la future direction est la meme que la direction courante
		*	-> retourne validCondition (1) si l'objet se trouve entre 2 cases et si la future direction est diff�rente de la direction courante
		*	-> retourne validNextHeading (2) si l'objet se trouve sur une case pleine et si la future direction est diff�rente de la direction courante
	*/
	Uint8 search(Map& map);

	// cherche la valeur du bonus sur la case o� est pr�sent Pacman
	void value(std::vector<std::vector<Tile>>& map, bool validMove);

	// gestion des collisions entre Pacman et les objets Ghost
	void collideGhost(std::vector<Ghost*>& ghost, Map& map);

	virtual void goHomeGhost();

	// pr�vision en ligne droite de la futur case de Pacman
	virtual void pathForecast(Map& map);

public: // affichage
	// affiche le nombre de vie restante et le score du joueur
	void afficherStats(SDL_Renderer*& renderer, TTF_Font* font[]);

	// affichage de la Texture en fonction de la direction et de l'alternance du skin
	virtual void afficher(std::vector<Texture*> tabTexture[]);

public: // assesseurs
	inline Uint8 GETlife()const { return _life; };
	inline Uint8 GETpowerUP()const { return _powerUP; };
	inline unsigned int GETtypeOfValue()const { return _typeOfValue; };
	inline Uint8 GETindexXpred()const { return _indexXPred; };
	inline Uint8 GETindexYpred()const { return _indexYPred; };

	inline void SETlife(Uint8 life) { _life = life; };
	inline void SETpowerUP(Uint8 powerUP) { _powerUP = powerUP; };
	inline void SETtypeOfValue(unsigned int typeOfValue) { _typeOfValue = typeOfValue; };

private:
	// vie restant de Pacman, valeur par d�faut 3
	Uint8 _life;

	// ****obsol�te**** permet de savoir si Pacman a mang� un PowerUp
	Uint8 _powerUP;

	// permet de connaitre la valeur du dernier bonus mang� par pacman
	unsigned int _typeOfValue;

	// noeud de la future intersection
	Uint8 _indexXPred;

	Uint8 _indexYPred;
};

//--- Ghost -------------------------------------------------------------------------------------------------------------------------------------

class Ghost : public Entity
{
public: // constructeurs et destructeur
	Ghost(std::string name, unsigned int x, unsigned int y, Uint8 type,unsigned int value = 0);
	~Ghost();

public: // op�rations sur l'objet
	/*
		fonction pouvant etre parcourue au maximum 2 fois (r�cursive)
		permet d'�valuer et de tester le mouvement possible
		en fonction des murs et des objets Ghost
		*	-> retourne 0 si la foncton ne rencontre pas d'erreur
		*	-> retourne -1 si la fonction rencontre une erreur
	*/
	int8_t move(Map& map, Sysinfo& sysinfo, unsigned int secondLoop = -1);

	/*
		cherche la position de l'objet Ghost
		*	-> retourne Not_Valid (0) si la future direction est la meme que la direction courante
		*	-> retourne validCondition (1) si l'objet se trouve entre 2 cases et si la future direction est diff�rente de la direction courante
		*	-> retourne validNextHeading (2) si l'objet se trouve sur une case pleine et si la future direction est diff�rente de la direction courante
	*/
	Uint8 search(Map& map, Uint8 indexXPac, Uint8 indexYPac, Uint8 indexXPacPred, Uint8 indexYPacPred);

	// cr�e une nouvelle direction future al�atoire pour pink et yellow
	void makeNextHeading(std::vector<std::vector<Tile>>& map, Pacman*& pacman);

	virtual void goHomeGhost();

public: // affichage
	// affichage de la Texture en fonction de la direction et de l'alternance du skin
	virtual void afficher(std::vector<Texture*> tabTexture[]);

public: // assesseurs
	inline Uint8 GETtype()const { return _type; };
	inline bool GETgoHome()const { return _goHome; };

	inline void SETtype(Uint8 type) { _type = type; };
	inline void SETgoHome(bool goHome) { _goHome = goHome; };

private:
	// type de Ghost : red, blue, yellow, pink 
	Uint8 _type;

	// permet de renvoyer le ghost au milieu (maison) lorqu'il est touch�
	bool _goHome;
};

#endif // !Entity_H

/*
*	End Of File
*/

