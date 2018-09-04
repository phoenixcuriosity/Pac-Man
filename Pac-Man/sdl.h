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

#ifndef sdl_H
#define sdl_H

#include "Pac_Man_lib.h"

void logfileconsole(const std::string &msg);
void logSDLError(std::ostream &os, const std::string &msg);
void initsdl(SDL_Window*&, SDL_Renderer*&, TTF_Font*[]);
SDL_Texture* renderText(SDL_Renderer*&, const std::string&, SDL_Color, TTF_Font*);
SDL_Texture* renderTextShaded(SDL_Renderer*&, const std::string&, SDL_Color, SDL_Color, TTF_Font*);

void loadImage(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, unsigned int statescreen, unsigned int select,
	const std::string &path, const std::string &msg, Uint8 alpha, int x, int y, int cnt = 0);
void loadwritetxt(sysinfo&, std::vector<Texture*>& tabTexture, const std::string &msg, SDL_Color, int, unsigned int, unsigned int, int = 0);
void loadwritetxtshaded(sysinfo&, std::vector<Texture*>& tabTexture, const std::string &msg, SDL_Color, SDL_Color, int, unsigned int, unsigned int, int = 0);

void writetxt(sysinfo&, const std::string &msg, SDL_Color, int, unsigned int, unsigned int, int = 0);
void writetxtshaded(sysinfo&, const std::string &msg, SDL_Color, SDL_Color, int, unsigned int, unsigned int, int = 0);
void loadAndWriteImage(SDL_Renderer*&, SDL_Texture*, unsigned int, unsigned int, int = 0);
void centrage(int&, int&, int, int, int = 0);

#endif