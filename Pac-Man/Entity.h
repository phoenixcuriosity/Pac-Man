/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.5

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
#include "Texture.h"



class Entity { // classe abstraite
public:
	Entity() {};
	Entity(std::string name, unsigned int x, unsigned int y, unsigned int value = 0);
	~Entity();

	std::string GETname()const;
	unsigned int GETx()const;
	unsigned int GETy()const;
	unsigned int GETvalue()const;

	void SETname(std::string name);
	void SETx(unsigned int x);
	void SETy(unsigned int y);
	void SETvalue(unsigned int value);

	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture) = 0;


private:
	std::string _name;
	unsigned int _x;
	unsigned int _y;
	unsigned int _value;
};

class Pacman : public Entity {
public:
	Pacman(std::string name, unsigned int x, unsigned int y, unsigned int value = 0);
	~Pacman();

	int move(tile map[], unsigned int secondLoop = -1);
	int tryToMove(tile map[], unsigned int pos);
	int tryToMoveSecondLoop(tile map[], unsigned int pos);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture);

	unsigned int GETcurrentHeading()const;
	unsigned int GETnextHeading()const;
	bool GETalternateSkin()const;

	void SETcurrentHeading(unsigned int);
	void SETnextHeading(unsigned int);
	void SETalternateSkin(bool);

private:
	unsigned int _currentHeading;
	unsigned int _nextHeading;
	bool _alternateSkin;
};

class Ghost : public Entity {
public:
	Ghost(std::string name, unsigned int x, unsigned int y, unsigned int type,unsigned int value = 0);
	~Ghost();

	int move(unsigned int pos);
	virtual void afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture);

	unsigned int GETcurrentHeading()const;
	unsigned int GETnextHeading()const;
	bool GETalternateSkin()const;

	void SETcurrentHeading(unsigned int);
	void SETnextHeading(unsigned int);
	void SETalternateSkin(bool);

private:
	unsigned int _currentHeading;
	unsigned int _nextHeading;
	bool _alternateSkin;
	unsigned int _type;
};
class Gold : public Entity {
public:
	Gold();
	~Gold();

private:
	unsigned int _type;
};

#endif // !Entity_H

