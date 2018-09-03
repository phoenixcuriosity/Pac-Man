/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.9

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2.0

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

#include "keyboardAndMouse.h"
#include "renduecran.h"

using namespace std;

void mouse(sysinfo& information, SDL_Event event) {
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT

	*/

	if (event.button.button == SDL_BUTTON_LEFT)
		cliqueGauche(information, event);
	

}
void cliqueGauche(sysinfo& information, SDL_Event event) {
	
	// recherche du bouton par comparaison de string et des positions x et y du clic
	for (unsigned int i = 0; i < information.tabbutton.size(); i++) { // recherche si une bouton est dans ces coordonnées
		switch (information.variable.statescreen) {
		case STATEmainmap:
			
			break;
		case STATEecrantitre:
			if (information.tabbutton[i]->searchButton((string&)"New Game", information.variable.statescreen, event.button.x, event.button.y)) {
				
				return;
			}
			else if (information.tabbutton[i]->searchButton((string&)"Reload", information.variable.statescreen, event.button.x, event.button.y)) {
				
				return;
			}
			else if (information.tabbutton[i]->searchButton((string&)"Option", information.variable.statescreen, event.button.x, event.button.y)) {
				//clearSave(information);
				return;
			}
			else if (information.tabbutton[i]->searchButton((string&)"Quit", information.variable.statescreen, event.button.x, event.button.y)) {
				information.variable.continuer = false;
				return;
			}
			break;
		}
	}
}