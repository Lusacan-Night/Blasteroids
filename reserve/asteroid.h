#include <allegro5/allegro_color.h>
#include <stdlib.h>


typedef struct 
{   
    float sx;
    float sy;
    float heading; // направление
    float twist;   // текущее вращение
    float speedx;
    float speedy;
    float rot_velocity; // кол-во вращений за один кадр
    float scale;
    int gone;
    bool show;
    int boundx;
    int boundy;
    ALLEGRO_COLOR color;
} Asteroid;

void Init_Asteroids(Asteroid asteroids[], int size); 
void draw_Asteroids(Asteroid asteroids[], int size);
void Update_Asteroids(Asteroid asteroids[], int size); 

void Init_Double_Asteroids(Asteroid asteroids[], int size);
void draw_Double_Asteroids(Asteroid asteroids[], int size, Asteroid cometa[], int cSize);