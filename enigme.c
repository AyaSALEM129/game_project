#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "enigme.h"




void init_enigme(enigme * e, char nomfichier[20])
{

	e->p.x=0;
	e->p.y=0;
	
	e->pv.x=75;
	e->pv.y=445;	
	
	e->pf.x=290;
	e->pf.y=445;	
	                                                                                                        
	                                                                                                       
	                                                                                                       
	
	
	int  i=0 ;
    srand(time(NULL));
	      e->l=1+rand()%6;//random number

		
	FILE* fichier = NULL;

    fichier = fopen(nomfichier, "r"); // opening a file
 
    if (fichier != NULL)
    {
        while ((fgets(e->txt, 200, fichier) != NULL)&&(i<(e->l-1)) )// parcour a file randomly and putting a sentance in a e->txt randomly
        {
     i++      ;
        }
   


        fclose(fichier);// closing the file
    }
	

 

	
	
	        e->img= IMG_Load("unnamed.gif"); // intiliazing an image 
	

}



 void generate_afficher (SDL_Surface * screen  ,  enigme e) // showing a  text
{ 

	

TTF_Font * fonttest=NULL;
SDL_Color colorCoor={255,255,255};
SDL_Surface *coordinates;
SDL_Rect coordinatespos;

TTF_Init();
coordinatespos.x=100;
coordinatespos.y=100;
fonttest=TTF_OpenFont("1.ttf",30);
coordinates=TTF_RenderText_Blended (fonttest,e.txt,colorCoor);
SDL_BlitSurface(e.img,NULL,screen,&e.p);
SDL_BlitSurface(coordinates, NULL, screen, &coordinatespos);

SDL_Flip(screen) ;                            
  
  
  
}
 

 
 
 
 int solution_e (int x)
 {
 	int solution =0 ;
 	
 	if(x==6)
 	{
     solution =1 ;
 	}
 	else  	 	if(x==1)
 	{
 		solution =2;

 	}
 	else 	 	if(x==2)
 	{
 		solution =1;	
 	}
 	else 	 	if(x==3)
 	{
 		solution =1;	
 	}
 	else 	 	if(x==4)
 	{
 		solution =2;	
 	}
 	else 	 	if(x==5)
 	{
 		solution =2;	
 	}
 	
 	
 	
 	
 	
 	return solution;
 }
 
 


int resolution (int *run ,enigme * e ,SDL_Surface *screen)
{
int runn =1 ; 
	SDL_Event event ;
  int r=0 ;
  
  
  
  

	
	while(runn)
	{
	
SDL_WaitEvent(&event);
	
	
	switch(event.type)
	{
		  case SDL_QUIT:
	
                *run = 0;
                runn=0;
				break ;

       case SDL_KEYDOWN : 
            switch( event.key.keysym.sym )
                {
			  case  SDLK_a: 
			   r= 1;
			   runn =0 ; 
			   break ;
			   case  SDLK_z :
			   r= 2;
			     runn =0 ; 
			   break;
			 
			   
			   
			   
	        }
	        
              break ; 
              
                            
                              case SDL_MOUSEBUTTONDOWN:
         if((event.button.button==SDL_BUTTON_LEFT)&&(event.button.x<e->pv.x+154&&event.button.x>e->pv.x)&&(event.button.y<e->pv.y+123&&event.button.y>e->pv.y))
{

   r= 1;
			   runn =0 ; 


}
else       if((event.button.button==SDL_BUTTON_LEFT)&&(event.button.x<e->pf.x+154&&event.button.x>e->pf.x)&&(event.button.y<e->pf.y+123&&event.button.y>e->pf.y))
{

   r= 2;
			   runn =0 ; 




}
                 
	}
	
	}

  return r ;
  
  
}




 
 void afficher_resultat (SDL_Surface * screen,int s,int r )
 {
 
 
 
SDL_Rect posbackground;
posbackground.x=posbackground.y=100;
char e[30];


 
 
 
 



	
	
	

	
	
 	if (r==s)
 	{
 	
 	
 	   for(int i=0;i<22;i++)
    

    {
        sprintf(e,"loading_t/%d.gif",i);
                SDL_BlitSurface(IMG_Load(e), NULL, screen, &posbackground);
          SDL_Flip(screen);
          SDL_Delay(100); 



}
 
 	}
 	
 	else if(r!=0)
 	
 	{
 	
 	

 	   for(int i=0;i<32;i++)
    

    {
        sprintf(e,"loading_f/%d.gif",i);
                SDL_BlitSurface(IMG_Load(e), NULL, screen, &posbackground);
          SDL_Flip(screen);
          SDL_Delay(100); 



}
 	
 	

 	
 	}

 }

void pregame(SDL_Surface*screen)
{

SDL_Surface *background;
SDL_Rect posbackground;
posbackground.x=0;
posbackground.y=0;
SDL_Event event;
char e[30];


SDL_Surface *x;


int quit = 0;









for (int i = 0; i < 440 && !quit; i++) {
    
    sprintf(e, "animation/%d.png", i);
    x = IMG_Load(e);
    SDL_BlitSurface(x, NULL, screen, &posbackground);
    
    SDL_Delay(20);
    SDL_Flip(screen);
    SDL_FreeSurface(x);

    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
           
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quit = 1;
    		
    		
                break;
            }
        }sprintf(e, "animation/%d.png", i);
    x = IMG_Load(e);
    SDL_BlitSurface(x, NULL, screen, &posbackground);
    }
}
    
    

}

 
