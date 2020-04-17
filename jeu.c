//
// Created by famille on 13/04/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL.h>
#include "fenetre.h"
#include "jeu.h"

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


void tourordi(int grille[], int point[], struct SDL_Renderer *renderer, int *gagne, int *nbtour){
    int m=0, n=0;
    if (!gagner(point, grille, renderer, gagne)){
        if (!empechegagner(point, grille, renderer, gagne)){
            n= rand()%9;
            m=(n+1)%9;
            while(m != n) {
                if (grille[m] == 0) {
                    grille[m] = -1;
                    rectangle(renderer, m / 3, m % 3);
                    addpoint(point, m / 3, m % 3, -1);
                    m = n;
                } else{
                    m =(m+1)%9;
                }
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
