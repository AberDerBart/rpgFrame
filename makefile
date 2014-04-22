LINKFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -L./rpgFrame/ -lrpgFrame
OBJS=main.o

pokethulu: ${OBJS} rpgFrame/librpgFrame.a
	gcc -o pokethulhu ${OBJS} ${LINKFLAGS}

%.o: %.c
	gcc -c $<

clean:
	rm -f *.o pokethulhu
