#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "fenetre.c"
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

int clicbon(int clicx, int clicy, int grille[], int point[], struct SDL_Renderer *renderer, int *gagne, int *nbtour);

void casemorpion (struct SDL_Rect rectangles[],struct SDL_Renderer *renderer, int taillefenetre);
void croix (struct SDL_Renderer *renderer, int i, int j);
void rectangle (struct SDL_Renderer *renderer, int i, int j);
void tourordi(int grille[], int point[], struct SDL_Renderer *renderer, int *gagne, int *nbtour);
int addpoint (int point[], int i, int j, int role);
int empechegagner(int point[],int grille[], struct SDL_Renderer *renderer, int *gagne);
int gagner(int point[],int grille[], struct SDL_Renderer *renderer, int *gagne);
void affligne(int k, struct SDL_Renderer *renderer);

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
int clicbon(int clicx, int clicy, int grille[], int point[], struct SDL_Renderer *renderer, int *gagne, int *nbtour){
    int i=-1, j=-1, taille_case = (TAILLE_FENETRE-2*MARGE)/3;
    clicx-=MARGE;
    clicy-=MARGE;
    i = clicx/taille_case;
    j = clicy/taille_case;
    if (i>=0 && i<3 && j>=0 && j<3) {
        if (grille[3 * i + j] == 0) {
            grille[3 * i + j] = 10;
            croix(renderer, i, j);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);
            *gagne = addpoint(point, i, j, 10);
            *nbtour+=1;;
        }
    }
}
void casemorpion (struct SDL_Rect rectangles[],struct SDL_Renderer *renderer, int taillefenetre){
    int i, j=0;
    for (i=0; i<3; i++){
        for(j=0; j<3; j++){
            rectangles[3*i+j].x = i*(taillefenetre-2*MARGE)/3+MARGE;
            rectangles[3*i+j].y = j*(taillefenetre-2*MARGE)/3+MARGE;
            rectangles[3*i+j].h = rectangles[3*i+j].w = (taillefenetre-2*MARGE)/3-2;
        }
    }
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 230, 230, 225, 255);
    SDL_RenderDrawRects(renderer, rectangles, 9);
    SDL_RenderFillRects(renderer, rectangles, 9);
}

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

void tourordi(int grille[], int point[], struct SDL_Renderer *renderer, int *gagne, int *nbtour){
    int m=0;
    if (!gagner(point, grille, renderer, gagne)){
        if (!empechegagner(point, grille, renderer, gagne)){
            while(m<9) {
                if (grille[m] == 0) {
                    grille[m] = -1;
                    rectangle(renderer, m / 3, m % 3);
                    addpoint(point, m / 3, m % 3, -1);
                    m = 10;
                }
                m += 1;
            }
        }
    }
    *nbtour+=1;
}

int addpoint (int point[], int i, int j, int role){ // role : 10 joueur, -1 ordi
    int k=-1;
    point[i]+= role;
    if (point[i]== 3*role){
        k=i;
    }
    point[j+3]+=role;
    if (point[j+3]== 3*role){
        k=3+j;
    }
    if(i==j){
        point[6] += role;
        if (point[6]== 3*role){
            k=6;
        }
    }
    if (2-i == j){
        point[7]+= role;
        if (point[7]== 3*role){
            k=7;
        }
    }
    return k;
}

int empechegagner(int point[],int grille[], struct SDL_Renderer *renderer, int *gagne){
    int joue = 0, k=0, l=0;
    while(k<8 && !joue){
        if (point[k] == 20){
            joue = 1;
            if (k<3){
                while( grille[3*k + l] == 10){
                    l++;
                }
                grille[3*k+l]=-1;
                rectangle(renderer, k, l);
                *gagne = addpoint(point, k, l, -1);
            } else if (k<6){
                while( grille[ 3*l + k - 3] == 10){
                    l++;
                }
                grille[ 3*l + k - 3] = -1;
                rectangle(renderer, l, k-3);
                *gagne = addpoint(point, l, k-3, -1);
            }
            else if (k==6){
                while (grille[3*l+l] == 10){
                    l++;
                }
                grille[3*l+l] = -1;
                rectangle(renderer, l, l);
                *gagne = addpoint(point, l, l, -1);
            }
            else {
                while (grille[3*l + 2-l] == 10){
                    l++;
                }
                grille [3*l + 2-l] = -1;
                rectangle(renderer, l, 2-l);
                *gagne = addpoint(point, l, 2-l, -1);

            }
        }
        k++;
    }
    return joue;
}

int gagner(int point[],int grille[], struct SDL_Renderer *renderer, int *gagne){
    int joue = 0, k=0, l=0;
    while(k<8 && !joue){
        if (point[k] == -2){
            joue = 1;
            if (k<3){
                while( grille[3*k + l] == -1){
                    l++;
                }
                grille[3*k+l]=-1;
                rectangle(renderer, k, l);
                *gagne = addpoint(point, k, l, -1);
            } else if (k<6){
                while( grille[ 3*l + k - 3] == -1){
                    l++;
                }
                grille[ 3*l + k - 3] = -1;
                rectangle(renderer, l, k-3);
                *gagne = addpoint(point, l, k-3, -1);
            }
            else if (k==6){
                while (grille[3*l+l] == -1){
                    l++;
                }
                grille[3*l+l] = -1;
                rectangle(renderer, l, l);
                *gagne = addpoint(point, l, l, -1);
            }
            else if (k==7){
                while (grille[3*l+2-l] == -1){
                    l++;
                }
                grille [3*l+2 - l] = -1;
                rectangle(renderer, l, 2-l);
                *gagne = addpoint(point, l, 2-l, -1);

            }
        }
        k++;
    }
    return joue;
}

void affligne(int k, struct SDL_Renderer *renderer){
    int x1, x2, y1, y2, taillecase = (TAILLE_FENETRE-2*MARGE)/3, i=0;
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