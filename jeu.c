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



void tourordi(int grille[], int point[], struct SDL_Renderer *renderer, int *gagne, int *nbtour){
    int m=0, n=0;
    if (!gagner(point, grille, renderer, gagne)){
        if (!empechegagner(point, grille, renderer, gagne)){
            if (*nbtour==1){
                if (grille[4]==0){
                    rectangle(renderer, 1, 1);
                    grille[4]=-1;
                    addpoint(point, 1, 1, -1);
                }else{
                    n = rand()%4;
                    rectangle(renderer, 2*(n/2), 2*(n%2));
                    grille[6*(n/2)+2*(n%2)]=-1;
                    addpoint(point, 2*(n/2), 2*(n%2), -1);
                    }
            }else if (*nbtour==3 && grille[0]+grille[2]+grille[6]+grille[8]==20) {
                n = rand() % 4;
                rectangle(renderer, (n + 1) / 2, (4 - n) % 3);
                grille[2 * n + 1] = -1;
                addpoint(point, (n + 1) / 2, (4 - n) % 3, -1);
            } else if(*nbtour==3 && (grille[1]+grille[7]==20|| grille[3]+grille[5]==20)){
                n = rand()%4;
                rectangle(renderer, 2*(n/2), 2*(n%2));
                grille[6*(n/2)+2*(n%2)]=-1;
                addpoint(point, 2*(n/2), 2*(n%2), -1);
            }else {
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
