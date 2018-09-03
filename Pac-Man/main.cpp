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

#include "lib.h"
#include "Pac_Man_lib.h"
#include "mainLoop.h"
#include "renduecran.h"
#include "sdl.h"
#include "deleteAll.h"

int main(int argc, char** argv) {
	sysinfo information;

	srand((unsigned int)time(NULL));


	initsdl(information.ecran.window, information.ecran.renderer, information.allTextures.font);
	initfile(information);

	logfileconsole("________PROGRAMME START________");

	calculimage(information);

	ecrantitre(information);

	mainLoop(information);


	deleteAll(information);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	logfileconsole("SDL_Quit Success");
	logfileconsole("________PROGRAMME FINISH________");
	return 0;
}