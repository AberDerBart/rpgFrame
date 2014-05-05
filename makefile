LINKFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -L./rpgFrame/ -lrpgFrame
OBJS=testing.o
EDIT_OBJS=editor.o

pokethulu: ${OBJS} rpgFrame/librpgFrame.a
	gcc -o pokethulhu ${OBJS} ${LINKFLAGS}

editor: ${EDIT_OBJS} rpgFrame/librpgFrame.a
	gcc -o editor ${EDIT_OBJS} ${LINKFLAGS}

%.o: %.c
	gcc -c $<

clean:
	rm -f *.o pokethulhu
