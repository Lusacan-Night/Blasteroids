
launch: blasteroids.o asteroid.o blast.o spaceship.o
	gcc -lm blasteroids.o asteroid.o blast.o spaceship.o -o launch `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

asteroid.o: asteroid.h blasteroids.h
	gcc -c asteroid.c 

blast.o: blast.h
	gcc -c blast.c

blasteroids.o: asteroid.h blasteroids.h spaceship.h blast.h asteroid.c blast.c spaceship.c
	gcc -c blasteroids.c 

spaceship.o: asteroid.h blasteroids.h spaceship.h
	gcc -c spaceship.c

clean:
	rm *.o