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

#ifndef IHM_H
#define IHM_H

#include "lib.h"

class IHM {
public:

	static void initfile(const std::string& log);
	static void logfileconsole(const std::string &msg);
	static void logSDLError(std::ostream &os, const std::string &msg);
	static void initsdl(SDL_Window*&, SDL_Renderer*&, TTF_Font*[]);
	static void initTile(Tile& map, bool wall, Uint8 entity);
	static void forme(Tile& tmap, std::vector<std::vector<Tile>>& map, unsigned int length, unsigned int height, bool wall = true);
	static void initGrid(Map& map);
	static void calculimage(Sysinfo&);


	static void mouse(Sysinfo& sysinfo, Pacman& Player, SDL_Event event);
	static void cliqueGauche(Sysinfo& sysinfo, Pacman& Player, SDL_Event event);

	static std::string getName(Sysinfo& sysinfo, unsigned int position);

	static void ecrantitre(Sysinfo&);
	static void ecranScore(Sysinfo&, Pacman& player);
	static void alwaysrender(Sysinfo&, Pacman& player);
	static void afficherMap(Sysinfo& sysinfo);
	static void calculTime(Sysinfo& sysinfo);

	static int topScore(std::vector<ScorePlayer>& tabScorePlayer, unsigned int score);

	static void deleteAll(Sysinfo&);

};
template<class T>
T max(T& a, T& b) {
	if (a >= b)
		return a;
	else
		return b;
}
template<class T>
void deleteDyTabPlayerAndTextures(T& dytab, const std::string& name) {
	unsigned int size = dytab.size();
	for (unsigned int i = 0; i < size; i++) {
		IHM::logfileconsole("Delete " + name + " name = " + dytab[i]->GETname() + " Success");
		delete dytab[i];
		dytab[i] = nullptr;
	}
	for (unsigned int i = 0; i < size; i++)
		dytab.pop_back();
	if (dytab.size() != 0)
		IHM::logfileconsole("___________ERROR : " + name + ".size() != 0");
	else
		IHM::logfileconsole("Delete ALL " + name + " Success");
}


#endif
