/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.10

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


#include "Texture.h"
#include "sdl.h"

using namespace std;


Texture::Texture(SDL_Texture* image, const string& msg, unsigned int statescreen, unsigned int select, unsigned int x, unsigned int y, int w, int h)
	: _texture(image), _dst(rectangle(x,y,w,h)),_name(msg), _statescreen(statescreen), _select(select)
{
}

Texture::~Texture() {
	if (_texture != nullptr){
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}


SDL_Rect Texture::rectangle(int x, int y, int w, int h){
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	return rectangle;
}


void Texture::render(SDL_Renderer*& renderer, int x, int y) {
	if (x != -1 && y != -1) {
		_dst.x = x;
		_dst.y = y;
	}
	SDL_RenderCopy(renderer, _texture, NULL, &_dst);
}

void Texture::renderTexture(SDL_Renderer*& renderer, int x, int y) {
	render(renderer, x, y);
}

void Texture::renderTextureTestStates(SDL_Renderer*& renderer, unsigned int statescreen, int x, int y) {
	if (_statescreen == statescreen)
		render(renderer, x, y);
}

void Texture::renderTextureTestStatesAngle(SDL_Renderer*& renderer, unsigned int statescreen, int x, int y, unsigned int angle) {
	if (_statescreen == statescreen) {
		if (x != -1 && y != -1) {
			_dst.x = x;
			_dst.y = y;
		}
		SDL_RenderCopyEx(renderer, _texture, NULL, &_dst, angle, NULL, SDL_FLIP_NONE);
	}
}

void Texture::renderTextureTestString(SDL_Renderer*& renderer, const std::string& msg, int xc, int yc) {
	if (_name.compare(msg) == 0)
		render(renderer, xc, yc);
}

bool Texture::renderTextureTestStringAndStates(SDL_Renderer*& renderer, const std::string& msg, unsigned int statescreen, int xc, int yc) {
	if (_name.compare(msg) == 0 && _statescreen == statescreen){
		render(renderer, xc, yc);
		return true;
	}
	return false;	
}
bool Texture::TextureTestString(const std::string& msg) {
	if (_name.compare(msg) == 0)
		return true;
	return false;
}



void Texture::changeAlpha(Uint8 alpha) {
	if (SDL_SetTextureAlphaMod(_texture, alpha) != 0)
		logSDLError(cout, "alpha : ");
}




SDL_Texture* Texture::GETtexture() const{
	return _texture;
}
SDL_Rect Texture::GETdst()const {
	return _dst;
}
int Texture::GETdstx()const {
	return _dst.x;
}
int Texture::GETdsty()const {
	return _dst.y;
}
int Texture::GETdstw()const {
	return _dst.w;
}
int Texture::GETdsth()const {
	return _dst.h;
}
string Texture::GETname() const{
	return _name;
}
unsigned int Texture::GETstatescreen() const {
	return _statescreen;
}
unsigned int Texture::GETselect() const {
	return _select;
}


void Texture::SETdstx(int x) {
	_dst.x = x;
}
void Texture::SETdsty(int y) {
	_dst.y = y;
}
void Texture::SETdstw(int w) {
	_dst.w = w;
}
void Texture::SETdsth(int h) {
	_dst.h = h;
}

