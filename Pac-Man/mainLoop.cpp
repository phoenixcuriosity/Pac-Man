/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.6

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

#include "mainLoop.h"

#include "sdl.h"
#include "renduecran.h"
#include "keyboardAndMouse.h"
#include "Entity.h"



using namespace std;

void mainLoop(sysinfo& information) {
	logfileconsole("_mainLoop Start_");
	SDL_Event event;

	Pacman Player((string)"robin", 832, 512);
	information.ghost.push_back(new Ghost("Red", 640, 512, red));
	information.ghost.push_back(new Ghost("Blue", 1280, 512, blue));
	information.ghost.push_back(new Ghost("Yellow", 1280, 564, yellow));
	information.ghost.push_back(new Ghost("Pink", 1280, 596, pink));

	int SDL_EnableUNICODE(1); // on azerty

	while (information.variable.continuer) {
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
				mouse(information, event);
				break;
			case SDL_MOUSEWHEEL:
				//wheel(information, event.wheel.y);
			break;
			}

		}
		move(information, Player);
		alwaysrender(information, Player);
	}

	for (unsigned int i = 0; i < information.ghost.size(); i++)
		delete information.ghost[i];
	logfileconsole("_mainLoop End_");
}
	

void move(sysinfo& information, Pacman& Player) {
	unsigned int randomPos1 = 0, randomPos2 = 0, randomPos3 = 0, randomPos4 = 0;

	if (information.variable.statescreen == STATEplay && information.variable.select != pause) {
		information.variable.moduloPos = (information.variable.moduloPos + 1) % 60;
		if (information.variable.moduloPos == 0) {
			randomPos1 = rand() % 4; randomPos2 = rand() % 4; randomPos3 = rand() % 4; randomPos4 = rand() % 4;
			for (unsigned int i = 0; i < information.ghost.size(); i++) {
				switch (i) {
				case 0:
					information.ghost[i]->SETnextHeading(randomPos1);
					break;
				case 1:
					information.ghost[i]->SETnextHeading(randomPos2);
					break;
				case 2:
					information.ghost[i]->SETnextHeading(randomPos3);
					break;
				case 3:
					information.ghost[i]->SETnextHeading(randomPos4);
					break;
				}
			}
		}
		for (unsigned int i = 0; i < information.ghost.size(); i++)
			information.ghost[i]->move(information.map);
		Player.move(information.map);
	}
}

