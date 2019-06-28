#include <allegro5/allegro_color.h>
#include <stdlib.h>

#define ALLEGRO_PI        3.14159265358979323846
#define KEY_SEEN     1
#define KEY_RELEASED 2
#define DEGREES(radians) ((radians) * 180.0 / ALLEGRO_PI ) 
#define ROTATE_HEADING 0.002
#define WIDTH 600
#define HEIGHT 800
#define NUM_BULLETS 5
#define NUM_COMETS 1
#define NUM_SHIP_LIVES 3

typedef struct 
{   
    float sx;
    float sy;
    float heading;
    float twist;
    float speedx;
    float speedy;
    float rot_velocity;
    float scale;
    int gone;
    bool show;
    int boundx;
    int boundy;
    ALLEGRO_COLOR color;
} Asteroid;

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

/*
    Asteroids
*/

void Init_Asteroids(Asteroid asteroids[], int size); 
void draw_Asteroids(Asteroid asteroids[], int size);
void Update_Asteroids(Asteroid asteroids[], int size); 

void Init_Double_Asteroids(Asteroid asteroids[], int size);
void draw_Double_Asteroids(Asteroid asteroids[], int size, Asteroid cometa[], int cSize);

/*
    Bullets
*/
void InitBullets(Blast bullets[], int size);
void draw_Blast(Blast bullets[], int size);
void FireBullets(Blast bullets[], int size, Spaceship s);
void UpdateBullets(Blast bullets[], int size);
void CollideSpaceship(Asteroid asteroids[], int aSize, Spaceship *s, Spaceship ships[], int lives);
int CollideBullets(Blast bullets[], int bSize, Asteroid asteroids[], int aSize, Spaceship *s);

/*
    Spaceship
*/
void InitShipLives(Spaceship ships[], int lives);
void DrawShipLives(Spaceship ships[], int lives);
void draw_Ship(Spaceship *s);