CXX = g++
CXXFLAGS = -g -Wall
CXXLIBS = -lsfml-window -lsfml-graphics -lsfml-system
SRCDIR = src
BUILDDIR = build
SRC_DIRS = $(shell find $(SRCDIR) -type d)
BUILD_DIRS = $(subst src,build,$(SRC_DIRS))
CPP_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJ_FILES = $(subst src,build,$(CPP_FILES:.cpp=.o))

all: dirs $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/*.o -o $(BUILDDIR)/main $(CXXLIBS) 

dirs:
	@for dir in $(BUILD_DIRS); do \
		mkdir -p $$dir; \
	done

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf build
