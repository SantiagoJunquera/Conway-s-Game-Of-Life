#include "conwaysGame.h"

void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    //2^16-1 posibilidades con unsigned short int, mas que suficiente
    unsigned char done;
    unsigned short int width = 0, height = 0, skip = 0, delay = 100, contador = 0;
    //primeros dos parametros si o si deben ser estos
    if(argc > 2){
        sscanf(argv[1], "%hu", &width);
        sscanf(argv[2], "%hu", &height);
    }
    else{
        printf("Argumentos no suficientes para comenzar el programa.");
        return _errorParametros;
    }
    //parametros opcionales, sino funciona por default
    if( argc > 4){
        sscanf(argv[3], "%hu", &skip);
        sscanf(argv[4], "%hu", &delay);
    }
    //matriz dinamica bidimensional char, ahorramos casteos si fuese void
    char** matCelulas = crearMatrizBidimensional(width, height, sizeof(char));
    if(!matCelulas){
        printf("Error al asignar memoria dinamica.");
        return _errorMemDinamica;
    }

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event e;
    SDL_Rect fillRect;
    //revisar problemas primera pos
    cargarGenShip(matCelulas, 1, 1);
    cargarOscilador(matCelulas, 41, 21);
    cargarOscilador(matCelulas, 41, 36);
    cargarOscilador(matCelulas, 41, 51);
    cargarOscilador(matCelulas, 41, 66);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return _errorSDL;
    }

    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                width*10,
                                                height*10,
                                                SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return _errorSDLVentana;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return _errorSDLVentana;
    }

    while (!done) {
        int i=0, j=0;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                done = 1;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        calculaSiguiente(matCelulas, width, height);

        for(i = 0; i<width; i++) {
            for(j = 0; j<height; j++) {

                if(matCelulas[i][j] != MUERTO) {
                    fillRect.x = (i*10);
                    fillRect.y = (j*10);
                    fillRect.h = 3;
                    fillRect.w = 3;
                }

                if(matCelulas[i][j] == VIVO) {
                    fillRect.h = 10;
                    fillRect.w = 10;
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                }
                if(matCelulas[i][j] == MURIENDO)
                    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
                if(matCelulas[i][j] == NACIENDO)
                    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x40);

                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
        SDL_RenderPresent(renderer);
        contador++;

        char aux[40] = "";
        char num[10] = "";

        sprintf(num, "%d", contador);
        strcat(aux, "Juego de la vida ");
        strcat(aux, num);
        SDL_SetWindowTitle(window, aux);
        if(skip < contador)
            SDL_Delay(delay);

        aplicaSiguiente(matCelulas, width, height);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    liberarMatriz(matCelulas, width);

    return _finCorrecto;
}


