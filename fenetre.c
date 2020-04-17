#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "fenetre.h"
#define TAILLE_FENETRE 800
#define MARGE 20


void croix (struct SDL_Renderer *renderer, int i, int j){
    int x1, x2, y1, y2;
    x1 = 3*MARGE + i*TAILLE_FENETRE/3;
    x2 = -3*MARGE + (i+1)*TAILLE_FENETRE/3;
    y1 = 3*MARGE + j*TAILLE_FENETRE/3;
    y2 = -3*MARGE + (j+1)*TAILLE_FENETRE/3;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (i=1; i<7; i++){
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_RenderDrawLine(renderer, x1, y2, x2, y1);
        SDL_RenderDrawLine(renderer, x1+i, y1, x2, y2-i);
        SDL_RenderDrawLine(renderer, x1+i, y2, x2, y1+i);
        SDL_RenderDrawLine(renderer, x1, y1+i, x2-i, y2);
        SDL_RenderDrawLine(renderer, x1, y2-i, x2-i, y1);

    }
}
void rectangle (struct SDL_Renderer *renderer, int i, int j){
    int x1, x2, y1, y2;
    x1 = 3*MARGE + i*TAILLE_FENETRE/3;
    x2 = -3*MARGE + (i+1)*TAILLE_FENETRE/3;
    y1 = 3*MARGE + j*TAILLE_FENETRE/3;
    y2 = -3*MARGE + (j+1)*TAILLE_FENETRE/3;
    SDL_Rect petit = {x1 +6, y1+6, x2-x1-12, y2-y1-12}, grand= {x1, y1, x2-x1, y2-y1};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &grand);
    SDL_SetRenderDrawColor(renderer, 230, 230, 225, 255);
    SDL_RenderFillRect(renderer, &petit);

}

void affligne(int k, struct SDL_Renderer *renderer){
    int x1=0, x2=0, y1=0, y2=0, taillecase = (TAILLE_FENETRE-2*MARGE)/3, i=0;
    if (k==-1){
    }
    else if (k<3){
        x1 = x2 = MARGE + (k+0.5)*taillecase;
        y1 = MARGE + 0.5*taillecase;
        y2 = MARGE+ 2.5*taillecase;
    }
    else if (k<6){
        y1 = y2 = MARGE + (k-2.5)*taillecase;
        x1 = MARGE + 0.25*taillecase;
        x2 = MARGE+ 2.75*taillecase;
    } else if (k==6){
        y1 = x1 = MARGE + 0.25*taillecase;
        x2 = y2 = MARGE + 2.75*taillecase;
    } else {
        y2 = x1 = MARGE + 0.25*taillecase;
        x2 = y1 = MARGE + 2.75*taillecase;
    }
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    for (i=0; i<2; i++) {
        SDL_RenderDrawLine(renderer, x1-i, y1-i, x2-i, y2-i);
        SDL_RenderDrawLine(renderer, x1+i, y1+i, x2+i, y2+i);
    }
}


