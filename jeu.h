//
// Created by famille on 14/04/2020.
//

#ifndef OPENGLTEST_JEU_H
#define OPENGLTEST_JEU_H
int clicbon(int clicx, int clicy, int grille[], int point[], struct SDL_Renderer *renderer, int *gagne, int *nbtour);
void casemorpion (struct SDL_Rect rectangles[],struct SDL_Renderer *renderer, int taillefenetre);
void tourordi(int grille[], int point[], struct SDL_Renderer *renderer, int *gagne, int *nbtour);
int addpoint (int point[], int i, int j, int role);
int empechegagner(int point[],int grille[], struct SDL_Renderer *renderer, int *gagne);
int gagner(int point[],int grille[], struct SDL_Renderer *renderer, int *gagne);
#endif //OPENGLTEST_JEU_H


