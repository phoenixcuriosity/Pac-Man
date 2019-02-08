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

#include "Pac_Man_lib.h"

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
			IHM::initMusic(sysinfo.music);

			t2 = clock();
			IHM::logfileconsole("temps d'execution de l'initialisation : " + std::to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC) + " secondes");

			IHM::ecranTitre(sysinfo);

			int SDL_EnableUNICODE(SDL_ENABLE); // on azerty

			Mix_PlayMusic(sysinfo.music[music_intro], -1);


			while (sysinfo.var.continuer) {
				/*
					Boucle principale bloquante
					Boucle fonctionnant à la fréquence SCREEN_REFRESH_RATE
					cela est du au flag SDL_RENDERER_PRESENTVSYNC dans SDL_CreateRenderer()
					
					Toutes les frames (toutes les 1/SCREEN_REFRESH_RATE seconde):
						-> Gestion des évenements selon la définiton de la SDL (souris, clavier, ...)
						-> Appel de la fonction move pour faire bouger les objets Entity
						-> Appel de la fonction alwaysRender qui affiche la frame calculée du STATEplay (stateScreen == STATEplay)
				*/

				//t1 = clock();
				IHM::eventSDL(sysinfo);
				Entity::move(sysinfo);
				IHM::alwaysRender(sysinfo);
				//t2 = clock();
				//cout << endl << "temps d'execution d'une boucle : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
			}

			sysinfo.var.saveReload.saveScore(sysinfo.file.score);
		}
		IHM::deleteAll(sysinfo);
	}
	IHM::logfileconsole("SDL_Quit Success");
	IHM::logfileconsole("________PROGRAMME FINISH________");
	return EXIT_SUCCESS;
}

