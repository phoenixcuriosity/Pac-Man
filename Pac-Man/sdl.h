

#ifndef sdl_H
#define sdl_H

#include "Pac_Man_lib.h"

void logfileconsole(const std::string &msg);
void logSDLError(std::ostream &os, const std::string &msg);
void initsdl(SDL_Window*&, SDL_Renderer*&, TTF_Font*[]);
SDL_Texture* renderText(SDL_Renderer*&, const std::string&, SDL_Color, TTF_Font*);
SDL_Texture* renderTextShaded(SDL_Renderer*&, const std::string&, SDL_Color, SDL_Color, TTF_Font*);

void loadImage(sysinfo&, unsigned int&, const std::string&, const std::string&, Uint8, int, int, int = 0);
void loadwritetxt(sysinfo&, const std::string &msg, SDL_Color, int, unsigned int, unsigned int, int = 0);
void loadwritetxtshaded(sysinfo&, const std::string &msg, SDL_Color, SDL_Color, int, unsigned int, unsigned int, int = 0);

void writetxt(sysinfo&, const std::string &msg, SDL_Color, int, unsigned int, unsigned int, int = 0);
void writetxtshaded(sysinfo&, const std::string &msg, SDL_Color, SDL_Color, int, unsigned int, unsigned int, int = 0);
void loadAndWriteImage(SDL_Renderer*&, SDL_Texture*, unsigned int, unsigned int, int = 0);
void centrage(int&, int&, int, int, int = 0);

#endif