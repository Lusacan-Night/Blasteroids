#include <allegro5/allegro_color.h>
#include <stdlib.h>
#include "asteroid.h"
#include "spaceship.h"
#include "blasteroids.h"

typedef struct 
{
    float sx;
    float sy;
    float heading;
    float speed;
    int gone;
    bool show;
    ALLEGRO_COLOR color;
} Blast;

void InitBullets(Blast bullets[], int size);
void draw_Blast(Blast bullets[], int size);
void FireBullets(Blast bullets[], int size, Spaceship s);
void UpdateBullets(Blast bullets[], int size);
void CollideSpaceship(Asteroid asteroids[], int aSize, Spaceship *s, Spaceship ships[], int lives);
int CollideBullets(Blast bullets[], int bSize, Asteroid asteroids[], int aSize, Spaceship *s);