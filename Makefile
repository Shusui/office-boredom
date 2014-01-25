CXX = g++
CXXFLAGS = -g -Wall
CXXLIBS = -lsfml-window -lsfml-graphics -lsfml-system
SRCDIR = src
BUILDDIR = build

all: dirs $(BUILDDIR)/main.o
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $(BUILDDIR)/main.o -o $(BUILDDIR)/main

dirs:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
