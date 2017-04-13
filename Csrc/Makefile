CC = gcc
OBJS = histaugramment.o rdjpeg.o calculHistogrammes.o affichage.o
EXEC = ../histo
CFLAGS = -Wall -I ../include
SRCS = $(OBJS:.c=.o)

all : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -lm  -o $(EXEC)

clean:
	-rm -rf ./*.o
