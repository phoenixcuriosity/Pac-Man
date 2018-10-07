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

#include "Pac_Man_lib.h"
#include "SaveReload.h"

void mainLoop(Sysinfo& sysinfo);

int main(int argc, char** argv) {
	Sysinfo sysinfo;
	
	clock_t t1, t2;
	t1 = clock();

	srand((unsigned int)time(NULL));
	IHM::initfile(sysinfo.file.log);

	IHM::logfileconsole("________PROGRAMME START________");

	IHM::initsdl(sysinfo.screen.window, sysinfo.screen.renderer, sysinfo.allTextures.font);
	IHM::initGrid(sysinfo.map);
	SaveReload::loadScore(sysinfo.file.score, sysinfo.var.tabScorePlayer);
	IHM::calculimage(sysinfo);

	
	t2 = clock();
	IHM::logfileconsole("temps d'execution de l'initialisation : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC) + " secondes");

	IHM::ecrantitre(sysinfo);

	mainLoop(sysinfo);

	SaveReload::saveScore(sysinfo.file.score, sysinfo.var.tabScorePlayer);
	IHM::deleteAll(sysinfo);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	IHM::logfileconsole("SDL_Quit Success");
	IHM::logfileconsole("________PROGRAMME FINISH________");
	return 0;
}

void mainLoop(Sysinfo& sysinfo) {
	IHM::logfileconsole("_mainLoop Start_");
	SDL_Event event;

	Pacman Player("player", 832, 544);
	sysinfo.ghost.push_back(new Ghost("Red", 640, 512, red));
	sysinfo.ghost.push_back(new Ghost("Blue", 1280, 512, blue));
	sysinfo.ghost.push_back(new Ghost("Yellow", 1280, 564, yellow));
	sysinfo.ghost.push_back(new Ghost("Pink", 1280, 628, pink));

	int SDL_EnableUNICODE(SDL_ENABLE); // on azerty

	//clock_t t1, t2;
	while (sysinfo.var.continuer) {

		//t1 = clock();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:	// permet de quitter le jeu
				sysinfo.var.continuer = 0;
				break;
			case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					Player.SETnextHeading(UP);
					break;
				case SDLK_DOWN:
					Player.SETnextHeading(DOWN);
					break;
				case SDLK_RIGHT:
					Player.SETnextHeading(RIGHT);
					break;
				case SDLK_LEFT:
					Player.SETnextHeading(LEFT);
					break;
				case SDLK_ESCAPE:
					sysinfo.var.continuer = 0;
					break;
				case SDLK_SPACE:

					break;
				}
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
				IHM::mouse(sysinfo, Player, event);
				break;
			case SDL_MOUSEWHEEL:
				//wheel(sysinfo, event.wheel.y);
				break;
			}

		}
		Entity::move(sysinfo, Player);
		IHM::alwaysrender(sysinfo, Player);
		//t2 = clock();
		//cout << endl << "temps d'execution d'une boucle : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
	}

	
	for (unsigned int i = 0; i < sysinfo.ghost.size(); i++)
		delete sysinfo.ghost[i];
	IHM::logfileconsole("_mainLoop End_");
}

/*

Sysinfo* ptr = &sysinfo;

cout << endl << (*ptr).variable.continuer;

test(ptr);

cout << endl << (*ptr).variable.continuer;
ptr = nullptr;


void test(void* ptr) {
	cout << endl << (*(Sysinfo*)ptr).variable.continuer;
	(*(Sysinfo*)ptr).variable.continuer= false;
}

*/

