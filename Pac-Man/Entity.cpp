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

#include "Entity.h"
#include "Pac_Man_lib.h"
#include "Texture.h"


///////////////////////////// ENTITY //////////////////////////////
/* ENTITY :: STATIC */
void Entity::move(sysinfo& information, Pacman& Player) {

	if (information.variable.statescreen == STATEplay && information.variable.select == selectnothing) {
		for (unsigned int i = 0; i < information.ghost.size(); i++)
			information.ghost[i]->move(information.map, Player);
		Player.move(information.map, information.ghost);

		information.variable.win = true;
		for (unsigned int i = 0; i < MAP_LENGTH; i++) {
			for (unsigned int j = 0; j < MAP_HEIGHT; j++) {
				if (information.map[i][j].entity) {
					information.variable.win = false;
					break;
				}
			}
		}
		if (Player.GETlife() == 0) {
			information.variable.select = lost;
			IHM::logfileconsole("End Game");
		}
		if(information.variable.win) {
			information.variable.select = win;
			IHM::logfileconsole("End Game");
		}
	}
}

/* ENTITY :: METHODES */
Entity::Entity(std::string name, unsigned int x, unsigned int y, Uint8 currentHeading, Uint8 nextHeading, unsigned int value)
	: _name(name), _x(x), _y(y), _value(value), _xc(x + tileSize / 2),
	_yc(y + tileSize / 2), _currentHeading(currentHeading), _nextHeading(nextHeading), _invincible(true), _timeInvincible(tempoInvincible)
{
}
Entity::~Entity()
{
}
int Entity::tryToMove(std::vector<std::vector<tile>>& map, unsigned int pos) {
	unsigned int nextTileX = 0, nextTileY = 0;

	switch (pos) {
	case UP:
		nextTileX = this->GETtilex();
		nextTileY = this->GETtiley() - 1;
		if (map[nextTileX][nextTileY].wall) {
			if (this->GETy() - vitesse >= (map[nextTileX][nextTileY].tile_y + tileSize))
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case LEFT:
		nextTileX = this->GETtilex() - 1;
		nextTileY = this->GETtiley();
		if (map[nextTileX][nextTileY].wall) {
			if (this->GETx() - vitesse >= (map[nextTileX][nextTileY].tile_x + tileSize))
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case DOWN:
		nextTileX = this->GETtilex();
		nextTileY = this->GETtiley() + 1;
		if (map[nextTileX][nextTileY].wall) {
			if (((this->GETy() + tileSize) + vitesse) <= map[nextTileX][nextTileY].tile_y)
				return 1;
			else
				return 0;
		}
		else
			return 1;
		break;
	case RIGHT:
		nextTileX = this->GETtilex() + 1;
		nextTileY = this->GETtiley();
		if (map[nextTileX][nextTileY].wall) {
			if (((this->GETx() + tileSize) + vitesse) <= map[nextTileX][nextTileY].tile_x)
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
bool Entity::isOnFullTile(std::vector<std::vector<tile>>& map, unsigned int i, unsigned int j) {
	if (this->GETx() == map[i][j].tile_x) {
		if (this->GETy() == map[i][j].tile_y) {
			return true;
		}
		return false;
	}
	return false;
}
bool Entity::isOnTile(std::vector<std::vector<tile>>& map, unsigned int i, unsigned int j) {
	if (this->GETxc() >= map[i][j].tile_x && this->GETxc() < (map[i][j].tile_x + tileSize)) {
		if (this->GETyc() >= map[i][j].tile_y && this->GETyc() < (map[i][j].tile_y + tileSize)) {
			return true;
		}
		return false;
	}
	return false;
}
void Entity::makeTheMove(bool validMove, unsigned int pos) {
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
}
void Entity::teleport(){
	if (this->GETx() <= 592 && this->GETy() == 544)
		this->SETx(1306);
	else if (this->GETx() >= 1328 && this->GETy() == 544)
		this->SETx(594);
}
std::string Entity::GETname()const {
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
unsigned int Entity::GETtilex()const {
	return _tilex;
}
unsigned int Entity::GETtiley()const {
	return _tiley;
}
Uint8 Entity::GETcurrentHeading()const {
	return _currentHeading;
}
Uint8 Entity::GETnextHeading()const {
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

void Entity::SETname(std::string name) {
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
void Entity::SETtilex(unsigned int tilex) {
	_tilex = tilex;
}
void Entity::SETtiley(unsigned int tiley) {
	_tiley = tiley;
}
void Entity::SETcurrentHeading(Uint8 currentHeading) {
	_currentHeading = currentHeading;
}
void Entity::SETnextHeading(Uint8 nextHeading) {
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



///////////////////////////// PACMAN //////////////////////////////
/*  PACMAN :: METHODES */
Pacman::Pacman(std::string name, unsigned int x, unsigned int y, unsigned int value)
	: Entity(name, x, y, UP, UP, value), _life(3), _powerUP(0), _typeOfValue(0)
{
	IHM::logfileconsole("Pacman is alive");
}
Pacman::Pacman(const Pacman& player)
	: Entity(player.GETname(), player.GETx(), player.GETy(), player.GETcurrentHeading(), player.GETnextHeading(), player.GETvalue()),
	_typeOfValue(player.GETtypeOfValue())
{
	IHM::logfileconsole("Pacman is alive");
}
Pacman::~Pacman()
{
	IHM::logfileconsole("Pacman is dead");
}
Pacman& Pacman::operator = (const Pacman& a) {
	if (this != &a) {
		this->SETname(this->GETname());
		this->SETx(this->GETx());
		this->SETy(this->GETy());
		this->SETxc(this->GETxc());
		this->SETyc(this->GETyc());
		this->SETtilex(this->GETtilex());
		this->SETtiley(this->GETtiley());
		this->SETcurrentHeading(this->GETcurrentHeading());
		this->SETnextHeading(this->GETnextHeading());
		this->SETalternateSkin(this->GETalternateSkin());
		this->SETtimeInvincible(this->GETtimeInvincible());
		this->SETinvincible(this->GETinvincible());
		this->SETvalue(this->GETvalue());
		_life = a.GETlife();
		_powerUP = a.GETpowerUP();
		_typeOfValue = a.GETtypeOfValue();
	}
	return *this;
}
int Pacman::move(std::vector<std::vector<tile>>& map, std::vector<Ghost*>& ghost, unsigned int secondLoop) {
	Uint8 validTryToMove = 0;
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

	makeTheMove(validMove, pos);
	if(validMove)
		collideGhost(ghost);
	teleport();
	return 0;
}
Uint8 Pacman::search(std::vector<std::vector<tile>>& map) {
	Uint8 condition = 0;
	for (unsigned int i = 0; i < MAP_LENGTH; i++) {
		for (unsigned int j = 0; j < MAP_HEIGHT; j++) {
			if (this->GETcurrentHeading() != this->GETnextHeading()) {
				if (isOnFullTile(map, i, j)) {
					this->SETtilex(i);
					this->SETtiley(j);
					condition = validNextHeading;
					return condition;
				}
			}
			if (isOnTile(map, i, j)) {
				this->SETtilex(i);
				this->SETtiley(j);
				condition = validCondition;
				return condition;
			}
		}
	}
	return condition;
}
void Pacman::value(std::vector<std::vector<tile>>& map, bool validMove) {
	if (validMove) {
		switch (map[this->GETtilex()][this->GETtiley()].entity) {
		case nothing:
			_typeOfValue = 0;
			break;
		case gold:
			map[this->GETtilex()][this->GETtiley()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuegold);
			_typeOfValue = valuegold;
			break;
		case cherry:
			map[this->GETtilex()][this->GETtiley()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuecherry);
			_typeOfValue = valuecherry;
			_powerUP++;
			break;
		case strawberry:
			map[this->GETtilex()][this->GETtiley()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuestrawberry);
			_typeOfValue = valuestrawberry;
			_powerUP++;
			break;
		case peach:
			map[this->GETtilex()][this->GETtiley()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuepeach);
			_typeOfValue = valuepeach;
			_powerUP++;
			break;
		case apple:
			map[this->GETtilex()][this->GETtiley()].entity = nothing;
			this->SETvalue(this->GETvalue() + valueapple);
			_typeOfValue = valueapple;
			_powerUP++;
			break;
		case key:
			map[this->GETtilex()][this->GETtiley()].entity = nothing;
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
			&& (this->GETy() == ghost[l]->GETy())) {
			hit = true;
			break;
		}
		// pacman bas et ghost haut
		else if (((this->GETy()) >= ghost[l]->GETy()) && ((this->GETy()) <= (ghost[l]->GETy() + tileSize)) 
			&& (this->GETx() == ghost[l]->GETx())){
			hit = true;
			break;
		}
		// pacman droite et ghost gauche
		else if (((this->GETx()) >= ghost[l]->GETx()) && ((this->GETx()) <= (ghost[l]->GETx() + tileSize))
			&& (this->GETy() == ghost[l]->GETy())) {
			hit = true;
			break;
		}
		// pacman haut et ghost bas
		else if (((this->GETy() + tileSize) >= ghost[l]->GETy()) && ((this->GETy() + tileSize) <= (ghost[l]->GETy() + tileSize)) 
			&& (this->GETx() == ghost[l]->GETx())) {
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
			IHM::logfileconsole("Pacman hit a Ghost successfully");
		}
		else {
			this->SETx(608);
			this->SETy(544);
			if(_life > 0)
				_life--;
			IHM::logfileconsole("Pacman lost a life");
		}
	}
}
void Pacman::afficherStats(sysinfo& information) {
	Texture::writetxt(information, blended, std::to_string(this->GETvalue()), { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 76, center_x);
	Texture::writetxt(information, shaded, "Remaining life  : " + std::to_string(_life), { 255, 0, 0, 255 }, White, 32, 0, 250);
	Texture::writetxt(information, blended, std::to_string(this->GETx()) + " , " + std::to_string(this->GETy()), { 0, 64, 255, 255 }, NoColor, 24, 0, 300);
	if (this->GETinvincible())
		Texture::writetxt(information, blended, "Remaining time Invincible : " + std::to_string(this->GETtimeInvincible() / 60), { 0, 64, 255, 255 }, NoColor, 24, 0, 350);
}
void Pacman::afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture) {
	std::string pacmanPos[MAXPOS] = { "U", "L", "D", "R" }, pacmanSkin[MAXSKIN] = { "1", "2" };
	unsigned int skin = 0;
	if (this->GETalternateSkin())
		skin = 1;
	for (unsigned int i = 0; i < tabTexture.size(); i++) {
		if (tabTexture[i]->renderTextureTestString(renderer, "pacman_" + pacmanPos[this->GETcurrentHeading()]
			+ "_" + pacmanSkin[skin] + ".png", this->GETx(), this->GETy()))
			return;
	}
}
Uint8 Pacman::GETlife()const {
	return _life;
}
Uint8 Pacman::GETpowerUP()const {
	return _powerUP;
}
unsigned int Pacman::GETtypeOfValue()const {
	return _typeOfValue;
}
void Pacman::SETlife(Uint8 life) {
	_life = life;
}
void Pacman::SETpowerUP(Uint8 powerUP) {
	_powerUP = powerUP;
}
void Pacman::SETtypeOfValue(unsigned int typeOfValue) {
	_typeOfValue = typeOfValue;
}


///////////////////////////// GHOST //////////////////////////////
/*  GHOST :: METHODES */
Ghost::Ghost(std::string name, unsigned int x, unsigned int y, Uint8 type, unsigned int value)
	: Entity(name, x, y, UP, RIGHT,value), _type(type)
{
	IHM::logfileconsole(this->GETname() + " is alive");
}
Ghost::~Ghost()
{
	IHM::logfileconsole(this->GETname() + " is dead");
}
int Ghost::move(std::vector<std::vector<tile>>& map, Pacman& pacman, unsigned int secondLoop) {
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
				move(map, pacman, 1);
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

	makeTheMove(validMove, pos);
	teleport();
	makeNextHeading(map, pacman);

	return 0;
}
Uint8 Ghost::search(std::vector<std::vector<tile>>& map) {
	Uint8 condition = 0;
	for (unsigned int i = 0; i < MAP_LENGTH; i++) {
		for (unsigned int j = 0; j < MAP_HEIGHT; j++) {
			if (this->GETcurrentHeading() != this->GETnextHeading()) {
				if (isOnFullTile(map, i, j)) {
					this->SETtilex(i);
					this->SETtiley(j);
					if (_type == red) {
						condition = validNextHeading;
						return condition;
					}
					else {
						if (((this->GETcurrentHeading() + this->GETnextHeading()) % 2) == 0)
							condition = validCondition; // évite de changer de revenir en arrière
						else
							condition = validNextHeading;
						return condition;
					}
				}
			}
			if (isOnTile(map, i, j)) {
				this->SETtilex(i);
				this->SETtiley(j);
				condition = validCondition;
				return condition;
			}
		}
	}
	return condition;
}
void Ghost::makeNextHeading(std::vector<std::vector<tile>>& map, Pacman& pacman) {
	int deltaX = 0, deltaY = 0;
	Uint8 posi = 0;
	Uint8 randomNextHeading = 0;
	bool continuer = true;
	switch (_type) {
	case red:
		deltaX = this->GETxc() - pacman.GETxc();
		deltaY = this->GETyc() - pacman.GETyc();
		if (abs(deltaX) > abs(deltaY)) {
			if (this->GETxc() > pacman.GETxc())
				this->SETnextHeading(LEFT);
			else
				this->SETnextHeading(RIGHT);
		}
		else {
			if (this->GETyc() > pacman.GETyc())
				this->SETnextHeading(UP);
			else
				this->SETnextHeading(DOWN);
		}
		break;
	case blue:
		posi = pacman.GETcurrentHeading() + 2;
		posi = posi % 4;
		this->SETnextHeading(posi);
		break;
	case yellow:
		randomNextHeading = rand() % 4;
		while (continuer) {
			if (tryToMove(map, randomNextHeading)) {
				continuer = false;
				break;
			}
			randomNextHeading = rand() % 4;
		}
		this->SETnextHeading(randomNextHeading);
		break;
	case pink:
		randomNextHeading = rand() % 4;
		while (continuer) {
			if (tryToMove(map, randomNextHeading)) {
				continuer = false;
				break;
			}
			randomNextHeading = rand() % 4;
		}
		this->SETnextHeading(randomNextHeading);
		break;
	}
}
void Ghost::afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture) {
	
}
void Ghost::afficher(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, std::vector<Texture*>& misc) {
	std::string ghostName[MAXGHOST] = { "Red", "Blue", "Yellow", "Pink" }, ghostPos[MAXPOS] = { "U", "L", "D", "R" }, ghostSkin[MAXSKIN] = {"1", "2"};
	Uint8 skin = 0;
	if (this->GETalternateSkin()) 
		skin = 1; // évite le probleme : bool (false == 0) et (true == tout le reste)

	if (this->GETinvincible()) {
		for (unsigned int i = 0; i < tabTexture.size(); i++) {
			if (tabTexture[i]->renderTextureTestString(renderer, ghostName[_type] + "_" + ghostPos[this->GETcurrentHeading()] +
				"_" + ghostSkin[skin] + ".png", this->GETx(), this->GETy()))
				return;
		}
	}
	else{
		for (unsigned int i = 0; i < misc.size(); i++) {
			misc[i]->renderTextureTestString(renderer, "not_Invincible.png", this->GETx(), this->GETy());
		}
	}
}
Uint8 Ghost::GETtype()const {
	return _type;
}
void Ghost::SETtype(Uint8 type) {
	_type = type;
}
