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

class Entity { // classe abstraite
public:
	static void move(sysinfo& information, Pacman& Player);
	

	Entity() {};
	Entity(std::string name, unsigned int x, unsigned int y, Uint8 currentHeading, Uint8 nextHeading, unsigned int value = 0);
	~Entity();

	int tryToMove(std::vector<std::vector<tile>>& map, unsigned int pos);
	bool isOnFullTile(std::vector<std::vector<tile>>& map, unsigned int i, unsigned int j);
	bool isOnTile(std::vector<std::vector<tile>>& map, unsigned int i, unsigned int j);
	void makeTheMove(bool, unsigned int);
	void teleport();
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture) = 0;

	std::string GETname()const;
	unsigned int GETx()const;
	unsigned int GETy()const;
	unsigned int GETxc()const;
	unsigned int GETyc()const;
	unsigned int GETtilex()const;
	unsigned int GETtiley()const;
	Uint8 GETcurrentHeading()const;
	Uint8 GETnextHeading()const;
	bool GETalternateSkin()const;
	bool GETinvincible()const;
	unsigned int GETtimeInvincible()const;
	unsigned int GETvalue()const;

	void SETname(std::string name);
	void SETx(unsigned int x);
	void SETy(unsigned int y);
	void SETxc(unsigned int);
	void SETyc(unsigned int);
	void SETtilex(unsigned int tilex);
	void SETtiley(unsigned int tiley);
	void SETcurrentHeading(Uint8);
	void SETnextHeading(Uint8);
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
	unsigned int _tilex;
	unsigned int _tiley;

	Uint8 _currentHeading;
	Uint8 _nextHeading;
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

	Pacman& operator = (const Pacman&);

	int move(std::vector<std::vector<tile>>& map, std::vector<Ghost*>& ghost, unsigned int secondLoop = -1);
	Uint8 search(std::vector<std::vector<tile>>& map);
	void value(std::vector<std::vector<tile>>& map, bool validMove);
	void collideGhost(std::vector<Ghost*>& ghost);

	void afficherStats(sysinfo& information);
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

	int move(std::vector<std::vector<tile>>& map, Pacman& pacman, unsigned int secondLoop = -1);
	Uint8 search(std::vector<std::vector<tile>>& map);
	void makeNextHeading(std::vector<std::vector<tile>>& map, Pacman& pacman);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, std::vector<Texture*>& misc);

	Uint8 GETtype()const;
	void SETtype(Uint8 type);

private:
	
	Uint8 _type;
};

#endif // !Entity_H

