
CC=gcc
FLAGSS=-m32
EXE=lib_contexte

all: $(EXE)

%.o:%.c %.h
	$(CC) $(FLAGSS) $<

lib_contexte:lib_contexte.o
	$(CC) -o $@ $^ $(FLAGSS)


.PHONY: clean

clean:
	rm -f *.o *.i *.s *~ $(EXE)
