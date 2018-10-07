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

void mainLoop(sysinfo& information);

int main(int argc, char** argv) {
	sysinfo information;
	
	clock_t t1, t2;
	t1 = clock();

	srand((unsigned int)time(NULL));
	IHM::initfile(information.files.log);

	IHM::logfileconsole("________PROGRAMME START________");

	IHM::initsdl(information.ecran.window, information.ecran.renderer, information.allTextures.font);
	IHM::initGrid(information.map);
	SaveReload::loadScore(information.files.score, information.variable.tabScorePlayer);
	IHM::calculimage(information);

	
	t2 = clock();
	IHM::logfileconsole("temps d'execution de l'initialisation : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC) + " secondes");

	IHM::ecrantitre(information);

	mainLoop(information);

	SaveReload::saveScore(information.files.score, information.variable.tabScorePlayer);
	IHM::deleteAll(information);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	IHM::logfileconsole("SDL_Quit Success");
	IHM::logfileconsole("________PROGRAMME FINISH________");
	return 0;
}

void mainLoop(sysinfo& information) {
	IHM::logfileconsole("_mainLoop Start_");
	SDL_Event event;

	Pacman Player("player", 832, 544);
	information.ghost.push_back(new Ghost("Red", 640, 512, red));
	information.ghost.push_back(new Ghost("Blue", 1280, 512, blue));
	information.ghost.push_back(new Ghost("Yellow", 1280, 564, yellow));
	information.ghost.push_back(new Ghost("Pink", 1280, 628, pink));

	int SDL_EnableUNICODE(SDL_ENABLE); // on azerty

	//clock_t t1, t2;
	while (information.variable.continuer) {

		//t1 = clock();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:	// permet de quitter le jeu
				information.variable.continuer = 0;
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
					information.variable.continuer = 0;
					break;
				case SDLK_SPACE:

					break;
				}
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
				IHM::mouse(information, Player, event);
				break;
			case SDL_MOUSEWHEEL:
				//wheel(information, event.wheel.y);
				break;
			}

		}
		Entity::move(information, Player);
		IHM::alwaysrender(information, Player);
		//t2 = clock();
		//cout << endl << "temps d'execution d'une boucle : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
	}

	
	for (unsigned int i = 0; i < information.ghost.size(); i++)
		delete information.ghost[i];
	IHM::logfileconsole("_mainLoop End_");
}

/*

sysinfo* ptr = &information;

cout << endl << (*ptr).variable.continuer;

test(ptr);

cout << endl << (*ptr).variable.continuer;
ptr = nullptr;


void test(void* ptr) {
	cout << endl << (*(sysinfo*)ptr).variable.continuer;
	(*(sysinfo*)ptr).variable.continuer= false;
}

*/

