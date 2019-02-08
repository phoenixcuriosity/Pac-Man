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

#ifndef SaveReload_H
#define SaveReload_H

#include "lib.h"

struct ScorePlayer {
	// score du joueur
	unsigned int score = 0;

	// nom du joueur
	std::string name = "";
};

class SaveReload {

	/* *********************************************************
						STATIC
	 ********************************************************* */
public: 
	/* 
		Enregistre les attributs des objets Entity ainsi que configuration de la map
		retourne true si aucune erreur n'est survenue
		retourne false si une erreur est survenue
	*/
	static bool save(Sysinfo& sysinfo);

	/*
		Charge les attributs des objets Entity ainsi que configuration de la map
		retourne true si aucune erreur n'est survenue
		retourne false si une erreur est survenue
	*/
	static bool reload(Sysinfo& sysinfo);
	

	/* *********************************************************
						METHODES
	 ********************************************************* */
public:
	SaveReload();
	~SaveReload() {};

public:
	/*
		Enregistre le tableau des scores dans un fichier avec un format particulier
		retourne true si aucune erreur n'est survenue
		retourne false si une erreur est survenue
	*/
	bool saveScore(const std::string& score);

	/* 
		Charge le tableau de score TOP10 à partir d'un fichier formaté avec un format particulier
		retourne true si aucune erreur n'est survenue
		retourne false si une erreur est survenue
	*/
	bool loadScore(const std::string& score);

public:
	inline std::vector<ScorePlayer> GETtabScorePlayer()const { return _tabScorePlayer; };
	inline std::vector<ScorePlayer>& GETtabScorePlayerNONCONST() { return _tabScorePlayer; };

	inline void SETtabScorePlayer(std::vector<ScorePlayer>& tabScorePlayer) { _tabScorePlayer = tabScorePlayer; };

	/* *********************************************************
						ATTRIBUTS
	 ********************************************************* */
private:
	// tableau contenant la liste des joueurs (nom et score)
	std::vector<ScorePlayer> _tabScorePlayer;
};

#endif
