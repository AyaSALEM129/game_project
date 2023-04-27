#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "play.h"
	
void initPerso(personne* p1)
{
    p1->sprite = IMG_Load("css_sprites(2).png");
    if (p1->sprite == NULL)
    {
        printf("Unable to load sprite: %s\n", IMG_GetError());
        return;
    }

    p1->posSprite.x = 0;
    p1->posSprite.y = 0;
    p1->posSprite.w = 4784/16;
    p1->posSprite.h = 960/4;

    p1->posScreen.x = 49.275;
    p1->posScreen.y = 670;
    
    p1->vitesse=0.01; 
    p1->acceleration=0;
    p1->up=0;

}


void afficherPerso(personne p, SDL_Surface* screen)
{
    SDL_BlitSurface(p.sprite, &p.posSprite, screen, &p.posScreen);
}

void saut(personne* p,int posinit) 
 {
    if (p->up == 1) {
        
        //SDL_Delay(5);
   	p->posRelative.x+=20;
	p->posRelative.y= (-0.001) * p->posRelative.x * p->posRelative.x+150;
        //SDL_Delay(5);
       	p->posScreen.x=p->px + p->posRelative.x+100;
        if(p->posinit >= p->py - p->posRelative.y)
		p->posScreen.y=p->py - p->posRelative.y;
        else
         	p->posScreen.y=p->posinit;  

    }
    
}

void animerPerso(personne* p)
{
    int largeurSprite = 4784;
    int hauteurSprite = 960;

    if (p->posSprite.x == largeurSprite - p->posSprite.w)
    {
        p->posSprite.x = 0;
    }
    else
    {
        p->posSprite.x += p->posSprite.w;
    }

    p->posSprite.y = p->posSprite.h * p->direction;
}


void movePerso_right (personne *p, Uint32 dt)
{
    double dx;
    dx=1/2*(p->acceleration)*dt*dt+p->vitesse * dt;
    p->posScreen.x=p->posScreen.x + dx;

    animerPerso(p);
}

void movePerso_left (personne *p, Uint32 dt)
{
    double dx;
    dx=1/2*(p->acceleration)*dt*dt+p->vitesse * dt;
    p->posScreen.x=p->posScreen.x -dx;

    animerPerso(p);
}
void liberer(personne *p)
{
    SDL_FreeSurface(p->sprite);
}

///minimap
void initmap(minimap *m)
{
    m->position_mini.x = 0;
    m->position_mini.y = 0;
    m->sprite = NULL;
    m->sprite = IMG_Load("eg min.png");
    m->dot = IMG_Load("pr.bmp");
    m->posdot.x = 10.95;
    m->posdot.y = 159.91;
}
void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.sprite, NULL, screen, &m.position_mini);
    SDL_BlitSurface(m.dot,NULL,screen,&m.posdot);
}
void free_minimap(minimap m)
{
    SDL_FreeSurface(m.sprite);
    SDL_FreeSurface(m.dot);
}
int majminimap (personne *p, minimap *m ,int camera ,int redimensionnement)
{
    int deplacement=0;
    m->posdot.x = p->posScreen.x *redimensionnement/100;
        m->posdot.y = p->posScreen.y * redimensionnement/100;


    return deplacement;
}
SDL_Color GetPixel(SDL_Surface *Background, int x, int y)
{

    SDL_Color color;
    Uint32 col = 0;
    //Determine position

    char *pixelPosition = (char *)Background->pixels;
    //Offset by Y
    pixelPosition += (Background->pitch * y);
    //Offset by X
    pixelPosition += (Background->format->BytesPerPixel * x);
    //Copy pixel data
    memcpy(&col, pixelPosition, Background->format->BytesPerPixel);
    //Convert to color
    SDL_GetRGB(col, Background->format, &color.r, &color.g, &color.b);

    return (color);
}

int collisionPP(personne p, SDL_Surface *Masque)
{
    SDL_Color test, couleurnoir = {0, 0, 255};

    SDL_Rect pos[8];
    pos[0].x = p.posScreen.x;
    pos[0].y = p.posScreen.y;
    pos[1].x = p.posScreen.x + p.posSprite.w / 2;
    pos[1].y = p.posScreen.y;
    pos[2].x = p.posScreen.x + p.posSprite.w;
    pos[2].y = p.posScreen.y;
    pos[3].x = p.posScreen.x;
    pos[3].y = p.posScreen.y + p.posSprite.h / 2;
    pos[4].x = p.posScreen.x;
    pos[4].y = p.posScreen.y + p.posSprite.h;
    pos[5].x = p.posScreen.x + p.posSprite.w / 2;
    pos[5].y = p.posScreen.y + p.posSprite.h;
    pos[6].x = p.posScreen.x + p.posSprite.w;
    pos[6].y = p.posScreen.y + p.posSprite.h;
    pos[7].x = p.posScreen.x + p.posSprite.w;
    pos[7].y = p.posScreen.y + p.posSprite.h / 2;
    int collision = 0, x, y;

    for (int i = 0; i < 8 && collision == 0; i++)
    {
        x = pos[i].x;
        y = pos[i].y;
        test = GetPixel(Masque, x, y);
        if (test.r == 0 && test.g == 0 && test.b == 255)
            collision = 1;
    }
    return collision;
}
void affichertemp (Uint32 *temps,SDL_Surface *screen,TTF_Font *police)
{

SDL_Surface *chrono = NULL;
SDL_Rect positionChrono;
SDL_Color couleur = {255,255,255};
int min=0,sec=0;
char texteChrono [40] = "";
positionChrono.x = 840;
positionChrono.y = 10;
(*temps)=SDL_GetTicks();
(*temps)/=1000;
min=((*temps)/60);
sec=(*temps) - (60*min);


sprintf(texteChrono,"%02d:%02d",min,sec);
SDL_FreeSurface(chrono);
chrono = TTF_RenderText_Solid(police,texteChrono,couleur);
SDL_BlitSurface(chrono,NULL,screen,&positionChrono);
//}
}


/*void free_temps(temps *t, SDL_Surface *screen)
{
    SDL_FreeSurface(t->texte);
    TTF_CloseFont(t->police);
}*/


		
