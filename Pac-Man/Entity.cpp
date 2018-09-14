/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.7

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

Entity::Entity(std::string name, unsigned int x, unsigned int y, unsigned int currentHeading, unsigned int nextHeading, unsigned int value)
	: _name(name), _x(x), _y(y), _value(value), _xc(x + tileSize / 2),
	_yc(y + tileSize / 2),  _currentHeading(currentHeading), _nextHeading(nextHeading)
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
unsigned int Entity::GETxc()const {
	return _x + tileSize / 2;
}
unsigned int Entity::GETyc()const {
	return _y + tileSize / 2;
}
unsigned int Entity::GETtile()const {
	return _tile;
}
unsigned int Entity::GETcurrentHeading()const {
	return _currentHeading;
}
unsigned int Entity::GETnextHeading()const {
	return _nextHeading;
}
bool Entity::GETalternateSkin()const {
	return _alternateSkin;
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
void Entity::SETxc(unsigned int xc) {
	_xc = xc;
}
void Entity::SETyc(unsigned int yc) {
	_yc = yc;
}
void Entity::SETtile(unsigned int tile) {
	_tile = tile;
}
void Entity::SETcurrentHeading(unsigned int currentHeading) {
	_currentHeading = currentHeading;
}
void Entity::SETnextHeading(unsigned int nextHeading) {
	_nextHeading = nextHeading;
}
void Entity::SETalternateSkin(bool alternateSkin) {
	_alternateSkin = alternateSkin;
}
void Entity::SETvalue(unsigned int value) {
	_value = value;
}




Pacman::Pacman(string name, unsigned int x, unsigned int y, unsigned int value)
	: Entity(name, x, y, UP, UP, value), _life(3), _typeOfValue(0)
{
	logfileconsole("Pacman is alive");
}
Pacman::Pacman(Pacman& player)
	: Entity(player.GETname(), player.GETx(), player.GETy(), player.GETcurrentHeading(), player.GETnextHeading(), player.GETvalue()),
	_typeOfValue(player.GETtypeOfValue())
{
	logfileconsole("Pacman is alive");
}
Pacman::~Pacman()
{
	logfileconsole("Pacman is dead");
}


int Pacman::move(tile map[], unsigned int secondLoop) {
	unsigned int validTryToMove = 0;
	unsigned int pos = 0;
	bool validMove = false;
	
	if (secondLoop == -1) {
		switch (validTryToMove = search(map)) {
		case Not_Valid:
			break;
		case validCondition:
			if (tryToMove(map, this->GETcurrentHeading())) {
				validMove = validCondition;
				pos = this->GETcurrentHeading();
			}
			break;
		case validNextHeading:
			if (tryToMove(map, this->GETnextHeading())) {
				validMove = validCondition;
				pos = this->GETnextHeading();
				this->SETcurrentHeading(this->GETnextHeading());
			}
			else
				move(map, 1);
			break;
		}
	}
	else {
		if (validTryToMove = search(map)) {
			if (tryToMove(map, this->GETcurrentHeading())) {
				validMove = validCondition;
				pos = this->GETcurrentHeading();
			}
		}
	}

	if (validMove) {
		switch (map[this->GETtile()].entity) {
		case nothing:
			_typeOfValue = 0;
			break;
		case gold:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuegold);
			_typeOfValue = valuegold;
			break;
		case cherry:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuecherry);
			_typeOfValue = valuecherry;
			break;
		case strawberry:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuestrawberry);
			_typeOfValue = valuestrawberry;
			break;
		case peach:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuepeach);
			_typeOfValue = valuepeach;
			break;
		case key:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuekey);
			_typeOfValue = valuekey;
			break;
		}
	}
	
	if (validMove) {
		switch (pos) {
		case UP:
			this->SETy(this->GETy() - vitesse);
			break;
		case LEFT:
			this->SETx(this->GETx() - vitesse);
			break;
		case DOWN:
			this->SETy(this->GETy() + vitesse);
			break;
		case RIGHT:
			this->SETx(this->GETx() + vitesse);
			break;
		}
	}
	
	return 0;
}

