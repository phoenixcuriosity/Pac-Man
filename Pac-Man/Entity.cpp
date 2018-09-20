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

#include "Entity.h"
#include "Pac_Man_lib.h"

using namespace std;

Entity::Entity(std::string name, unsigned int x, unsigned int y, unsigned int currentHeading, unsigned int nextHeading, unsigned int value)
	: _name(name), _x(x), _y(y), _value(value), _xc(x + tileSize / 2),
	_yc(y + tileSize / 2),  _currentHeading(currentHeading), _nextHeading(nextHeading), _invincible(true), _timeInvincible(tempoInvincible)
{
}

Entity::~Entity()
{
}

int Entity::tryToMove(tile map[], unsigned int pos) {
	unsigned int nextTile = 0;

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
bool Entity::GETinvincible()const {
	return _invincible;
}
unsigned int Entity::GETtimeInvincible()const {
	return _timeInvincible;
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
void Entity::SETinvincible(bool invincible) {
	_invincible = invincible;
}
void Entity::SETtimeInvincible(unsigned int timeInvincible) {
	_timeInvincible = timeInvincible;
}
void Entity::SETvalue(unsigned int value) {
	_value = value;
}




Pacman::Pacman(string name, unsigned int x, unsigned int y, unsigned int value)
	: Entity(name, x, y, UP, UP, value), _life(3), _powerUP(0), _typeOfValue(0)
{
	logfileconsole("Pacman is alive");
}
Pacman::Pacman(const Pacman& player)
	: Entity(player.GETname(), player.GETx(), player.GETy(), player.GETcurrentHeading(), player.GETnextHeading(), player.GETvalue()),
	_typeOfValue(player.GETtypeOfValue())
{
	logfileconsole("Pacman is alive");
}
Pacman::~Pacman()
{
	logfileconsole("Pacman is dead");
}


int Pacman::move(tile map[], std::vector<Ghost*>& ghost, unsigned int secondLoop) {
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
				move(map, ghost, 1);
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

	if (this->GETinvincible()) {
		if (this->GETtimeInvincible() > 0)
			this->SETtimeInvincible(this->GETtimeInvincible() - 1);
		else {
			this->SETtimeInvincible(tempoInvincible);
			this->SETinvincible(false);
			for (unsigned int i = 0; i < ghost.size(); i++)
				ghost[i]->SETinvincible(true);
		}
	}
	value(map, validMove);
	if (_powerUP) {
		this->SETinvincible(true);
		for (unsigned int i = 0; i < ghost.size(); i++)
			ghost[i]->SETinvincible(false);
		_powerUP = 0;
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
		collideGhost(ghost);
	}
	if (this->GETx() <= 592 && this->GETy() == 544) 
		this->SETx(1306);
	else if (this->GETx() >= 1328 && this->GETy() == 544) 
		this->SETx(594);
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

void Pacman::value(tile map[], bool validMove) {
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
			_powerUP++;
			break;
		case strawberry:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuestrawberry);
			_typeOfValue = valuestrawberry;
			_powerUP++;
			break;
		case peach:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuepeach);
			_typeOfValue = valuepeach;
			_powerUP++;
			break;
		case apple:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valueapple);
			_typeOfValue = valueapple;
			_powerUP++;
			break;
		case key:
			map[this->GETtile()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuekey);
			_typeOfValue = valuekey;
			break;
		}
	}
}

