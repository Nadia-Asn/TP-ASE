
CC = gcc
FLAGSS = -m32
EXE=

all: $(EXE)

%.o:%.c %.h
	$(CC) $(FLAGSS) $<

lib_contexte:lib_contexte.o
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f *.o *.i *.s *~ $(EXE)
