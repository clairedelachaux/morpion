#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "jeu.h"
#include "fenetre.h"
#define TAILLE_FENETRE 800
#define MARGE 20

/**
 * Pour installer la SDL pour CLion,
 *
 * Installer: Télécharger SDL Devel MinGW pour Windows
 *
 * Utiliser le CmakeList.txt inclus
 * Creer un dossier include/ et lib/ et copier les fichier correspondants dans l'archive
 * (ATTENTION: PRENDRE la version c)
 *
 * Copier SDL2.dll dans le /bin pour le mettre dans le cmake-build-debug/
 *
 * Recompiler le cmake
 *
 *
 */
void pause(int grille[], int point[], struct SDL_Renderer *renderer);


int main(int argc, char* argv []) {
    int grille[9] = {0,0,0,0,0,0,0,0,0}, point[8] = {0,0,0,0,0,0,0,0};
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return EXIT_FAILURE;
    }
    SDL_Window *fenetre;
    SDL_Renderer *renderer;
    SDL_Surface *icone;
    SDL_Rect cases[9];

    fenetre =SDL_CreateWindow("morpion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_FENETRE, TAILLE_FENETRE, SDL_WINDOW_SHOWN);

    if (fenetre == NULL){
        printf("La fenetre ne s'ouvre pas!");
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL){
        printf("Erreur renderer : %s", SDL_GetError());
        return  EXIT_FAILURE;
    }
    SDL_RenderClear(renderer);


    icone = SDL_LoadBMP("sdl_icone.bmp");
    SDL_SetWindowIcon(fenetre, icone);
    SDL_SetRenderDrawColor(renderer, 80, 40, 30, 255);
    casemorpion (cases, renderer, TAILLE_FENETRE);
    SDL_RenderPresent(renderer);


    pause(grille, point, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void  pause(int grille[], int point[], struct SDL_Renderer *renderer){
    int continuer = 1, sourix = 0, souriy = 0, k=0, nb=0, nbgagne = -1, nbtour = 0;
    SDL_Event event;
    srand(time(NULL));
    while (continuer){
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT :
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP :
                sourix = event.button.x;
                souriy = event.button.y;
                clicbon(sourix, souriy, grille, point, renderer, &nbgagne, &nbtour);
                if (nbgagne==-1 && nbtour<9){
                    tourordi(grille, point, renderer, &nbgagne, &nbtour);
                }else {
                    continuer = 0;
                }
                if (nbgagne!=-1 || nbtour==9){
                    continuer=0;
                }
                SDL_RenderPresent(renderer);
                break;

        }
    }
    SDL_Delay(50);
    SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
    affligne(nbgagne, renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

}

