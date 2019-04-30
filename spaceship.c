#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro5.h>
#include <math.h>
#include <stdlib.h>
#include "blasteroids.h"
#include "asteroid.h"
#include "spaceship.h"

// Spaceship lives
void InitShipLives(Spaceship ships[], int lives)
{
    int sx = 30;
    for (int i = 0; i < lives; i++)
    {
        ships[i].sx = sx;
        ships[i].sy = 100;
        ships[i].boundx = 10;
        ships[i].boundy = 10;
        ships[i].heading = 0;
        ships[i].speed = 0.0;
        ships[i].scale = 2.5;
        ships[i].show = true;
        ships[i].ship_score = 0;
        ships[i].lives = 1;
        ships[i].color = al_map_rgb(0, 255, 0);
        sx += 50;
    }
}

void DrawShipLives(Spaceship ships[], int lives)
{
    for (int i = 0; i < lives ; i++) 
    {
        if (ships[i].show)
        {
            ALLEGRO_TRANSFORM transform;
            al_build_transform(&transform, ships[i].sx, ships[i].sy, ships[i].scale, ships[i].scale, DEGREES(ships[i].heading));
            al_use_transform(&transform);
            al_draw_line(-8, 9, 0, -11, al_map_rgb(0, 255, 0), 3.0f);
            al_draw_line(0, -11, 8, 9, al_map_rgb(0, 255, 0), 3.0f);
            al_draw_line(-6, 4, -1, 4, al_map_rgb(0, 255, 0), 3.0f);
            al_draw_line(6, 4, 1, 4, al_map_rgb(0, 255, 0), 3.0f);
            al_identity_transform(&transform);
            al_use_transform(&transform);
        }
    }
}

void draw_Ship(Spaceship *s) {
    ALLEGRO_TRANSFORM transform;
    al_build_transform(&transform, s->sx, s->sy, s->scale, s->scale, DEGREES(s->heading));
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(0, -11, 8, 9, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(-6, 4, -1, 4, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(6, 4, 1, 4, al_map_rgb(0, 255, 0), 3.0f);
    al_identity_transform(&transform);
    al_use_transform(&transform);
}