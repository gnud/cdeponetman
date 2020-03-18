#
# In order to execute this "Makefile" just type "make"
#	A. Delis (ad@di.uoa.gr)
#

OBJS	= cmdList.o cmdMan.o network.o server.o
SOURCE	= cmdList.c cmdMan.c network.c server.c
HEADER	= network.h server.h
OUT	= project
CC	 = gcc
FLAGS	 = -g3 -c -Wall
LFLAGS	 = -lpthread -lmxml
# -g option enables debugging mode 
# -c flag generates object code for separate files


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


# create/compile the individual files >>separately<<
cmdList.o: cmdList.c
	$(CC) $(FLAGS) cmdList.c -std=gnu99

cmdMan.o: cmdMan.c
	$(CC) $(FLAGS) cmdMan.c -std=gnu99

network.o: network.c
	$(CC) $(FLAGS) network.c -std=gnu99

server.o: server.c
	$(CC) $(FLAGS) server.c -std=gnu99


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# run the program
run: $(OUT)
	./$(OUT)

# compile program with debugging information
debug: $(OUT)
	valgrind $(OUT)

# run program with valgrind for errors
valgrind: $(OUT)
	valgrind $(OUT)

# run program with valgrind for leak checks
valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

# run program with valgrind for leak checks (extreme)
valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)
