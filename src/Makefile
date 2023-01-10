parametrosCompilacao=-Wall -lm #-Wshadow
nomePrograma=vcube

all: $(nomePrograma)

$(nomePrograma): vcube.o smpl.o rand.o
	$(LINK.c) -o $@ -Bstatic vcube.o smpl.o rand.o $(parametrosCompilacao)

smpl.o: smpl.c smpl.h
	$(COMPILE.c)  -g smpl.c $(parametrosCompilacao)

vcube.o: vcube.c smpl.h
	$(COMPILE.c) -g  vcube.c $(parametrosCompilacao)

rand.o: rand.c
	$(COMPILE.c) -g rand.c $(parametrosCompilacao)

clean:
	$(RM) *.o $(nomePrograma) relat saida