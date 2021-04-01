#compiler
CXX=
#compiler options
CFLAGS=
#target file
TARGET=
#source files 
SRCS=
#source files
OBJS= $(SRCS:.cpp=.o)
#Include path
INCDIR=
#Library search path
LIBDIR=
#Library path
LIBS=

#Create target file
$(TARGET):$(OBJS)
  $(CXX) -o $@ $^ $(LIBDIR) $(LIBS)

#Create object files
.cpp.o:
  $(CXX) -c $< $(INCDIR) $(CFLAGS)

all:clean $(TARGET)

clean:
  rm -r $(TARGET) $(OBJS)
