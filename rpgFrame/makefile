CC=gcc
AR=ar
LL_FLAGS=-lSDL2
OBJS=window.o tile.o map.o mapParser.o mainloop.o keylist.o character.o list.o scene.o events.o gui.o

librpgFrame.a: clean ${OBJS}
	${AR} -cvq librpgFrame.a ${OBJS}
	
%.o:%.c
	${CC} -c $<

clean:
	rm -f *.o
	rm -f librpgFrame.a