unsigned int Pacman::search(tile map[]) {
	unsigned int k = 0, condition = 0;
	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			if (this->GETcurrentHeading() != this->GETnextHeading()) {
				if (this->GETx() == map[k].tile_x) {
					if (this->GETy() == map[k].tile_y) {
						this->SETtile(k);
						condition = validNextHeading;
						return condition;
						break;
					}
				}
			}
			if (this->GETxc() >= map[k].tile_x && this->GETxc() < (map[k].tile_x + tileSize)) {
				if (this->GETyc() >= map[k].tile_y && this->GETyc() < (map[k].tile_y + tileSize)) {
					this->SETtile(k);
					condition = validCondition;
					return condition;
				}
			}
			k++;
		}
	}
	return condition;
}

int Pacman::tryToMove(tile map[], unsigned int pos) {
	unsigned int k = 0, nextTile = 0;
	
	switch (pos) {
	case UP:
		nextTile = this->GETtile() - 1;
		if (map[nextTile].wall) {
			if (this->GETy() - vitesse >= (map[nextTile].tile_y + tileSize))
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case LEFT:
		nextTile = this->GETtile() - mapHeight;
		if (map[nextTile].wall) {
			if (this->GETx() - vitesse >= (map[nextTile].tile_x + tileSize))
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case DOWN:
		nextTile = this->GETtile() + 1;
		if (map[nextTile].wall) {
			if (((this->GETy() + tileSize) + vitesse) <= map[nextTile].tile_y)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case RIGHT:
		nextTile = this->GETtile() + mapHeight;
		if (map[nextTile].wall) {
			if (((this->GETx() + tileSize) + vitesse) <= map[nextTile].tile_x)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	}

	return Not_Valid;
}

void Pacman::afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture) {
	for (unsigned int i = 0; i < tabTexture.size(); i++) {
		switch (this->GETcurrentHeading()) {
		case UP:
			if (this->GETalternateSkin())
				tabTexture[i]->renderTextureTestString(renderer, "pacman_U_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, "pacman_U_2.png", this->GETx(), this->GETy());
			break;
		case LEFT:
			if (this->GETalternateSkin())
				tabTexture[i]->renderTextureTestString(renderer, "pacman_L_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, "pacman_L_2.png", this->GETx(), this->GETy());
			break;
		case DOWN:
			if (this->GETalternateSkin())
				tabTexture[i]->renderTextureTestString(renderer, "pacman_D_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, "pacman_D_2.png", this->GETx(), this->GETy());
			break;
		case RIGHT:
			if (this->GETalternateSkin())
				tabTexture[i]->renderTextureTestString(renderer, "pacman_R_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, "pacman_R_2.png", this->GETx(), this->GETy());
			break;
		}
	}
}

unsigned int Pacman::GETlife()const {
	return _life;
}
unsigned int Pacman::GETtypeOfValue()const {
	return _typeOfValue;
}


void Pacman::SETlife(unsigned int life) {
	_life = life;
}
void Pacman::SETtypeOfValue(unsigned int typeOfValue) {
	_typeOfValue = typeOfValue;
}





Ghost::Ghost(string name, unsigned int x, unsigned int y, unsigned int type, unsigned int value)
	: Entity(name, x, y, UP, UP,value), _type(type)
{
	logfileconsole(this->GETname() + " is alive");
}
Ghost::~Ghost()
{
	logfileconsole(this->GETname() + " is dead");
}

int Ghost::move(tile map[], unsigned int secondLoop) {
	unsigned int validTryToMove = 0;
	unsigned int pos = 0;
	bool validMove = false;

	if (secondLoop == -1) {
		switch (validTryToMove = search(map)) {
		case Not_Valid:
			break;
		case validCondition:
			if (tryToMove(map, this->GETcurrentHeading())) {
				validMove = validCondition;
				pos = this->GETcurrentHeading();
			}
			break;
		case validNextHeading:
			if (tryToMove(map, this->GETnextHeading())) {
				validMove = validCondition;
				pos = this->GETnextHeading();
				this->SETcurrentHeading(this->GETnextHeading());
			}
			else
				move(map, 1);
			break;
		}
	}
	else {
		if (validTryToMove = search(map)) {
			if (tryToMove(map, this->GETcurrentHeading())) {
				validMove = validCondition;
				pos = this->GETcurrentHeading();
			}
		}
	}

	
	if (validMove) {
		switch (pos) {
		case UP:
			this->SETy(this->GETy() - vitesse);
			break;
		case LEFT:
			this->SETx(this->GETx() - vitesse);
			break;
		case DOWN:
			this->SETy(this->GETy() + vitesse);
			break;
		case RIGHT:
			this->SETx(this->GETx() + vitesse);
			break;
		}
	}

	return 0;
}

unsigned int Ghost::search(tile map[]) {
	unsigned int k = 0, condition = 0;
	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			if (this->GETcurrentHeading() != this->GETnextHeading()) {
				if (this->GETx() == map[k].tile_x) {
					if (this->GETy() == map[k].tile_y) {
						this->SETtile(k);
						condition = validNextHeading;
						return condition;
						break;
					}
				}
			}
			if (this->GETxc() >= map[k].tile_x && this->GETxc() < (map[k].tile_x + tileSize)) {
				if (this->GETyc() >= map[k].tile_y && this->GETyc() < (map[k].tile_y + tileSize)) {
					this->SETtile(k);
					condition = validCondition;
					return condition;
				}
			}
			k++;
		}
	}
	return condition;
}

int Ghost::tryToMove(tile map[], unsigned int pos) {
	unsigned int k = 0, nextTile = 0;

	switch (pos) {
	case UP:
		nextTile = this->GETtile() - 1;
		if (map[nextTile].wall) {
			if (this->GETy() - vitesse >= (map[nextTile].tile_y + tileSize))
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case LEFT:
		nextTile = this->GETtile() - mapHeight;
		if (map[nextTile].wall) {
			if (this->GETx() - vitesse >= (map[nextTile].tile_x + tileSize))
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case DOWN:
		nextTile = this->GETtile() + 1;
		if (map[nextTile].wall) {
			if (((this->GETy() + tileSize) + vitesse) <= map[nextTile].tile_y)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case RIGHT:
		nextTile = this->GETtile() + mapHeight;
		if (map[nextTile].wall) {
			if (((this->GETx() + tileSize) + vitesse) <= map[nextTile].tile_x)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	}

	return Not_Valid;
}
void Ghost::afficher(SDL_Renderer*& renderer, std::vector<Texture*> tabTexture) {
	std::string ghost = "";
	std::vector<std::string> ghostName;
	ghostName.push_back("Red"); ghostName.push_back("Blue"); ghostName.push_back("Yellow"); ghostName.push_back("Pink");

	for (unsigned int i = 0; i < tabTexture.size(); i++) {
		switch (this->GETcurrentHeading()) {
		case UP:
			if (this->GETalternateSkin())
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_U_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_U_2.png", this->GETx(), this->GETy());
			break;
		case LEFT:
			if (this->GETalternateSkin())
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_L_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_L_2.png", this->GETx(), this->GETy());
			break;
		case DOWN:
			if (this->GETalternateSkin())
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_D_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_D_2.png", this->GETx(), this->GETy());
			break;
		case RIGHT:
			if (this->GETalternateSkin())
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_R_1.png", this->GETx(), this->GETy());
			else
				tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_R_2.png", this->GETx(), this->GETy());
			break;
		}
	}
}

unsigned int Ghost::GETtype()const {
	return _type;
}



void Ghost::SETtype(unsigned int type) {
	_type = type;
}


