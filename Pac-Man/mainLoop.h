

#ifndef mainLoop_H
#define mainLoop_H
#include "Pac_Man_lib.h"

void mainLoop(sysinfo&);
void initfile(sysinfo& information);
void calculimage(sysinfo&);
void createbutton(sysinfo&, const std::string &msg, SDL_Color, SDL_Color, int, int, int, int = 0); // parametre par defaut -> nocenter
void searchcenter(int &x, int &y, int &xc, int &yc, int iW, int iH, int centerbutton);

#endif