IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)
DEPS =shader.h glad.h khrplatform.h stb_image.h

%.o: %.c $(DEPS)
	$(CC) -cpp -o $@ $< $(CFLAGS)

window: context.o glad.o shader.o
	$(CC) -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lglfw -o window context.o glad.o shader.o && ./window

clean:
	rm -f *.o ../include/*.gch window
	