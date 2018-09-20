/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.9

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
#include "init.h"
#include "Texture.h"



class Entity { // classe abstraite
public:
	Entity() {};
	Entity(std::string name, unsigned int x, unsigned int y, unsigned int currentHeading, unsigned int nextHeading, unsigned int value = 0);
	~Entity();

	
	int tryToMove(tile map[], unsigned int pos);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture) = 0;

	std::string GETname()const;
	unsigned int GETx()const;
	unsigned int GETy()const;
	unsigned int GETxc()const;
	unsigned int GETyc()const;
	unsigned int GETtile()const;
	unsigned int GETcurrentHeading()const;
	unsigned int GETnextHeading()const;
	bool GETalternateSkin()const;
	bool GETinvincible()const;
	unsigned int GETtimeInvincible()const;
	unsigned int GETvalue()const;

	void SETname(std::string name);
	void SETx(unsigned int x);
	void SETy(unsigned int y);
	void SETxc(unsigned int);
	void SETyc(unsigned int);
	void SETtile(unsigned int tile);
	void SETcurrentHeading(unsigned int);
	void SETnextHeading(unsigned int);
	void SETalternateSkin(bool);
	void SETinvincible(bool);
	void SETtimeInvincible(unsigned int);
	void SETvalue(unsigned int value);

private:
	std::string _name;
	unsigned int _x;
	unsigned int _y;
	unsigned int _xc;
	unsigned int _yc;
	unsigned int _tile;

	unsigned int _currentHeading;
	unsigned int _nextHeading;
	bool _alternateSkin;

	bool _invincible;
	unsigned int _timeInvincible;
	unsigned int _value;
};

class Pacman : public Entity {
public:
	Pacman(std::string name, unsigned int x, unsigned int y, unsigned int value = 0);
	Pacman(const Pacman& player);
	~Pacman();

	int move(tile map[], std::vector<Ghost*>& ghost, unsigned int secondLoop = -1);
	unsigned int search(tile map[]);
	void value(tile map[], bool validMove);
	void collideGhost(std::vector<Ghost*>& ghost);

	void afficherStats(sysinfo& information);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture);
	

	unsigned int GETlife()const;
	unsigned int GETpowerUP()const;
	unsigned int GETtypeOfValue()const;

	void SETlife(unsigned int life);
	void SETpowerUP(unsigned int powerUP);
	void SETtypeOfValue(unsigned int);

private:
	
	unsigned int _life;
	unsigned int _powerUP;
	unsigned int _typeOfValue;
};

class Ghost : public Entity {
public:
	Ghost(std::string name, unsigned int x, unsigned int y, unsigned int type,unsigned int value = 0);
	~Ghost();

	int move(tile map[], unsigned int secondLoop = -1);
	unsigned int search(tile map[]);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, std::vector<Texture*>& misc);

	unsigned int GETtype()const;
	void SETtype(unsigned int type);

private:
	
	unsigned int _type;
};

#endif // !Entity_H

