#Commands
MKDIR := mkdir
RMDIR := rm -rf

#Folders to make life easier
OBJ 	:= ./obj
HDR     := ./include
SRC 	:= ./src

#Compiler features
CC      := g++
CFLAGS  := -g -Wall -Wextra -Wunused -Werror -I$(HDR) \

#Variables
EXE   := ./a.out
HDRS  := $(wildcard $(HDR)/*.h)
SRCS  := $(wildcard $(SRC)/*.cpp)
OBJS  := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))	
OBJS  += $(OBJ)/example.o

$(EXE): $(OBJS)
	$(CC) $^ -o $@ 

$(OBJ)/example.o  : ./example.cpp $(HDR)/tags.h $(HDR)/doc.h | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/color.o : $(SRC)/color.cpp $(HDR)/color.h | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/doc.o   : $(SRC)/doc.cpp $(HDR)/doc.h $(HDR)/tag.h | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/point.o : $(SRC)/point.cpp $(HDR)/point.h | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/tag.o : $(SRC)/tag.cpp $(HDR)/tag.h | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/tags.o : $(SRC)/tags.cpp $(HDR)/tags.h $(HDR)/tag.h $(HDR)/color.h $(HDR)/point.h | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ):
	$(MKDIR) $@

.PHONY: clean debug release

clean:
	$(RMDIR) $(OBJ) $(EXE)
