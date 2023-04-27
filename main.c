#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "play.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#define largeur_background 1942
#define largeur_map 425

int main(int argc, char** argv)
{
    SDL_Surface* screen = NULL;
    SDL_Surface *background = NULL;
    SDL_Surface *Masque = IMG_Load("bl eg.png");
    SDL_Rect positionbackground;
    SDL_Event event;
    int boucle = 1,dir=0,i=0;
    float t_prev = 0, dt = 0;
    personne p1,p2;
    minimap map;
    TTF_Font * police =NULL ;
    Uint32 temps;
    
    
    int collision=0;
    int redimensionnement = 20;
    int direction=-1;
    int deplacement=0;
    int faster=0;
    
    
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen)
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    initPerso(&p1);
    initmap(&map);
    //initialiser_temps(&t);
    
    background = IMG_Load("eg.png");
    positionbackground.x = 0;
    positionbackground.y = 0;
    positionbackground.w = 1942;
    positionbackground.h = 840;
    police = TTF_OpenFont("avocado.ttf",70);
    SDL_EnableKeyRepeat(100,10);
    
    while (boucle)
    {
        
        t_prev = SDL_GetTicks();
        SDL_BlitSurface(background, NULL, screen, &positionbackground);
        afficherPerso(p1,screen);
        deplacement=majminimap(&p1,&map,direction,redimensionnement);
        afficherminimap(map,screen);
        affichertemp(&temps,screen,police);
        SDL_Flip(screen);
        
        //direction = Get_EventDirection(&event,&faster);
        
        int collision = collisionPP(p1,Masque);
       
             
        
        if(dir==0  )
        {
            p1.direction=2;
            animerPerso(&p1);
            SDL_Flip(screen);
            SDL_Delay(40);
            
        }
        
        
        while (SDL_PollEvent(&event))
        {
            
            switch (event.type)
            {
                case SDL_QUIT:
                    boucle = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            
                            dir=1;
                            if(p1.up==0)
                            {
                            p1.up = 1;
                            p1.posinit=p1.posScreen.y;
                            deplacement=1;
                            SDL_Flip(screen);
                           
                            }
                            
                            break;
                        case SDLK_RIGHT:
                             p1.direction = 3;
                            
		        
		         if (p1.vitesse >=0.9)
		         {
		         p1.vitesse =0.9;
		         p1.direction=1;
		         deplacement=1;
		         SDL_Flip(screen);
		         }
		         else
		        {
                         p1.acceleration +=  0.0001; 
		         p1.vitesse += p1.acceleration*dt ; 
		       
		         }
		         movePerso_right(&p1,dt);
		         SDL_Flip(screen);
		         break;

                        case SDLK_LEFT:
                            p1.direction = 3;
		        if (p1.vitesse >=0.9)
		         {
		         p1.vitesse =0.9;
		         p1.direction=1;
		         deplacement=1;
		         SDL_Flip(screen);
		         }
		         else
		         {
		         p1.acceleration +=  0.0001; 
		         p1.vitesse += p1.acceleration*dt ; 
		         }
		         movePerso_left(&p1,dt);
		         SDL_Flip(screen);
                            break; 
                          
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            dir=0; 
                            p1.vitesse=0.01;
                            p1.acceleration=0;
                            break;
                        case SDLK_UP:
                            dir=0; 
                            break;
                        case SDLK_LEFT:
                            dir=0; 
                            p1.vitesse=0.01;
                            p1.acceleration=0;
                            break;
                    }
                    break;
            }
           if (collisionPP(p1,Masque)== 1)
            {
              
                p1.vitesse = 0;
                p1.acceleration = 0;
                collision = 0;
            }
        }

        if (p1.up == 1) 
        {
                    p1.direction=0;
		p1.px=p1.posScreen.x;
		p1.py=p1.posScreen.y;
		while(p1.posRelative.x>=0 && p1.posRelative.x<=400)
		{
			saut (&p1,p1.posinit);
			animerPerso(&p1);
                              SDL_BlitSurface(background, NULL, screen, &positionbackground);
                  		afficherPerso(p1,screen);
                  		afficherminimap(map,screen);
                              SDL_Delay(5);     
                              SDL_Flip(screen);
                              
		}
		 
			p1.posRelative.x=0;
			p1.posRelative.y=0;
			p1.up=0;
			dir=0;
			
	}

        dt = (SDL_GetTicks() - t_prev) ; 
        
        SDL_Flip(screen);

    }

    liberer(&p1);
    free_minimap(map);
   // free_temps(&t, screen);
    SDL_FreeSurface(background);
    SDL_Quit();

    return 0;
}




