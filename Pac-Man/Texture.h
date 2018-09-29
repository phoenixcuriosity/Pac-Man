/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.13

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

#ifndef Texture_H
#define Texture_H

/*

	Texture :
	Cette classe est la repr�sentation d'un objet texture

	Une Texture est d�fini par une image contenu dans SDL_Texture*
	Le nom de la texture est le nom de l'image dans le dossier
	_statescreen permet de diff�rencier sur lequel des �crans la texture est affich�e(STATEecrantitre, STATEecrannewgame, STATEmainmap ...)
	_select permet de diff�rencier l'�tat de s�l�ction (selectnothing, NotToSelect, selectcreate, ...)




	la m�thode changeAlpha permet de changer la transparance de l'image entre 0 et 255 (255 �tant visibilit� max)

*/

#include "lib.h"

class Texture {
public:
	static SDL_Texture* renderText(SDL_Renderer*& renderer, unsigned int type,
		const std::string &message, SDL_Color color, SDL_Color colorback, TTF_Font* font);
	static void loadImage(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, unsigned int statescreen, unsigned int select,
		const std::string &path, const std::string &msg, Uint8 alpha, int x, int y, unsigned int w, unsigned int h, int cnt = 0);
	static void loadwritetxt(sysinfo& information, std::vector<Texture*>& tabTexture, unsigned int type, const std::string &msg,
		SDL_Color color, SDL_Color backcolor, unsigned int size, int x, int y, int cnt = 0);
	static void writetxt(sysinfo& information, unsigned int type, const std::string &msg, SDL_Color color,
		SDL_Color backcolor, unsigned int size, unsigned int x, unsigned int y, int cnt = 0);
	static void loadAndWriteImage(SDL_Renderer*&, SDL_Texture*, unsigned int, unsigned int, int = 0);
	static void centrage(int&, int&, int, int, int = 0);


	Texture() {};
	Texture(SDL_Texture* image, const std::string& msg, unsigned int statescreen, unsigned int select,
		unsigned int x, unsigned int y, int w, int h);
	~Texture();

	virtual void render(SDL_Renderer*&, int = -1, int = -1);
	virtual void renderTextureTestStates(SDL_Renderer*& renderer, unsigned int statescreen, unsigned int select, int x = -1, int y = -1);
	virtual void renderTextureTestStatesAngle(SDL_Renderer*& renderer, unsigned int statescreen, int xc = -1, int yc = -1, unsigned int angle = 0);
	virtual bool renderTextureTestString(SDL_Renderer*&, const std::string&, int = -1, int = -1);
	virtual bool renderTextureTestStringAndStates(SDL_Renderer*&, const std::string&, unsigned int, int = -1, int = -1);
	virtual bool TextureTestString(const std::string&);

	virtual void changeAlpha(Uint8);
	virtual void changeTextureMsg(sysinfo& information, unsigned int type, const std::string &msg,
		SDL_Color color, SDL_Color backcolor, unsigned int size, unsigned int x, unsigned int y, int cnt = 0);

	virtual SDL_Texture* GETtexture() const;
	virtual SDL_Rect GETdst()const;
	virtual int GETdstx()const;
	virtual int GETdsty()const;
	virtual int GETdstw()const;
	virtual int GETdsth()const;
	virtual std::string GETname() const;
	virtual unsigned int GETstatescreen() const;
	virtual unsigned int GETselect()const;


	virtual void SETdstx(int x);
	virtual void SETdsty(int y);
	virtual void SETdstw(int w);
	virtual void SETdsth(int h);

	SDL_Rect rectangle(int xc, int yc, int w, int h);

private:
	SDL_Texture* _texture;
	SDL_Rect _dst;
	std::string _name;
	unsigned int _statescreen;
	unsigned int _select;
};
/*

	Buttons :
	Cette classe est la repr�sentation d'un objet Buttons qui est heriti� de la classe m�re Texture

	Un Buttons est d�fini par une image et une imageOn qui sont contenu dans SDL_Texture* de la classe m�re et celle-ci
	Cet objet h�rite de tous les attributs de la classe Texture
	_txtcolor repr�sente la couleur de l'�criture
	_backcolor repr�sente la couleur du fond du bouton
	_on repr�sente l'�tat du bouton l'image est normal ou On


	searchButton permet de chercher le bouton en fonction de son nom ainsi que de l'ecran et de la position x,y
	renderButton permet d'afficher le bouton avec l'aide de la fonction de la SDL2.0.6 SDL_RenderCopy
	resetOnStatescreen permet de reset l'image si l'on n'est plus sur la bonne s�l�ction ou sur le bon �cran
	resetOnPlayer permet de reset l'image si le joueur s�l�ctionner n'est plus le meme
	changeOn permet de changer entre l'imageOn et l'image

*/
class Buttons : public Texture {
public:
	static void createbutton(sysinfo& information, std::vector<Buttons*>& tabbutton, unsigned int type, const std::string& msg,
		SDL_Color color, SDL_Color backcolor, unsigned int size, int x, int y, int centerbutton = 0);

	Buttons() {};
	Buttons(SDL_Texture* image, const std::string& msg, unsigned int statescreen, unsigned int select, int x, int y, int w, int h,
		SDL_Texture* imageOn, SDL_Color txtcolor, SDL_Color backcolor, bool on = false);
	~Buttons();

	virtual unsigned int testcolor(SDL_Color, SDL_Color) const;
	virtual unsigned int searchButton(std::string msg, unsigned int statescreen, signed int x, signed int y);
	virtual unsigned int searchButtonName(std::string& msg, unsigned int statescreen);

	virtual void resetOnStatescreen(unsigned int, unsigned int);
	virtual void resetOnPlayer(unsigned int, std::vector<std::string>);
	virtual bool renderButton(SDL_Renderer*&, unsigned int);
	virtual bool renderButtonTestString(SDL_Renderer*&, unsigned int, std::string& msg, int newx = -1, int newy = -1, int center = 0);

	virtual void changeOn();

	virtual SDL_Texture* GETimageOn() const;
	virtual SDL_Color GETtxtcolor() const;
	virtual SDL_Color GETbackcolor() const;
	virtual bool GETon() const;

	virtual void SETon(bool);

private:
	SDL_Texture* _imageOn;
	SDL_Color _txtcolor;
	SDL_Color _backcolor;
	bool _on;

};

#endif
