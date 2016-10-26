program_NAME := memo

CXX := g++
CXXFLAGS := -std=c++11 -Wall -pedantic -O2 -Wswitch

program_SHADERS := $(wildcard common/*.cpp)

program_CXX_SRCS := $(wildcard *.cpp)
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o} ${program_SHADERS:.cpp=.o}
program_OBJS := $(program_CXX_OBJS)

program_INCLUDE_DIRS := /usr/local/include/ /usr/local/include/GLFW/
program_LIBRARY_DIRS :=
program_LIBRARIES := glfw3 GLEW
program_FRAMEWORKS := OpenGL # GLUT

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))
FRAMEWORKFLAGS += $(foreach framework,$(program_FRAMEWORKS),-framework $(framework))
# TARGET_ARCH :=

LINKER := $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(FRAMEWORKFLAGS)  # $(TARGET_ARCH)

.PHONY: all clean distclean
all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINKER) $(program_OBJS) --std=c++11 -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean

