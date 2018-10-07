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


bool SaveReload::save(Sysinfo& sysinfo, Pacman& player) {
	IHM::logfileconsole("_Save Start_");

	std::ofstream saveEntity(sysinfo.file.saveEntity);
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

		for (unsigned int i = 0; i < sysinfo.ghost.size(); i++) {
			saveEntity << std::endl << std::endl << "Ghost:" << std::endl;
			saveEntity << sysinfo.ghost[i]->GETname() << std::endl;
			saveEntity << sysinfo.ghost[i]->GETx() << std::endl;
			saveEntity << sysinfo.ghost[i]->GETy() << std::endl;
			saveEntity << sysinfo.ghost[i]->GETtilex() << std::endl;
			saveEntity << sysinfo.ghost[i]->GETtiley() << std::endl;

			saveEntity << (unsigned int)sysinfo.ghost[i]->GETcurrentHeading() << std::endl;
			saveEntity << (unsigned int)sysinfo.ghost[i]->GETnextHeading() << std::endl;

			saveEntity << sysinfo.ghost[i]->GETinvincible() << std::endl;
			saveEntity << sysinfo.ghost[i]->GETtimeInvincible() << std::endl;
		}
		
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.saveEntity);



	std::ofstream saveMap(sysinfo.file.saveMap);
	if (saveMap) {
		saveMap << "MAP_LENGTH=\t" << sysinfo.map.map_length << std::endl;
		saveMap << "MAP_HEIGHT=\t" << sysinfo.map.map_height << std::endl;
		for (unsigned int i = 0; i < sysinfo.map.map_length; i++) {
			for (unsigned int j = 0; j < sysinfo.map.map_height; j++)
				saveMap << (unsigned int)sysinfo.map.matriceMap[i][j].entity << std::endl;
		}
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.saveMap);

	IHM::logfileconsole("_Save End_");
	return false;
}
bool SaveReload::reload(Sysinfo& sysinfo, Pacman& player) {
	IHM::logfileconsole("_Reload Start_");

	std::string destroy;
	unsigned int value = 0;
	std::ifstream saveEntity(sysinfo.file.saveEntity);
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

			for (unsigned int i = 0; i < sysinfo.ghost.size(); i++) {
				saveEntity >> destroy;

				saveEntity >> destroy;
				sysinfo.ghost[i]->SETname(destroy);

				saveEntity >> value;
				sysinfo.ghost[i]->SETx(value);
				saveEntity >> value;
				sysinfo.ghost[i]->SETy(value);
				saveEntity >> value;
				sysinfo.ghost[i]->SETtilex(value);
				saveEntity >> value;
				sysinfo.ghost[i]->SETtiley(value);

				saveEntity >> value;
				sysinfo.ghost[i]->SETcurrentHeading((Uint8)value);
				saveEntity >> value;
				sysinfo.ghost[i]->SETnextHeading((Uint8)value);

				saveEntity >> value;
				sysinfo.ghost[i]->SETinvincible(value);
				saveEntity >> value;
				sysinfo.ghost[i]->SETtimeInvincible(value);
			}
		}
		else
			IHM::logfileconsole("________ERROR : reload : file corrupt : " + sysinfo.file.saveEntity);
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.saveEntity);


	unsigned int entity = 0;
	std::ifstream saveMap(sysinfo.file.saveMap);
	if (saveMap) {
		saveMap >> destroy;
		if (destroy.compare("MAP_LENGTH=") == 0) {
			saveMap >> destroy;
			saveMap >> destroy;
			saveMap >> destroy;
			for (unsigned int i = 0; i < sysinfo.map.map_length; i++) {
				for (unsigned int j = 0; j < sysinfo.map.map_height; j++) {
					saveMap >> entity;
					sysinfo.map.matriceMap[i][j].entity = (Uint8)entity;
				}
			}
		}
		else
			IHM::logfileconsole("________ERROR : reload : file corrupt : " + sysinfo.file.saveMap);
	}
	else
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.saveMap);

	IHM::logfileconsole("_Reload End_");
	return false;
}
void SaveReload::loadScore(const std::string& score, std::vector<ScorePlayer>& tabScorePlayer) {
	/*
		charge le tableau de score TOP10 à partir d'un fichier formaté avec un format particulier
	*/
	IHM::logfileconsole("_loadScore Start_");
	std::string destroy;
	ScorePlayer player;
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
void SaveReload::saveScore(const std::string& score, std::vector<ScorePlayer>& tabScorePlayer) {
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