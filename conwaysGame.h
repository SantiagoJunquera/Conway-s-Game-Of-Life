#ifndef CONWAYSGAME_H_INCLUDED
#define CONWAYSGAME_H_INCLUDED

#include <stdio.h>

#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL_main.h>
#endif

#include <SDL.h>

#define MUERTO 0
#define VIVO 1
#define MURIENDO 2
#define NACIENDO 3

#define _finCorrecto 0
#define _errorParametros 1
#define _errorMemDinamica 2
#define _errorSDL 3
#define _errorSDLVentana 4

//Funciones del programa
int cuentaVecinos(char* matCelulas[], const unsigned short int i, const unsigned short int j, const unsigned short int width, const unsigned short int  height);
void calculaSiguiente(char* matCelulas[], const unsigned short int width, const unsigned short int  height);
void aplicaSiguiente(char* matCelulas[], const unsigned short int width, const unsigned short int  height);

//Funciones de matriz
char** crearMatrizBidimensional(const unsigned short int width, const unsigned short int  height, const unsigned short int varSize);
void liberarMatriz(char* matCelulas[], const unsigned short int width);

//Funciones de carga
void cargarOscilador(char* matCelulas[], const unsigned short int i, const unsigned short int j);
void cargarGenShip(char* matCelulas[], const unsigned short int i, const unsigned short int j);

#endif // CONWAYSGAME_H_INCLUDED
