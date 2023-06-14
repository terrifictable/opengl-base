CC 		:= g++
INCLUDE := -Iinclude/ -Isrc/ -Iinclude/imgui/ -Iinclude/imgui/backends/
LINKS   := -Llibs/ -lglfw3 -lglew32 -lgdi32 -lpthread -lopengl32
DEFS    := -DDEBUG
FLAGS 	:= -std=c++14 -g -Wall -Wextra -Werror -Wpedantic $(INCLUDE) $(DEFS)

LD      := ld
LDFLAGS :=


srcdir := src
src    := $(wildcard $(srcdir)/*.cpp $(srcdir)/**/*.cpp $(srcdir)/**/**/*.cpp $(srcdir)/**/**/shader/*.cpp)
obj    := $(src:%.cpp=%.o)

libdir 	:= include/imgui/
libs    := $(wildcard $(libdir)/*.c $(libdir)/*.cpp $(libdir)/**/*.c $(libdir)/**/*.cpp)
libsobj := $(libs:%.c=lib/%.o) $(libs:%.cpp=lib/%.o)

bin := bin
OUT := opengl_base


run: build
	./$(OUT) $(args)

build: $(obj)
	$(CC) $(FLAGS) $(wildcard $(bin)/*.o) $(LINKS) -o $(OUT)

libs: $(libsobj)

cc:
	compiledb make build --dry-run
.PHONY: build all cc build-libs clean run push

%.o: %.cpp
	-@mkdir -p $(bin)/
	$(CC) $(FLAGS) $< $(LINKS) -c -o $(bin)/$(@F)

lib/%.o: %.c
	-@mkdir -p $(bin)/
	$(CC) $(FLAGS) $< $(LINKS) -c -o $(bin)/$(@F)
lib/%.o: %.cpp
	-@mkdir -p $(bin)/
	$(CC) $(FLAGS) $< $(LINKS) -c -o $(bin)/$(@F)

clean:
	@rm $(bin)/*.o
	@rm $(OUT)

