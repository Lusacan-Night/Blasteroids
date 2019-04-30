/* 
 * Ядро игрульки
*/

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro5.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "blasteroids.h"
#include "blast.h"

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void draw_Score(ALLEGRO_FONT* font, Spaceship s) {
    ALLEGRO_TRANSFORM text;
    al_build_transform(&text, 10, 30, 3, 3, 0);
    al_use_transform(&text);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "%d", s.ship_score);
}
  

int main()
{
    long ltime = time(NULL);
    int stime = (unsigned int) ltime/2;
    srand(stime);
    bool isGameOver = false;
    
    ALLEGRO_COLOR color_white = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR color_green = al_map_rgb(0, 255, 0);
    ALLEGRO_COLOR color_blue = al_map_rgb(0, 0, 255);
    ALLEGRO_COLOR color_red = al_map_rgb(255, 0, 0);

    Spaceship vectorize = {HEIGHT/2, WIDTH/2, 10, 10, 0, 0.0, 1, false, 0, 3, color_green};
    Spaceship ship_lives[NUM_SHIP_LIVES];
    Asteroid cometa[NUM_COMETS];
    Asteroid double_cometa[2];
    Blast bullets[NUM_BULLETS];

    InitBullets(bullets, NUM_BULLETS);
    Init_Asteroids(cometa, NUM_COMETS);
    Init_Double_Asteroids(double_cometa, 2);
    InitShipLives(ship_lives, NUM_SHIP_LIVES);
    

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_primitives_addon(), "primitives");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(HEIGHT, WIDTH);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    
    al_start_timer(timer);

    float vel_x;
    float vel_y;
    float bullet_velx;
    float bullet_vely;
    
    while(!done)
    {
        al_wait_for_event(queue, &event);
        float heading_degrees = DEGREES(DEGREES(vectorize.heading));
        //float bullet_heading_degrees = DEGREES(DEGREES(bullet.heading));
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                vel_x = vectorize.speed * sin(heading_degrees * ALLEGRO_PI / 180);
                vel_y = vectorize.speed * cos(heading_degrees * ALLEGRO_PI / 180);
                // bullet_velx = bullet.speed * sin(bullet_heading_degrees * ALLEGRO_PI / 180);
                // bullet_vely = bullet.speed * cos(bullet_heading_degrees * ALLEGRO_PI / 180);
                if(key[ALLEGRO_KEY_UP] && (vectorize.speed <= 10))
                    vectorize.speed += 1;
                if(key[ALLEGRO_KEY_DOWN] && vectorize.speed >= 0)
                    vectorize.speed -= 1;
                if(key[ALLEGRO_KEY_LEFT])
                    vectorize.heading -= ROTATE_HEADING;
                if(key[ALLEGRO_KEY_RIGHT])
                    vectorize.heading += ROTATE_HEADING;
                if(vectorize.speed > 0) {
                       vectorize.sx += vel_x;
                       vectorize.sy -= vel_y;
                       }
                if(key[ALLEGRO_KEY_SPACE]) {                    
                    FireBullets(bullets, NUM_BULLETS, vectorize);
                }

                if (!isGameOver)
                {
                    
                    Update_Asteroids(cometa, NUM_COMETS);
                    Update_Asteroids(double_cometa, 2);
                    UpdateBullets(bullets, NUM_BULLETS);
                    CollideBullets(bullets, NUM_BULLETS, cometa, NUM_COMETS, &vectorize);
                    CollideBullets(bullets, NUM_BULLETS, double_cometa, 2, &vectorize);
                    CollideSpaceship(cometa, NUM_COMETS, &vectorize, ship_lives, NUM_SHIP_LIVES);
                    
                    if (vectorize.lives <= 0)
                    {
                        isGameOver = true;
                    }
                }
                
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                if(vectorize.sy < 0)
                    vectorize.sy = WIDTH;
                if(vectorize.sy > WIDTH)
                    vectorize.sy = 0.0;
                if(vectorize.sx < 0)
                    vectorize.sx = HEIGHT;
                if(vectorize.sx > HEIGHT)
                    vectorize.sx = 0;
                
                while(heading_degrees >= 360) heading_degrees -= 360;
                while(heading_degrees < 0) heading_degrees += 360;
                    
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        // if(done)
        //     break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %d", cometa[0].show);
            if (!isGameOver)
            {
                draw_Score(font, vectorize);
                draw_Blast(bullets, NUM_BULLETS);
                draw_Ship(&vectorize);
                DrawShipLives(ship_lives, NUM_SHIP_LIVES);
                draw_Asteroids(cometa, NUM_COMETS);
                if (cometa[0].show == 0) {
                    draw_Double_Asteroids(double_cometa, 2, cometa, NUM_COMETS);
                }
                
            } else {
                al_draw_textf(font, al_map_rgb(255, 255, 255), HEIGHT/2, WIDTH/2, ALLEGRO_ALIGN_CENTER, "GAME OVER!");
            }
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}

