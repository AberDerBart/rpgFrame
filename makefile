LINKFLAGS= -lSDL2 -lSDL2_image -L./rpgFrame/ -lrpgFrame
OBJS=main.o

pokethulu: ${OBJS} rpgFrame/librpgFrame.a
	gcc -o pokethulhu main.o d12.o ${LINKFLAGS}

%.o: %.c
	gcc -c $<

clean:
	rm -f *.o pokethulhu
