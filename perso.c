#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "perso.h"
#include <SDL/SDL_image.h>
#include <math.h>
#include "background.h"

void initPerso(Personne *p)
{
p->pastvitesse=0;
p->on_ground=1;
p-> posScreen.y=560;
p-> posScreen.w=1500/12;
p-> posScreen.h=2000/12;
p-> posSprite.x=0;
p-> posSprite.y=0;
if(p->numberplayers==1)
{
p-> posScreen.x=0;
p->posxmax=SCREEN_W;
p->posxmin=0;
 p->posmoney.x=1400;
 p->posmoney.y=20;
p->posvie.x=1550;
     p->posvie.y=20;
p->posscore.x=1300;
p->posscore.y=20;
}
if(p->numberplayers==2){
if(p->number==1)
	{
p->posvie.x=700;
p->posscore.x=460;
p->posscore.y=100;
     p->posvie.y=100;
		p-> posScreen.x=0;
		p->posxmax=SCREEN_W/2;
		p->posxmin=0;
		 p->posmoney.x=580;
                  p->posmoney.y=105;
	}
if(p->number==2)
	{
p->posvie.x=1600;
     p->posvie.y=100;
p->posscore.x=1370;
p->posscore.y=100;
		p-> posScreen.x=SCREEN_W/2;
		p->posxmax=SCREEN_W;
		p->posxmin=SCREEN_W/2;
	 p->posmoney.x=1480;
 p->posmoney.y=105;
	}
}
p->score=IMG_Load("score.png");
p->down=0;
p->cureval=0;
p->hit=0;
p->valmoney=0;
p->pastdirection=0;
p-> posSprite.w=1500/6;
p-> posSprite.h=2000/8;
p->imgperso = IMG_Load("perso.png");
p->vitesse=0;
p->acceleration=0.0004;
p->up=0;
p->money=IMG_Load("money.png");
p->valscore=0;
p->valvie=7;
for(int i=0; i<7; i++)
{
    char ch[20]; 
    strcpy(ch,"vie");
    sprintf(ch+3, "%d", i+1); 
    strcat(ch,".png");
    p->vie[i]=IMG_Load(ch); 
}
     
}

void afficherPerso(Personne p, SDL_Surface * screen)
{
  SDL_BlitSurface(p.imgperso,&p.posSprite,screen,&p.posScreen);
  SDL_BlitSurface(p.money,NULL,screen,&p.posmoney);
  SDL_BlitSurface(p.vie[7-p.valvie],NULL,screen,&p.posvie);
  SDL_BlitSurface(p.score,NULL,screen,&p.posscore);
}

float clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}


void movePerso (Personne *p) 
{
float dt=100;
p->pastvitesse=p->vitesse;
  if(p->posScreen.x>=p->posxmin && p->posScreen.x<p->posxmax-p-> posSprite.w  )
     {
          if(p->move)
             {
		p->vitesse+=p->acceleration*dt;
	     }
           else
	     {
	  	p->vitesse-=p->acceleration*dt+0.07;
             }
          
          p->vitesse = clamp(p->vitesse, 0, 0.8);
if(0<p->vitesse-0.8&& p->vitesse-0.8<0.1)p->valscore+=1;

if( p->vy>0 &&p->down==0 ) p->down=1;
          if(p->direction==0 && (p->posScreen.x<=p->posxmax/2 || p->val>=p->valmax-p->valmax/5))
            {		
		    p->posScreen.x+=p->vitesse*dt+50;
                  p->dx=p->vitesse*dt;
                   
           }
            if(p->direction==1 && (p->posScreen.x>=p->posxmax/3 || p->val==0))
	   {

                    p->posScreen.x-=p->vitesse*dt;
	    }
  
     }
p->posScreen.x = clamp(p->posScreen.x, p->posxmin, p->posxmax-p-> posSprite.w-1);
}

void saut(Personne *p,int* n)
{


(*n)++;
float dt=2;
 const float GRAVITY = 2.0f;//lower
 const float JUMP_VELOCITY = -35.0f; 
const float JUMP_VELOCITx = 20.0f; 
    if (p->on_ground ) {
        p->vy = JUMP_VELOCITY;
        p->on_ground = 0;
    }

if((p->posScreen.x+(int)p->vx * dt + 0.5f * GRAVITY * dt * dt-40<=p->posxmax-p->posxmax/3 &&p->pastdirection==0)||  (p->posScreen.x+(int)p->vx * dt + 0.5f * GRAVITY * dt * dt-40>=p->posxmin+p->posxmax/5 &&p->pastdirection) )
{
p->vx=0.0f;
     if(0<p->vitesse && p->vitesse<=0.2)
		{
			p->vx=10.0f;
		}
     else{if(p->vitesse>0.3)p->vx=JUMP_VELOCITx;
}
if(p->pastdirection && p->vx-0.0f> 0.00001f )
    {

p->posScreen.x -= (int)p->vx * dt + 0.5f * GRAVITY * dt * dt;}
else
	{
    	if(p->vx-0.0f> 0.00001f )
              { p->posScreen.x += (int)p->vx * dt + 0.5f * GRAVITY * dt * dt-10;
               p->dx=(int)p->vx * dt + 0.5f * GRAVITY * dt * dt;}
	}
}

    p->posScreen.y +=(int) p->vy * dt + 0.5f * GRAVITY * dt * dt;

    p->vy += GRAVITY * dt;
if(p->vy>=0 && p->down==0) p->down=1;
    if (p->posScreen.y > 560  ) {
        p->posScreen.y = 560;
        p->vy = 0;
        (*n)=0;
p->down=0;
p->valscore+=3;
        p->on_ground = 1;
       p->up=0;
    }

}


void animePerso(Personne* p)
{
p-> posSprite.y=(p->direction)*p-> posSprite.h;
if(p-> posSprite.x<1100-1100/5 && (p->move|| p->up ||p->hit))
{p-> posSprite.x+=p-> posSprite.w;}
else{p-> posSprite.x=0;}
}

void kill(Personne* p,SDL_Rect posennemie ,int* vieEnnemie)
{
if((0<posennemie.x-p->posScreen.x-p->posScreen.w && posennemie.x-p->posScreen.x-p->posScreen.w<150 && p->pastdirection==0 )||(0<p->posScreen.x-posennemie.w-posennemie.x&& p->posScreen.x-posennemie.w-posennemie.x<150 && p->pastdirection==1 ))
{(*vieEnnemie)--;p->valscore+=7;}
}

void initialiser_audiobref(Mix_Chunk **musbref,char nom[])
{
//load music file
  (*musbref) = Mix_LoadWAV(nom);
  if((*musbref)== NULL){
    printf("Error:%s\n", Mix_GetError());
    exit(1);
  }
}
void jouermusiquebref(Mix_Chunk *musbref)
{
//play music
  if(Mix_PlayChannel(-1, musbref, 0) == -1){
    printf("Error:  %s\n", Mix_GetError());
    exit(1);
  }
}
void liberer_musiquebref(Mix_Chunk *musbref){
Mix_FreeChunk(musbref);
}


void initialiser_audio(Mix_Music **music,char nom[])
{
//load the music file
(*music) = Mix_LoadMUS(nom);
  if (music == NULL) {
    printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    exit(1);
  }
}
void jouermusique(Mix_Music *music)
{
// Play the music
  if (Mix_PlayMusic(music, -1) == -1) {
    printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
    exit(1);
  }
}
void liberer_musique(Mix_Music *music){
Mix_FreeMusic(music);
}

