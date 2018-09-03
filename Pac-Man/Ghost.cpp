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

#include "Ghost.h"
#include "sdl.h"

using namespace std;

Ghost::Ghost(string name, unsigned int x, unsigned int y): _name(name), _x(x), _y(y)
{
	logfileconsole("A ghost have been created Successfully");
}

Ghost::~Ghost()
{
	logfileconsole("A ghost have been deleted Successfully");
}

string Ghost::GETname()const {
	return _name;
}
unsigned int Ghost::GETx()const {
	return _x;
}
unsigned int Ghost::GETy()const {
	return _y;
}

void Ghost::SETname(string name) {
	_name = name;
}
void Ghost::SETx(unsigned int x) {
	_x = x;
}
void Ghost::SETy(unsigned int y) {
	_x = y;
}
