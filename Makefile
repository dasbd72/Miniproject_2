# Makefile for Windows
# Ref:https://www.gnu.org/software/make/manual/html_node/index.html#Top
ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname -s)
endif
########## Windows ##########
ifeq ($(detected_OS),Windows)
CXX = g++
ODIR = obj
EXE = TowerDefense

SRC  := $(wildcard *.cpp)
OBJ  := $(SRC:%.cpp=$(ODIR)\\%.o)
IDIR = $(CURDIR)\allegro-x86_64-w64-mingw32-gcc-10.2.0-posix-seh-static-5.2.7.0\include
LDIR = $(CURDIR)\allegro-x86_64-w64-mingw32-gcc-10.2.0-posix-seh-static-5.2.7.0\lib

CXXFLAGS = -std=c++17 -I$(IDIR)
LDFLAGS = -lm -Wall -Wextra -L$(LDIR) -lallegro -lallegro_main -lallegro_font -lallegro_color -lallegro_image -lallegro_acodec -lallegro_audio -lallegro_dialog -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf
# -lallegro_monolith

.PHONY: all dbg clean run run-dbg
all: $(OBJ)
	$(CXX) -o $(EXE).exe $(OBJ) -O2 $(CXXFLAGS) $(LDFLAGS)
%.o: %.cpp
	$(CXX) -c $< -o $(ODIR)\$@ -O2 $(CXXFLAGS) 
$(OBJ): $(ODIR)\\%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
dbg:
	$(CXX) -g $(SRC) -o $(EXE)_dbg.exe $(LDFLAGS) $(CXXFLAGS) 
clean:
	del $(EXE).exe $(EXE)_dbg.exe $(ODIR)\*.o
run:
	make all
	.\\$(EXE).exe
run-dbg:
	make dbg
	gdb .\\$(EXE)_dbg.exe

endif
########## Linux ##########
ifeq ($(detected_OS),Linux)
# sudo add-apt-repository ppa:allegro/5.2
# sudo apt-get install liballegro*5.2 liballegro*5-dev
# sudo apt-get update
CXX = g++
ODIR = obj
EXE = TowerDefense

SRC  := $(wildcard *.cpp)
OBJ  := $(SRC:%.cpp=$(ODIR)/%.o)
ALLEGRO_LIBRARIES := allegro-5 allegro_main-5 allegro_font-5 allegro_color-5 allegro_image-5 allegro_acodec-5 allegro_audio-5 allegro_dialog-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5 allegro_video-5
ALLEGRO_FLAGS := $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES))

CXXFLAGS = -std=c++11 -O2
LDFLAGS = -lm -Wall -Wextra

.PHONY: all
all: $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(ALLEGRO_FLAGS) $(CXXFLAGS) $(LDFLAGS)
%.o: %.cpp
	$(CXX) -c $< -o $(ODIR)/$@ $(ALLEGRO_FLAGS) $(CXXFLAGS)
$(OBJ): $(ODIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(ALLEGRO_FLAGS) $(CXXFLAGS)
clean:
	rm $(EXE) $(OBJ)
run:
	./$(EXE)
endif
########## MacOS ##########
ifeq ($(detected_OS),Darwin)
# brew install make
# brew install pkg-config
# brew install allegro
# brew install freetype
CXX = g++
ODIR = obj
EXE = TowerDefense

SRC  := $(wildcard *.cpp)
OBJ  := $(SRC:%.cpp=$(ODIR)/%.o)
CXXFLAGS = -std=c++11 -O2 -m64
LDFLAGS = -lm -Wall -Wextra -lallegro -lallegro_main -lallegro_font -lallegro_color -lallegro_image -lallegro_acodec -lallegro_audio -lallegro_dialog -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf

.PHONY: all
all: $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(CXXFLAGS) $(LDFLAGS)
%.o: %.cpp
	$(CXX) -c $< -o $(ODIR)/$@ $(CXXFLAGS)
$(OBJ): $(ODIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
clean:
	rm -rf $(OBJ) $(EXE)
endif


