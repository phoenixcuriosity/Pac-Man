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

/* *********************************************************
			Calcul des Constantes de Pac_Man_lib.h
  ********************************************************* */

// Donne la valeur en pixel de la longueur et de la largeur de l'écran
Uint16 getHorizontal(){
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.right % TILE_SIZE)) == 0)
		return (Uint16)desktop.right;
	return (Uint16)desktop.right + (TILE_SIZE - complete);
}
Uint16 getVertical(){
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Uint16 complete = 0;
	if ((complete = ((Uint16)desktop.bottom % TILE_SIZE)) == 0)
		return (Uint16)desktop.bottom;
	return (Uint16)desktop.bottom + (TILE_SIZE - complete);
}
// Donne la fréquence de rafraichissement de l'écran en Hz
Uint8 getRefreshRate() {
	DEVMODE screen;
	memset(&screen, 0, sizeof(DEVMODE));
	if (EnumDisplaySettings(NULL, 0, &screen)) {
		return (Uint8)screen.dmDisplayFrequency;
	}
	return 0;
}




/* *********************************************************
						MAIN
  ********************************************************* */
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

			IHM::ecranTitre(sysinfo);

			int SDL_EnableUNICODE(SDL_ENABLE); // on azerty

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
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
	IHM::logfileconsole("SDL_Quit Success");
	IHM::logfileconsole("________PROGRAMME FINISH________");
	return EXIT_SUCCESS;
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

