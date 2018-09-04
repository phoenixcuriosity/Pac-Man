/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.3

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

#include "deleteAll.h"

using namespace std;


void deleteAll(sysinfo& information){
	logfileconsole("*********_________ Start DeleteAll _________*********");

	for (unsigned int i = 1; i < 80; i++) 
		TTF_CloseFont(information.allTextures.font[i]);

	deleteDyTabPlayerAndTextures(information.allTextures.ground, "ground Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.pacman, "pacman Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.red, "red Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.blue, "blue Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.yellow, "yellow Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.pink, "pink Texture");
	deleteDyTabPlayerAndTextures(information.allTextures.txtecrantitre, "txtecrantitre Texture"); 
	deleteDyTabPlayerAndTextures(information.allTextures.txtplay, "txtplay Texture");

	deleteDyTabPlayerAndTextures(information.allButton.buttonecrantitre, "Button ecrantitre");
	deleteDyTabPlayerAndTextures(information.allButton.buttonplay, "Button play");

	SDL_DestroyRenderer(information.ecran.renderer);
	SDL_DestroyWindow(information.ecran.window);
	information.ecran.renderer = nullptr;
	information.ecran.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}