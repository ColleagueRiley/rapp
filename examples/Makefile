CC ?= gcc

EXAMPLES = example


LIBS := -lgdi32 -ggdb -lopengl32
detected_OS = windows

ifeq (,$(filter $(CC),x86_64-w64-mingw32-gcc i686-w64-mingw32-gcc x86_64-w64-mingw32-g++ /opt/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	detected_OS := $(shell uname 2>/dev/null || echo Unknown)

	ifeq ($(detected_OS),Darwin)        # Mac OS X
		LIBS := -framework CoreVideo -framework Cocoa -framework OpenGL -framework IOKit -framework OpenGL
		LIB_EXT = .dylib
	endif
	ifeq ($(detected_OS),Linux)
    	LIBS := -lXrandr -lX11 -ldl -lpthread -lGL
		LIB_EXT = .so
	endif

	ifeq (,$(filter $(detected_OS),Linux Darwin))
		detected_OS := windows
	endif
else
	LIBS += -lm
endif

ifneq (,$(filter $(CC),cl /opt/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	LIBS = -lm
	OBJ_FILE = .obj
else ifneq (,$(filter $(CC),emcc em++))
	EXPORTED_JS = -s EXPORTED_RUNTIME_METHODS="['stringToNewUTF8']"
	LIBS = -s WASM=1 -s ASYNCIFY -s GL_SUPPORT_EXPLICIT_SWAP_CONTROL=1 $(EXPORTED_JS) -s FULL_ES3 -s USE_WEBGL2 -lm 
	detected_OS = web
endif

LIB = ../source/librilib.a

all: $(EXAMPLES)

%: %.c
	$(CC) $^ $(LIB) $(LIBS) -I../include -o $@

clean:
	rm -f $(EXAMPLES) *.obj *.exp *.lib *.exe
