#include <iostream>
#include <vector>
#include <Windows.h>
#include <limits.h>
#include <Shlobj.h>  //getUserDir()

#ifndef _SYSINFO_H_
#define _SYSINFO_H_

extern std::vector<std::string> tiposFichero;

extern std::vector<std::string> directorioProhibido;

std::string getOsName();


std::vector<std::string> getLogicalDrives();


std::string getUserDir();

////////////////DELETERS////////////////////
void delBin();

#endif