/*
*
*	rapp 0.01-dev
*
* Copyright (C) 2025 ColleagueRiley
*
* libpng license
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*
*/

#if _MSC_VER
	#pragma comment(lib, "gdi32")
	#pragma comment(lib, "shell32")
	#pragma comment(lib, "opengl32")
	#pragma comment(lib, "winmm")
	#pragma comment(lib, "user32")
#endif

#ifndef RAPPAPI
#if defined(_WIN32)
        #if defined(__TINYC__)
            #define __declspec(x) __attrapp_bute__((x))
        #endif
        #if defined(RAPPLIB_SHARED)
            #define RAPPAPI __declspec(dllexport)
        #elif defined(RAPPLIB_USE_SHARED)
            #define RAPPAPI __declspec(dllimport)
        #endif
    #else
        #if defined(RAPPLIB_EXPORT)
            #define RAPPAPI __attrapp_bute__((visibility("default")))
        #endif
    #endif
#endif

#ifndef RAPPAPI
	#define RAPPAPI 
#endif

#ifndef RAPP_ENUM
	#define RAPP_ENUM(type, name) type name; enum
#endif


#if defined(__cplusplus)
	extern "C" {
#endif

	/* makes sure the header file part is only defined once by default */
#ifndef RAPP_HEADER

#define RAPP_HEADER

#include <stddef.h>
#if !defined(u8)
	#ifdef RAPP_USE_INT /* optional for any system that might not have stdint.h */
		typedef unsigned char 	u8;
		typedef signed char		i8;
		typedef unsigned short  u16;
		typedef signed short 	i16;
		typedef unsigned long int 	u32;
		typedef signed long int		i32;
		typedef unsigned long long	u64;
		typedef signed long long		i64;
	#else /* use stdint standard types instead of c ""standard"" types */
		#include <stdint.h>

		typedef uint8_t     u8;
		typedef int8_t      i8;
		typedef uint16_t   u16;
		typedef int16_t    i16;
		typedef uint32_t   u32;
		typedef int32_t    i32;
		typedef uint64_t   u64;
		typedef int64_t    i64;
	#endif
	#define u8 u8
#endif

#ifndef RAPP_BOOL_DEFINED /* rapp bool type */
	#define RAPP_BOOL_DEFINED
    typedef u8 rapp_bool;
#endif

#define RAPP_TRUE (rapp_bool)1
#define RAPP_FALSE (rapp_bool)0
#define RAPP_BOOL(x) (rapp_bool)((x) ? RAPP_TRUE : RAPP_FALSE) /* force an value to be 0 or 1 */

#define rapp_key u8

/* 
*******
rapp_[shape]
*******
*/

/*! basic vector type, if there's not already a point/vector type of choice */
#ifndef rapp_point
	typedef struct { i32 x, y; } rapp_point;
#endif

/*! basic rect type, if there's not already a rect type of choice */
#ifndef rapp_rect
	typedef struct { i32 x, y, w, h; } rapp_rect;
#endif

/*! basic area type, if there's not already a area type of choice */
#ifndef rapp_area
	typedef struct { u32 w, h; } rapp_area;
#endif

#if defined(__cplusplus) && !defined(__APPLE__)
#define RAPP_POINT(x, y) {(i32)x, (i32)y}
#define rapp_rect(x, y, w, h) {(i32)x, (i32)y, (i32)w, (i32)h}
#define RAPP_AREA(w, h) {(u32)w, (u32)h}
#else
#define RAPP_POINT(x, y) (rapp_point){(i32)(x), (i32)(y)}
#define RAPP_RECT(x, y, w, h) (rapp_rect){(i32)(x), (i32)(y), (i32)(w), (i32)(h)}
#define RAPP_AREA(w, h) (rapp_area){(u32)(w), (u32)(h)}
#endif

typedef struct rapp_rectF { float x, y, w, h; } rapp_rectF;
#define RAPP_RECTF(x, y, w, h) (rapp_rectF){(float)x, (float)y, (float)w, (float)h}

typedef struct rapp_pointF { float x, y; } rapp_pointF;
#define RAPP_POINTF(x, y) (rapp_pointF){x, y}

typedef struct rapp_point3D { float x, y, z; } rapp_point3D;
#define RAPP_POINT3D(x, y, z) (rapp_point3D){(float)x, (float)y, (float)z}

typedef struct rapp_point4D { float x, y, z, w; } rapp_point4D;
#define RAPP_POINT4D(x, y, z, w) (rapp_point3D){(float)x, (float)y, (float)z, (float)w}

typedef struct rapp_areaF { float w, h;} rapp_AreaF;
#define RAPP_AREAF(w, h) (rapp_areaF){(float)w, (float)h}

typedef struct rapp_circle {
    i32 x, y, d;
} rapp_circle;
#define RAPP_CIRCLE(x, y, d) (rapp_circle){(i32)x, (i32)y, (i32)d}

typedef struct rapp_circleF { float x, y, d; } rapp_circleF;
#define RAPP_CIRCLEF(x, y, d) (rapp_circleF){(float)x, (float)y, (float)d}

typedef struct rapp_triangle {
    rapp_point p1, p2, p3;
} rapp_triangle;
#define RAPP_TRIANGLE(p1, p2, p3) (rapp_triangle){p1, p2, p3}

typedef struct rapp_triangleF { rapp_pointF p1, p2, p3; } rapp_triangleF;
#define RAPP_TRIANGLEF(p1, p2, p3) (rapp_triangleF){p1, p2, p3}

typedef struct rapp_triangle3D {
    rapp_point3D p1, p2, p3;
} rapp_triangle3D;
#define RAPP_TRIANGLE3D(p1, p2, p3) (rapp_triangle3D){p1, p2, p3}

#define rapp_createTriangle(x1, y1, x2, y2, x3, y3) (rapp_triangle){{x1, y1}, {x2, y2}, {x3, y3}}
#define rapp_createTriangleF(x1, y1, x2, y2, x3, y3) (rapp_triangleF){{x1, y1}, {x2, y2}, {x3, y3}}
#define rapp_createTriangle3D(x1, y1, x2, y2, x3, y3) (rapp_triangle){{x1, y1, z1}, {x2, y2, z3}, {x3, y3, z3}}

typedef struct rapp_cube {
    float x, y, z, w, h, l;
} rapp_cube;
#define RAPP_CUBE(x, y, z, w, h, l) (rapp_cube){x, y, z, w, h, l}

/* drawing functions */
#ifndef rapp_texture
#define rapp_texture size_t
#endif
typedef struct rapp_image { rapp_texture tex; rapp_area srcSize; } rapp_image;

/* 
the color stucture is in 
aABGR by default for performance reasons 
(converting color to hex for example)
*/
typedef struct rapp_color {
    u8 a, b, g, r;
} rapp_color;

#define RAPP_RGBA(r, g, b, a) ((rapp_color){(u8)(a), (u8)(b), (u8)(g), (u8)(r)})
#define RAPP_RGB(r, g, b) ((rapp_color){255, (u8)(b), (u8)(g), (u8)(r)})

#define rapp_color_TO_HEX(color) ((u32)(color) & 0xFFFFFF00)
#define RAPP_RGB_TO_HEX(r, g, b, a) (rapp_color_TO_HEX(RAPP_RGBA(r, g, b, a)))
#define RAPP_RGBA_TO_HEX(r, g, b) (rapp_color_TO_HEX(RAPP_RGB(r, g, b, a)))



typedef RAPP_ENUM(u8, rapp_eventType) {
	/*! event codes */
	rapp_eventNone = 0, /*!< no event has been sent */
 	rapp_keyPressed, /* a key has been pressed */
	rapp_keyReleased, /*!< a key has been released */
	/*! key event note
		the code of the key pressed is stored in
		rapp_event.key
		!!Keycodes defined at the bottom of the RAPP_HEADER part of this file!!

		rapp_event.keyMod holds the current keyMod
		this means if CapsLock, NumLock are active or not
	*/
	rapp_mouseButtonPressed, /*!< a mouse button has been pressed (left,middle,right) */
	rapp_mouseButtonReleased, /*!< a mouse button has been released (left,middle,right) */
	rapp_mousePosChanged, /*!< the position of the mouse has been changed */
	/*! mouse event note
		the x and y of the mouse can be found in the vector, rapp_event.point

		rapp_event.button holds which mouse button was pressed
	*/
	rapp_gamepadConnected, /*!< a gamepad was connected */
	rapp_gamepadDisconnected, /*!< a gamepad was disconnected */
	rapp_gamepadButtonPressed, /*!< a gamepad button was pressed */
	rapp_gamepadButtonReleased, /*!< a gamepad button was released */
	rapp_gamepadAxisMove, /*!< an axis of a gamepad was moved */
	/*! gamepad event note
		rapp_event.gamepad holds which gamepad was altered, if any
		rapp_event.button holds which gamepad button was pressed

		rapp_event.axis holds the data of all the axises
		rapp_event.axisesCount says how many axises there are
	*/
	rapp_windowMoved, /*!< the window was moved (by the user) */
	rapp_windowResized, /*!< the window was resized (by the user), [on WASM this means the browser was resized] */
	rapp_focusIn, /*!< window is in focus now */
	rapp_focusOut, /*!< window is out of focus now */
	rapp_mouseEnter, /* mouse entered the window */
	rapp_mouseLeave, /* mouse left the window */
	rapp_windowRefresh, /* The window content needs to be refreshed */

	/* attribs change event note
		The event data is sent straight to the window structure
		with win->r.x, win->r.y, win->r.w and win->r.h
	*/
	rapp_quit, /*!< the user clicked the quit button */
	rapp_DND, /*!< a file has been dropped into the window */
	rapp_DNDInit, /*!< the start of a dnd event, when the place where the file drop is known */
	/* dnd data note
		The x and y coords of the drop are stored in the vector rapp_event.point

		rapp_event.droppedFilesCount holds how many files were dropped

		This is also the size of the array which stores all the dropped file string,
		rapp_event.droppedFiles
	*/
	rapp_windowMaximized, /*!< the window was maximized */
	rapp_windowMinimized, /*!< the window was minimized */
	rapp_windowRestored, /*!< the window was restored */
	rapp_scaleUpdated, /*!< content scale factor changed */
};

/*! mouse button codes (rapp_event.button) */
typedef RAPP_ENUM(u8, rapp_mouseButton) {
	rapp_mouseLeft = 0, /*!< left mouse button is pressed */
	rapp_mouseMiddle, /*!< mouse-wheel-button is pressed */
	rapp_mouseright, /*!< right mouse button is pressed */
	rapp_mouseScrollUp, /*!< mouse wheel is scrolling up */
	rapp_mouseScrollDown, /*!< mouse wheel is scrolling down */
	rapp_mouseMisc1, rapp_mouseMisc2, rapp_mouseMisc3, rapp_mouseMisc4, rapp_mouseMisc5,
	rapp_mouseFinal
};

#ifndef RAPP_MAX_PATH
#define RAPP_MAX_PATH 260 /* max length of a path (for dnd) */
#endif
#ifndef RAPP_MAX_DROPS
#define RAPP_MAX_DROPS 260 /* max items you can drop at once */
#endif

#define RAPP_BIT(x) (1L << x)

/* for rapp_event.lockstate */
typedef RAPP_ENUM(u8, rapp_keymod) {
	rapp_modCapsLock = RAPP_BIT(0),
	rapp_modNumLock  = RAPP_BIT(1),
	rapp_modControl  = RAPP_BIT(2),
	rapp_modAlt = RAPP_BIT(3),
	rapp_modShift  = RAPP_BIT(4),
	rapp_modSuper = RAPP_BIT(5),
	rapp_modScrollLock = RAPP_BIT(6)
};

/*! gamepad button codes (based on xbox/playstation), you may need to change these values per controller */
typedef RAPP_ENUM(u8, rapp_gamepadCodes) {
	rapp_gamepadNone = 0, /*!< or PS X button */
	rapp_gamepadA, /*!< or PS X button */
	rapp_gamepadB, /*!< or PS circle button */
	rapp_gamepadY, /*!< or PS triangle button */
	rapp_gamepadX, /*!< or PS square button */
	rapp_gamepadStart, /*!< start button */
	rapp_gamepadSelect, /*!< select button */
	rapp_gamepadHome, /*!< home button */
	rapp_gamepadUp, /*!< dpad up */
	rapp_gamepadDown, /*!< dpad down */
	rapp_gamepadLeft, /*!< dpad left */
	rapp_gamepadRight, /*!< dpad right */
	rapp_gamepadL1, /*!< left bump */
	rapp_gamepadL2, /*!< left trigger */
	rapp_gamepadR1, /*!< right bumper */
	rapp_gamepadR2, /*!< right trigger */
	rapp_gamepadL3,  /* left thumb stick */
	rapp_gamepadR3, /*!< right thumb stick */
	rapp_gamepadFinal
};

#ifndef rapp_NO_MONITOR
	/* monitor mode data | can be changed by the user (with functions)*/
	typedef struct rapp_monitorMode {
		rapp_area area; /*!< monitor workarea size */
		u32 refreshRate; /*!< monitor refresh rate */
		u8 red, blue, green; 
	} rapp_monitorMode;

	/*! structure for monitor data */
	typedef struct rapp_monitor {
		i32 x, y; /*!< x - y of the monitor workarea */
		char name[128]; /*!< monitor name */
		float scaleX, scaleY; /*!< monitor content scale */
		float pixelRatio; /*!< pixel ratio for monitor (1.0 for regular, 2.0 for hiDPI)  */
		float physW, physH; /*!< monitor physical size in inches */

		rapp_monitorMode mode;
	} rapp_monitor;

	/*! get an array of all the monitors (max 6) */
	RAPPAPI rapp_monitor* rapp_getMonitors(size_t* len);
	/*! get the primary monitor */
	RAPPAPI rapp_monitor rapp_getPrimarMonitor(void);

	typedef RAPP_ENUM(u8, rapp_modeRequest) {
		rapp_monitorScale = RAPP_BIT(0), /*!< scale the monitor size */
		rapp_monitorRefresh = RAPP_BIT(1), /*!< change the refresh rate */
		rapp_monitorRGB = RAPP_BIT(2), /*!< change the monitor RGB bits size */
		rapp_monitorAll = rapp_monitorScale | rapp_monitorRefresh | rapp_monitorRGB
	};

	/*! request a specific mode */
	RAPPAPI rapp_bool rapp_monitor_requestMode(rapp_monitor mon, rapp_monitorMode mode, rapp_modeRequest request);
	/*! check if 2 monitor modes are the same */
	RAPPAPI rapp_bool rapp_monitor_modeCompare(rapp_monitorMode mon, rapp_monitorMode mon2, rapp_modeRequest request);
#endif

/* rapp mouse loading */
typedef void rapp_mouse;

/*!< loads mouse icon from bitmap (similar to rapp_window_setIcon). Icon NOT resized by default */
RAPPAPI rapp_mouse* rapp_loadMouse(u8* icon, rapp_area a, i32 channels);
/*!< frees rapp_mouse data */
RAPPAPI void rapp_freeMouse(rapp_mouse* mouse);

/* NOTE: some parts of the data can represent different things based on the event (read comments in rapp_event struct) */
/*! Event structure for checking/getting events */
typedef struct rapp_event {
	rapp_eventType type; /*!< which event has been sent?*/
	rapp_point point; /*!< mouse x, y of event (or drop point) */
	rapp_point vector; /*!< raw mouse movement */
	float scaleX, scaleY; /*!< DPI scaling */

	rapp_key key; /*!< the physical key of the event, refers to where key is physically !!Keycodes defined at the bottom of the RAPP_HEADER part of this file!! */
	u8 keyChar; /*!< mapped key char of the event */

	rapp_bool repeat; /*!< key press event repeated (the key is being held) */
	rapp_keymod keyMod;

	u8 button; /* !< which mouse (or gamepad) button was pressed */
	double scroll; /*!< the raw mouse scroll value */

	u16 gamepad; /*! which gamepad this event applies to (if applicable to any) */
	u8 axisesCount; /*!< number of axises */

	u8 whichAxis; /* which axis was effected */
	rapp_point axis[4]; /*!< x, y of axises (-100 to 100) */

	/*! drag and drop data */
	/* 260 max paths with a max length of 260 */
	char** droppedFiles; /*!< dropped files */
	size_t droppedFilesCount; /*!< house many files were dropped */

	void* _win; /*!< the window this event applies too (for event queue events) */
} rapp_event;

/*! Optional arguments for making a windows */
typedef RAPP_ENUM(u32, rapp_windowFlags) {
	rapp_windowNoInitAPI = RAPP_BIT(0), /* do NOT init an API (mostly for bindings. you should use `#define RAPP_NO_API` in C) */
	rapp_windowNoBorder = RAPP_BIT(1), /*!< the window doesn't have a border */
	rapp_windowNoResize = RAPP_BIT(2), /*!< the window cannot be resized by the user */
	rapp_windowAllowDND = RAPP_BIT(3), /*!< the window supports drag and drop */
	rapp_windowHideMouse = RAPP_BIT(4), /*! the window should hide the mouse (can be toggled later on using `rapp_window_mouseShow`) */
	rapp_windowFullscreen = RAPP_BIT(5), /*!< the window is fullscreen by default */
	rapp_windowTransparent = RAPP_BIT(6), /*!< the window is transparent (only properly works on X11 and MacOS, although it's meant for for windows) */
	rapp_windowCenter = RAPP_BIT(7), /*! center the window on the screen */
	rapp_windowOpenglSoftware = RAPP_BIT(8), /*! use OpenGL software rendering */
	rapp_windowCocoaCHDirToRes = RAPP_BIT(9), /*! (cocoa only), change directory to resource folder */
	rapp_windowScaleToMonitor = RAPP_BIT(10), /*! scale the window to the screen */
	rapp_windowHide = RAPP_BIT(11), /*! the window is hidden */
	rapp_windowMaximize = RAPP_BIT(12),
	rapp_windowCenterCursor = RAPP_BIT(13),
	rapp_windowFloating = RAPP_BIT(14), /*!< create a floating window */
	rapp_windowFreeOnClose = RAPP_BIT(15), /*!< free (rapp_window_close) the rapp_window struct when the window is closed (by the end user) */
	rapp_windowFocusOnShow = RAPP_BIT(16), /*!< focus the window when it's shown */
	rapp_windowMinimize =RAPP_BIT(17), /*!< focus the window when it's shown */
	rapp_windowFocus = RAPP_BIT(18), /*!< if the window is in focus */
	rapp_windowedFullscreen = rapp_windowNoBorder | rapp_windowMaximize,
};

typedef struct rapp_window {
	void* src;
	void* userPtr; /* ptr for usr data */
	rapp_event event; /*!< current event */
	rapp_rect r; /*!< the x, y, w and h of the struct */
} rapp_window; /*!< window structure for managing the window */

typedef rapp_window* rapp_windowHandle;

/*! scale monitor to window size */
RAPPAPI rapp_bool rapp_monitor_scaleToWindow(rapp_monitor mon, rapp_window* win);

/** * @defgroup Window_management
* @{ */

/* NOTE: (windows) if the executable has an icon resource named RGFW_ICON, it will be set as the initial icon for the window */

RAPPAPI rapp_window* rapp_createWindow(
	const char* name, /* name of the window */
	rapp_rect rect, /* rect of window */
	rapp_windowFlags flags /* extra arguments ((u32)0 means no flags used)*/
); /*!< function to create a window and struct */

RAPPAPI rapp_window* rapp_createWindowPtr(
	const char* name, /* name of the window */
	rapp_rect rect, /* rect of window */
	rapp_windowFlags flags, /* extra arguments (NULL / (u32)0 means no flags used) */
	rapp_window* win /* ptr to the window struct you want to use */
); /*!< function to create a window (without allocating a window struct) */

/*! set the window flags (will undo flags if they don't match the old ones) */
RAPPAPI void rapp_window_setFlags(rapp_window* win, rapp_windowFlags);

/*! get the size of the screen to an area struct */
RAPPAPI rapp_area rapp_getScreenSize(void);

/*!
	for rapp_window_eventWait and rapp_window_checkEvents
	waitMS -> Allows the function to keep checking for events even after `rapp_window_checkEvent == NULL`
			  if waitMS == 0, the loop will not wait for events
			  if waitMS > 0, the loop will wait that many miliseconds after there are no more events until it returns
			  if waitMS == -1 or waitMS == the max size of an unsigned 32-bit int, the loop will not return until it gets another event
*/
typedef RAPP_ENUM(u32, rapp_eventWait) {
	rapp_eventNoWait = 0,
	rapp_eventWaitNext = -1
};

/*! sleep until rapp gets an event or the timer ends (defined by OS) */
RAPPAPI void rapp_window_eventWait(rapp_window* win, u32 waitMS);

/*!
	check all the events until there are none left.
	This should only be used if you're using callbacks only
*/
RAPPAPI rapp_event* rapp_window_checkEvent(rapp_window* win);

/*!
	tell rapp_window_eventWait to stop waiting (to be ran from another thread)
*/
RAPPAPI void rapp_stopCheckEvents(void);

/*! window managment functions */
RAPPAPI void rapp_window_close(rapp_window* win); /*!< close the window and free leftover data */

/*! move a window to a given point */
RAPPAPI void rapp_window_move(rapp_window* win,
	rapp_point v /*!< new pos */
);

#ifndef rapp_NO_MONITOR
	/*! move window to a specific monitor */
	RAPPAPI void rapp_window_moveToMonitor(rapp_window* win, rapp_monitor m /* monitor */);
#endif

/*! resize window to a current size/area */
RAPPAPI void rapp_window_resize(rapp_window* win, /*!< source window */
	rapp_area a /*!< new size */
);

/*! set window aspect ratio */
RAPPAPI void rapp_window_setAspectRatio(rapp_window* win, rapp_area a);
/*! set the minimum dimensions of a window */
RAPPAPI void rapp_window_setMinSize(rapp_window* win, rapp_area a);
/*! set the maximum dimensions of a window */
RAPPAPI void rapp_window_setMaxSize(rapp_window* win, rapp_area a);

RAPPAPI void rapp_window_focus(rapp_window* win); /*!< sets the focus to this window */
RAPPAPI rapp_bool rapp_window_isInFocus(rapp_window* win); /*!< checks the focus to this window */
RAPPAPI void rapp_window_raise(rapp_window* win); /*!< raise the window (to the top) */
RAPPAPI void rapp_window_maximize(rapp_window* win); /*!< maximize the window */
RAPPAPI void rapp_window_setFullscreen(rapp_window* win, rapp_bool fullscreen); /*!< turn fullscreen on / off for a window */
RAPPAPI void rapp_window_center(rapp_window* win); /*!< center the window */
RAPPAPI void rapp_window_minimize(rapp_window* win); /*!< minimize the window (in taskbar (per OS))*/
RAPPAPI void rapp_wiandow_restore(rapp_window* win); /*!< restore the window from minimized (per OS)*/
RAPPAPI void rapp_window_setFloating(rapp_window* win, rapp_bool floating); /*!< make the window a floating window */
RAPPAPI void rapp_window_setOpacity(rapp_window* win, u8 opacity); /*!< sets the opacity of a window */

/*! if the window should have a border or not (borderless) based on bool value of `border` */
RAPPAPI void rapp_window_setBorder(rapp_window* win, rapp_bool border);
RAPPAPI rapp_bool rapp_window_borderless(rapp_window* win);

/*! turn on / off dnd (rapp_windowAllowDND stil must be passed to the window)*/
RAPPAPI void rapp_window_setDND(rapp_window* win, rapp_bool allow);
/*! check if DND is allowed */
RAPPAPI rapp_bool rapp_window_allowsDND(rapp_window* win);


#ifndef rapp_NO_PASSTHROUGH
	/*! turn on / off mouse passthrough */
	RAPPAPI void rapp_window_setMousePassthrough(rapp_window* win, rapp_bool passthrough);
#endif

/*! rename window to a given string */
RAPPAPI void rapp_window_setName(rapp_window* win,
	const char* name
);


RAPPAPI u8* rapp_window_setIconImage(rapp_window* win, const char* file);
RAPPAPI void rapp_window_freeIconImage(u8* buffer);

typedef struct rapp_mouseImage { u8* image;  rapp_mouse* mouse; } rapp_mouseImage;
RAPPAPI rapp_mouseImage rapp_window_loadMouseImage(rapp_window* win, const char* file);
RAPPAPI void rapp_window_freeMouseImage(rapp_mouseImage  mouse);

RAPPAPI rapp_bool rapp_window_setIcon(rapp_window* win, /*!< source window */
	u8* icon /*!< icon bitmap */,
	rapp_area a /*!< width and height of the bitmap */,
	i32 channels /*!< how many channels the bitmap has (rgb : 3, rgba : 4) */
); /*!< image MAY be resized by default, set both the taskbar and window icon */

typedef RAPP_ENUM(u8, rapp_icon) {
	rapp_iconTaskbar = RAPP_BIT(0),
	rapp_iconWindow = RAPP_BIT(1),
	rapp_iconBoth = rapp_iconTaskbar | rapp_iconWindow
};
RAPPAPI rapp_bool rapp_window_setIconEx(rapp_window* win, u8* icon, rapp_area a, i32 channels, u8 type);

/*!< sets mouse to rapp_mouse icon (loaded from a bitmap struct) */
RAPPAPI void rapp_window_setMouse(rapp_window* win, rapp_mouse* mouse);

/*!< sets the mouse to a standard API cursor (based on rapp_MOUSE, as seen at the end of the RAPP_HEADER part of this file) */
RAPPAPI	rapp_bool rapp_window_setMouseStandard(rapp_window* win, u8 mouse);

RAPPAPI rapp_bool rapp_window_setMouseDefault(rapp_window* win); /*!< sets the mouse to the default mouse icon */
/*
	Locks cursor at the center of the window
	win->event.point becomes raw mouse movement data

	this is useful for a 3D camera
*/
RAPPAPI void rapp_window_mouseHold(rapp_window* win, rapp_area area);
/*! stop holding the mouse and let it move freely */
RAPPAPI void rapp_window_mouseUnhold(rapp_window* win);

/*! hide the window */
RAPPAPI void rapp_window_hide(rapp_window* win);
/*! show the window */
RAPPAPI void rapp_window_show(rapp_window* win);

/*
	makes it so `rapp_window_shouldClose` returns true or overrapp_des a window close 
	by modifying window flags
*/
RAPPAPI void rapp_window_setShouldClose(rapp_window* win, rapp_bool shouldClose);

/*! where the mouse is on the screen */
RAPPAPI rapp_point rapp_getGlobalMousePoint(void);

/*! where the mouse is on the window */
RAPPAPI rapp_point rapp_window_getMousePoint(rapp_window* win);

/*! show the mouse or hide the mouse */
RAPPAPI void rapp_window_showMouse(rapp_window* win, rapp_bool show);
/*! if the mouse is hidden */
RAPPAPI rapp_bool rapp_window_mouseHidden(rapp_window* win);
/*! move the mouse to a given point */
RAPPAPI void rapp_window_moveMouse(rapp_window* win, rapp_point v);

/*! if the window should close (rapp_close was sent or escape was pressed) */
RAPPAPI rapp_bool rapp_window_shouldClose(rapp_window* win);
/*! if the window is fullscreen */
RAPPAPI rapp_bool rapp_window_isFullscreen(rapp_window* win);
/*! if the window is hidden */
RAPPAPI rapp_bool rapp_window_isHidden(rapp_window* win);
/*! if the window is minimized */
RAPPAPI rapp_bool rapp_window_isMinimized(rapp_window* win);
/*! if the window is maximized */
RAPPAPI rapp_bool rapp_window_isMaximized(rapp_window* win);
/*! if the window is floating */
RAPPAPI rapp_bool rapp_window_isFloating(rapp_window* win);
/** @} */

/** * @defgroup Monitor
* @{ */

#ifndef RAPP_NO_MONITOR
/*
	scale the window to the monitor.
	This is run by default if the user uses the arg `rapp_scaleToMonitor` durapp_ng window creation
*/
RAPPAPI void rapp_window_scaleToMonitor(rapp_window* win);
/*! get the struct of the window's monitor  */
RAPPAPI rapp_monitor rapp_window_getMonitor(rapp_window* win);
#endif

/** @} */

/** * @defgroup Input
* @{ */

/*! if window == NULL, it checks if the key is pressed globally. Otherwise, it checks only if the key is pressed while the window in focus. */
RAPPAPI rapp_bool rapp_isPressed(rapp_window* win, rapp_key key); /*!< if key is pressed (key code)*/

RAPPAPI rapp_bool rapp_wasPressed(rapp_window* win, rapp_key key); /*!< if key was pressed (checks previous state only) (key code) */

RAPPAPI rapp_bool rapp_isHeld(rapp_window* win, rapp_key key); /*!< if key is held (key code) */
RAPPAPI rapp_bool rapp_isReleased(rapp_window* win, rapp_key key); /*!< if key is released (key code) */

/* if a key is pressed and then released, pretty much the same as rapp_isReleased */
RAPPAPI rapp_bool rapp_isClicked(rapp_window* win, rapp_key key /*!< key code */);

/*! if a mouse button is pressed */
RAPPAPI rapp_bool rapp_isMousePressed(rapp_window* win, rapp_mouseButton button /*!< mouse button code */ );
/*! if a mouse button is held */
RAPPAPI rapp_bool rapp_isMouseHeld(rapp_window* win, rapp_mouseButton button /*!< mouse button code */ );
/*! if a mouse button was released */
RAPPAPI rapp_bool rapp_isMouseReleased(rapp_window* win, rapp_mouseButton button /*!< mouse button code */ );
/*! if a mouse button was pressed (checks previous state only) */
RAPPAPI rapp_bool rapp_wasMousePressed(rapp_window* win, rapp_mouseButton button /*!< mouse button code */ );
/** @} */

/** * @defgroup Clipboard
* @{ */
typedef ptrdiff_t rapp_ssize_t;

RAPPAPI const char* rapp_readClipboard(size_t* size); /*!< read clipboard data */
/*! read clipboard data or send a NULL str to just get the length of the clipboard data */
RAPPAPI rapp_ssize_t rapp_readClipboardPtr(char* str, size_t strCapacity);
RAPPAPI void rapp_writeClipboard(const char* text, u32 textLen); /*!< write text to the clipboard */
/** @} */

/** * @defgroup gamepad
* @{ */

typedef RAPP_ENUM(u8, rapp_gamepadType) {
	rapp_gamepadMicrosoft = 0, rapp_gamepadSony, rapp_gamepadNintendo, rapp_gamepadLogitech, rapp_gamepadUnknown
};

/*! gamepad count starts at 0*/
RAPPAPI u32 rapp_isPressedGamepad(rapp_window* win, u8 controller, rapp_gamepadCodes button);
RAPPAPI u32 rapp_isReleasedGamepad(rapp_window* win, u8 controller, rapp_gamepadCodes button);
RAPPAPI u32 rapp_isHeldGamepad(rapp_window* win, u8 controller, rapp_gamepadCodes button);
RAPPAPI u32 rapp_wasPressedGamepad(rapp_window* win, u8 controller, rapp_gamepadCodes button);
RAPPAPI rapp_point rapp_getGamepadAxis(rapp_window* win, u16 controller, u16 whichAxis);
RAPPAPI const char* rapp_getGamepadName(rapp_window* win, u16 controller);
RAPPAPI size_t rapp_getGamepadCount(rapp_window* win);
RAPPAPI rapp_gamepadType rapp_getGamepadType(rapp_window* win, u16 controller);

/** @} */

/** * @defgroup graphics_API
* @{ */

/*!< make the window the current opengl drawing context

	NOTE:
 	if you want to switch the graphics context's thread,
	you have to run rapp_window_makeCurrent(NULL); on the old thread
	then rapp_window_makeCurrent(valid_window) on the new thread
*/
RAPPAPI void rapp_window_makeCurrent(rapp_window* win);

/* supports openGL, directX, OSMesa, EGL and software rendering */
RAPPAPI void rapp_window_swapBuffers(rapp_window* win); /*!< swap the renderingng buffer */
RAPPAPI void rapp_window_vsync(rapp_window* win, rapp_bool enable);

/* 
*********************
RAPP_GRAPHICS_CONTEXT
*********************
*/

/* 
*******
rapp_draw
*******
*/


RAPPAPI void rapp_setTexture(rapp_texture texture); /* apply texture to drawing */
RAPPAPI void rapp_setProgram(u32 program); /* use shader program for drawing */
RAPPAPI void rapp_setGradient(
                                float* gradient, /* array of gradients */
                                size_t len /* length of array */
                            ); /* apply gradient to drawing, based on color list*/
RAPPAPI void rapp_fill(rapp_bool fill); /* toggle filling, if fill is false it runs rapp_draw<whatever>_outline instead */
RAPPAPI void rapp_center(rapp_point3D center); /* the center of the drawing (or shape), this is used for rotation */

/* args clear after a draw function by default, this toggles that */
RAPPAPI void rapp_setClearArgs(rapp_bool clearArgs); /* toggles if args are cleared by default or not */
RAPPAPI void rapp_clearArgs(void); /* clears the args */
/* calculate the align a smaller rect with larger rect */
typedef RAPP_ENUM(u8, rapp_alignment) {
    rapp_alignNone = RAPP_BIT(0),
    /* horapp_zontal */
    rapp_alignLeft = RAPP_BIT(1),
    rapp_alignCenter = RAPP_BIT(2),
    rapp_alignRight = RAPP_BIT(3),
    
    /* vertical */
    rapp_alignUp = RAPP_BIT(4),
    rapp_alignMiddle = RAPP_BIT(5),
    rapp_alignDown = RAPP_BIT(6),

    rapp_alignHorizontal = rapp_alignLeft | rapp_alignCenter | rapp_alignRight,
    rapp_alignVertical = rapp_alignUp | rapp_alignMiddle | rapp_alignDown,
/* ex : alignment = (rapp_alignLeft | rapp_alignLeft) */
};

/* align smaller rect onto larger rect based on a given alignment */
RAPPAPI rapp_rect rapp_alignRect(rapp_rect larger, rapp_rect smaller, u16 alignment);
RAPPAPI rapp_rectF rapp_alignRectF(rapp_rectF larger, rapp_rectF smaller, u16 alignment);

typedef struct rapp_mat4 {
    float m[16];
} rapp_mat4;

RAPPAPI rapp_mat4 rapp_initDrawMatrapp_x(rapp_point3D center);
RAPPAPI void rapp_clear(rapp_color color);
RAPPAPI void rapp_viewport(i32 x, i32 y, i32 w, i32 h);
/* create a texture based on a given bitmap, this must be freed later using rapp_deleteTexture or opengl*/
RAPPAPI rapp_texture rapp_createTexture(u8* bitmap, rapp_area memsize,  u8 channels);
/* delete a texture */
RAPPAPI void rapp_deleteTexture(rapp_texture tex);
/* starts scissorapp_ng */
RAPPAPI void rapp_scissorStart(rapp_rectF scissor);
/* stops scissorapp_ng */
RAPPAPI void rapp_scissorEnd(void);

/*!< draw current batch to the window */
RAPPAPI void rapp_window_draw(rapp_window* win);

/*!< clear graphics and update window size info (should be ran before RSGL_draw<x> calls) */
RAPPAPI void rapp_window_clear(rapp_window* win, rapp_color color);

/* custom shader program */
typedef struct rapp_programInfo {
    u32 vShader, fShader, program;
} rapp_programInfo;

RAPPAPI rapp_programInfo rapp_renderCreateProgram(const char* VShaderCode, const char* FShaderCode, const char* posName, const char* texName, const char* colorName);
RAPPAPI void rapp_renderDeleteProgram(rapp_programInfo program);
RAPPAPI void rapp_renderSetShaderValue(u32 program, char* var, float value[], u8 len);

/* these are RFont functions that also must be defined by the renderer

32 RFont_create_atlas(u32 atlasWidth, u32 atlasHeight);
void RFont_bitmap_to_atlas(rapp_rsoft_texture atlas, u8* bitmap, float x, float y, float w, float h);

*/

/* rapp_ translation */
typedef struct rapp_camera {
    rapp_point3D pos;
    float fov; 
    float pitch, yaw; 
} rapp_camera;

RAPPAPI rapp_mat4 rapp_getCameraMatrix(rapp_camera camera);
RAPPAPI rapp_mat4 rapp_getCameraMatrixEx(rapp_camera camera, float ratio, float maxPitch, float min, float max);

RAPPAPI void rapp_setGlobalMatrix(rapp_mat4 matrix);
RAPPAPI void rapp_resetGlobalMatrix();


RAPPAPI rapp_mat4 rapp_loadIdentity(void);
RAPPAPI rapp_mat4 rapp_mat4Multiply(float left[16], float right[16]);
RAPPAPI rapp_mat4 rapp_rotate(rapp_mat4 matrix, float angle, float x, float y, float z); 
RAPPAPI rapp_mat4 rapp_translate(rapp_mat4 matrix, float x, float y, float z);
RAPPAPI rapp_mat4 rapp_perspective(rapp_mat4 matrix, float fovY, float aspect, float zNear, float zFar);
RAPPAPI rapp_mat4 rapp_ortho(rapp_mat4 matrix, float left, float right, float bottom, float top, float znear, float zfar);
RAPPAPI rapp_mat4 rapp_scale(rapp_mat4 matrix, float x, float y, float z);


/* 2D shape drawing */
/* in the function names, F means float */

RAPPAPI void rapp_drawPoint(rapp_point p, rapp_color c);
RAPPAPI void rapp_drawPointF(rapp_pointF p, rapp_color c);

RAPPAPI void rapp_drawTriangle(rapp_triangle t, rapp_color c);
RAPPAPI void rapp_drawTriangleF(rapp_triangleF t, rapp_color c);

RAPPAPI void rapp_drawtriangleHyp(rapp_pointF p, size_t angle, float hypotenuse, rapp_color color);

RAPPAPI void rapp_drawRect(rapp_rect r, rapp_color c);
RAPPAPI void rapp_drawRectF(rapp_rectF r, rapp_color c);


RAPPAPI void rapp_drawRoundRect(rapp_rect r, rapp_point rounding, rapp_color c);
RAPPAPI void rapp_drawRoundRectF(rapp_rectF r, rapp_point rounding, rapp_color c);

RAPPAPI void rapp_drawPolygon(rapp_rect r, u32 sides, rapp_color c);
RAPPAPI void rapp_drawPolygonF(rapp_rectF r, u32 sides, rapp_color c);

RAPPAPI void rapp_drawArc(rapp_rect o, rapp_point arc, rapp_color color);
RAPPAPI void rapp_drawArcF(rapp_rectF o, rapp_pointF arc, rapp_color color);

RAPPAPI void rapp_drawCircle(rapp_circle c, rapp_color color);
RAPPAPI void rapp_drawCircleF(rapp_circleF c, rapp_color color);

RAPPAPI void rapp_drawOval(rapp_rect o, rapp_color c);
RAPPAPI void rapp_drawOvalF(rapp_rectF o, rapp_color c);

RAPPAPI void rapp_drawLine(rapp_point p1, rapp_point p2, u32 thickness, rapp_color c);
RAPPAPI void rapp_drawLineF(rapp_pointF p1, rapp_pointF p2, u32 thickness, rapp_color c);

/* 3D drawing */
RAPPAPI void rapp_drawTriangle3D(rapp_triangle3D t, rapp_color c);
RAPPAPI void rapp_drawPoint3D(rapp_point3D p, rapp_color c);
RAPPAPI void rapp_drawLine3D(rapp_point3D p1, rapp_point3D p2, u32 thickness, rapp_color c);
RAPPAPI void rapp_drawCube(rapp_cube cube, rapp_color c);


/* 2D outlines */

/* thickness means the thickness of the line */

RAPPAPI void rapp_drawTriangleOutline(rapp_triangle t, u32 thickness, rapp_color c);
RAPPAPI void rapp_drawTriangleFOutline(rapp_triangleF t, u32 thickness, rapp_color c);

RAPPAPI void rapp_drawRectOutline(rapp_rect r, u32 thickness, rapp_color c);
RAPPAPI void rapp_drawRectFOutline(rapp_rectF r, u32 thickness, rapp_color c);

RAPPAPI void rapp_drawRoundRectOutline(rapp_rect r, rapp_point rounding, u32 thickness, rapp_color c);
RAPPAPI void rapp_drawRoundRectFOutline(rapp_rectF r, rapp_point rounding, u32 thickness, rapp_color c);

RAPPAPI void rapp_drawPolygonOutline(rapp_rect r, u32 sides, u32 thickness, rapp_color c);
RAPPAPI void rapp_drawPolygonFOutline(rapp_rectF r, u32 sides, u32 thickness, rapp_color c);

RAPPAPI void rapp_drawArcOutline(rapp_rect o, rapp_point arc, u32 thickness, rapp_color color);
RAPPAPI void rapp_drawArcFOutline(rapp_rectF o, rapp_pointF arc, u32 thickness, rapp_color color);

RAPPAPI void rapp_drawCircleOutline(rapp_circle c, u32 thickness, rapp_color color);
RAPPAPI void rapp_drawCircleFOutline(rapp_circleF c, u32 thickness, rapp_color color);

RAPPAPI void rapp_drawOvalOutline(rapp_rect o, u32 thickness, rapp_color c);
RAPPAPI void rapp_drawOvalFOutline(rapp_rectF o, u32 thickness, rapp_color c);

struct RSGL_font;
typedef struct RSGL_font rapp_font;

/* format a string */
RAPPAPI const char* rapp_strFmt(const char* string, ...);

/* loads a font into rapp_, returns it's index into the rapp_fonts array, this is used as an id in later functions */
RAPPAPI rapp_font* rapp_loadFont(const char* font);
/* (pro) loads a font into rapp_, returns it's index into the rapp_fonts array, this is used as an id in later functions 
    using a given atlasWidth + atlasHeight
*/
RAPPAPI rapp_font* rapp_loadFontEx(const char* font, size_t atlasWidth, size_t atlasHeight);
/* sets font as the current font in use based on index in rapp_font, given when it was loaded */
RAPPAPI void rapp_setFont(rapp_font* font);

RAPPAPI void rapp_drawText_len(const char* text, size_t len, rapp_circle c, rapp_color color);
RAPPAPI void rapp_drawText_pro(const char* text, size_t len, float spacing, rapp_circle c, rapp_color color);
RAPPAPI void rapp_drawText(const char* text, rapp_circle c, rapp_color color);
#define RAPP_drawTextF(text, font, c, color) \
    rapp_setFont(font);\
    rapp_drawText(text, c, color);

/* align text onto larger rect based on a given alignment */
RAPPAPI rapp_circle rapp_alignText(const char* str, rapp_circle c, rapp_rectF larger, u8 alignment);
/* align text based on a length */
RAPPAPI rapp_circle rapp_alignText_len(const char* str, size_t str_len, rapp_circle c, rapp_rectF larger, u8 alignment);

/* 
    returns the width of a text when rendered with the set font with the size of `fontSize
    stops at `textEnd` or when it reaches '\0'
*/
RAPPAPI rapp_area rapp_textArea(const char* text, u32 fontSize, size_t textEnd);
RAPPAPI rapp_area rapp_textLineArea(const char* text, u32 fontSize, size_t textEnd, size_t line);
#define RAPP_textAreaF(text, fontSize, textEnd) \
    rapp_setFont(font);\
    rapp_textAreaF(text, fontSize, textEnd);

/* 
    this creates a texture based on a given image, draws it on a rectangle and then returns the loaded texture 
    
    if the rectangle's width and height are 0 it doesn't draw the image
    the texture is loaded into rapp_image, this means it doesn't need to be freed
    but you can still free it early
*/

RAPPAPI rapp_image rapp_loadImage(const char* image);
RAPPAPI rapp_image rapp_drawImage(rapp_image, rapp_rect r);
RAPPAPI rapp_image rapp_drawImageFile(const char* image, rapp_rect r);

/* 
    these two functions can be used before rapp_renderCreateTexture in order to create 
    an swizzle'd texutre or atlas
*/

/* 
*******
extra
*******
*/

typedef struct RAPP_BATCH {
    size_t start, len; /* when batch starts and it's length */
    u32 type;
    rapp_texture tex;
    float lineWidth;
    rapp_mat4 matrix;
} RAPP_BATCH; /* batch data type for rendering */

typedef struct RAPP_RENDER_INFO {
    RAPP_BATCH* batches;

    float* verts;
    float* texCoords;
    float* colors;

    size_t len; /* number of batches*/
    size_t vert_len; /* number of verts */
    rapp_mat4 matrix;
} RAPP_RENDER_INFO; /* render data */

typedef struct rapp_renderer {
    void (* batch)(RAPP_RENDER_INFO* info);
    void (* init)(void* proc, RAPP_RENDER_INFO* info); /* init render backend */
    void (* free)(void); /* free render backend */
    void (* clear)(float r, float g, float b, float a);
    void (* viewport)(i32 x, i32 y, i32 w, i32 h);
    rapp_texture (* createTexture)(u8* bitmap, rapp_area memsize,  u8 channels);
    void (* updateTexture)(rapp_texture texture, u8* bitmap, rapp_area memsize, u8 channels);
    void (* deleteTexture)(rapp_texture tex);
    void (* scissorStart)(rapp_rectF scissor);
    void (* scissorEnd)(void);
    rapp_programInfo (*createProgram)(const char* VShaderCode, const char* FShaderCode, const char* posName, const char* texName, const char* colorName);
    void (* deleteProgram)(rapp_programInfo program);
    void (* setShaderValue)(u32 program, char* var, float value[], u8 len);
    rapp_texture (* createAtlas)(u32 atlasWidth, u32 atlasHeight);
    u8 (* resizeAtlas)(rapp_texture* atlas, u32 newWidth, u32 newHeight);
    void (* bitmapToAtlas)(rapp_texture atlas, u8* bitmap, float x, float y, float w, float h);
} rapp_renderer;


RAPPAPI void rapp_setRenderer(rapp_renderer renderer);

/* ** collision functions ** */
RAPPAPI rapp_bool rapp_circleCollidePoint(rapp_circle c, rapp_point p);
RAPPAPI rapp_bool rapp_circleCollideRect(rapp_circle c, rapp_rect r);
RAPPAPI rapp_bool rapp_circleCollide(rapp_circle cir1, rapp_circle cir2);
RAPPAPI rapp_bool rapp_rectCollidePoint(rapp_rect r, rapp_point p);
RAPPAPI rapp_bool rapp_rectCollide(rapp_rect r, rapp_rect r2);
RAPPAPI rapp_bool rapp_pointCollide(rapp_point p, rapp_point p2);

RAPPAPI rapp_bool rapp_circleCollidePointF(rapp_circleF c, rapp_pointF p);
RAPPAPI rapp_bool rapp_circleCollideRectF(rapp_circleF c, rapp_rectF r);
RAPPAPI rapp_bool rapp_circleCollideF(rapp_circleF cir1, rapp_circleF cir2);
RAPPAPI rapp_bool rapp_rectCollidePointF(rapp_rectF r, rapp_pointF p);
RAPPAPI rapp_bool rapp_rectCollideF(rapp_rectF r, rapp_rectF r2);
RAPPAPI rapp_bool rapp_pointCollideF(rapp_pointF p, rapp_pointF p2);

RAPPAPI rapp_bool rapp_cubeCollideVec3(rapp_cube cube, rapp_point3D p); 
RAPPAPI rapp_bool rapp_cubeCollide(rapp_cube r, rapp_cube r2);

/* ** vector math ** */
RAPPAPI rapp_point rapp_pointAdd(rapp_point v1, rapp_point v2);
RAPPAPI rapp_pointF rapp_pointFAdd(rapp_pointF v1, rapp_pointF v2);
RAPPAPI rapp_point3D rapp_point3DAdd(rapp_point3D v1, rapp_point3D v2);
RAPPAPI rapp_point4D rapp_point4DAdd(rapp_point4D v1, rapp_point4D v2);

RAPPAPI rapp_point rapp_pointSubrtact(rapp_point v1, rapp_point v2);
RAPPAPI rapp_pointF rapp_pointFSubrtact(rapp_pointF v1, rapp_pointF v2);
RAPPAPI rapp_point3D rapp_point3DSubtract(rapp_point3D v1, rapp_point3D v2);
RAPPAPI rapp_point4D rapp_point4DSubtract(rapp_point4D v1, rapp_point4D v2);

RAPPAPI rapp_point rapp_pointMultiply(rapp_point v1, rapp_point v2);
RAPPAPI rapp_pointF rapp_pointFMultiply(rapp_pointF v1, rapp_pointF v2);
RAPPAPI rapp_point3D rapp_point3DMultiply(rapp_point3D v1, rapp_point3D v2);
RAPPAPI rapp_point4D rapp_point4DMultiply(rapp_point4D v1, rapp_point4D v2);

RAPPAPI rapp_point rapp_pointDivide(rapp_point v1, rapp_point v2);
RAPPAPI rapp_pointF rapp_pointFDivide(rapp_pointF v1, rapp_pointF v2);
RAPPAPI rapp_point3D rapp_point3DDivide(rapp_point3D v1, rapp_point3D v2);
RAPPAPI rapp_point4D rapp_point4DDivide(rapp_point4D v1, rapp_point4D v2);

RAPPAPI rapp_point rapp_pointMultiplyMat4(rapp_point vec, rapp_mat4 matrix); 
RAPPAPI rapp_pointF rapp_pointFMultiplyMat4(rapp_pointF vec, rapp_mat4 matrix); 
RAPPAPI rapp_point3D rapp_point3DMultiplyMat4(rapp_point3D vec, rapp_mat4 matrix); 
RAPPAPI rapp_point4D rapp_point4DMultiplyMat4(rapp_point4D vec, rapp_mat4 matrix); 

RAPPAPI rapp_point rapp_pointToWorld(rapp_point v, float screenWidth, float screenHeight);
RAPPAPI rapp_pointF rapp_pointFToWorld(rapp_pointF v, float screenWidth, float screenHeight);
RAPPAPI rapp_point3D rapp_point3DToWorld(rapp_point3D v, float screenWidth, float screenHeight);
RAPPAPI rapp_point4D rapp_point4DToWorld(rapp_point4D v, float screenWidth, float screenHeight);

RAPPAPI rapp_point rapp_pointToScreen(rapp_point v, float screenWidth, float screenHeight);
RAPPAPI rapp_pointF rapp_pointFToScreen(rapp_pointF v, float screenWidth, float screenHeight);
RAPPAPI rapp_point3D rapp_point3DToScreen(rapp_point3D v, float screenWidth, float screenHeight);  
RAPPAPI rapp_point4D rapp_point4DToScreen(rapp_point4D v, float screenWidth, float screenHeight);

RAPPAPI rapp_point3D rapp_point4ToVec3(rapp_point4D v);

/* extra math */
RAPPAPI float rapp_clamp(float value, float min, float max);
RAPPAPI float rapp_normalize(float value, float start, float end);
RAPPAPI float rapp_lerp(float start, float end, float amount);
RAPPAPI float rapp_wrap(float value, float min, float max);

RAPPAPI float rapp_pointDist(rapp_point v1, rapp_point v2);
RAPPAPI float rapp_pointFDist(rapp_pointF v1, rapp_pointF v2);

RAPPAPI float rapp_point3Dist(rapp_point3D v1, rapp_point3D v2);

RAPPAPI float rapp_point4Dist(rapp_point4D v1, rapp_point4D v2);

RAPPAPI float rapp_pointFDot(rapp_pointF v, rapp_pointF v1);
RAPPAPI float rapp_point3Dot(rapp_point3D v, rapp_point3D v1);
RAPPAPI float rapp_point4DDot(rapp_point4D v, rapp_point4D v1);

RAPPAPI float rapp_pointCross(rapp_point v, rapp_point v1);
RAPPAPI float rapp_pointFCross(rapp_pointF v, rapp_pointF v1);
RAPPAPI float rapp_point3DCross(rapp_point3D v, rapp_point3D v1);
RAPPAPI float rapp_point4DCross(rapp_point4D v, rapp_point4D v1);

RAPPAPI rapp_bool rapp_pointCmp(rapp_point v, rapp_point v1);
RAPPAPI rapp_bool rapp_pointFCmp(rapp_pointF v, rapp_pointF v1);
RAPPAPI rapp_bool rapp_point3DCmp(rapp_point3D v, rapp_point3D v1);
RAPPAPI rapp_bool rapp_point4DCmp(rapp_point4D v, rapp_point4D v1);

typedef void (*rapp_proc)(void); // function pointer equivalent of void*

/*! native API functions */
/*! OpenGL init hints */
typedef RAPP_ENUM(u8, rapp_glHints)  {
	rapp_glStencil = 0,  /*!< set stencil buffer bit size (8 by default) */
	rapp_glSamples, /*!< set number of sampiling buffers (4 by default) */
	rapp_glStereo, /*!< use GL_STEREO (GL_FALSE by default) */
	rapp_glAuxBuffers, /*!< number of aux buffers (0 by default) */
	rapp_glDoubleBuffer, /*!< request double bufferapp_ng */
	rapp_glRed, rapp_glGreen, rapp_glBlue, rapp_glAlpha, /*!< set RGBA bit sizes */
	rapp_glDepth, 
	rapp_glAccumRed, rapp_glAccumGreen, rapp_glAccumBlue,rapp_glAccumAlpha, /*!< set accumulated RGBA bit sizes */
	rapp_glSRGB, /*!< request sRGA */
	rapp_glRobustness, /*!< request a robust context */
	rapp_glDebug, /*!< request opengl debugging */
	rapp_glNoError, /*!< request no opengl errors */
	rapp_glReleaseBehavior,
	rapp_glProfile,
	rapp_glMajor, rapp_glMinor,
	rapp_glFinalHint, /*!< the final hint (not for setting) */
	rapp_releaseFlush = 0,  rapp_glReleaseNone, /* rapp_glReleaseBehavior options */
	rapp_glCore = 0,  rapp_glCompatibility /*!< rapp_glProfile options */
};
RAPPAPI void rapp_setGLHint(rapp_glHints hint, i32 value);
RAPPAPI rapp_proc rapp_getProcAddress(const char* procname); /*!< get native opengl proc address */
/** * @defgroup Supporting

* @{ */
RAPPAPI double rapp_getTime(void); /*!< get time in seconds since rapp_setTime, which ran when the first window is open  */
RAPPAPI u64 rapp_getTimeNS(void); /*!< get time in nanoseconds rapp_setTime, which ran when the first window is open */
RAPPAPI void rapp_sleep(u64 milisecond); /*!< sleep for a set time */
RAPPAPI void rapp_setTime(double time); /*!< set timer in seconds */
RAPPAPI u64 rapp_getTimerValue(void); /*!< get API timer value */
RAPPAPI u64 rapp_getTimerFreq(void); /*!< get API time freq */

/*< updates fps / sets fps to cap (must by ran manually by the user at the end of a frame), returns current fps */
RAPPAPI u32 rapp_checkFPS(double startTime, u32 frameCount, u32 fpsCap);

/*!
	key codes and mouse icon enums
*/
#undef rapp_key
typedef RAPP_ENUM(u8, rapp_key) {
	rapp_keyNULL = 0,
	rapp_escape = '\033',
	rapp_backtick = '`',
	rapp_0 = '0',
	rapp_1 = '1',
	rapp_2 = '2',
	rapp_3 = '3',
	rapp_4 = '4',
	rapp_5 = '5',
	rapp_6 = '6',
	rapp_7 = '7',
	rapp_8 = '8',
	rapp_9 = '9',

	rapp_minus = '-',
	rapp_equals = '=',
	rapp_backSpace = '\b',
	rapp_tab = '\t',
	rapp_space = ' ',

	rapp_a = 'a',
	rapp_b = 'b',
	rapp_c = 'c',
	rapp_d = 'd',
	rapp_e = 'e',
	rapp_f = 'f',
	rapp_g = 'g',
	rapp_h = 'h',
	rapp_i = 'i',
	rapp_j = 'j',
	rapp_k = 'k',
	rapp_l = 'l',
	rapp_m = 'm',
	rapp_n = 'n',
	rapp_o = 'o',
	rapp_p = 'p',
	rapp_q = 'q',
	rapp_r = 'r',
	rapp_s = 's',
	rapp_t = 't',
	rapp_u = 'u',
	rapp_v = 'v',
	rapp_w = 'w',
	rapp_x = 'x',
	rapp_y = 'y',
	rapp_z = 'z',

	rapp_period = '.',
	rapp_comma = ',',
	rapp_slash = '/',
	rapp_bracket = '{',
	rapp_closeBracket = '}',
	rapp_semicolon = ';',
	rapp_apostrophe = '\'',
	rapp_backSlash = '\\',
	rapp_return = '\n',

	rapp_delete = '\177', /* 127 */

	rapp_F1,
	rapp_F2,
	rapp_F3,
	rapp_F4,
	rapp_F5,
	rapp_F6,
	rapp_F7,
	rapp_F8,
	rapp_F9,
	rapp_F10,
	rapp_F11,
	rapp_F12,

	rapp_capsLock,
	rapp_shiftL,
	rapp_controlL,
	rapp_altL,
	rapp_superL,
	rapp_shiftR,
	rapp_controlR,
	rapp_altR,
	rapp_superR,
	rapp_up,
	rapp_down,
	rapp_left,
	rapp_right,

	rapp_insert,
	rapp_end,
	rapp_home,
	rapp_pageUp,
	rapp_pageDown,

	rapp_numLock,
	rapp_KP_Slash,
	rapp_multiply,
	rapp_KP_Minus,
	rapp_KP_1,
	rapp_KP_2,
	rapp_KP_3,
	rapp_KP_4,
	rapp_KP_5,
	rapp_KP_6,
	rapp_KP_7,
	rapp_KP_8,
	rapp_KP_9,
	rapp_KP_0,
	rapp_KP_period,
	rapp_KP_Return,
	rapp_scrollLock,
	rapp_keyLast
};

typedef RAPP_ENUM(u8, rapp_mouseIcons) {
	rapp_mouseNormal = 0,
	rapp_mouseArrow,
	rapp_mouseIbeam,
	rapp_mouseCrosshair,
	rapp_mousePointingHand,
	rapp_mouseResizeEW,
	rapp_mouseResizeNS,
	rapp_mouseResizeNWSE,
	rapp_mouseResizeNESW,
	rapp_mouseResizeAll,
	rapp_mouseNotAllowed,
};

/** @} */

#endif /* RAPP_HEADER */

#if defined(__cplusplus)
}
#endif
