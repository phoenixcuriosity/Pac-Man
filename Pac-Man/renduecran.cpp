/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.4

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
	SDL_SetRenderDrawColor(information.ecran.renderer, 0, 0, 0, 255);
	SDL_RenderClear(information.ecran.renderer);

	for (unsigned int i = 0; i < information.allTextures.txtecrantitre.size(); i++)
		information.allTextures.txtecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
	
	for (unsigned int i = 0; i < information.allTextures.imgecrantitre.size(); i++)
		information.allTextures.imgecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);
	
	for (unsigned int i = 0; i < information.allButton.buttonecrantitre.size(); i++)
		information.allButton.buttonecrantitre[i]->renderButton(information.ecran.renderer, information.variable.statescreen);
	
	
	SDL_RenderPresent(information.ecran.renderer);

	logfileconsole("_Ecrantitres End_");
}


void alwaysrender(sysinfo& information, Pacman& player){
	//clock_t t1, t2;
	//t1 = clock();

	switch (information.variable.statescreen) {
	case STATEplay:

		/*
			fond gris et affichage de la map avec les couloirs et murs
		*/
		SDL_RenderClear(information.ecran.renderer);
		SDL_SetRenderDrawColor(information.ecran.renderer, 128, 128, 128, 0xFF);
		afficherMap(information);

		/*
			changement de skin toutes 10 boucles
		*/
		information.variable.modulo = (information.variable.modulo + 1) % 10;
		if (information.variable.modulo == 0) {
			player.SETalternateSkin(!player.GETalternateSkin());
			for (unsigned int i = 0; i < information.ghost.size(); i++)
				information.ghost[i]->SETalternateSkin(!information.ghost[i]->GETalternateSkin());
		}
			

		for (unsigned int i = 0; i < information.allTextures.txtplay.size(); i++) {
			information.allTextures.txtplay[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen, information.variable.select);

		}


		//
		player.move(information.map);
		player.afficher(information.ecran.renderer, information.allTextures.pacman);
		for (unsigned int i = 0; i < information.ghost.size(); i++) {
			if(i == red)
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.red);
			else if(i == blue)
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.blue);
			else if(i == yellow)
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.yellow);
			else
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.pink);
		}
			

		for (unsigned int i = 0; i < information.allButton.buttonplay.size(); i++)
			information.allButton.buttonplay[i]->renderButton(information.ecran.renderer, information.variable.statescreen);

		SDL_RenderPresent(information.ecran.renderer);
		break;
	}

	//t2 = clock();
	//cout << endl << "temps d'execution de alwaysrender : " + to_string(((double)t2 - (double)t1) / CLOCKS_PER_SEC);
}

void afficherMap(sysinfo& information) {
	unsigned int k = 0;

	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			if (information.map[k].wall == true)
				information.allTextures.ground[1]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
			else
				information.allTextures.ground[0]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
			k++;
		}
	}
}