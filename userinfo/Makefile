#INC=/home/joel/Workspace/redis/deps/hiredis
INC=.
OBJ=userinfo.pb.o

CC=g++ 
CFLAGS=-g -Wall -I$(INC)
LDFLAGS=
LIBS=-lboost_thread-mt -lz -lprotobuf

all: redis_insert
test: redis_decode

redis_insert: redis_insert.o $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(INC)/libhiredis.a $(LIBS)

redis_decode: redis_decode.o
	$(CC) $(LDFLAGS) -o $@ $^ $(INC)/libhiredis.a $(LIBS)

redis_deserial: redis_deserial.o $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(INC)/libhiredis.a $(LIBS)

%.o : %.cc
	$(CC) $(CFLAGS) -c $^ -o $@	

clean:
	rm -rf *.o redis_insert redis_decode redis_deserial
