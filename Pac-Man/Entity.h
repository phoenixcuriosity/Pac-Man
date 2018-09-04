/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.1

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
	Entity();
	Entity(std::string name, unsigned int x, unsigned int y);
	~Entity();

	std::string GETname()const;
	unsigned int GETx()const;
	unsigned int GETy()const;

	void SETname(std::string name);
	void SETx(unsigned int x);
	void SETy(unsigned int y);

	virtual const void printOn(bool on = true)const = 0;


private:
	std::string _name;
	unsigned int _x;
	unsigned int _y;
};

class Pacman : public Entity {
public:
	Pacman(std::string name, unsigned int x, unsigned int y);
	~Pacman();

	int move();

	unsigned int GETcurrentHeading()const;
	unsigned int GETnextHeading()const;
	bool GETalternateSkin()const;

	void SETcurrentHeading(unsigned int);
	void SETnextHeading(unsigned int);
	void SETalternateSkin(bool);

	virtual const void printOn(bool on = true)const;

private:
	unsigned int _currentHeading;
	unsigned int _nextHeading;
	bool _alternateSkin;
};

class Ghost : public Entity {

};
class Gold : public Entity {

};

#endif // !Entity_H

