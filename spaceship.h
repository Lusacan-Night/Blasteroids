#include <allegro5/allegro_color.h>
#include <stdlib.h>

typedef struct 
{
    float sx;
    float sy;
    float boundx;
    float boundy;
    float heading;
    float speed;
    int scale;
    bool show;
    int ship_score;
    int lives;
    ALLEGRO_COLOR color;
} Spaceship;

void InitShipLives(Spaceship ships[], int lives);
void DrawShipLives(Spaceship ships[], int lives);
void draw_Ship(Spaceship *s);