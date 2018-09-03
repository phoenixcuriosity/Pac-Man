/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:0.7

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

/*

	Texture : 
	Cette classe est la repr�sentation d'un objet texture

	Une Texture est d�fini par une image contenu dans SDL_Texture*
	Le nom de la texture est le nom de l'image dans le dossier
	_statescreen permet de diff�rencier sur lequel des �crans la texture est affich�e(STATEecrantitre, STATEecrannewgame, STATEmainmap ...)
	_select permet de diff�rencier l'�tat de s�l�ction (selectnothing, NotToSelect, selectcreate, ...)
	_xc et _yc sont la position de la texture:
			les options nocenter, center_x, center_y et center permettent de changer l'affectation de xc et yc
			si center alors xc et yc repr�sentent le milieu le point milieu de l'image
			si nocenter alors xc et yc repr�sentent le coin haut gauche de l'image
	_w et _h repr�sente la hauteur et la largeur de l'image sur l'ecran



	la m�thode changeAlpha permet de changer la transparance de l'image entre 0 et 255 (255 �tant visibilit� max)
	
*/

#ifndef Texture_H
#define Texture_H

#include "LIB.h"

class Texture{
public:
	Texture(){};
	Texture(SDL_Texture*, const std::string&, unsigned int, unsigned int, unsigned int, unsigned int, int, int);
	~Texture();

	virtual void render(SDL_Renderer*&, int = -1, int = -1);
	virtual void renderTexture(SDL_Renderer*&, int = -1, int = -1);
	virtual void renderTextureTestStates(SDL_Renderer*&,unsigned int, unsigned int, int = -1, int = -1);
	virtual void renderTextureTestString(SDL_Renderer*&, const std::string&, int = -1, int = -1);
	virtual bool renderTextureTestStringAndStates(SDL_Renderer*&, const std::string&, unsigned int, int = -1, int = -1);

	virtual void changeAlpha(Uint8);

	virtual SDL_Texture* GETtexture() const;
	virtual SDL_Rect GETdst()const;
	virtual std::string GETname() const;
	virtual unsigned int GETstatescreen() const;
	virtual unsigned int GETselect()const;
	virtual int GETxc() const;
	virtual int GETyc() const;
	virtual int GETw() const;
	virtual int GETh() const;

	virtual void SETdstx(int x);
	virtual void SETdsty(int y);
	virtual void SETxc(int xc);
	virtual void SETyc(int yc);
	virtual void SETw(int w);
	virtual void SETh(int h);

	SDL_Rect rectangle(int xc, int yc, int w, int h);

private:
	SDL_Texture* _texture;
	SDL_Rect _dst;
	std::string _name;
	unsigned int _statescreen;
	unsigned int _select;
	int _xc;
	int _yc;
	int _w;
	int _h;
};



#endif

