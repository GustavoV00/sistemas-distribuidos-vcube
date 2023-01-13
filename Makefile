parametrosCompilacao=-Wall -lm #-Wshadow
nomePrograma=vcube

all: $(nomePrograma)

$(nomePrograma): vcube.o smpl.o rand.o cisj.o utils.o
	$(LINK.c) -o $@ -Bstatic vcube.o smpl.o rand.o cisj.o utils.o $(parametrosCompilacao)

smpl.o: smpl.c smpl.h
	$(COMPILE.c)  -g smpl.c $(parametrosCompilacao)

vcube.o: vcube.c smpl.h
	$(COMPILE.c) -g  vcube.c $(parametrosCompilacao)

rand.o: rand.c
	$(COMPILE.c) -g rand.c $(parametrosCompilacao)

cisj.o: cisj.c cisj.h
	$(COMPILE.c) -g cisj.c $(parametrosCompilacao)

utils.o: utils.c utils.h
	$(COMPILE.c) -g utils.c $(parametrosCompilacao)

clean:
	$(RM) *.o $(nomePrograma) relat saida