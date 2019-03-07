/*

   Pac-Man
   Copyright SAUTER Robin (robin.sauter@orange.fr)
   last modification on this file on version : 0.17
   file version : 1.0

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


///////////////////////////// ENTITY //////////////////////////////
	/* *********************************************************
						ENTITY::STATIC
	 ********************************************************* */
void Entity::move(Sysinfo& sysinfo)
{

	// mouvement de tous objets Entity
	if (sysinfo.var.stateScreen == STATEplay && sysinfo.var.select == selectnothing)
	{
		for (unsigned int i = 0; i < sysinfo.ghost.size(); i++)
			sysinfo.ghost[i]->move(sysinfo.map, sysinfo);
		sysinfo.pacman->move(sysinfo.map, sysinfo.ghost);

		// recherche si Pacman a mangé toutes les pastilles
		sysinfo.var.win = true;
		for (Uint8 i = 0; i < sysinfo.map.map_length && sysinfo.var.win; i++)
		{
			for (Uint8 j = 0; j < sysinfo.map.map_height && sysinfo.var.win; j++)
			{
				if (sysinfo.map.matriceMap[i][j].entity)
				{
					sysinfo.var.win = false;
					break;
				}
			}
		}
		if (sysinfo.pacman->GETlife() == 0)
		{
			sysinfo.var.select = lost;
			IHM::logfileconsole("End Game");
			Mix_PlayMusic(sysinfo.music[music_died], 1);
		}
		if(sysinfo.var.win)
		{
			sysinfo.var.select = win;
			IHM::logfileconsole("End Game");
		}
	}
}
void Entity::initEntity(Pacman*& pacman, std::vector<Ghost*>& ghost, std::vector<std::vector<Tile>>& map)
{
	destroyEntity(pacman, ghost);

	// initialisation des positions de Pacman au milieu de gauche de la grille
	Uint8 initialPosIndexX = 3, initialPosIndexY = map[initialPosIndexX][map[initialPosIndexX].size() / 2].indexY;
	pacman = new Pacman("player", map[initialPosIndexX][initialPosIndexY].tile_x, map[initialPosIndexX][initialPosIndexY].tile_y);
	pacman->SETindexX(initialPosIndexX);
	pacman->SETindexY(initialPosIndexY);

	// initialisation des positions des Ghost au milieu
	unsigned int x = map[map.size() / 2][map[0].size() / 2].tile_x, y = map[map.size() / 2][map[0].size() / 2].tile_y;
	ghost.push_back(new Ghost("Red", x, y, red));
	ghost.push_back(new Ghost("Blue", x, y, blue));
	ghost.push_back(new Ghost("Yellow", x, y, yellow));
	ghost.push_back(new Ghost("Pink", x, y, pink));
}
void Entity::destroyEntity(Pacman*& pacman, std::vector<Ghost*>& ghost)
{
	if (pacman != nullptr)
	{
		delete pacman;
		pacman = nullptr;
	}
	for (unsigned int g = 0; g < ghost.size(); g++)
	{
		if (ghost[g] != nullptr)
		{
			delete ghost[g];
			ghost[g] = nullptr;
		}
	}
	ghost.clear();
}

/* *********************************************************
					ENTITY::METHODES
 ********************************************************* */

//--- constructeurs et destructeur ---------------------------------------------------------------------------------------------------------------

Entity::Entity(std::string name, unsigned int x, unsigned int y, Uint8 currentHeading, Uint8 nextHeading, unsigned int value)
	: _name(name), _x(x), _y(y), _value(value), _currentHeading(currentHeading),
	_indexX(0), _indexY(0), _nextHeading(nextHeading), _invincible(true), _alternateSkin(false),
	_timeInvincible(TEMPO_INVINCIBLE), _velocity(INITIAL_VELOCITY)
{
}
Entity::~Entity()
{
}

//--- Algorithme ---------------------------------------------------------------------------------------------------------------------------------

bool Entity::notPreviousTile(std::vector<Node>& path, Uint8 newIndexX, Uint8 newIndexY)
{
	for (unsigned int i = 0; i < path.size(); i++)
	{
		if (path[i].indexX == newIndexX && path[i].indexY == newIndexY)
			return false;
	}
	return true;
}
void Entity::findAPath(std::vector<std::vector<Tile>>& map, Uint8 indexX, Uint8 indexY)
{
	if (_indexX != indexX || _indexY != indexY)
	{

		// tableau d'un chemin constitué de Node
		std::vector<Node> blankTab, newPath;

		// Node 1 : position initiale de l'objet
		Node blankTile;
		blankTile.indexX = _indexX; blankTile.indexY = _indexY;
		blankTab.push_back(blankTile);
		_tabPath.push_back(blankTab);

		unsigned int indexTabFound = 0;
		int8_t tabX[MAX_POS] = { -1 , 1, 0 , 0 }, tabY[MAX_POS] = { 0, 0, -1, 1 };
		bool breakLoop = false;

		/* 
		*	Recherche sur un Node si les 4 directions sont disponibles (pas de mur)
		*		-> Si la direction testée est libre alors un nouveau chemin est créé à partir de l'ancien chemin
		*	Chaque chemin a au moins le Node initial en commun
		*	L'algorithme s'arrete une fois que le premier chemin trouve la cible (forcement le chemin le plus court)
		*/
		for (unsigned int i = 0; i < _tabPath.size(); i++)
		{
			if (!breakLoop) 
			{
				for (unsigned int m = 0; m < MAX_POS; m++)
				{

					if ((unsigned int)(_tabPath[i][_tabPath[i].size() - 1].indexX + tabX[m]) >= 0 && (unsigned int)(_tabPath[i][_tabPath[i].size() - 1].indexX + tabX[m]) < map.size()
						&& (unsigned int)(_tabPath[i][_tabPath[i].size() - 1].indexY + tabY[m]) >= 0 && (unsigned int)(_tabPath[i][_tabPath[i].size() - 1].indexY + tabY[m]) < map.size())
					{

						if (!map[_tabPath[i][_tabPath[i].size() - 1].indexX + tabX[m]][_tabPath[i][_tabPath[i].size() - 1].indexY + tabY[m]].wall
							&& notPreviousTile(_tabPath[i], _tabPath[i][_tabPath[i].size() - 1].indexX + tabX[m], _tabPath[i][_tabPath[i].size() - 1].indexY + tabY[m])) 
						{

							blankTile.indexX = _tabPath[i][_tabPath[i].size() - 1].indexX + tabX[m];
							blankTile.indexY = _tabPath[i][_tabPath[i].size() - 1].indexY + tabY[m];

							newPath = _tabPath[i];
							newPath.push_back(blankTile);
							_tabPath.push_back(newPath);

							if (_tabPath[i][_tabPath[i].size() - 1].indexX + tabX[m] == indexX
								&& _tabPath[i][_tabPath[i].size() - 1].indexY + tabY[m] == indexY)
							{
								indexTabFound = i;
								breakLoop = true;
								break;
							}

						}
					}
				}
			}
			else
				break;
		}

		// affectation du nextHeading en fonction du chemin le plus court
		if (_tabPath[indexTabFound].size() > 1)
		{
			if (_tabPath[0][0].indexX != _tabPath[indexTabFound][1].indexX)
			{
				if (_tabPath[indexTabFound][1].indexX < _tabPath[0][0].indexX)
					_nextHeading = LEFT;
				else
					_nextHeading = RIGHT;
			}
			else 
			{
				if (_tabPath[indexTabFound][1].indexY < _tabPath[0][0].indexY)
					_nextHeading = UP;
				else
					_nextHeading = DOWN;
			}
		}
		else
		{
			goHomeGhost();
		}

		_tabPath.clear();
	}
}

