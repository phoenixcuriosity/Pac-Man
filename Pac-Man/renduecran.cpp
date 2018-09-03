/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.1

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

#include "renduecran.h"
#include "sdl.h"
#include "mainLoop.h"

using namespace std;

void ecrantitre(sysinfo& information){
	/*
	
		affiche toutes les textures ainsi que les boutons ayant l'attribut _statescreen == STATEecrantitre

	*/
	logfileconsole("_Ecrantitres Start_");
	
	information.variable.statescreen = STATEecrantitre;
	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allTextures.tabTexture.size(); i++)
		information.allTextures.tabTexture[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
	for (unsigned int i = 0; i < information.tabbutton.size(); i++)
		information.tabbutton[i]->renderButton(information.ecran.renderer, information.variable.statescreen);
	
	
	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_Ecrantitres End_");
}


void alwaysrender(sysinfo& information){
	//clock_t t1, t2;
	//t1 = clock();

	
	

	switch (information.variable.statescreen) {
	case STATEplay:
		SDL_RenderClear(information.ecran.renderer);

		for (unsigned int i = 0; i < information.allTextures.tabTexture.size(); i++)
			information.allTextures.tabTexture[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
		for (unsigned int i = 0; i < information.tabbutton.size(); i++)
			information.tabbutton[i]->renderButton(information.ecran.renderer, information.variable.statescreen);

		SDL_RenderPresent(information.ecran.renderer);
		break;
	}


	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}