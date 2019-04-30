
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro5.h>
#include <math.h>
#include <stdlib.h>
#include "blast.h"

void InitBullets(Blast bullets[], int size) {
    for (int i = 0; i < size; i++) {
        bullets[i].sx = 0;
        bullets[i].sy = 0;
        bullets[i].heading = 0;
        bullets[i].show = false;
        bullets[i].speed = 20;
        bullets[i].gone = 0;
        bullets[i].color = al_map_rgb(255, 0, 0);
    }
}

void draw_Blast(Blast bullets[], int size)
{
    for (int i = 0; i < size; i++) {
        if (bullets[i].show) {
        ALLEGRO_TRANSFORM blast;
        al_build_transform(&blast, bullets[i].sx, bullets[i].sy, 1.0, 1.0, DEGREES(bullets[i].heading));
        al_use_transform(&blast);
        al_draw_line(0, 10, 0.5, 0, al_map_rgb(255, 0, 0), 2.0f);
        al_identity_transform(&blast);
        al_use_transform(&blast);
        }
    }
}
    
void FireBullets(Blast bullets[], int size, Spaceship s) 
{
    for (int i = 0; i < size; i++) {
        if (!bullets[i].show) {
            bullets[i].sx = s.sx;
            bullets[i].sy = s.sy;
            bullets[i].heading = s.heading;
            bullets[i].show = true;
            break;
        }
    }
}

void UpdateBullets(Blast bullets[], int size)
{
    float bullet_velx;
    float bullet_vely;
    float bullet_heading_degrees;
    for (int i = 0; i < size; i++) {
        bullet_heading_degrees = DEGREES(DEGREES(bullets[i].heading));
        bullet_velx = bullets[i].speed * sin(bullet_heading_degrees * ALLEGRO_PI / 180);
        bullet_vely = bullets[i].speed * cos(bullet_heading_degrees * ALLEGRO_PI / 180);
        if (bullets[i].show)
        {
            bullets[i].sx += bullet_velx;
            bullets[i].sy -= bullet_vely;
            if(bullets[i].sy < 0)
                bullets[i].show = false;
            if(bullets[i].sy > WIDTH)
                bullets[i].show = false;
            if(bullets[i].sx < 0)
                bullets[i].show = false;
            if(bullets[i].sx > HEIGHT)
                bullets[i].show = false;
        }
    }
}

int CollideBullets(Blast bullets[], int bSize, Asteroid asteroids[], int aSize, Spaceship *s)
{
    for (int i = 0; i < bSize; i++)
    {
        if(bullets[i].show)
        {
            for (int j = 0; j < aSize; j++)
            {
                if (asteroids[j].show)
                {
                    if(bullets[i].sx > (asteroids[j].sx - asteroids[j].boundx) &&
                        bullets[i].sx < (asteroids[j].sx + asteroids[j].boundx) &&
                        bullets[i].sy > (asteroids[j].sy - asteroids[j].boundy)&&
                        bullets[i].sy < (asteroids[j].sy + asteroids[j].boundy))
                    {
                        bullets[i].show = false;
                        asteroids[j].show = false;
                        s->ship_score += 100;
                        return 1;
                    }
                }
            }
        }
    }
}

void CollideSpaceship(Asteroid asteroids[], int aSize, Spaceship *s, Spaceship ships[], int lives)
{
    for (int i = 0; i < lives; i++)
    {
        if(ships[i].show)
        {
            for (int j = 0; j < aSize; j++)
            {
                if (asteroids[j].show)
                {
                    if(asteroids[j].sx - asteroids[j].boundx < s->sx + s->boundx &&
                        asteroids[j].sx + asteroids[j].boundx > s->sx - s->boundx &&
                        asteroids[j].sy - asteroids[j].boundy < s->sy + s->boundy &&
                        asteroids[j].sy + asteroids[j].boundy > s->sy - s->boundy)
                    {
                        asteroids[j].show = false;
                        ships[i].show = false;
                        s->lives--;
                    } 
                }
            }
        }
    }
}