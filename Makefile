CC=clang
CFLAGS= -O3 -Wno-pragma-pack -I SDL/include -I include -I include/components
LDFLAGS= -lSDL2 -L SDL/lib/x64

all: tetris

tetris: main.o logic.o music.o gfx.o texture.o tex_list.o texture_mgr.o player.o component.o actor.o render_component.o moveup_component.o engine.o sprite.o vec.o palette.o moveball_component.o bounce_component.o move_component.o animation_component.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $^

logic.o: src/logic.c
	$(CC) $(CFLAGS) -c -o $@ $^

music.o: src/music.c
	$(CC) $(CFLAGS) -c -o $@ $^

gfx.o: src/gfx.c
	$(CC) $(CFLAGS) -c -o $@ $^

texture.o: src/texture.c
	$(CC) $(CFLAGS) -c -o $@ $^

tex_list.o: src/tex_list.c
	$(CC) $(CFLAGS) -c -o $@ $^

texture_mgr.o: src/texture_mgr.c
	$(CC) $(CFLAGS) -c -o $@ $^

player.o: src/player.c
	$(CC) $(CFLAGS) -c -o $@ $^

component.o: src/components/component.c
	$(CC) $(CFLAGS) -c -o $@ $^

actor.o: src/actor.c
	$(CC) $(CFLAGS) -c -o $@ $^

render_component.o: src/components/render_component.c
	$(CC) $(CFLAGS) -c -o $@ $^

moveup_component.o: src/components/moveup_component.c
	$(CC) $(CFLAGS) -c -o $@ $^

sprite.o: src/sprite.c
	$(CC) $(CFLAGS) -c -o $@ $^

engine.o: src/engine.c
	$(CC) $(CFLAGS) -c -o $@ $^

vec.o: src/vec.c
	$(CC) $(CFLAGS) -c -o $@ $^

palette.o: src/palette.c
	$(CC) $(CFLAGS) -c -o $@ $^

moveball_component.o: src/components/moveball_component.c
	$(CC) $(CFLAGS) -c -o $@ $^

bounce_component.o: src/components/bounce_component.c
	$(CC) $(CFLAGS) -c -o $@ $^

move_component.o: src/components/move_component.c
	$(CC) $(CFLAGS) -c -o $@ $^

animation_component.o: src/components/animation_component.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o