/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.115

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


bool SaveReload::save(Sysinfo& sysinfo) {
	IHM::logfileconsole("_Save Start_");

	std::ofstream saveEntity(sysinfo.file.saveEntity);
	if (saveEntity) {
		saveEntity << "Pacman:" << std::endl;
		saveEntity << sysinfo.pacman->GETname() << std::endl;
		saveEntity << sysinfo.pacman->GETx() << std::endl;
		saveEntity << sysinfo.pacman->GETy() << std::endl;
		saveEntity << (unsigned int)sysinfo.pacman->GETindexX() << std::endl;
		saveEntity << (unsigned int)sysinfo.pacman->GETindexY() << std::endl;

		saveEntity << (unsigned int)sysinfo.pacman->GETcurrentHeading() << std::endl;
		saveEntity << (unsigned int)sysinfo.pacman->GETnextHeading() << std::endl;

		saveEntity << sysinfo.pacman->GETinvincible() << std::endl;
		saveEntity << sysinfo.pacman->GETtimeInvincible() << std::endl;
		saveEntity << sysinfo.pacman->GETvalue() << std::endl;

		for (unsigned int i = 0; i < sysinfo.ghost.size(); i++) {
			saveEntity << std::endl << std::endl << "Ghost:" << std::endl;
			saveEntity << sysinfo.ghost[i]->GETname() << std::endl;
			saveEntity << sysinfo.ghost[i]->GETx() << std::endl;
			saveEntity << sysinfo.ghost[i]->GETy() << std::endl;
			saveEntity << (unsigned int)sysinfo.ghost[i]->GETindexX() << std::endl;
			saveEntity << (unsigned int)sysinfo.ghost[i]->GETindexY() << std::endl;

			saveEntity << (unsigned int)sysinfo.ghost[i]->GETcurrentHeading() << std::endl;
			saveEntity << (unsigned int)sysinfo.ghost[i]->GETnextHeading() << std::endl;

			saveEntity << sysinfo.ghost[i]->GETinvincible() << std::endl;
			saveEntity << sysinfo.ghost[i]->GETtimeInvincible() << std::endl;
		}
		
	}
	else {
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.saveEntity);
		return false;
	}


	std::ofstream saveMap(sysinfo.file.saveMap);
	if (saveMap) {
		saveMap << "MAP_LENGTH=\t" << (unsigned int)sysinfo.map.map_length << std::endl;
		saveMap << "MAP_HEIGHT=\t" << (unsigned int)sysinfo.map.map_height << std::endl;
		for (Uint8 i = 0; i < sysinfo.map.map_length; i++) {
			for (Uint8 j = 0; j < sysinfo.map.map_height; j++)
				saveMap << (unsigned int)sysinfo.map.matriceMap[i][j].entity << std::endl;
		}
	}
	else {
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.saveMap);
		return false;
	}
		
	IHM::logfileconsole("_Save End_");
	return true;
}
bool SaveReload::reload(Sysinfo& sysinfo) {
	IHM::logfileconsole("_Reload Start_");

	std::string destroy;
	unsigned int value = 0;
	std::ifstream saveEntity(sysinfo.file.saveEntity);
	if (saveEntity) {
		saveEntity >> destroy;
		if (destroy.compare("Pacman:") == 0) {
			saveEntity >> destroy;
			sysinfo.pacman->SETname(destroy);

			saveEntity >> value;
			sysinfo.pacman->SETx(value);
			saveEntity >> value;
			sysinfo.pacman->SETy(value);
			saveEntity >> value;
			sysinfo.pacman->SETindexX((Uint8)value);
			saveEntity >> value;
			sysinfo.pacman->SETindexY((Uint8)value);

			saveEntity >> value;
			sysinfo.pacman->SETcurrentHeading((Uint8)value);
			saveEntity >> value;
			sysinfo.pacman->SETnextHeading((Uint8)value);

			saveEntity >> value;
			sysinfo.pacman->SETinvincible(value);
			saveEntity >> value;
			sysinfo.pacman->SETtimeInvincible(value);
			saveEntity >> value;
			sysinfo.pacman->SETvalue(value);

			for (unsigned int i = 0; i < sysinfo.ghost.size(); i++) {
				saveEntity >> destroy;

				saveEntity >> destroy;
				sysinfo.ghost[i]->SETname(destroy);

				saveEntity >> value;
				sysinfo.ghost[i]->SETx(value);
				saveEntity >> value;
				sysinfo.ghost[i]->SETy(value);
				saveEntity >> value;
				sysinfo.ghost[i]->SETindexX((Uint8)value);
				saveEntity >> value;
				sysinfo.ghost[i]->SETindexY((Uint8)value);

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
		else {
			IHM::logfileconsole("________ERROR : reload : file corrupt : " + sysinfo.file.saveEntity);
			return false;
		}
			
	}
	else {
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.saveEntity);
		return false;
	}

	unsigned int entity = 0;
	std::ifstream saveMap(sysinfo.file.saveMap);
	if (saveMap) {
		saveMap >> destroy;
		if (destroy.compare("MAP_LENGTH=") == 0) {
			saveMap >> destroy;
			saveMap >> destroy;
			saveMap >> destroy;
			for (Uint8 i = 0; i < sysinfo.map.map_length; i++) {
				for (Uint8 j = 0; j < sysinfo.map.map_height; j++) {
					saveMap >> entity;
					sysinfo.map.matriceMap[i][j].entity = (Uint8)entity;
				}
			}
		}
		else {
			IHM::logfileconsole("________ERROR : reload : file corrupt : " + sysinfo.file.saveMap);
			return false;
		}
	}
	else {
		IHM::logfileconsole("ERREUR: Impossible d'ouvrir le fichier " + sysinfo.file.saveMap);
		return false;
	}
		
	IHM::logfileconsole("_Reload End_");
	return true;
}
bool SaveReload::saveScore(const std::string& score) {
	IHM::logfileconsole("_saveScore Start_");
	std::ofstream saveScore(score);
	if (saveScore) {
		saveScore << "numberOfScore=\t";
		saveScore << _tabScorePlayer.size();
		for (unsigned int i = 0; i < _tabScorePlayer.size(); i++)
			saveScore << std::endl << _tabScorePlayer[i].name + "\t\t\t\t\t" << _tabScorePlayer[i].score;
	}
	else {
		IHM::logfileconsole("________ERROR : loadScore : cannot open file : " + score);
		return false;
	}

	IHM::logfileconsole("_saveScore End_");
	return true;
}
bool SaveReload::loadScore(const std::string& score) {
	
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
				_tabScorePlayer.push_back(player);
			}
		}
		else {
			IHM::logfileconsole("________ERROR : loadScore : file corrupt : " + score);
			return false;
		}
			
	}
	else {
		IHM::logfileconsole("________ERROR : loadScore : cannot open file : " + score);
		return false;
	}

	IHM::logfileconsole("_loadScore End_");
	return true;
}

SaveReload::SaveReload()
{
}

std::vector<ScorePlayer> SaveReload::GETtabScorePlayer()const {
	return _tabScorePlayer;
}
std::vector<ScorePlayer>& SaveReload::GETtabScorePlayerNONCONST() {
	return _tabScorePlayer;
}
void SaveReload::SETtabScorePlayer(std::vector<ScorePlayer>& tabScorePlayer) {
	_tabScorePlayer = tabScorePlayer;
}
