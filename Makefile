program_NAME := memo

CXX := g++
CXXFLAGS := -std=c++11 -Wall -pedantic -O2

program_SHADERS := $(wildcard common/*.cpp)

program_CXX_SRCS := $(wildcard *.cpp)
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o} ${program_SHADERS:.cpp=.o}
program_OBJS := $(program_CXX_OBJS)

program_INCLUDE_DIRS := /usr/local/include/ /usr/local/include/GLFW/
program_LIBRARIES := glfw3 GLEW
program_LINUX_LIBRARIES := GL
program_FRAMEWORKS := OpenGL # GLUT

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))
LINUXFLAGS += $(foreach library,$(program_LINUX_LIBRARIES),-l$(library))
FRAMEWORKFLAGS += $(foreach framework,$(program_FRAMEWORKS),-framework $(framework))

LINKER_MACOS := $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(FRAMEWORKFLAGS)
LINKER_LINUX := $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LINUXFLAGS)

.PHONY: all mac linux clean distclean
all: mac

mac: $(program_OBJS)
	$(LINKER_MACOS) $(program_OBJS) --std=c++11 -o $(program_NAME)

linux: $(program_OBJS)
	$(LINKER_LINUX) $(program_OBJS) --std=c++11 -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean

