#ifndef perso_H
#define perso_H
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#define SCREEN_W  1900
#define SCREEN_H 800
typedef struct
{
int val,valmax;
double vitesse,acceleration;
SDL_Rect posScreen; 
float vy,vx,pastvitesse;
int posxmin,posxmax,numberplayers,number;
//score 
int valscore;
SDL_Surface *score;
SDL_Rect posscore;
TTF_Font *font_score;
//money
SDL_Surface *money;
int valmoney;
int cureval;
SDL_Rect posmoney;
TTF_Font *font_money;
//vie personne 
SDL_Surface *vie[10];
int valvie;
SDL_Rect posvie;
TTF_Font *font_vie;
 // SDL_Color viecolor;
SDL_Rect posSprite;
float dx,dy;
int hit;
int direction,on_ground;//0droite 1 gauche 2 saut
int pastdirection,move;
SDL_Surface *imgperso;
SDL_Surface *sprite;
int up,down;
}Personne;
void kill(Personne* p,SDL_Rect posennemie ,int* vieEnnemie);
void getinput(int* run,Personne* p);

void initialiser_audio(Mix_Music **music,char nom[]);
void jouermusique(Mix_Music *music);
void liberer_musique(Mix_Music *music);
void saut_normal(Personne *p,Uint32 dt);	
void initPerso(Personne *p);		
void afficherPerso(Personne p, SDL_Surface * screen);	
float clamp(float value, float min, float max);	
void movePerso (Personne *p) ;	
void animePerso(Personne* p);		
void saut(Personne *p,int* n); 
void initialiser_audiobref(Mix_Chunk **musbref,char nom[]);
void jouermusiquebref(Mix_Chunk *musbref);
void liberer_musiquebref(Mix_Chunk *musbref);
	
#endif
