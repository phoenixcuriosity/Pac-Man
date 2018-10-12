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

#ifndef Entity_H
#define Entity_H

#include "lib.h"
// classe abstraite
class Entity { 
public:
	static void move(Sysinfo& sysinfo);
public:
	static void initEntity(Pacman*& pacman, std::vector<Ghost*>& ghost);
	static void destroyEntity(Pacman*& pacman, std::vector<Ghost*>& ghost);

public:
	Entity() {};
	Entity(std::string name, unsigned int x, unsigned int y, Uint8 currentHeading, Uint8 nextHeading, unsigned int value = 0);
	~Entity();

	bool tryToMove(std::vector<std::vector<Tile>>& map, unsigned int pos);
	bool isOnFullTile(std::vector<std::vector<Tile>>& map, unsigned int i, unsigned int j);
	bool isOnTile(std::vector<std::vector<Tile>>& map, unsigned int i, unsigned int j);
	void makeTheMove(bool validMove, unsigned int pos);
	void teleport();
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture) = 0;

	std::string GETname()const;
	unsigned int GETx()const;
	unsigned int GETy()const;
	unsigned int GETxc()const;
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

	void SETname(std::string name);
	void SETx(unsigned int x);
	void SETy(unsigned int y);
	void SETxc(unsigned int);
	void SETyc(unsigned int);
	void SETindexX(Uint8 indexX);
	void SETindexY(Uint8 indexY);
	void SETcurrentHeading(Uint8);
	void SETnextHeading(Uint8);
	void SETalternateSkin(bool);
	void SETinvincible(bool);
	void SETtimeInvincible(unsigned int);
	void SETvalue(unsigned int value);
	void SETvelocity(Uint8 velocity);

private:
	std::string _name;
	unsigned int _x;
	unsigned int _y;
	unsigned int _xc;
	unsigned int _yc;
	Uint8 _indexX;
	Uint8 _indexY;

	Uint8 _currentHeading;
	Uint8 _nextHeading;
	bool _alternateSkin;

	bool _invincible;
	unsigned int _timeInvincible;
	unsigned int _value;

	Uint8 _velocity;
};

class Pacman : public Entity {
public:
	Pacman(std::string name, unsigned int x, unsigned int y, unsigned int value = 0);
	Pacman(const Pacman& player);
	~Pacman();

	int8_t move(Map& map, std::vector<Ghost*>& ghost, unsigned int secondLoop = -1);
	Uint8 search(Map& map);
	void value(std::vector<std::vector<Tile>>& map, bool validMove);
	void collideGhost(std::vector<Ghost*>& ghost);

	void afficherStats(Sysinfo& sysinfo);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture);
	

	Uint8 GETlife()const;
	Uint8 GETpowerUP()const;
	unsigned int GETtypeOfValue()const;

	void SETlife(Uint8 life);
	void SETpowerUP(Uint8 powerUP);
	void SETtypeOfValue(unsigned int);

private:
	
	Uint8 _life;
	Uint8 _powerUP;
	unsigned int _typeOfValue;
};

class Ghost : public Entity {
public:
	Ghost(std::string name, unsigned int x, unsigned int y, Uint8 type,unsigned int value = 0);
	~Ghost();

	int8_t move(Map& map, Sysinfo& sysinfo, unsigned int secondLoop = -1);
	Uint8 search(Map& map);
	void makeNextHeading(std::vector<std::vector<Tile>>& map, Pacman*& pacman);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, std::vector<Texture*>& misc);

	Uint8 GETtype()const;
	void SETtype(Uint8 type);

private:
	
	Uint8 _type;
};

#endif // !Entity_H

