#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "background.h"
#include "perso.h"
#include "enemy.h"
#include "enigme.h"
#include "minimap.h"
#include "gain.h"
int main(int argc, char* argv[]){
Uint32 dt, t_prev;
SDL_Surface *Masque = IMG_Load("idk_masque.png"),*masque2= IMG_Load("idk_masque.png");
minimap m,m2;
int redimensionnement = 8,d=0,d2=0;
double a;
Mix_Chunk *jumpup,*jumpdown,*runvoice ;
Mix_Music *music_game;
SDL_Surface *screen;
SDL_Event event;
int first=1, x=-5,n=0,n2=0,boucle=1,running =1,move=0;
Personne p,p2;
Background B,B2, Back [20];
char ch[10];
Image money[7],money2[7];
int c1=0,c2=0;
input in,in2;
Text moneytext,money2text,scoretext,scoretext2;
int hitn=0,hitn2=0;
char moneychar[10],money2char[10],scorechar[100],scorechar2[100];
int c;
int click=1,click2=1;
int FPS =30;
enemie en,en2;
Uint32 start, end;
int colisiongain[7],colisiongain2[7];
int firstenigme=1,firstenigme2=1;
Enigme e,e2;
int scene = 1;
p.numberplayers=1;
int ondisplayenigme=0,ondisplayenigme2=0;
Image  gift1;
Uint32 temps;

// Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO|SDL_INIT_TIMER) < 0) {
    printf( "Unable to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
// Initialize SDL_mixer library
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2040) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    return 1;
  }
 // Set the video mode
  screen = SDL_SetVideoMode((SCREEN_W), (SCREEN_H), 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (screen == NULL) {
    fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
    exit(1);
  }
p.number=1;
e.numberplayers=p.numberplayers;
e.number=1;
initPerso(&p);
B.numberplayers=p.numberplayers;
initialiser_audiobref(&jumpup,"jumpup.wav");
initialiser_audiobref(&jumpdown,"jumpdown.wav");
initialiser_audiobref(&runvoice,"running.wav");
initialiser_audio(&music_game,"musique.mp3");
B.number=1;
initBackground(&B);
m.numberplayers=p.numberplayers;
m.number=1;
initmap(&m);
initimage(&money[0], "money.png",1000,300,0,0,"money");
initimage(&money[1], "money.png",1050,400,0,0,"money");
initimage(&money[2], "money.png",1100,500,0,0,"money");
initimage(&money[3], "money.png",1150,400,0,0,"money");
initimage(&money[4], "money.png",1800,400,0,0,"money");
initimage(&money[5], "cure.png",2000,400,0,0,"cure");
initimage(&money[6], "cure.png",2200,400,0,0,"cure");
initimage(&gift1, "gift1.png" ,600,670,0,0,"gift");
genererEnigme(&e,"questions.txt", "reponses.txt", "vraireponses.txt");
initText(&moneytext);
initText(&scoretext);
jouermusique(music_game);
en.numberplayers=1;
en.number=1;
initennemi(&en);
animerennemi(&en);
if(p.numberplayers==2)
{
e2.numberplayers=2;e2.number=2;
p2.numberplayers=2;
initBackground(&B2);
B2.number=2;
p2.number=2;
initPerso(&p2);
m2.numberplayers=p.numberplayers;
m2.number=2;
initmap(&m2);
initimage(&money2[0], "money.png",1800,300,0,0,"money");
initimage(&money2[1], "money.png",1850,400,0,0,"money");
initimage(&money2[2], "money.png",1800,500,0,0,"money");
initimage(&money2[3], "money.png",1850,400,0,0,"money");
initimage(&money2[4], "money.png",2400,400,0,0,"money");
initimage(&money2[5], "cure.png",2600,400,0,0,"cure");
initimage(&money2[6], "cure.png",2900,400,0,0,"cure");
initText(&money2text);
initText(&scoretext2);
genererEnigme(&e2,"questions.txt", "reponses.txt", "vraireponses.txt");
en2.numberplayers=2;  
en2.number=1;
initennemi(&en2);
animerennemi(&en2);
}
while(boucle)
{
d=0;
t_prev=SDL_GetTicks();

if((collisionBB(p.posScreen,gift1.pos1)||p.posScreen.x>=gift1.pos1.x) && firstenigme) 
{
Display_Enigme(&e, screen);
ondisplayenigme=1;
}
else {afficherBack (B,screen);
if(B.anim!=1){animation(&B, screen) ;}
if(gift1.pos1.x<=p.posxmax &&  gift1.pos1.x>=p.posxmin )
{afficher(gift1,screen);}
scrolling(&B,p,&in,&en,money);
afficherminimap(m, screen);
 affichertemps (&temps,screen);
d= majminimap ( p.posScreen, &m ,B.camera, redimensionnement);
 if (collisionPP(p,Masque)== 1)
            {
              
                p.vitesse = 0;
                p.acceleration = 0;
                
            }

for(int i=0;i<7;i++){
if(colisiongain[i]==0 && money[i].pos1.x<=p.posxmax &&  money[i].pos1.x>=p.posxmin )
{
afficher(money[i],screen);
colisiongain[i]=collisionBBgain(p.posScreen, money[i].pos1) ;
if(colisiongain[i]==1){
if(strcmp(money[i].type,"money")==0)
p.valmoney++;
else p.cureval++;
}
}
}
sprintf(scorechar, "%d", p.valscore);
sprintf(moneychar, "%d", p.valmoney);
strcat(moneychar,"x");
if(p.numberplayers==1){displayText(moneytext,screen,1470,40,moneychar);displayText(scoretext,screen,1350,40,scorechar);}
else  {displayText(moneytext,screen,650,130,moneychar);displayText(scoretext,screen,500,120,scorechar);}
if(en.vieEnnemie>=0)
{
if(en.vieEnnemie>0)
moveen(&en);
animerennemi(&en);
SDL_Delay(50);}

c=collisionBB(p.posScreen,en.postScreen);
if(c==1)
{
p.valvie--;
}
if(en.postScreen.x<p.posxmax && en.postScreen.x>p.posxmin )
  afficherennemi(&en,screen);

if(p.hit)
{animePerso(&p);
hitn++;
SDL_Delay(50);
if(hitn==5){hitn=0;p.hit=0; kill(&p,en.postScreen ,&en.vieEnnemie);}
}
if(p.valvie==0) boucle=0;
afficherPerso(p, screen);
if(p.up==1 )
{
if(n==0)
{
jouermusiquebref(jumpup);
}
saut(&p,&n);
animePerso(&p);
SDL_Flip(screen);
if(!p.up)
jouermusiquebref(jumpdown);
SDL_Flip(screen);
}
if((p.move ||p.vitesse>0) && !p.up)
{
p.val=B.camera.x;
p.valmax=B.BgImg->w;
p.val=B.camera.x;
p.valmax=B.BgImg->w;
movePerso (&p);
animePerso(&p);
SDL_Flip(screen);
SDL_Delay(50);
}
}
if(p.numberplayers==2)
{
if(p2.posScreen.x>=1004 && B2.camera.x >=2040 && firstenigme2) 
{

Display_Enigme(&e2, screen);
ondisplayenigme2=1;
}
else{
afficherBack (B2,screen);
scrolling(&B2,p2,&in2,&en2,money2);
d2= majminimap ( p2.posScreen, &m2 ,B2.camera, redimensionnement);
 afficherminimap(m2, screen);
for(int i=0;i<7;i++){
if(colisiongain2[i]==0 && money2[i].pos1.x<=p2.posxmax &&  money2[i].pos1.x>=p2.posxmin)
{
afficher(money2[i],screen);
colisiongain2[i]=collisionBBgain(p2.posScreen, money2[i].pos1) ;
if(colisiongain2[i]==1){
if(strcmp(money2[i].type,"money")==0)
p2.valmoney++;
else p2.cureval++;
}
}
}
sprintf(money2char, "%d", p2.valmoney);
strcat(money2char,"x");
displayText(money2text,screen,1550,130,money2char);
;displayText(scoretext2,screen,1400,120,scorechar);
if(en2.vieEnnemie>=0)
{
if(en2.vieEnnemie>0)
moveen(&en2);
animerennemi(&en2);
SDL_Delay(50);
}
c2=collisionBB(p2.posScreen,en2.postScreen);
if(c2==1)
{
p2.valvie--;
}
if(en2.postScreen.x<=p2.posxmax && en2.postScreen.x>=p2.posxmin )
  afficherennemi(&en2,screen);



if(p2.hit)
{animePerso(&p2);
hitn2++;
SDL_Delay(50);
if(hitn2==5){hitn2=0;p2.hit=0; kill(&p2,en2.postScreen ,&en2.vieEnnemie);}
}
if(p2.valvie==0) {boucle=0;void bestScore("score.txt", p2.scoreval);}
afficherPerso(p2, screen);
if(p2.up==1 )
{
if(n2==0)
{
jouermusiquebref(jumpup);
}
saut(&p2,&n2);
animePerso(&p2);
SDL_Flip(screen);
if(!p2.up)
jouermusiquebref(jumpdown);
SDL_Flip(screen);
}
if((p2.move ||p2.vitesse>0) && !p2.up)
{
p2.val=B2.camera.x;
p2.valmax=B2.BgImg->w;
movePerso (&p2);

animePerso(&p2);
SDL_Flip(screen);
SDL_Delay(50);
}}
	}


	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE: 
			                       boucle =0;
                        			exit(0);
                    				break;
					case SDLK_RIGHT:
jouermusiquebref(runvoice);
click=1;
						in.right=1;
						p.move=1;
                                                p.pastdirection=0;
                                                p.direction=0;
						//n=0;
					break;
					case SDLK_d:
						jouermusiquebref(runvoice);
						click2=1;
						in2.right=1;
						p2.move=1;
                                                p2.pastdirection=0;
                                                p2.direction=0;
					break;
					case SDLK_LEFT: 
jouermusiquebref(runvoice);		
click=2;
						in.left=1;
						p.move=1;
                                                p.pastdirection=1;
                                                p.direction=1;
						//n=0;	
					break;
					case SDLK_q:
						jouermusiquebref(runvoice);		
						click2=2;
						in2.left=1;
						p2.move=1;
                                                p2.pastdirection=1;
                                                p2.direction=1;

					break;
					case SDLK_DOWN:
						in.down=1;
						break;
					case SDLK_UP:
						//first=1;
						in.up=1;
						if(p.pastdirection==0)					
						{p.direction=2;}
						if(p.pastdirection==1)
						p.direction=3;
						p.up=1;
						
					break;
					case SDLK_z:
						in2.up=1;
						if(p2.pastdirection==0)					
						{p2.direction=2;}
						if(p2.pastdirection==1)
						p2.direction=3;
						p2.up=1;
					break;
				case SDLK_SPACE:
						if(p.pastdirection==0)					
						p.direction=4;
						if(p.pastdirection==1) p.direction=5;
						p.hit=1;
                                        break;
				case SDLK_x:
						if(p2.pastdirection==0)					
						p2.direction=4;
						if(p2.pastdirection==1) p2.direction=5;
						p2.hit=1;
                                        break;
				}
			break;
			 case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_RIGHT: 
Mix_HaltChannel(-1);			
						p.move=0;
						in.right=0;
						
					break;
					case SDLK_d: 
Mix_HaltChannel(-1);			
						p2.move=0;
						in2.right=0;
						
					break;
					case SDLK_LEFT: 
Mix_HaltChannel(-1);
						p.move=0;
						in.left=0;
							
					break;
					case SDLK_q: 
Mix_HaltChannel(-1);
						p2.move=0;
						in2.left=0;
							
					break;
					case SDLK_UP:
						in.up=0;
						break;
					case SDLK_z:
						in2.up=0;
						break;
					case SDLK_DOWN:
						in.down=0;
						break;
					
					
				}
			break;
