//
// Created by famille on 13/04/2020.
//

#ifndef OPENGLTEST_FENETRE_H
#define OPENGLTEST_FENETRE_H
void casemorpion (struct SDL_Rect rectangles[],struct SDL_Renderer *renderer, int taillefenetre);
void croix (struct SDL_Renderer *renderer, int i, int j);
void rectangle (struct SDL_Renderer *renderer, int i, int j);
void affligne(int k, struct SDL_Renderer *renderer);
#define TAILLE_FENETRE 800
#define MARGE 20
#endif //OPENGLTEST_FENETRE_H

