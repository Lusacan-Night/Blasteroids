#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro5.h>
#include <math.h>
#include <stdlib.h>
#include "blasteroids.h"
#include "asteroid.h"


void Init_Asteroids(Asteroid asteroids[], int size) 
{
    for (int i = 0; i < size; i++) {
        float a = (-1.0) + rand() % 6;
        if (a == 0)
        {
            a += (-1.0) + rand() % 6;
        }
        asteroids[i].sx = rand() % HEIGHT;
        asteroids[i].sy = rand() % WIDTH;
        asteroids[i].heading = 0;
        asteroids[i].twist = 0;
        asteroids[i].speedx = a;
        asteroids[i].speedy = a;
        asteroids[i].rot_velocity = ((float)rand() / (float)RAND_MAX * 0.001);
        // asteroids[i].scale = ((float)rand() / (float)RAND_MAX * 2);
        // if (asteroids[i].scale < 1.0) {
        //     asteroids[i].scale += 1.0;
        // }
        asteroids[i].scale = 2;
        asteroids[i].show = true;
        asteroids[i].boundx = 25 * asteroids[i].scale;
        asteroids[i].boundy = 25 * asteroids[i].scale;
        asteroids[i].color = al_map_rgb(0, 0, 0);
    }
}

void draw_Asteroids(Asteroid asteroids[], int size) 
{
    for (int i = 0; i < size; i++)
    {
        if(asteroids[i].show) 
        {
        ALLEGRO_TRANSFORM com;
        al_build_transform(&com, asteroids[i].sx, asteroids[i].sy, asteroids[i].scale,
                                 asteroids[i].scale, DEGREES(asteroids[i].heading));
        al_use_transform(&com);
        al_draw_line(-20, 20, -25, 5, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(-25, 5, -25, -10, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(-25, -10, -5, -10, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(-5, -10, -10, -20, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(-10, -20, 5, -20, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(5, -20, 20, -10, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(20, -10, 20, -5, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(20, -5, 0, 0, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(0, 0, 20, 10, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(20, 10, 10, 20, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(10, 20, 0, 15, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(0, 15, -20, 20, al_map_rgb(255,255,255), 2.0f);
        al_identity_transform(&com);
        al_use_transform(&com);
        }
    }
}

void Update_Asteroids(Asteroid asteroids[], int size) 
{
    for (int i = 0; i < size; i++) {
        asteroids[i].sx += asteroids[i].speedx;
        asteroids[i].sy += asteroids[i].speedy;
        asteroids[i].heading += asteroids[i].rot_velocity;
        if(asteroids[i].sy < 0)
            asteroids[i].sy = WIDTH;
        if(asteroids[i].sy > WIDTH)
            asteroids[i].sy = 0.0;
        if(asteroids[i].sx < 0)
            asteroids[i].sx += HEIGHT;
        if(asteroids[i].sx > HEIGHT)
            asteroids[i].sx = 0;
    }
    
}

// DOUBLE ASTEROIDS
void Init_Double_Asteroids(Asteroid asteroids[], int size) 
{
    for (int i = 0; i < size; i++) {
        float a = (-1.0) + rand() % 6;
        if (a == 0)
        {
            a += (-1.0) + rand() % 6;
        }
        asteroids[i].sx = rand() % HEIGHT;
        asteroids[i].sy = rand() % WIDTH;
        asteroids[i].heading = 0;
        asteroids[i].twist = 0;
        asteroids[i].speedx = a;
        asteroids[i].speedy = a;
        asteroids[i].rot_velocity = ((float)rand() / (float)RAND_MAX * 0.001);
        // asteroids[i].scale = ((float)rand() / (float)RAND_MAX * 2);
        // if (asteroids[i].scale < 1.0) {
        //     asteroids[i].scale += 1.0;
        // }
        asteroids[i].scale = 2;
        asteroids[i].show = true;
        asteroids[i].boundx = 25 * asteroids[i].scale;
        asteroids[i].boundy = 25 * asteroids[i].scale;
        asteroids[i].color = al_map_rgb(0, 0, 0);
    }
}

void draw_Double_Asteroids(Asteroid asteroids[], int size, Asteroid cometa[], int cSize) 
{
    for (int i = 0; i < size; i++)
    {
        if(asteroids[i].show) 
        {
        ALLEGRO_TRANSFORM com;
        al_build_transform(&com, cometa[0].sx, cometa[0].sy, asteroids[i].scale,
                                 asteroids[i].scale, DEGREES(asteroids[i].heading));
        al_use_transform(&com);
        al_draw_line(-20, 20, -25, 5, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(-25, 5, -25, -10, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(-25, -10, -5, -10, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(-5, -10, -10, -20, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(-10, -20, 5, -20, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(5, -20, 20, -10, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(20, -10, 20, -5, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(20, -5, 0, 0, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(0, 0, 20, 10, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(20, 10, 10, 20, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(10, 20, 0, 15, al_map_rgb(255,255,255), 2.0f);
        al_draw_line(0, 15, -20, 20, al_map_rgb(255,255,255), 2.0f);
        al_identity_transform(&com);
        al_use_transform(&com);
        }
    }
}