CXX = g++
CXXFLAGS = -g -Wall
CXXLIBS = -lsfml-window -lsfml-graphics -lsfml-system
SRCDIR = src
BUILDDIR = build
CPP_FILES = $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES = $(addprefix $(BUILDDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

all: dirs $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $(BUILDDIR)/main.o -o $(BUILDDIR)/main

dirs:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
