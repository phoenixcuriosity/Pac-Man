

#ifndef deleteAll_H
#define deleteAll_H

#include "Pac_Man_lib.h"

#include "sdl.h"

void deleteAll(sysinfo&);

template<class T>
void deleteDyTabPlayerAndTextures(T& dytab, const std::string& name) {
	unsigned int size = dytab.size();
	for (unsigned int i = 0; i < size; i++) {
		logfileconsole("Delete " + name + " n:" + to_string(i) + " name = " + dytab[i]->GETname() + " Success");
		delete dytab[i];
	}
	for (unsigned int i = 0; i < size; i++)
		dytab.pop_back();
	if (dytab.size() != 0)
		logfileconsole("___________ERROR : " + name + ".size() != 0");
	else
		logfileconsole("Delete ALL " + name + " Success");
}

#endif 