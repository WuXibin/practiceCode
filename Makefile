CC=g++
CFLAGS=-Wall
LDFLAGS=

OBJS=foo.o bar.o test.o
TAGS=hehe

all: $(TAGS)

$(TAGS): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ 

$(OBJS):%.o:%.cc
	$(CC) -c $(CFLAGS) $< -o $@ 
