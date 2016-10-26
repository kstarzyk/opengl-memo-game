program_NAME := memo

CXX := g++
CXXFLAGS := -std=c++11 -Wall -pedantic -O2 

program_SHADERS := $(wildcard common/*.cpp)

program_CXX_SRCS := $(wildcard *.cpp)
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o} ${program_SHADERS:.cpp=.o}
program_OBJS := $(program_CXX_OBJS)

program_INCLUDE_DIRS := /home/anl/PGK/include/ /home/anl/PGK/include/GLFW/
program_LIBRARIES := glfw3 GL GLU GLEW X11 Xxf86vm pthread Xrandr Xi 

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS :=
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

LINKER := $(CXX) -L/home/anl/PGK/libs/  $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) 

.PHONY: all mac linux clean distclean
all: linux

linux: $(program_OBJS)
	$(LINKER) $(program_OBJS) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean

