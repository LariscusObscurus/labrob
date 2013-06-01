CC=g++
NAME=labrob
CFLAGS=-Wall -std=c++0x
LFLAGS=
ifdef NDEBUG
CFLAGS+=-O3
else
CFLAGS+=-g -D_DEBUG=1
endif

SRC=Labyrinth.cpp main.cpp Robot.cpp RobotLeftHand.cpp RobotRightHand.cpp RobotInsane.cpp
OBJ=$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

clean:
	rm -f $(OBJ) $(NAME)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
