#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "enigme.h"

int main()
{ 

	SDL_Surface *screen ;

	enigme  e;
	 Mix_Music *musique;
Mix_Music *musique1;
	int s,r,run =1;
	char txt[30]="";
	
	 
  

	 SDL_Init ( SDL_INIT_VIDEO ) ;

	 screen= SDL_SetVideoMode(1120,630,32,SDL_HWSURFACE |  SDL_DOUBLEBUF ); 

if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
  {printf("%s",Mix_GetError()); }
	   musique=Mix_LoadMUS("mesic/begin.mp3");
		
Mix_PlayMusic(musique,-1);
         
	
   pregame(screen);
	
  
Mix_CloseAudio();


	
	

	 
	 while (run)
	 {
	 	 init_enigme(&e,"fic");


	 r=0 ;
		

         generate_afficher (screen,e) ;



     
      
printf("%d",e.l)  ;	
      s=solution_e (e.l );
      printf("%d",s)  ;	

			r=resolution (&run,&e,screen);
			printf("%d",r)  ;
			printf("\n");	

		if(run==1)	
       afficher_resultat (screen,s,r) ; 
   }

      SDL_FreeSurface(screen);
      SDL_Quit();
	return 0;
}
