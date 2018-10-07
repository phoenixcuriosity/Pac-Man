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

#include "SaveReload.h"
#include "IHM.h"
#include "Pac_Man_lib.h"


bool SaveReload::save(sysinfo& information, Pacman& player) {
	IHM::logfileconsole("_Save Start_");

	std::ofstream saveEntity(information.files.saveEntity);
	if (saveEntity) {
		saveEntity << "Pacman:" << std::endl;
		saveEntity << player.GETname() << std::endl;
		saveEntity << player.GETx() << std::endl;
		saveEntity << player.GETy() << std::endl;
		saveEntity << player.GETtilex() << std::endl;
		saveEntity << player.GETtiley() << std::endl;

		saveEntity << (unsigned int)player.GETcurrentHeading() << std::endl;
		saveEntity << (unsigned int)player.GETnextHeading() << std::endl;

		saveEntity << player.GETinvincible() << std::endl;
		saveEntity << player.GETtimeInvincible() << std::endl;
		saveEntity << player.GETvalue() << std::endl;

		for (unsigned int i = 0; i < information.ghost.size(); i++) {
			saveEntity << std::endl << std::endl << "Ghost:" << std::endl;
			saveEntity << information.ghost[i]->GETname() << std::endl;
			saveEntity << information.ghost[i]->GETx() << std::endl;
			saveEntity << information.ghost[i]->GETy() << std::endl;
			saveEntity << information.ghost[i]->GETtilex() << std::endl;
			saveEntity << information.ghost[i]->GETtiley() << std::endl;

			saveEntity << (unsigned int)information.ghost[i]->GETcurrentHeading() << std::endl;
			saveEntity << (unsigned int)information.ghost[i]->GETnextHeading() << std::endl;

			saveEntity << information.ghost[i]->GETinvincible() << std::endl;
			saveEntity << information.ghost[i]->GETtimeInvincible() << std::endl;
		}
		
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.files.saveEntity);



	std::ofstream saveMap(information.files.saveMap);
	if (saveMap) {
		saveMap << "MAP_LENGTH=\t" << MAP_LENGTH << std::endl;
		saveMap << "MAP_HEIGHT=\t" << MAP_HEIGHT << std::endl;
		for (unsigned int i = 0; i < MAP_LENGTH; i++) {
			for (unsigned int j = 0; j < MAP_HEIGHT; j++)
				saveMap << (unsigned int)information.map[i][j].entity << std::endl;
		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.files.saveMap);

	IHM::logfileconsole("_Save End_");
	return false;
}
bool SaveReload::reload(sysinfo& information, Pacman& player) {
	IHM::logfileconsole("_Reload Start_");

	std::string destroy;
	unsigned int value = 0;
	std::ifstream saveEntity(information.files.saveEntity);
	if (saveEntity) {
		saveEntity >> destroy;
		if (destroy.compare("Pacman:") == 0) {
			saveEntity >> destroy;
			player.SETname(destroy);

			saveEntity >> value;
			player.SETx(value);
			saveEntity >> value;
			player.SETy(value);
			saveEntity >> value;
			player.SETtilex(value);
			saveEntity >> value;
			player.SETtiley(value);

			saveEntity >> value;
			player.SETcurrentHeading((Uint8)value);
			saveEntity >> value;
			player.SETnextHeading((Uint8)value);

			saveEntity >> value;
			player.SETinvincible(value);
			saveEntity >> value;
			player.SETtimeInvincible(value);
			saveEntity >> value;
			player.SETvalue(value);

			for (unsigned int i = 0; i < information.ghost.size(); i++) {
				saveEntity >> destroy;

				saveEntity >> destroy;
				information.ghost[i]->SETname(destroy);

				saveEntity >> value;
				information.ghost[i]->SETx(value);
				saveEntity >> value;
				information.ghost[i]->SETy(value);
				saveEntity >> value;
				information.ghost[i]->SETtilex(value);
				saveEntity >> value;
				information.ghost[i]->SETtiley(value);

				saveEntity >> value;
				information.ghost[i]->SETcurrentHeading((Uint8)value);
				saveEntity >> value;
				information.ghost[i]->SETnextHeading((Uint8)value);

				saveEntity >> value;
				information.ghost[i]->SETinvincible(value);
				saveEntity >> value;
				information.ghost[i]->SETtimeInvincible(value);
			}
		}
		else
			IHM::logfileconsole("________ERROR : reload : file corrupt : " + information.files.saveEntity);
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.files.saveEntity);


	unsigned int entity = 0;
	std::ifstream saveMap(information.files.saveMap);
	if (saveMap) {
		saveMap >> destroy;
		if (destroy.compare("MAP_LENGTH=") == 0) {
			saveMap >> destroy;
			saveMap >> destroy;
			saveMap >> destroy;
			for (unsigned int i = 0; i < MAP_LENGTH; i++) {
				for (unsigned int j = 0; j < MAP_HEIGHT; j++) {
					saveMap >> entity;
					information.map[i][j].entity = (Uint8)entity;
				}
			}
		}
		else
			IHM::logfileconsole("________ERROR : reload : file corrupt : " + information.files.saveMap);
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + information.files.saveMap);

	IHM::logfileconsole("_Reload End_");
	return false;
}
void SaveReload::loadScore(const std::string& score, std::vector<scorePlayer>& tabScorePlayer) {
	/*
		charge le tableau de score TOP10 à partir d'un fichier formaté avec un format particulier
	*/
	IHM::logfileconsole("_loadScore Start_");
	std::string destroy;
	scorePlayer player;
	unsigned int maxScore = 0;

	std::ifstream loadScore(score);
	if (loadScore) {
		loadScore >> destroy;
		if (destroy.compare("numberOfScore=") == 0) {
			loadScore >> maxScore;
			for (unsigned int i = 0; i < maxScore; i++) {
				loadScore >> player.name;
				loadScore >> player.score;
				tabScorePlayer.push_back(player);
			}
		}
		else
			IHM::logfileconsole("________ERROR : loadScore : file corrupt : " + score);
	}
	else
		IHM::logfileconsole("________ERROR : loadScore : cannot open file : " + score);

	IHM::logfileconsole("_loadScore End_");
}
void SaveReload::saveScore(const std::string& score, std::vector<scorePlayer>& tabScorePlayer) {
	/*
		Enregistre le tableau des scores dans un fichier avec un format particulier
	*/
	IHM::logfileconsole("_saveScore Start_");
	std::ofstream saveScore(score);
	if (saveScore) {
		saveScore << "numberOfScore=\t";
		saveScore << tabScorePlayer.size();
		for (unsigned int i = 0; i < tabScorePlayer.size(); i++)
			saveScore << std::endl << tabScorePlayer[i].name + "\t\t\t\t\t" << tabScorePlayer[i].score;
	}
	else
		IHM::logfileconsole("________ERROR : loadScore : cannot open file : " + score);
	IHM::logfileconsole("_saveScore End_");
}