/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.2

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

#ifndef keyboardAndMouse_H
#define keyboardAndMouse_H

#include "Pac_Man_lib.h"
#include "sdl.h"

void keySDLK_UP(sysinfo& information);
void keySDLK_DOWN(sysinfo& information);
void keySDLK_RIGHT(sysinfo& information);
void keySDLK_LEFT(sysinfo& information);
void mouse(sysinfo&, SDL_Event event);
void cliqueGauche(sysinfo&, SDL_Event event);



#endif