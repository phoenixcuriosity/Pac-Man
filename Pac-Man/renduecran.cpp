/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.8a

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
		information.allTextures.txtecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen);
	
	for (unsigned int i = 0; i < information.allTextures.imgecrantitre.size(); i++)
		information.allTextures.imgecrantitre[i]->renderTextureTestStates(information.ecran.renderer, information.variable.statescreen);
	
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
			information.allTextures.txtplay[i]->renderTextureTestString(information.ecran.renderer, "Your Score");
			if (player.GETlife() == 0)
				information.allTextures.txtplay[i]->renderTextureTestString(information.ecran.renderer, "YOU DIED");
		}


		//
		player.afficherStats(information);
		player.afficher(information.ecran.renderer, information.allTextures.pacman);
		for (unsigned int i = 0; i < information.ghost.size(); i++) {
			if(i == red)
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.red, information.allTextures.miscGhost);
			else if(i == blue)
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.blue, information.allTextures.miscGhost);
			else if(i == yellow)
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.yellow, information.allTextures.miscGhost);
			else
				information.ghost[i]->afficher(information.ecran.renderer, information.allTextures.pink, information.allTextures.miscGhost);
		}
		



		
		information.variable.moduloScore = (information.variable.moduloScore + 1) % 30;
		if (player.GETtypeOfValue() != 0 || information.variable.tempoScore != 0) {
			if(player.GETtypeOfValue() != 0)
				information.variable.tempoScore = player.GETtypeOfValue();
			switch (information.variable.tempoScore) {
			case valuegold:
				information.allTextures.scoreValue[0]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			case valuecherry:
				information.allTextures.scoreValue[1]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			case valuestrawberry:
				information.allTextures.scoreValue[2]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			case valuepeach:
				information.allTextures.scoreValue[3]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			case valueapple:
				information.allTextures.scoreValue[4]->render(information.ecran.renderer, player.GETx() + tileSize, player.GETy() + tileSize);
				break;
			}

			if (information.variable.moduloScore == 0)
				information.variable.tempoScore = 0;
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
	/*
		� utiliser si besoin de changer la map
		screenshot de l'ecran et rogner sous paint pour n'utiliser que la map -> map.png � mettre dans le dossier image
		
	unsigned int k = 0;
	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			if (information.map[k].wall)
				information.allTextures.ground[blackTile]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
			else {
				information.allTextures.ground[whiteTile]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
				if(information.map[k].entity != nothing)
					information.allTextures.collectibles[information.map[k].entity - 1]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
			}
			k++;
		}
	}
	*/
	

	unsigned int k = 0;
	information.allTextures.ground[mapTile]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);

	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapHeight; j++) {
			if(!information.map[k].wall && information.map[k].entity != nothing)
				information.allTextures.collectibles[information.map[k].entity - 1]->render(information.ecran.renderer, information.map[k].tile_x, information.map[k].tile_y);
			k++;
		}
	}

}