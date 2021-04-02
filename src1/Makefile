#compiler
CXX=g++
#compiler options
CFLAGS=-Wall
#target file
TARGET=Main
#source files 
SRCS=Main.cpp Game.cpp Math.cpp Component.cpp Actor.cpp SpriteComponent.cpp AnimSpriteComponent.cpp
#source files
OBJS= $(SRCS:.cpp=.o)
#Include path
INCDIR= -I../External/SDL/include
#Library search path
LIBDIR=-L../External/SDL/lib
#Library path
LIBS=-lSDL2-2.0.0 -lSDL2_image-2.0.0

#Create target file
$(TARGET):$(OBJS)
  $(CXX) -o $@ $^ $(LIBDIR) $(LIBS)

#Create object files
.cpp.o:
  $(CXX) -c $< $(INCDIR) $(CFLAGS)

all:clean $(TARGET)

clean:
  rm -r $(TARGET) $(OBJS)
