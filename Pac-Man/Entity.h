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

#ifndef Entity_H
#define Entity_H

#include "lib.h"

// structure représentant une case de la grille pour etre utilisée dans findAPath()
struct Node {
	Uint8 indexX = 0;
	Uint8 indexY = 0;
};

//--- Entity -------------------------------------------------------------------------------------------------------------------------------------

// classe abstraite
class Entity { 

	/* *********************************************************
						STATIC
	 ********************************************************* */
public:
	// demande un mouvement de tous les objets Entity, conditions de victoire et de défaite
	static void move(Sysinfo& sysinfo);

public:
	// initialisation des objets Entity au positions et paramètres pré-définis
	static void initEntity(Pacman*& pacman, std::vector<Ghost*>& ghost, std::vector<std::vector<Tile>>& map);

	// destruction de tous les objets Entity
	static void destroyEntity(Pacman*& pacman, std::vector<Ghost*>& ghost);


	/* *********************************************************
						METHODES
	 ********************************************************* */
public: // constructeurs et destructeur
	Entity(std::string name, unsigned int x, unsigned int y, Uint8 currentHeading, Uint8 nextHeading, unsigned int value = 0);
	~Entity();


public: // Algorithme
	/*
		Algorithme de recherche de chemin le plus court entre 2 points
	*/
	void findAPath(std::vector<std::vector<Tile>>& map, Uint8 indexX, Uint8 indexY);

	/*
		recherche si la case avec les indexX et indexY est déjà dans le chemin
		*	-> retorune false si la case se trouve déjà dans le chemin
		*	-> retourne true si la case ne fait pas encore parti du chemin
	*/
	bool notPreviousTile(std::vector<Node>& path, Uint8 newIndexX, Uint8 newIndexY);

public: // opérations sur l'objet
	/*
		test la future position de l'objet
		*	-> retourne Not_Valid (false) si la future position est bloquée
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

	// change les coordonnées de l'objet
	void makeTheMove(bool validMove, unsigned int pos);

	// test de la position spécifique de téléporation
	void teleport(std::vector<std::vector<Tile>>& map);

	virtual void goHomeGhost();

public: // affichage
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture[]) = 0;

public: // assesseurs
	std::string GETname()const;
	unsigned int GETx()const;
	unsigned int GETy()const;
	// déduis de x
	unsigned int GETxc()const;
	// déduis de y
	unsigned int GETyc()const;
	Uint8 GETindexX()const;
	Uint8 GETindexY()const;
	Uint8 GETcurrentHeading()const;
	Uint8 GETnextHeading()const;
	bool GETalternateSkin()const;
	bool GETinvincible()const;
	unsigned int GETtimeInvincible()const;
	unsigned int GETvalue()const;
	Uint8 GETvelocity()const;
	std::vector<std::vector<Node>> GETtabPath()const;
	std::vector<std::vector<Node>>& GETtabPathNONCONST();

	void SETname(std::string name);
	void SETx(unsigned int x);
	void SETy(unsigned int y);
	void SETindexX(Uint8 indexX);
	void SETindexY(Uint8 indexY);
	void SETcurrentHeading(Uint8);
	void SETnextHeading(Uint8);
	void SETalternateSkin(bool);
	void SETinvincible(bool);
	void SETtimeInvincible(unsigned int);
	void SETvalue(unsigned int value);
	void SETvelocity(Uint8 velocity);
	void SETtabPath(std::vector<std::vector<Node>>& tabPath);


	/* *********************************************************
						ATTRIBUTS
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

	// permet d'alterner le skin pour créer une animation
	bool _alternateSkin;

	// invincibilité de l'objet Entity
	bool _invincible;

	// temps restant de l'invincibilité
	unsigned int _timeInvincible;

	// valeur ou score de l'objet
	unsigned int _value;

	// vitesse en pixel de l'objet, par défaut INITIAL_VELOCITY = 2
	Uint8 _velocity;

	// tableau des differents chemins pour aller à la cible
	std::vector<std::vector<Node>> _tabPath;

};

//--- Pacman ------------------------------------------------------------------------------------------------------------------------------------

class Pacman : public Entity {
public: // constructeurs et destructeur
	Pacman(std::string name, unsigned int x, unsigned int y, unsigned int value = 0);
	Pacman(const Pacman& player);
	~Pacman();

public: // opérations sur l'objet
	/*
		boucle pouvant etre parcouru au maximum 2 fois
		permet d'évaluer et de tester le mouvement possible
		en fonction des murs et des objets Ghost
		*	-> retourne 0 si la foncton ne rencontre pas d'erreur
		*	-> retourne -1 si la fonction rencontre une erreur
	*/
	int8_t move(Map& map, std::vector<Ghost*>& ghost, unsigned int secondLoop = -1);
	