void Pacman::collideGhost(std::vector<Ghost*>& ghost) {
	bool hit = false;
	unsigned int l = 0;
	for (l; l < ghost.size(); l++) {
		// pacman gauche et ghost droite
		if (((this->GETx() + tileSize) >= ghost[l]->GETx()) && ((this->GETx() + tileSize) <= (ghost[l]->GETx() + tileSize)) 
			&& (this->GETy() >= ghost[l]->GETy()) && (this->GETy() <= (ghost[l]->GETy() + tileSize))) {
			hit = true;
			break;
		}
		// pacman bas et ghost haut
		else if (((this->GETy()) >= ghost[l]->GETy()) && ((this->GETy()) <= (ghost[l]->GETy() + tileSize)) 
			&& (this->GETx() >= ghost[l]->GETx()) && (this->GETx() <= (ghost[l]->GETx() + tileSize))){
			hit = true;
			break;
		}
		// pacman droite et ghost gauche
		else if (((this->GETx()) >= ghost[l]->GETx()) && ((this->GETx()) <= (ghost[l]->GETx() + tileSize))
			&& (this->GETy() >= ghost[l]->GETy()) && (this->GETy() <= (ghost[l]->GETy() + tileSize))) {
			hit = true;
			break;
		}
		// pacman haut et ghost bas
		else if (((this->GETy() + tileSize) >= ghost[l]->GETy()) && ((this->GETy() + tileSize) <= (ghost[l]->GETy() + tileSize)) 
			&& (this->GETx() >= ghost[l]->GETx()) && (this->GETx() <= (ghost[l]->GETx() + tileSize))) {
			hit = true;
			break;
		}
	}
	if (hit) {
		if (this->GETinvincible()) {
			ghost[l]->SETx(SCREEN_WIDTH / 2);
			ghost[l]->SETy(SCREEN_HEIGHT / 2);
			ghost[l]->SETinvincible(true);
			this->SETvalue(this->GETvalue() + ghost1);
		}
		else {
			this->SETx(SCREEN_WIDTH / 2);
			this->SETy(SCREEN_HEIGHT / 2);
			if(_life > 0)
				_life--;
		}
	}
}

void Pacman::afficherStats(sysinfo& information) {
	Texture::writetxt(information, blended, to_string(this->GETvalue()), { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 76, center_x);
	Texture::writetxt(information, shaded, "Remaining life  : " + to_string(_life), { 255, 0, 0, 255 }, White, 32, 0, 250);
	Texture::writetxt(information, blended, to_string(this->GETx()) + " , " + to_string(this->GETy()), { 0, 64, 255, 255 }, NoColor, 24, 0, 300);
	if(this->GETinvincible())
		Texture::writetxt(information, blended, "Remaining time Invincible : " + to_string(this->GETtimeInvincible() / 60), { 0, 64, 255, 255 }, NoColor, 24, 0, 350);
}

void Pacman::afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture) {
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
unsigned int Pacman::GETpowerUP()const {
	return _powerUP;
}
unsigned int Pacman::GETtypeOfValue()const {
	return _typeOfValue;
}


void Pacman::SETlife(unsigned int life) {
	_life = life;
}
void Pacman::SETpowerUP(unsigned int powerUP) {
	_powerUP = powerUP;
}
void Pacman::SETtypeOfValue(unsigned int typeOfValue) {
	_typeOfValue = typeOfValue;
}





Ghost::Ghost(string name, unsigned int x, unsigned int y, unsigned int type, unsigned int value)
	: Entity(name, x, y, UP, RIGHT,value), _type(type)
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


	if (this->GETx() <= 592 && this->GETy() == 544)
		this->SETx(1306);
	else if (this->GETx() >= 1328 && this->GETy() == 544)
		this->SETx(594);



	unsigned int randomNextHeading = 0;
	randomNextHeading = rand() % 4;
	bool continuer = true;
	while (continuer) {
		if (tryToMove(map, randomNextHeading)) {
			continuer = false;
			break;
		}
		randomNextHeading = rand() % 4;
	}
	this->SETnextHeading(randomNextHeading);

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
						if(((this->GETcurrentHeading() + this->GETnextHeading()) % 2) == 0)
							condition = validCondition; // évite de changer de revenir en arrière
						else
							condition = validNextHeading;
						return condition;
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

void Ghost::afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture) {

}

void Ghost::afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, std::vector<Texture*>& misc) {
	std::string ghost = "";
	std::vector<std::string> ghostName;
	ghostName.push_back("Red"); ghostName.push_back("Blue"); ghostName.push_back("Yellow"); ghostName.push_back("Pink");

	if (this->GETinvincible()) {
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
	else{
		for (unsigned int i = 0; i < misc.size(); i++) {
			misc[i]->renderTextureTestString(renderer, "not_Invincible.png", this->GETx(), this->GETy());
		}
	}
}

unsigned int Ghost::GETtype()const {
	return _type;
}



void Ghost::SETtype(unsigned int type) {
	_type = type;
}


