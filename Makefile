CC = gcc
CFLAGS = -g -std=c11 -Wall
EXEC = bin/snake-io

SDIR = src
ODIR = obj
OBJs = $(patsubst $(SDIR)/%.c,%.o, $(rwildcard $(SDIR)/*.c))

all: $(EXEC)

$(EXEC): $(ODIR)/$(OBJs)
	$(CC) -o $@ $^
	
$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
.PHONY: clean cclean

clean:
	rm -f $(ODIR)/*.o
	
cclean: clean
	rm -f $(EXEC)