	/*
		cherche la position de Pacman 
		*	-> retourne Not_Valid (0) si la future direction est la meme que la direction courante
		*	-> retourne validCondition (1) si l'objet se trouve entre 2 cases et si la future direction est différente de la direction courante
		*	-> retourne validNextHeading (2) si l'objet se trouve sur une case pleine et si la future direction est différente de la direction courante
	*/
	Uint8 search(Map& map);

	// cherche la valeur du bonus sur la case où est présent Pacman
	void value(std::vector<std::vector<Tile>>& map, bool validMove);

	// gestion des collisions entre Pacman et les objets Ghost
	void collideGhost(std::vector<Ghost*>& ghost);

	virtual void goHomeGhost();

public: // affichage
	// affiche le nombre de vie restante et le score du joueur
	void afficherStats(SDL_Renderer*& renderer, TTF_Font* font[]);

	// affichage de la Texture en fonction de la direction et de l'alternance du skin
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture[]);
	
public: // assesseurs
	Uint8 GETlife()const;
	Uint8 GETpowerUP()const;
	unsigned int GETtypeOfValue()const;

	void SETlife(Uint8 life);
	void SETpowerUP(Uint8 powerUP);
	void SETtypeOfValue(unsigned int);

private:
	// vie restant de Pacman, valeur par défaut 3
	Uint8 _life;

	// ****obsolète**** permet de savoir si Pacman a mangé un PowerUp
	Uint8 _powerUP;

	// permet de connaitre la valeur du dernier bonus mangé par pacman
	unsigned int _typeOfValue;
};

//--- Ghost -------------------------------------------------------------------------------------------------------------------------------------

class Ghost : public Entity {
public: // constructeurs et destructeur
	Ghost(std::string name, unsigned int x, unsigned int y, Uint8 type,unsigned int value = 0);
	~Ghost();

public: // opérations sur l'objet
	/*
		fonction pouvant etre parcourue au maximum 2 fois (récursive)
		permet d'évaluer et de tester le mouvement possible
		en fonction des murs et des objets Ghost
		*	-> retourne 0 si la foncton ne rencontre pas d'erreur
		*	-> retourne -1 si la fonction rencontre une erreur
	*/
	int8_t move(Map& map, Sysinfo& sysinfo, unsigned int secondLoop = -1);

	/*
		cherche la position de l'objet Ghost
		*	-> retourne Not_Valid (0) si la future direction est la meme que la direction courante
		*	-> retourne validCondition (1) si l'objet se trouve entre 2 cases et si la future direction est différente de la direction courante
		*	-> retourne validNextHeading (2) si l'objet se trouve sur une case pleine et si la future direction est différente de la direction courante
	*/
	Uint8 search(Map& map, Uint8 indexX, Uint8 indexY);

	// créer une nouvelle direction future en fonction du type de Ghost
	void makeNextHeading(std::vector<std::vector<Tile>>& map, Pacman*& pacman);

	virtual void goHomeGhost();

public: // affichage
	// affichage de la Texture en fonction de la direction et de l'alternance du skin
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture[]);

public: // assesseurs
	Uint8 GETtype()const;
	bool GETgoHome()const;

	void SETtype(Uint8 type);
	void SETgoHome(bool goHome);

private:
	// type de Ghost : red, blue, yellow, pink 
	Uint8 _type;

	// permet de renvoyer le ghost au milieu (maison) lorqu'il est touché
	bool _goHome;
};

#endif // !Entity_H