//--- opérations sur l'objet -----------------------------------------------------------------------------------------------------------------------

bool Entity::tryToMove(std::vector<std::vector<Tile>>& map, unsigned int pos)
{
	unsigned int nextindexX = 0, nextindexY = 0;

	/*
		recherche si la prochaine direction est disponible (pas de mur)
			si elle est disponible l'objet ce déplace de "velocity" pixels dans cette direction
	*/
	switch (pos)
	{
	case UP:
		nextindexX = _indexX;
		nextindexY = _indexY - 1;
		if (map[nextindexX][nextindexY].wall)
		{
			if (_y - _velocity >= (map[nextindexX][nextindexY].tile_y + TILE_SIZE))
				return (bool)validCondition;
			else
				return (bool)Not_Valid;
		}
		else
			return (bool)validCondition;
		break;
	case LEFT:
		nextindexX = _indexX - 1;
		nextindexY = _indexY;
		if (map[nextindexX][nextindexY].wall)
		{
			if (_x - _velocity >= (map[nextindexX][nextindexY].tile_x + TILE_SIZE))
				return (bool)validCondition;
			else
				return (bool)Not_Valid;
		}
		else
			return (bool)validCondition;
		break;
	case DOWN:
		nextindexX = _indexX;
		nextindexY = _indexY + 1;
		if (map[nextindexX][nextindexY].wall)
		{
			if (((_y + TILE_SIZE) + _velocity) <= map[nextindexX][nextindexY].tile_y)
				return (bool)validCondition;
			else
				return (bool)Not_Valid;
		}
		else
			return (bool)validCondition;
		break;
	case RIGHT:
		nextindexX = _indexX + 1;
		nextindexY = _indexY;
		if (map[nextindexX][nextindexY].wall)
		{
			if (((_x + TILE_SIZE) + _velocity) <= map[nextindexX][nextindexY].tile_x)
				return (bool)validCondition;
			else
				return (bool)Not_Valid;
		}
		else
			return (bool)validCondition;
		break;
	}

	return (bool)Not_Valid;
}
bool Entity::isOnFullTile(std::vector<std::vector<Tile>>& map, unsigned int i, unsigned int j)
{
	if (_x == map[i][j].tile_x)
	{
		if (_y == map[i][j].tile_y)
		{
			return true;
		}
		return false;
	}
	return false;
}
bool Entity::isOnTile(std::vector<std::vector<Tile>>& map, unsigned int i, unsigned int j)
{
	if ((_x + TILE_SIZE / 2) >= map[i][j].tile_x && (_x + TILE_SIZE / 2) < (map[i][j].tile_x + TILE_SIZE))
	{
		if ((_y + TILE_SIZE / 2) >= map[i][j].tile_y && (_y + TILE_SIZE / 2) < (map[i][j].tile_y + TILE_SIZE))
		{
			return true;
		}
		return false;
	}
	return false;
}
void Entity::makeTheMove(bool validMove, unsigned int pos)
{
	if (validMove)
	{
		switch (pos)
		{
		case UP:
			_y -= _velocity;
			break;
		case LEFT:
			_x -= _velocity;
			break;
		case DOWN:
			_y += _velocity;
			break;
		case RIGHT:
			_x += _velocity;
			break;
		}
	}
}
void Entity::teleport(std::vector<std::vector<Tile>>& map)
{
	if (_x <= map[1][0].tile_x && _y == map[0][map[0].size() / 2].tile_y)
		_x = map[map.size() - 2][0].tile_x;
	else if (_x >= map[map.size() - 2][0].tile_x && _y == map[0][map[0].size() / 2].tile_y)
		_x = map[1][0].tile_x;
}
void Entity::goHomeGhost()
{

}

