CC ?= gcc

LIBS := -lgdi32 -ggdb -lopengl32
LIB_EXT = .dll
detected_OS = windows
OBJ_FILE = .o
CARGS = -fPIC

OBJECTS =	gfx$(OBJ_FILE) \
			core$(OBJ_FILE) \


# not using a cross compiler
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
endif

ifneq (,$(filter $(CC),cl /opt/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	LIBS =	
	OBJ_FILE = .obj
	CARGS = 
else ifneq (,$(filter $(CC),emcc em++))
	EXPORTED_JS = -s EXPORTED_RUNTIME_METHODS="['stringToNewUTF8']"
	LIBS = -s WASM=1 -s ASYNCIFY -s GL_SUPPORT_EXPLICIT_SWAP_CONTROL=1 $(EXPORTED_JS) -s FULL_ES3 -s USE_WEBGL2 
	detected_OS = web
	LIBS += -lm
else
	LIBS += -lm
endif

CARGS = -I../include -D RAPP_RENDERER_OPENGL

all:
	make librilib$(LIB_EXT)
	make librilib.a

%$(OBJ_FILE): %.c
	$(CC) $(CARGS) -c $^ 

librilib$(LIB_EXT): $(OBJECTS)  
ifneq (,$(filter $(CC),cl /opt/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	link -DLL /OUT:$@ $^
else
	$(CC) -D$(PLATFORM) -D$(RENDERER) -shared $^ $(CARGS) $(LIBS) -o $@
endif

librilib.a: $(OBJECTS)	
	ar rcs $@ $^

clean:
	rm -f librilib.a *.o librilib.so librilib.dll librilib.dylib *.obj librilib.lib librilib.exp

