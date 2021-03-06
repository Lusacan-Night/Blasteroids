
launch: blasteroids.o asteroid.o blast.o spaceship.o
	gcc -lm blasteroids.o asteroid.o blast.o spaceship.o -o launch `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags`

asteroid.o: blasteroids.h
	gcc -c asteroid.c 

blast.o: blasteroids.h
	gcc -c blast.c 

spaceship.o: blasteroids.h
	gcc -c spaceship.c

clean:
	rm *.o