CC = gcc
OBJS = histaugramment.o proc.o rdjpeg.o calculHistogrammes.o affichage.o chargementHisto.o
EXEC = ../histo
CFLAGS = -Wall -I ../include
SRCS = $(OBJS:.c=.o)

all : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -lm  -o $(EXEC)

clean:
	-rm -rf ./*.o
