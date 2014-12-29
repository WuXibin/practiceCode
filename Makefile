CC=g++
CFLAGS=-c -Wall
LDFLAGS=

OBJS=foo.o bar.o test.o
DEPS=
TAGS=hehe

all: $(TAGS)

$(TAGS): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ 

%.o:%.cc
	$(CC) $(CFLAGS) $< -o $@ 

.PHONY: clean

clean:
	rm $(TAGS) $(OBJS)
