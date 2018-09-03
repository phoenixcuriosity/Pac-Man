
#include "Texture.h"
#include "sdl.h"

using namespace std;


Texture::Texture(SDL_Texture* image, const string& msg, unsigned int statescreen, unsigned int select, unsigned int xc, unsigned int yc, int w, int h)
	: _texture(image), _dst(rectangle(xc,yc,w,h)),_name(msg), _statescreen(statescreen), _select(select), _xc(xc), _yc(yc), _w(w), _h(h)
{
}

Texture::~Texture() {
	if (_texture != nullptr){
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}


SDL_Rect Texture::rectangle(int xc, int yc, int w, int h){
	SDL_Rect rectangle;
	rectangle.x = xc;
	rectangle.y = yc;
	rectangle.w = w;
	rectangle.h = h;
	return rectangle;
}


void Texture::render(SDL_Renderer*& renderer, int xc, int yc) {
	if (xc != -1 && yc != -1) {
		_dst.x = xc;
		_dst.y = yc;
	}
	SDL_RenderCopy(renderer, _texture, NULL, &_dst);
}


void Texture::renderTexture(SDL_Renderer*& renderer, int xc, int yc) {
	render(renderer, xc, yc);
}

void Texture::renderTextureTestStates(SDL_Renderer*& renderer, unsigned int statescreen, unsigned int select, int xc, int yc) {
	if (_statescreen == statescreen)
		render(renderer, xc, yc);
}

void Texture::renderTextureTestString(SDL_Renderer*& renderer, const std::string& msg, int xc, int yc) {
	if (_name == msg)
		render(renderer, xc, yc);
}

bool Texture::renderTextureTestStringAndStates(SDL_Renderer*& renderer, const std::string& msg, unsigned int statescreen, int xc, int yc) {
	if (_name == msg && _statescreen == statescreen){
		render(renderer, xc, yc);
		return true;
	}
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
string Texture::GETname() const{
	return _name;
}
unsigned int Texture::GETstatescreen() const {
	return _statescreen;
}
unsigned int Texture::GETselect() const {
	return _select;
}
int Texture::GETxc() const {
	return _xc;
}
int Texture::GETyc() const {
	return _yc;
}
int Texture::GETw() const {
	return _w;
}
int Texture::GETh() const {
	return _h;
}


void Texture::SETdstx(int x) {
	_dst.x = x;
}
void Texture::SETdsty(int y) {
	_dst.y = y;
}
void Texture::SETxc(int xc) {
	_xc = xc;
}
void Texture::SETyc(int yc) {
	_yc = yc;
}
void Texture::SETw(int w) {
	_w = w;
}
void Texture::SETh(int h) {
	_h = h;
}
