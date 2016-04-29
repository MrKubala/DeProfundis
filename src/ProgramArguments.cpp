/* ProgramArguments.hpp
 * Udostepnia funkcję do pobierania argumentów programu.
 * (C) Jan Bielański 2016
 */

#ifndef __PROGRAM_ARGUMENTS_HPP__
#define __PROGRAM_ARGUMENTS_HPP__

#include "ProgramArguments.hpp"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

// Pobranie argumentów
void getArguments(int argc, char *argv[], int *win_width, int *win_height, std::string *win_name)
{
  //Domyślne parametry
  *win_width = 800; //Szerokość
  *win_height = 600; //Wysokość
  *win_name = argv[0]; //Nazwa okna = nawz programu

  //Pobranie argumentów
  if(argc > 1 && ((argc-1)%2) == 0) {
    std::string option; std::string test; std::string value; std::string::size_type string_size;
    for(int i=1; i<argc; i+=2) {
      test = argv[i];

      //Opcja 1: szerokość
      option = "-width";
      if(option.compare(test) == 0) {
	value = argv[i+1];
	*win_width = std::stoi(value,&string_size);
	continue;
      }

      //Opcja 2: wysokość
      option = "-height";
      if(option.compare(test) == 0) {
	value = argv[i+1];
	*win_height = std::stoi(value,&string_size);
	continue;
      }
      
      //Opcja 3: nazwa
      option = "-name";
      if(option.compare(test) == 0) {
	value = argv[i+1];
	*win_name = value;
	continue;
      }
    }

    if(*win_width < 1 || *win_height < 1 || win_name->empty()) {
      std::cerr<<"Wrong program arguments: win_name = "<<*win_name<<" ; win_width = "<<*win_width<<" ; win_height = "<<*win_height<<std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

#endif
