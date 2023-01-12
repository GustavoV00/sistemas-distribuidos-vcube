############ NOME DO EXECUTÁVEL #########
nomePrograma=vcube

###########DIRETÓRIOS CRIADOS ##############
SRC=src
UTILS=src/utils
SMPL=src/smpl
VCUBE=src/vcube
BIN=src/bin

########### PARAMETROS DE COMPILAÇÃO #############
parametrosCompilacao=-Wall -lm #-Wshadow


all: $(nomePrograma)

$(nomePrograma): $(BIN)/main.o $(BIN)/vcube.o $(BIN)/smpl.o $(BIN)/rand.o $(BIN)/cisj.o $(BIN)/utils.o
	$(LINK.c) -o $@ -Bstatic $(BIN)/main.o $(BIN)/vcube.o $(BIN)/smpl.o $(BIN)/rand.o $(BIN)/cisj.o $(BIN)/utils.o $(parametrosCompilacao)
	
$(BIN)/main.o: $(SRC)/main.c $(VCUBE)/vcube.h $(VCUBE)/cisj.h $(UTILS)/utils.h
	$(COMPILE.c)  -g $(SRC)/main.c $(parametrosCompilacao) -o $(BIN)/main.o

$(BIN)/utils.o: $(UTILS)/utils.c $(UTILS)/utils.h
	$(COMPILE.c)  -g $(UTILS)/utils.c $(parametrosCompilacao) -o $(BIN)/utils.o

$(BIN)/smpl.o: $(SMPL)/smpl.c $(SMPL)/smpl.h
	$(COMPILE.c)  -g $(SMPL)/smpl.c $(parametrosCompilacao) -o $(BIN)/smpl.o

$(BIN)/vcube.o: $(VCUBE)/vcube.c $(SMPL)/smpl.h
	$(COMPILE.c) -g  $(VCUBE)/vcube.c $(parametrosCompilacao) -o $(BIN)/vcube.o

$(BIN)/rand.o: $(SMPL)/rand.c
	$(COMPILE.c) -g $(SMPL)/rand.c $(parametrosCompilacao) -o $(BIN)/rand.o

$(BIN)/cisj.o: $(VCUBE)/cisj.c $(VCUBE)/cisj.h
	$(COMPILE.c) -g $(VCUBE)/cisj.c $(parametrosCompilacao) -o $(BIN)/cisj.o

clean:
	$(RM) $(BIN)/*.o $(nomePrograma) relat saida