/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15

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

/*
	Boucle principale bloquante
	Gestion des �venements selon la d�finiton de la SDL (souris, clavier, ...)
	Fonctionne � la fr�quence du moniteur (ici 60Hz)
	
	Toutes les frames :
		-> Appel de la fonction move
		-> Appel de la fonction alwaysrender qui affiche la frame calcul�e du STATEplay (statescreen == STATEplay)
*/
void mainLoop(Sysinfo& sysinfo);

int main(int argc, char** argv) {
	Sysinfo sysinfo;
	
	clock_t t1, t2;
	t1 = clock();

	srand((unsigned int)time(NULL));
	IHM::initfile(sysinfo.file.log);

	IHM::logfileconsole("________PROGRAMME START________");

	if (IHM::initsdl(sysinfo.screen.window, sysinfo.screen.renderer, sysinfo.allTextes.font)) {
		if (sysinfo.var.saveReload.loadScore(sysinfo.file.score)) {
			IHM::calculimage(sysinfo);

			t2 = clock();
			IHM::logfileconsole("temps d'execution de l'initialisation : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC) + " secondes");

			IHM::ecrantitre(sysinfo);

			mainLoop(sysinfo);

			sysinfo.var.saveReload.saveScore(sysinfo.file.score);
		}
		IHM::deleteAll(sysinfo);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
	IHM::logfileconsole("SDL_Quit Success");
	IHM::logfileconsole("________PROGRAMME FINISH________");
	return EXIT_SUCCESS;
}

void mainLoop(Sysinfo& sysinfo) {
	IHM::logfileconsole("_mainLoop Start_");
	SDL_Event event;

	int SDL_EnableUNICODE(SDL_ENABLE); // on azerty

	//clock_t t1, t2;
	while (sysinfo.var.continuer) {
		//t1 = clock();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:	// permet de quitter le jeu
				sysinfo.var.continuer = 0;
				break;
			case SDL_KEYDOWN: // test sur le type d'�v�nement touche enfonc�
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					sysinfo.pacman->SETnextHeading(UP);
					break;
				case SDLK_DOWN:
					sysinfo.pacman->SETnextHeading(DOWN);
					break;
				case SDLK_RIGHT:
					sysinfo.pacman->SETnextHeading(RIGHT);
					break;
				case SDLK_LEFT:
					sysinfo.pacman->SETnextHeading(LEFT);
					break;
				case SDLK_ESCAPE:
					sysinfo.var.continuer = 0;
					break;
				case SDLK_SPACE:

					break;
				}
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'�v�nement click souris (enfonc�)
				IHM::mouse(sysinfo, event);
				break;
			case SDL_MOUSEWHEEL:
				//wheel(sysinfo, event.wheel.y);
				break;
			}
		}
		Entity::move(sysinfo);
		IHM::alwaysrender(sysinfo);
		//t2 = clock();
		//cout << endl << "temps d'execution d'une boucle : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
	}
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

