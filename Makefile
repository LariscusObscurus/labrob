CC=g++
NAME=labrob
CFLAGS=-Wall -std=c++0x
LFLAGS=-pthread
ifdef NDEBUG
CFLAGS+=-O3
else
CFLAGS+=-g -D_DEBUG=1
endif

SRC=Labyrinth.cpp main.cpp Robot.cpp RobotLeftHand.cpp RobotRightHand.cpp RobotInsane.cpp
OBJ=$(SRC:.cpp=.o)

ARCHIVE=$(NAME)

all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

clean:
	rm -f $(OBJ) $(NAME)

dist:
	cd ..; tar czf $(ARCHIVE).tar.gz $(NAME); mv $(ARCHIVE).tar.gz $(NAME)

distclean:
	rm $(ARCHIVE).tar.gz

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
