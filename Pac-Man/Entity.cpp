/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.4

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

Entity::Entity(std::string name, unsigned int x, unsigned int y, unsigned int value)
	: _name(name), _x(x), _y(y), _value(value)
{
}

Entity::~Entity()
{
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
unsigned int Entity::GETvalue()const {
	return _value;
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
void Entity::SETvalue(unsigned int value) {
	_value = value;
}




Pacman::Pacman(string name, unsigned int x, unsigned int y, unsigned int value) : Entity(name, x, y, value), _currentHeading(RIGHT), _nextHeading(UP), _alternateSkin(false)
{
	logfileconsole("Pacman is alive");
}
Pacman::~Pacman()
{
	logfileconsole("Pacman is dead");
}


int Pacman::move(tile map[], unsigned int pos) {


	switch (pos) {
	case UP:
		if (tryToMove(map, UP) == validCondition) {
			this->SETy(this->GETy() - vitesse);
			_currentHeading = UP;
		}
		break;
	case LEFT:
		if (tryToMove(map, LEFT) == validCondition) {
			this->SETx(this->GETx() - vitesse);
			_currentHeading = LEFT;
		}
		break;
	case DOWN:
		if (tryToMove(map, DOWN) == validCondition) {
			this->SETy(this->GETy() + vitesse);
			_currentHeading = DOWN;
		}
		break;
	case RIGHT:
		if (tryToMove(map, RIGHT) == validCondition) {
			this->SETx(this->GETx() + vitesse);
			_currentHeading = RIGHT;
		}
		break;
	}
	return 0;
}
int Pacman::tryToMove(tile map[], unsigned int pos) {
	unsigned int moyX = 0, moyY = 0, k = 0, pacmanTile = 0, nextTile = 0;
	for (unsigned int m = 0; m < SCREEN_WIDTH; m += tileSize) {
		if (m >= this->GETx()) {
			moyX = m;
			break;
		}
	}
	for (unsigned int m = 0; m < SCREEN_HEIGHT; m += tileSize) {
		if (m >= this->GETy()) {
			moyY = m;
			break;
		}
	}
	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			if (map[k].tile_x == moyX && map[k].tile_y == moyY) {
				pacmanTile = k;
				break;
			}
			k++;
		}
	}

	switch (pos){
	case UP:
		nextTile = pacmanTile - 1;
		if (map[nextTile].wall) {
			if (this->GETy() - vitesse > map[nextTile].tile_y + tileSize)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case LEFT:
		nextTile = pacmanTile - mapHeight;
		if (map[nextTile].wall) {
			if (this->GETx() - vitesse > map[nextTile].tile_x + tileSize)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case DOWN:
		nextTile = pacmanTile + 1;
		if (map[nextTile].wall) {
			if (this->GETy() + vitesse < map[nextTile].tile_y - tileSize)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case RIGHT:
		nextTile = pacmanTile + mapHeight;
		if (map[nextTile].wall) {
			if (this->GETx() + vitesse < map[nextTile].tile_x - tileSize)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	}
	
}

void Pacman::afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture) {
	for (unsigned int i = 0; i < tabTexture.size(); i++) {
		switch (_currentHeading) {
		case UP:
			if (_alternateSkin)
				tabTexture[i]->renderTextureTestString(renderer, "pacman_U_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, "pacman_U_2.png", this->GETx(), this->GETy());
			break;
		case LEFT:
			if (_alternateSkin)
				tabTexture[i]->renderTextureTestString(renderer, "pacman_L_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, "pacman_L_2.png", this->GETx(), this->GETy());
			break;
		case DOWN:
			if (_alternateSkin)
				tabTexture[i]->renderTextureTestString(renderer, "pacman_D_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, "pacman_D_2.png", this->GETx(), this->GETy());
			break;
		case RIGHT:
			if (_alternateSkin)
				tabTexture[i]->renderTextureTestString(renderer, "pacman_R_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, "pacman_R_2.png", this->GETx(), this->GETy());
			break;
		}
	}
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





Ghost::Ghost(string name, unsigned int x, unsigned int y, unsigned int type, unsigned int value)
	: Entity(name, x, y, value), _currentHeading(UP), _nextHeading(UP), _alternateSkin(false), _type(type)
{
	logfileconsole(this->GETname() + " is alive");
}
Ghost::~Ghost()
{
	logfileconsole(this->GETname() + " is dead");
}

int Ghost::move(unsigned int pos) {
	return 0;
}
void Ghost::afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture) {
	std::string ghost = "";
	std::vector<std::string> ghostName;
	ghostName.push_back("Red"); ghostName.push_back("Blue"); ghostName.push_back("Yellow"); ghostName.push_back("Pink");

	for (unsigned int i = 0; i < tabTexture.size(); i++) {
		switch (_currentHeading) {
		case UP:
			if (_alternateSkin)
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_U_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_U_2.png", this->GETx(), this->GETy());
			break;
		case LEFT:
			if (_alternateSkin)
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_L_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_L_2.png", this->GETx(), this->GETy());
			break;
		case DOWN:
			if (_alternateSkin)
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_D_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_D_2.png", this->GETx(), this->GETy());
			break;
		case RIGHT:
			if (_alternateSkin)
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_R_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_R_2.png", this->GETx(), this->GETy());
			break;
		}
	}
}

unsigned int Ghost::GETcurrentHeading()const {
	return _currentHeading;
}
unsigned int Ghost::GETnextHeading()const {
	return _nextHeading;
}
bool Ghost::GETalternateSkin()const {
	return _alternateSkin;
}


void Ghost::SETcurrentHeading(unsigned int currentHeading) {
	_currentHeading = currentHeading;
}
void Ghost::SETnextHeading(unsigned int nextHeading) {
	_nextHeading = nextHeading;
}
void Ghost::SETalternateSkin(bool alternateSkin) {
	_alternateSkin = alternateSkin;
}

