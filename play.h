#ifndef MENU_H
#define MENU_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <time.h>
#define SCREEN_W 1942
#define SCREEN_H 840
#define GRAVITY 9.81 

typedef struct
{
 SDL_Surface *sprite;
 SDL_Rect posScreen;
 SDL_Rect posSprite;
 SDL_Rect posRelative;
 int direction,up,px,py,posinit;
 double vitesse,   acceleration;
}personne;

typedef struct
{
	SDL_Rect position_mini;
	SDL_Surface *sprite;
	SDL_Surface *dot;
	SDL_Rect posdot;
	int deplacement;
} minimap;


	
void initPerso(personne *p1);	
	
		
void movePerso_right (personne *p, Uint32 dt);
void movePerso_left (personne *p, Uint32 dt);

void saut(personne *p,int posinit);	
void animerPerso (personne* p);


void afficherPerso(personne p, SDL_Surface * screen);
void liberer(personne *p);
///minimap

void initmap(minimap *m);
void afficherminimap(minimap m, SDL_Surface *screen);
void free_minimap(minimap m);
int majminimap (personne *p, minimap *m ,int camera ,int redimensionnement);

SDL_Color GetPixel(SDL_Surface *Background, int x, int y);
int collisionPP(personne p, SDL_Surface *Masque);

void affichertemp (Uint32 *temps,SDL_Surface *screen,TTF_Font *police);
//void afficher_temps(temps *t, SDL_Surface *ecran);


#endif