case SDL_MOUSEMOTION:
{

				if (event.motion.x > 390 && event.motion.x < 733 && event.motion.y > 145 && event.motion.y < 229 && ondisplayenigme )
				{
					e.image_courrante = 1;
					
					break;
				}
				else if (event.motion.x > 390 && event.motion.x < 733 && event.motion.y > 290 && event.motion.y < 364 && ondisplayenigme)
				{
					e.image_courrante = 2;
					
					break;
				}
				else if (event.motion.x > 390 && event.motion.x<733 && event.motion.y>421 && event.motion.y<506 && ondisplayenigme)
				{
					e.image_courrante=3;
					
break;
				}
                                else
                                     e.image_courrante = 0;
 if (event.motion.x > 990 && event.motion.x < 1330 && event.motion.y > 145 && event.motion.y < 229 && ondisplayenigme2 )
				{
					e2.image_courrante = 1;
					
					break;
				}
				else if (event.motion.x > 990 && event.motion.x < 1330 && event.motion.y > 290 && event.motion.y < 364 && ondisplayenigme2)
				{
					e2.image_courrante = 2;
					
					break;
				}
				else if (event.motion.x > 990 && event.motion.x < 1330 && event.motion.y>421 && event.motion.y<506 && ondisplayenigme2)
				{
					e2.image_courrante=3;
					
					break;
				}
                                else
                                     e2.image_courrante = 0;

				break;
			}
      break;
