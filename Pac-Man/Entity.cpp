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

#include "Entity.h"
#include "sdl.h"

using namespace std;

Entity::Entity(std::string name, unsigned int x, unsigned int y)
	: _name(name), _x(x), _y(y)
{
	logfileconsole("A Entity have been created Successfully");
}

Entity::~Entity()
{
	logfileconsole("A Entity have been deleted Successfully");
}

string Entity::GETname()const {
	return _name;
}
unsigned int Entity::GETx()const {
	return _x;
}
unsigned int Entity::GETy()const {
	return _y;
}

void Entity::SETname(string name) {
	_name = name;
}
void Entity::SETx(unsigned int x) {
	_x = x;
}
void Entity::SETy(unsigned int y) {
	_y = y;
}




Pacman::Pacman(string name, unsigned int x, unsigned int y) : Entity(name, x, y), _currentHeading(UP), _nextHeading(UP), _alternateSkin(false)
{
	logfileconsole("Pacman is alive");
}
Pacman::~Pacman()
{
	logfileconsole("Pacman is dead");
}

unsigned int Pacman::GETcurrentHeading()const {
	return _currentHeading;
}
unsigned int Pacman::GETnextHeading()const {
	return _nextHeading;
}
bool Pacman::GETalternateSkin()const {
	return _alternateSkin;
}



void Pacman::SETcurrentHeading(unsigned int currentHeading) {
	_currentHeading = currentHeading;
}
void Pacman::SETnextHeading(unsigned int nextHeading){
	_nextHeading = nextHeading;
}
void Pacman::SETalternateSkin(bool alternateSkin) {
	_alternateSkin = alternateSkin;
}

const void Pacman::printOn(bool on)const {

}
