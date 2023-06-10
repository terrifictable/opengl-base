CC 		:= g++
INCLUDE := -Iinclude/ -Isrc/
LINKS   := -Llibs/ -lglfw3 -lglew32 -lgdi32 -lpthread -lopengl32
DEFS    := -DDEBUG
FLAGS 	:= -std=c++14 -g -Wall -Wextra -Werror -Wpedantic $(INCLUDE) $(DEFS)

LD      := ld
LDFLAGS :=


srcdir := src
src    := $(wildcard $(srcdir)/*.cpp $(srcdir)/**/*.cpp $(srcdir)/**/**/*.cpp)
obj    := $(src:%.cpp=%.o)


bin := bin
OUT := opengl_base


run: build
	./$(OUT) $(args)

build: $(obj)
	$(CC) $(FLAGS) $(wildcard $(bin)/*.o) $(LINKS) -o $(OUT)

cc:
	compiledb make build --dry-run

.PHONY: build all clean run

%.o: %.cpp
	-@mkdir -p $(bin)/
	$(CC) $(FLAGS) $< $(LINKS) -c -o $(bin)/$(@F)


clean:
	@rm $(bin)/*.o
	@rm $(OUT)

