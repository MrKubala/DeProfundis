/* ProgramArguments.hpp
 * Udostepnia funkcję do pobierania argumentów programu.
 * (C) Jan Bielański 2016
 */

#ifndef __PROGRAM_ARGUMENTS_HPP__
#define __PROGRAM_ARGUMENTS_HPP__

#include <string>

// Pobranie argumentów
void getArguments(int argc, char *argv[], int *win_width, int *win_height, std::string *win_name);

#endif