case SDL_MOUSEBUTTONUP:
			{

				if (event.motion.x > 390 && event.motion.x < 733 && event.motion.y > 145 && event.motion.y < 229 && ondisplayenigme )
				{
					e.image_courrante = 1;
					if (event.button.button == SDL_BUTTON_LEFT)
					{        
						 VerifierEnigme(&e, screen);
ondisplayenigme=0;
firstenigme=0;
					}
					break;
				}
				else if (event.motion.x > 390 && event.motion.x < 733 && event.motion.y > 290 && event.motion.y < 364 && ondisplayenigme)
				{
					e.image_courrante = 2;
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						 VerifierEnigme(&e,screen);
ondisplayenigme=0;
firstenigme=0;
					}
					break;
				}
				else if (event.motion.x > 390 && event.motion.x<733 && event.motion.y>421 && event.motion.y<506 && ondisplayenigme)
				{
					e.image_courrante=3;
					if (event.button.button==SDL_BUTTON_LEFT)
					{
						 VerifierEnigme(&e, screen);
ondisplayenigme=0;
firstenigme=0;
					}
break;
				}
                                else
                                     e.image_courrante = 0;
 if (event.motion.x > 990 && event.motion.x < 1330 && event.motion.y > 145 && event.motion.y < 229 && ondisplayenigme2 )
				{
					e2.image_courrante = 1;
					if (event.button.button == SDL_BUTTON_LEFT)
					{        
						 VerifierEnigme(&e2, screen);
ondisplayenigme2=0;
firstenigme2=0;
					}
					break;
				}
				else if (event.motion.x > 990 && event.motion.x < 1330 && event.motion.y > 290 && event.motion.y < 364 && ondisplayenigme2)
				{
					e2.image_courrante = 2;
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						 VerifierEnigme(&e2,screen);
ondisplayenigme2=0;
firstenigme2=0;
					}
					break;
				}
				else if (event.motion.x > 990 && event.motion.x < 1330 && event.motion.y>421 && event.motion.y<506 && ondisplayenigme2)
				{
					e2.image_courrante=3;
					if (event.button.button==SDL_BUTTON_LEFT)
					{
						 VerifierEnigme(&e2, screen);
ondisplayenigme2=0;
firstenigme2=0;
					}
					break;
				}
                                else
                                     e2.image_courrante = 0;

				break;
			}
			case SDL_QUIT:
				boucle=0;
			break;
		}
		SDL_Flip(screen);
	}
SDL_Flip(screen);
dt=SDL_GetTicks()-t_prev;
	//à la fin de la boucle de jeu
}
free_minimap(m);

return 0;}