///////////////////////////// PACMAN //////////////////////////////
/*  PACMAN :: METHODES */
Pacman::Pacman(std::string name, unsigned int x, unsigned int y, unsigned int value)
	: Entity(name, x, y, UP, UP, value), _life(3), _powerUP(0), _typeOfValue(0), _indexXPred(3), _indexYPred(12)
{
	IHM::logfileconsole("Pacman is alive");
}
Pacman::Pacman(const Pacman& player)
	: Entity(player.GETname(), player.GETx(), player.GETy(), player.GETcurrentHeading(), player.GETnextHeading(), player.GETvalue()),
	_typeOfValue(player.GETtypeOfValue()), _life(player.GETlife()), _powerUP(0), _indexXPred(3), _indexYPred(12)
{
	IHM::logfileconsole("Pacman is alive");
}
Pacman::~Pacman()
{
	IHM::logfileconsole("Pacman is dead");
}
int8_t Pacman::move(Map& map, std::vector<Ghost*>& ghost, unsigned int secondLoop)
{
	Uint8 validTryToMove = 0;
	unsigned int pos = 0;
	bool validMove = false;
	
	if (secondLoop == -1)
	{
		// cherche une première fois à faire un mouvement
		// test avec nextHeading et currentHeading

		switch (validTryToMove = search(map))
		{
		case Not_Valid:
			break;
		case validCondition:
			if (tryToMove(map.matriceMap, this->GETcurrentHeading()))
			{
				validMove = validCondition;
				pos = this->GETcurrentHeading();
			}
			break;
		case validNextHeading:
			if (tryToMove(map.matriceMap, this->GETnextHeading()))
			{
				validMove = validCondition;
				pos = this->GETnextHeading();
				this->SETcurrentHeading(this->GETnextHeading());
			}
			else
				move(map, ghost, 1);
			break;
		}
	}
	else
	{
		// cherche une deuxième fois à faire un mouvement après l'echec du premier test de mouvement
		// test uniquement sur currentHeading

		if ((validTryToMove = search(map)) != Not_Valid)
		{
			if (tryToMove(map.matriceMap, this->GETcurrentHeading()))
			{
				validMove = validCondition;
				pos = this->GETcurrentHeading();
			}
		}
	}

	if (this->GETinvincible())
	{
		if (this->GETtimeInvincible() > 0)
			this->SETtimeInvincible(this->GETtimeInvincible() - 1);
		else 
		{
			this->SETtimeInvincible(TEMPO_INVINCIBLE);
			this->SETinvincible(false);
			for (unsigned int i = 0; i < ghost.size(); i++)
				ghost[i]->SETinvincible(true);
		}
	}
	value(map.matriceMap, validMove);
	if (_powerUP)
	{
		this->SETinvincible(true);
		for (unsigned int i = 0; i < ghost.size(); i++)
			ghost[i]->SETinvincible(false);
		_powerUP = 0;
	}

	makeTheMove(validMove, pos);
	
	collideGhost(ghost, map);
	
	teleport(map.matriceMap);

	pathForecast(map);

	return 0;
}
Uint8 Pacman::search(Map& map)
{
	Uint8 condition = Not_Valid;
	for (Uint8 i = 0; i < map.map_length; i++)
	{
		for (Uint8 j = 0; j < map.map_height; j++)
		{
			if (this->GETcurrentHeading() != this->GETnextHeading())
			{
				if (isOnFullTile(map.matriceMap, i, j))
				{
					this->SETindexX(i);
					this->SETindexY(j);
					condition = validNextHeading;
					return condition;
				}
			}
			if (isOnTile(map.matriceMap, i, j))
			{
				this->SETindexX(i);
				this->SETindexY(j);
				condition = validCondition;
				return condition;
			}
		}
	}
	return condition;
}
void Pacman::value(std::vector<std::vector<Tile>>& map, bool validMove)
{
	if (validMove)
	{
		switch (map[this->GETindexX()][this->GETindexY()].entity)
		{
		case nothing:
			_typeOfValue = 0;
			break;
		case gold:
			map[this->GETindexX()][this->GETindexY()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuegold);
			_typeOfValue = valuegold;
			break;
		case cherry:
			map[this->GETindexX()][this->GETindexY()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuecherry);
			_typeOfValue = valuecherry;
			_powerUP++;
			break;
		case strawberry:
			map[this->GETindexX()][this->GETindexY()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuestrawberry);
			_typeOfValue = valuestrawberry;
			_powerUP++;
			break;
		case peach:
			map[this->GETindexX()][this->GETindexY()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuepeach);
			_typeOfValue = valuepeach;
			_powerUP++;
			break;
		case apple:
			map[this->GETindexX()][this->GETindexY()].entity = nothing;
			this->SETvalue(this->GETvalue() + valueapple);
			_typeOfValue = valueapple;
			_powerUP++;
			break;
		case key:
			map[this->GETindexX()][this->GETindexY()].entity = nothing;
			this->SETvalue(this->GETvalue() + valuekey);
			_typeOfValue = valuekey;
			break;
		}
	}
}
void Pacman::collideGhost(std::vector<Ghost*>& ghost, Map& map)
{
	bool hit = false;
	unsigned int l = 0;
	for (l; l < ghost.size(); l++)
	{
		// pacman gauche et ghost droite
		if (((this->GETx() + TILE_SIZE) >= ghost[l]->GETx()) && ((this->GETx() + TILE_SIZE) <= (ghost[l]->GETx() + TILE_SIZE)) 
			&& (this->GETy() == ghost[l]->GETy()))
		{
			hit = true;
			break;
		}
		// pacman bas et ghost haut
		else if (((this->GETy()) >= ghost[l]->GETy()) && ((this->GETy()) <= (ghost[l]->GETy() + TILE_SIZE)) 
			&& (this->GETx() == ghost[l]->GETx()))
		{
			hit = true;
			break;
		}
		// pacman droite et ghost gauche
		else if (((this->GETx()) >= ghost[l]->GETx()) && ((this->GETx()) <= (ghost[l]->GETx() + TILE_SIZE))
			&& (this->GETy() == ghost[l]->GETy())) 
		{
			hit = true;
			break;
		}
		// pacman haut et ghost bas
		else if (((this->GETy() + TILE_SIZE) >= ghost[l]->GETy()) && ((this->GETy() + TILE_SIZE) <= (ghost[l]->GETy() + TILE_SIZE)) 
			&& (this->GETx() == ghost[l]->GETx())) 
		{
			hit = true;
			break;
		}
	}
	if (hit && !ghost[l]->GETgoHome())
	{

		if (this->GETinvincible())
		{
			ghost[l]->SETinvincible(true);
			ghost[l]->SETgoHome(true);
			this->SETvalue(this->GETvalue() + ghost1);
			IHM::logfileconsole("Pacman hit a Ghost successfully");
		}
		else 
		{
			this->SETx(map.matriceMap[3][map.map_height / 2].tile_x);
			this->SETy(map.matriceMap[3][map.map_height / 2].tile_y);
			if (_life > 0)
				_life--;
			IHM::logfileconsole("Pacman lost a life");
		}
	}
}
void Pacman::goHomeGhost()
{
	// à utiliser pour une future version où pacman ne se téléporte pas en mourant
}
void Pacman::pathForecast(Map& map)
{
	int8_t offSetX = 0, offSetY = 0;

	// recherche de la direction courante en terme d'indexX et indexY
	switch (this->GETcurrentHeading())
	{
	case UP:
		offSetY = -1;
		break;
	case LEFT:
		offSetX = -1;
		break;
	case DOWN:
		offSetY = 1;
		break;
	case RIGHT:
		offSetX = 1;
		break;
	}
	Uint8 newIndexXPred = this->GETindexX(), newIndexYPred = this->GETindexY();

	// recherche du premier mur pour la direction fixée
	bool continuer = true;
	while (continuer)
	{
		if (map.matriceMap[newIndexXPred][newIndexYPred].wall
			|| (newIndexXPred == 0 && newIndexYPred == (map.map_height - 1) / 2)
			|| (newIndexXPred == map.map_length - 1 && newIndexYPred == (map.map_height - 1) / 2))
		{
			
			_indexXPred = newIndexXPred - offSetX;
			_indexYPred = newIndexYPred - offSetY;
			continuer = false;
		}	
		else 
		{
			newIndexXPred += offSetX;
			newIndexYPred += offSetY;
		}
	}
}
void Pacman::afficherStats(SDL_Renderer*& renderer, TTF_Font* font[])
{
	Texte::writeTexte(renderer, font,
		blended, std::to_string(this->GETvalue()), { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 126, no_angle, center_x);
	Texte::writeTexte(renderer, font,
		shaded, "Remaining life  : " + std::to_string(_life), { 255, 0, 0, 255 }, White, 32, 0, 250, no_angle);
	// debug positions pacman sur l'ecran
	//Texte::writeTexte(renderer, font,
	//	blended, std::to_string(this->GETx()) + " , " + std::to_string(this->GETy()), { 0, 64, 255, 255 }, NoColor, 24, 0, 300);
	if (this->GETinvincible())
		Texte::writeTexte(renderer,font,
			blended, "Remaining time Invincible : " + std::to_string(this->GETtimeInvincible() / SCREEN_REFRESH_RATE), { 0, 64, 255, 255 }, NoColor, 24, 0, 350, no_angle);
}
void Pacman::afficher(std::vector<Texture*> tabTexture[])
{
	std::string pacmanPos[MAX_POS] = { "U", "L", "D", "R" }, pacmanSkin[MAX_SKIN] = { "1", "2" };
	unsigned int skin = 0;
	if (this->GETalternateSkin())
		skin = 1;
	for (unsigned int i = 0; i < tabTexture[0].size(); i++)
	{
		if (tabTexture[0][i]->renderTextureTestString("pacman_" + pacmanPos[this->GETcurrentHeading()]
			+ "_" + pacmanSkin[skin] + ".png", this->GETx(), this->GETy()))
			return;
	}
}


///////////////////////////// GHOST //////////////////////////////
/*  GHOST :: METHODES */
Ghost::Ghost(std::string name, unsigned int x, unsigned int y, Uint8 type, unsigned int value)
	: Entity(name, x, y, UP, RIGHT,value), _type(type), _goHome(false)
{
	IHM::logfileconsole(this->GETname() + " is alive");
}
Ghost::~Ghost()
{
	IHM::logfileconsole(this->GETname() + " is dead");
}
int8_t Ghost::move(Map& map, Sysinfo& sysinfo, unsigned int secondLoop)
{
	unsigned int validTryToMove = 0;
	unsigned int pos = 0;
	bool validMove = false;


	if (secondLoop == -1)
	{
		// cherche une première fois à faire un mouvement
		// test avec nextHeading et currentHeading

		switch (validTryToMove = search(map, sysinfo.pacman->GETindexX(), sysinfo.pacman->GETindexY(),
			sysinfo.pacman->GETindexXpred(), sysinfo.pacman->GETindexYpred()))
		{
		case Not_Valid:
			break;
		case validCondition:
			if (tryToMove(map.matriceMap, this->GETcurrentHeading()))
			{
				validMove = validCondition;
				pos = this->GETcurrentHeading();
			}
			break;
		case validNextHeading:
			if (tryToMove(map.matriceMap, this->GETnextHeading()))
			{
				validMove = validCondition;
				pos = this->GETnextHeading();
				this->SETcurrentHeading(this->GETnextHeading());
			}
			else
				move(map, sysinfo, trySecondTime);
			break;
		}
	}
	else
	{
		// cherche une deuxième fois à faire un mouvement après l'echec du premier test de mouvement
		// test uniquement currentHeading

		if ((validTryToMove = search(map, sysinfo.pacman->GETindexX(), sysinfo.pacman->GETindexY(),
			sysinfo.pacman->GETindexXpred(), sysinfo.pacman->GETindexYpred())) != Not_Valid)
		{
			if (tryToMove(map.matriceMap, this->GETcurrentHeading()))
			{
				validMove = validCondition;
				pos = this->GETcurrentHeading();
			}
		}
	}

	makeTheMove(validMove, pos);
	teleport(map.matriceMap);
	makeNextHeading(map.matriceMap, sysinfo.pacman); 

	return 0;
}
Uint8 Ghost::search(Map& map, Uint8 indexXPac, Uint8 indexYPac, Uint8 indexXPacPred, Uint8 indexYPacPred)
{
	Uint8 condition = 0;
	for (Uint8 i = 0; i < map.map_length; i++)
	{
		for (Uint8 j = 0; j < map.map_height; j++)
		{

			if (isOnFullTile(map.matriceMap, i, j))
			{
				this->SETindexX(i);
				this->SETindexY(j);

				if (_goHome)
				{
					findAPath(map.matriceMap, map.map_length / 2, map.map_height / 2);
					condition = validNextHeading;
					return condition;
				}
				else
				{
					if (_type == red)
					{
						findAPath(map.matriceMap, indexXPac, indexYPac);
						condition = validNextHeading;
						return condition;
					}
					else if (_type == blue)
					{
						findAPath(map.matriceMap, indexXPacPred, indexYPacPred);
						condition = validNextHeading;
						return condition;
					}
					else
					{
						if (((this->GETcurrentHeading() + this->GETnextHeading()) % 2) == 0)
							condition = validCondition; // évite de changer de direction et de revenir en arrière
						else
							condition = validNextHeading;
						return condition;
					}
				}
				
			}

			if (isOnTile(map.matriceMap, i, j))
			{
				this->SETindexX(i);
				this->SETindexY(j);
				condition = validCondition;
				return condition;
			}
		}
	}
	return condition;
}
void Ghost::makeNextHeading(std::vector<std::vector<Tile>>& map, Pacman*& pacman) 
{
	Uint8 randomNextHeading = 0;
	bool continuer = true;
	
	if(_type == yellow || _type == pink)
	{
		randomNextHeading = rand() % MAX_POS;
		while (continuer) {
			if (tryToMove(map, randomNextHeading))
			{
				continuer = false;
				break;
			}
			randomNextHeading = rand() % MAX_POS;
		}
		this->SETnextHeading(randomNextHeading);
	}
}
void Ghost::goHomeGhost()
{
	_goHome = false;
}
void Ghost::afficher(std::vector<Texture*> tabTexture[])
{
	std::string ghostName[MAX_GHOST] = { "Red", "Blue", "Yellow", "Pink" }, ghostPos[MAX_POS] = { "U", "L", "D", "R" }, ghostSkin[MAX_SKIN] = { "1", "2" };
	Uint8 skin = 0;
	if (this->GETalternateSkin())
		skin = 1; // évite le probleme : bool (false == 0) et (true == tout le reste)

	if (_goHome)
	{
		for(unsigned int i = 0; i < tabTexture[MAX_GHOST].size(); i++)
			tabTexture[MAX_GHOST][i]->renderTextureTestString("goHome.png", this->GETx(), this->GETy());
	}
	else
	{
		if (this->GETinvincible())
		{
			for (unsigned int i = 0; i < tabTexture[_type].size(); i++)
			{
				if (tabTexture[_type][i]->renderTextureTestString(ghostName[_type] + "_" + ghostPos[this->GETcurrentHeading()] +
					"_" + ghostSkin[skin] + ".png", this->GETx(), this->GETy()))
					return;
			}
		}
		else
			tabTexture[MAX_GHOST][skin]->render(this->GETx(), this->GETy());
	}
}

/*
*	End Of File
*/
