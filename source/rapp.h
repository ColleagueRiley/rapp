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

#if !defined(rapp_Bool) /* rapp_lib bool type */
	typedef u8 rapp_Bool;
	#define rapp_Bool u8
#endif

#define RAPP_TRUE (rapp_Bool)1
#define RAPP_FALSE (rapp_Bool)0
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
#define RAPP_POINT(x, y) (rapp_Point){(i32)(x), (i32)(y)}
#define rapp_rect(x, y, w, h) (rapp_Rect){(i32)(x), (i32)(y), (i32)(w), (i32)(h)}
#define RAPP_AREA(w, h) (rapp_Area){(u32)(w), (u32)(h)}
#endif

typedef struct rapp_rectF { float x, y, w, h; } rapp_RectF;
#define rapp_rectF(x, y, w, h) (rapp_RectF){(float)x, (float)y, (float)w, (float)h}

typedef struct rapp_PointF { float x, y; } rapp_PointF;
#define RAPP_POINTF(x, y) (rapp_PointF){x, y}

typedef struct rapp_Point3D {
    i32 x, y, z;
} rapp_Point3D;

typedef struct rapp_Point3DF { float x, y, z; } rapp_Point3DF;

#define RAPP_POINT3D(x, y, z) (rapp_Point3D){(i32)x, (i32)y, (i32)z}
#define RAPP_POINT3DF(x, y, z) (rapp_Point3DF){(float)x, (float)y, (float)z}

typedef struct rapp_AreaF { float w, h;} rapp_AreaF;
#define RAPP_AREAF(w, h) (rapp_AreaF){(float)w, (float)h}

typedef struct rapp_Circle {
    i32 x, y, d;
} rapp_Circle;
#define rapp_Circle(x, y, d) (rapp_Circle){(i32)x, (i32)y, (i32)d}

typedef struct rapp_CircleF { float x, y, d; } rapp_CircleF;
#define rapp_CircleF(x, y, d) (rapp_CircleF){(float)x, (float)y, (float)d}

typedef struct rapp_Trapp_angle {
    rapp_Point p1, p2, p3;
} rapp_Trapp_angle;
#define RAPP_TRAPPANGLE(p1, p2, p3) (rapp_trapp_angle){p1, p2, p3}

typedef struct rapp_Trapp_angleF { rapp_PointF p1, p2, p3; } rapp_Trapp_angleF;
#define RAPP_TRAPPANGLEF(p1, p2, p3) (rapp_Trapp_angleF){p1, p2, p3}

#define RAPP_createTrapp_angle(x1, y1, x2, y2, x3, y3) (rapp_Trapp_angle){{x1, y1}, {x2, y2}, {x3, y3}}
#define RAPP_createTrapp_angleF(x1, y1, x2, y2, x3, y3) (rapp_Trapp_angleF){{x1, y1}, {x2, y2}, {x3, y3}}

typedef struct rapp_Cube {
    i32 x, y, z, w, h, l;
} rapp_Cube;
#define RAPP_CUBE(x, y, z, w, h, l) (rapp_cube){x, y, z, w, h, l}

typedef struct rapp_CubeF { float x, y, z, w, h, l; } rapp_CubeF;
#define RAPP_CUBEF(x, y, z, w, h, l) (rapp_CubeF){x, y, z, w, h, l}

/* drawing functions */
#ifndef rapp_Texture
#define rapp_Texture size_t
#endif
typedef struct rapp_Image { rapp_Texture tex; rapp_Area srcSize; char file[255]; } rapp_Image;

/* 
the color stucture is in 
ABGR by default for performance reasons 
(converting color to hex for example)
*/
typedef struct rapp_Color {
    u8 a, b, g, r;
} rapp_Color;

#define RAPP_RGBA(r, g, b, a) ((rapp_Color){(u8)(a), (u8)(b), (u8)(g), (u8)(r)})
#define RAPP_RGB(r, g, b) ((rapp_Color){255, (u8)(b), (u8)(g), (u8)(r)})

#define rapp_Color_TO_HEX(color) ((u32)(color) & 0xFFFFFF00)
#define RAPP_RGB_TO_HEX(r, g, b, a) (rapp_Color_TO_HEX(rapp_RGBA(r, g, b, a)))
#define RAPP_RGBA_TO_HEX(r, g, b) (rapp_Color_TO_HEX(rapp_RGB(r, g, b, a)))



typedef RAPP_ENUM(u8, rapp_EventType) {
	/*! event codes */
	rapp_EventNone = 0, /*!< no event has been sent */
 	rapp_keyPressed, /* a key has been pressed */
	rapp_keyReleased, /*!< a key has been released */
	/*! key event note
		the code of the key pressed is stored in
		rapp_Event.key
		!!Keycodes defined at the bottom of the RAPP_HEADER part of this file!!

		while a strapp_ng version is stored in
		rapp_Event.KeyStrapp_ng

		rapp_Event.keyMod holds the current keyMod
		this means if CapsLock, NumLock are active or not
	*/
	rapp_mouseButtonPressed, /*!< a mouse button has been pressed (left,middle,rapp_ght) */
	rapp_mouseButtonReleased, /*!< a mouse button has been released (left,middle,rapp_ght) */
	rapp_mousePosChanged, /*!< the position of the mouse has been changed */
	/*! mouse event note
		the x and y of the mouse can be found in the vector, rapp_Event.point

		rapp_Event.button holds which mouse button was pressed
	*/
	rapp_gamepadConnected, /*!< a gamepad was connected */
	rapp_gamepadDisconnected, /*!< a gamepad was disconnected */
	rapp_gamepadButtonPressed, /*!< a gamepad button was pressed */
	rapp_gamepadButtonReleased, /*!< a gamepad button was released */
	rapp_gamepadAxisMove, /*!< an axis of a gamepad was moved */
	/*! gamepad event note
		rapp_Event.gamepad holds which gamepad was altered, if any
		rapp_Event.button holds which gamepad button was pressed

		rapp_Event.axis holds the data of all the axises
		rapp_Event.axisesCount says how many axises there are
	*/
	rapp_WindowMoved, /*!< the window was moved (by the user) */
	rapp_WindowResized, /*!< the window was resized (by the user), [on WASM this means the browser was resized] */
	rapp_focusIn, /*!< window is in focus now */
	rapp_focusOut, /*!< window is out of focus now */
	rapp_mouseEnter, /* mouse entered the window */
	rapp_mouseLeave, /* mouse left the window */
	rapp_WindowRefresh, /* The window content needs to be refreshed */

	/* attrapp_bs change event note
		The event data is sent straight to the window structure
		with win->r.x, win->r.y, win->r.w and win->r.h
	*/
	rapp_quit, /*!< the user clicked the quit button */
	rapp_DND, /*!< a file has been dropped into the window */
	rapp_DNDInit, /*!< the start of a dnd event, when the place where the file drop is known */
	/* dnd data note
		The x and y coords of the drop are stored in the vector rapp_Event.point

		rapp_Event.droppedFilesCount holds how many files were dropped

		This is also the size of the array which stores all the dropped file strapp_ng,
		rapp_Event.droppedFiles
	*/
	rapp_WindowMaximized, /*!< the window was maximized */
	rapp_WindowMinimized, /*!< the window was minimized */
	rapp_WindowRestored, /*!< the window was restored */
	rapp_scaleUpdated, /*!< content scale factor changed */
};

/*! mouse button codes (rapp_Event.button) */
typedef RAPP_ENUM(u8, rapp_mouseButton) {
	rapp_mouseLeft = 0, /*!< left mouse button is pressed */
	rapp_mouseMiddle, /*!< mouse-wheel-button is pressed */
	rapp_mouserapp_ght, /*!< rapp_ght mouse button is pressed */
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

/* for rapp_Event.lockstate */
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
	rapp_gamepadY, /*!< or PS trapp_angle button */
	rapp_gamepadX, /*!< or PS square button */
	rapp_gamepadStart, /*!< start button */
	rapp_gamepadSelect, /*!< select button */
	rapp_gamepadHome, /*!< home button */
	rapp_gamepadUp, /*!< dpad up */
	rapp_gamepadDown, /*!< dpad down */
	rapp_gamepadLeft, /*!< dpad left */
	rapp_gamepadrapp_ght, /*!< dpad rapp_ght */
	rapp_gamepadL1, /*!< left bump */
	rapp_gamepadL2, /*!< left trapp_gger */
	rapp_gamepadR1, /*!< rapp_ght bumper */
	rapp_gamepadR2, /*!< rapp_ght trapp_gger */
	rapp_gamepadL3,  /* left thumb stick */
	rapp_gamepadR3, /*!< rapp_ght thumb stick */
	rapp_gamepadFinal
};

#ifndef rapp_NO_MONITOR
	/* monitor mode data | can be changed by the user (with functions)*/
	typedef struct rapp_MonitorMode {
		rapp_Area area; /*!< monitor workarea size */
		u32 refreshRate; /*!< monitor refresh rate */
		u8 red, blue, green; 
	} rapp_MonitorMode;

	/*! structure for monitor data */
	typedef struct rapp_Monitor {
		i32 x, y; /*!< x - y of the monitor workarea */
		char name[128]; /*!< monitor name */
		float scaleX, scaleY; /*!< monitor content scale */
		float pixelRatio; /*!< pixel ratio for monitor (1.0 for regular, 2.0 for hiDPI)  */
		float physW, physH; /*!< monitor physical size in inches */

		rapp_MonitorMode mode;
	} rapp_Monitor;

	/*! get an array of all the monitors (max 6) */
	RAPPAPI rapp_Monitor* rapp_getMonitors(size_t* len);
	/*! get the prapp_mary monitor */
	RAPPAPI rapp_Monitor rapp_getPrapp_maryMonitor(void);

	typedef RAPP_ENUM(u8, rapp_modeRequest) {
		rapp_MonitorScale = RAPP_BIT(0), /*!< scale the monitor size */
		rapp_MonitorRefresh = RAPP_BIT(1), /*!< change the refresh rate */
		rapp_MonitorRGB = RAPP_BIT(2), /*!< change the monitor RGB bits size */
		rapp_MonitorAll = rapp_MonitorScale | rapp_MonitorRefresh | rapp_MonitorRGB
	};

	/*! request a specific mode */
	RAPPAPI rapp_Bool rapp_Monitor_requestMode(rapp_Monitor mon, rapp_MonitorMode mode, rapp_modeRequest request);
	/*! check if 2 monitor modes are the same */
	RAPPAPI rapp_Bool rapp_Monitor_modeCompare(rapp_MonitorMode mon, rapp_MonitorMode mon2, rapp_modeRequest request);
#endif

/* rapp_lib mouse loading */
typedef void rapp_mouse;

/*!< loads mouse icon from bitmap (similar to rapp_Window_setIcon). Icon NOT resized by default */
RAPPAPI rapp_mouse* rapp_loadMouse(u8* icon, rapp_Area a, i32 channels);
/*!< frees rapp_mouse data */
RAPPAPI void rapp_freeMouse(rapp_mouse* mouse);

/* NOTE: some parts of the data can represent different things based on the event (read comments in rapp_Event struct) */
/*! Event structure for checking/getting events */
typedef struct rapp_Event {
	rapp_EventType type; /*!< which event has been sent?*/
	rapp_Point point; /*!< mouse x, y of event (or drop point) */
	rapp_Point vector; /*!< raw mouse movement */
	float scaleX, scaleY; /*!< DPI scaling */

	rapp_key key; /*!< the physical key of the event, refers to where key is physically !!Keycodes defined at the bottom of the RAPP_HEADER part of this file!! */
	u8 keyChar; /*!< mapped key char of the event */

	rapp_Bool repeat; /*!< key press event repeated (the key is being held) */
	rapp_keymod keyMod;

	u8 button; /* !< which mouse (or gamepad) button was pressed */
	double scroll; /*!< the raw mouse scroll value */

	u16 gamepad; /*! which gamepad this event applies to (if applicable to any) */
	u8 axisesCount; /*!< number of axises */

	u8 whichAxis; /* which axis was effected */
	rapp_Point axis[4]; /*!< x, y of axises (-100 to 100) */

	/*! drag and drop data */
	/* 260 max paths with a max length of 260 */
	char** droppedFiles; /*!< dropped files */
	size_t droppedFilesCount; /*!< house many files were dropped */

	void* _win; /*!< the window this event applies too (for event queue events) */
} rapp_Event;

/*! Optional arguments for making a windows */
typedef RAPP_ENUM(u32, rapp_WindowFlags) {
	rapp_WindowNoInitAPI = RAPP_BIT(0), /* do NOT init an API (mostly for bindings. you should use `#define RAPP_NO_API` in C) */
	rapp_WindowNoBorder = RAPP_BIT(1), /*!< the window doesn't have a border */
	rapp_WindowNoResize = RAPP_BIT(2), /*!< the window cannot be resized by the user */
	rapp_WindowAllowDND = RAPP_BIT(3), /*!< the window supports drag and drop */
	rapp_WindowHideMouse = RAPP_BIT(4), /*! the window should hide the mouse (can be toggled later on using `rapp_Window_mouseShow`) */
	rapp_WindowFullscreen = RAPP_BIT(5), /*!< the window is fullscreen by default */
	rapp_WindowTransparent = RAPP_BIT(6), /*!< the window is transparent (only properly works on X11 and MacOS, although it's meant for for windows) */
	rapp_WindowCenter = RAPP_BIT(7), /*! center the window on the screen */
	rapp_WindowOpenglSoftware = RAPP_BIT(8), /*! use OpenGL software renderapp_ng */
	rapp_WindowCocoaCHDirToRes = RAPP_BIT(9), /*! (cocoa only), change directory to resource folder */
	rapp_WindowScaleToMonitor = RAPP_BIT(10), /*! scale the window to the screen */
	rapp_WindowHide = RAPP_BIT(11), /*! the window is hidden */
	rapp_WindowMaximize = RAPP_BIT(12),
	rapp_WindowCenterCursor = RAPP_BIT(13),
	rapp_WindowFloating = RAPP_BIT(14), /*!< create a floating window */
	rapp_WindowFreeOnClose = RAPP_BIT(15), /*!< free (rapp_Window_close) the rapp_Window struct when the window is closed (by the end user) */
	rapp_WindowFocusOnShow = RAPP_BIT(16), /*!< focus the window when it's shown */
	rapp_WindowMinimize =RAPP_BIT(17), /*!< focus the window when it's shown */
	rapp_WindowFocus = RAPP_BIT(18), /*!< if the window is in focus */
	rapp_WindowedFullscreen = rapp_WindowNoBorder | rapp_WindowMaximize,
};

typedef struct rapp_Window {
	void* src;
	void* userPtr; /* ptr for usr data */
	rapp_Event event; /*!< current event */
	rapp_rect r; /*!< the x, y, w and h of the struct */
} rapp_Window; /*!< window structure for managing the window */

typedef rapp_Window* rapp_WindowHandle;

/*! scale monitor to window size */
RAPPAPI rapp_Bool rapp_Monitor_scaleToWindow(rapp_Monitor mon, rapp_Window* win);

/** * @defgroup Window_management
* @{ */

/* NOTE: (windows) if the executable has an icon resource named rapp_ICON, it will be set as the initial icon for the window */

RAPPAPI rapp_Window* rapp_createWindow(
	const char* name, /* name of the window */
	rapp_rect rect, /* rect of window */
	rapp_WindowFlags flags /* extra arguments ((u32)0 means no flags used)*/
); /*!< function to create a window and struct */

RAPPAPI rapp_Window* rapp_createWindowPtr(
	const char* name, /* name of the window */
	rapp_rect rect, /* rect of window */
	rapp_WindowFlags flags, /* extra arguments (NULL / (u32)0 means no flags used) */
	rapp_Window* win /* ptr to the window struct you want to use */
); /*!< function to create a window (without allocating a window struct) */

/*! set the window flags (will undo flags if they don't match the old ones) */
RAPPAPI void rapp_Window_setFlags(rapp_Window* win, rapp_WindowFlags);

/*! get the size of the screen to an area struct */
RAPPAPI rapp_Area rapp_getScreenSize(void);

/*!
	for rapp_Window_eventWait and rapp_Window_checkEvents
	waitMS -> Allows the function to keep checking for events even after `rapp_Window_checkEvent == NULL`
			  if waitMS == 0, the loop will not wait for events
			  if waitMS > 0, the loop will wait that many miliseconds after there are no more events until it returns
			  if waitMS == -1 or waitMS == the max size of an unsigned 32-bit int, the loop will not return until it gets another event
*/
typedef RAPP_ENUM(u32, rapp_EventWait) {
	rapp_EventNoWait = 0,
	rapp_EventWaitNext = -1
};

/*! sleep until rapp_lib gets an event or the timer ends (defined by OS) */
RAPPAPI void rapp_Window_eventWait(rapp_Window* win, u32 waitMS);

/*!
	check all the events until there are none left.
	This should only be used if you're using callbacks only
*/
RAPPAPI rapp_Event* rapp_Window_checkEvent(rapp_Window* win);

/*!
	tell rapp_Window_eventWait to stop waiting (to be ran from another thread)
*/
RAPPAPI void rapp_stopCheckEvents(void);

/*! window managment functions */
RAPPAPI void rapp_Window_close(rapp_Window* win); /*!< close the window and free leftover data */

/*! move a window to a given point */
RAPPAPI void rapp_Window_move(rapp_Window* win,
	rapp_Point v /*!< new pos */
);

#ifndef rapp_NO_MONITOR
	/*! move window to a specific monitor */
	RAPPAPI void rapp_Window_moveToMonitor(rapp_Window* win, rapp_Monitor m /* monitor */);
#endif

/*! resize window to a current size/area */
RAPPAPI void rapp_Window_resize(rapp_Window* win, /*!< source window */
	rapp_Area a /*!< new size */
);

/*! set window aspect ratio */
RAPPAPI void rapp_Window_setAspectRatio(rapp_Window* win, rapp_Area a);
/*! set the minimum dimensions of a window */
RAPPAPI void rapp_Window_setMinSize(rapp_Window* win, rapp_Area a);
/*! set the maximum dimensions of a window */
RAPPAPI void rapp_Window_setMaxSize(rapp_Window* win, rapp_Area a);

RAPPAPI void rapp_Window_focus(rapp_Window* win); /*!< sets the focus to this window */
RAPPAPI rapp_Bool rapp_Window_isInFocus(rapp_Window* win); /*!< checks the focus to this window */
RAPPAPI void rapp_Window_raise(rapp_Window* win); /*!< raise the window (to the top) */
RAPPAPI void rapp_Window_maximize(rapp_Window* win); /*!< maximize the window */
RAPPAPI void rapp_Window_setFullscreen(rapp_Window* win, rapp_Bool fullscreen); /*!< turn fullscreen on / off for a window */
RAPPAPI void rapp_Window_center(rapp_Window* win); /*!< center the window */
RAPPAPI void rapp_Window_minimize(rapp_Window* win); /*!< minimize the window (in taskbar (per OS))*/
RAPPAPI void rapp_Window_restore(rapp_Window* win); /*!< restore the window from minimized (per OS)*/
RAPPAPI void rapp_Window_setFloating(rapp_Window* win, rapp_Bool floating); /*!< make the window a floating window */
RAPPAPI void rapp_Window_setOpacity(rapp_Window* win, u8 opacity); /*!< sets the opacity of a window */

/*! if the window should have a border or not (borderless) based on bool value of `border` */
RAPPAPI void rapp_Window_setBorder(rapp_Window* win, rapp_Bool border);
RAPPAPI rapp_Bool rapp_Window_borderless(rapp_Window* win);

/*! turn on / off dnd (rapp_WindowAllowDND stil must be passed to the window)*/
RAPPAPI void rapp_Window_setDND(rapp_Window* win, rapp_Bool allow);
/*! check if DND is allowed */
RAPPAPI rapp_Bool rapp_Window_allowsDND(rapp_Window* win);


#ifndef rapp_NO_PASSTHROUGH
	/*! turn on / off mouse passthrough */
	RAPPAPI void rapp_Window_setMousePassthrough(rapp_Window* win, rapp_Bool passthrough);
#endif

/*! rename window to a given strapp_ng */
RAPPAPI void rapp_Window_setName(rapp_Window* win,
	const char* name
);

RAPPAPI rapp_Bool rapp_Window_setIcon(rapp_Window* win, /*!< source window */
	u8* icon /*!< icon bitmap */,
	rapp_Area a /*!< width and height of the bitmap */,
	i32 channels /*!< how many channels the bitmap has (rgb : 3, rgba : 4) */
); /*!< image MAY be resized by default, set both the taskbar and window icon */

typedef RAPP_ENUM(u8, rapp_icon) {
	rapp_iconTaskbar = RAPP_BIT(0),
	rapp_iconWindow = RAPP_BIT(1),
	rapp_iconBoth = rapp_iconTaskbar | rapp_iconWindow
};
RAPPAPI rapp_Bool rapp_Window_setIconEx(rapp_Window* win, u8* icon, rapp_Area a, i32 channels, u8 type);

/*!< sets mouse to rapp_mouse icon (loaded from a bitmap struct) */
RAPPAPI void rapp_Window_setMouse(rapp_Window* win, rapp_mouse* mouse);

/*!< sets the mouse to a standard API cursor (based on rapp_MOUSE, as seen at the end of the RAPP_HEADER part of this file) */
RAPPAPI	rapp_Bool rapp_Window_setMouseStandard(rapp_Window* win, u8 mouse);

RAPPAPI rapp_Bool rapp_Window_setMouseDefault(rapp_Window* win); /*!< sets the mouse to the default mouse icon */
/*
	Locks cursor at the center of the window
	win->event.point becomes raw mouse movement data

	this is useful for a 3D camera
*/
RAPPAPI void rapp_Window_mouseHold(rapp_Window* win, rapp_Area area);
/*! stop holding the mouse and let it move freely */
RAPPAPI void rapp_Window_mouseUnhold(rapp_Window* win);

/*! hide the window */
RAPPAPI void rapp_Window_hide(rapp_Window* win);
/*! show the window */
RAPPAPI void rapp_Window_show(rapp_Window* win);

/*
	makes it so `rapp_Window_shouldClose` returns true or overrapp_des a window close 
	by modifying window flags
*/
RAPPAPI void rapp_Window_setShouldClose(rapp_Window* win, rapp_Bool shouldClose);

/*! where the mouse is on the screen */
RAPPAPI rapp_Point rapp_getGlobalMousePoint(void);

/*! where the mouse is on the window */
RAPPAPI rapp_Point rapp_Window_getMousePoint(rapp_Window* win);

/*! show the mouse or hide the mouse */
RAPPAPI void rapp_Window_showMouse(rapp_Window* win, rapp_Bool show);
/*! if the mouse is hidden */
RAPPAPI rapp_Bool rapp_Window_mouseHidden(rapp_Window* win);
/*! move the mouse to a given point */
RAPPAPI void rapp_Window_moveMouse(rapp_Window* win, rapp_Point v);

/*! if the window should close (rapp_close was sent or escape was pressed) */
RAPPAPI rapp_Bool rapp_Window_shouldClose(rapp_Window* win);
/*! if the window is fullscreen */
RAPPAPI rapp_Bool rapp_Window_isFullscreen(rapp_Window* win);
/*! if the window is hidden */
RAPPAPI rapp_Bool rapp_Window_isHidden(rapp_Window* win);
/*! if the window is minimized */
RAPPAPI rapp_Bool rapp_Window_isMinimized(rapp_Window* win);
/*! if the window is maximized */
RAPPAPI rapp_Bool rapp_Window_isMaximized(rapp_Window* win);
/*! if the window is floating */
RAPPAPI rapp_Bool rapp_Window_isFloating(rapp_Window* win);
/** @} */

/** * @defgroup Monitor
* @{ */

#ifndef RAPP_NO_MONITOR
/*
	scale the window to the monitor.
	This is run by default if the user uses the arg `rapp_scaleToMonitor` durapp_ng window creation
*/
RAPPAPI void rapp_Window_scaleToMonitor(rapp_Window* win);
/*! get the struct of the window's monitor  */
RAPPAPI rapp_Monitor rapp_Window_getMonitor(rapp_Window* win);
#endif

/** @} */

/** * @defgroup Input
* @{ */

/*! if window == NULL, it checks if the key is pressed globally. Otherwise, it checks only if the key is pressed while the window in focus. */
RAPPAPI rapp_Bool rapp_isPressed(rapp_Window* win, rapp_key key); /*!< if key is pressed (key code)*/

RAPPAPI rapp_Bool rapp_wasPressed(rapp_Window* win, rapp_key key); /*!< if key was pressed (checks previous state only) (key code) */

RAPPAPI rapp_Bool rapp_isHeld(rapp_Window* win, rapp_key key); /*!< if key is held (key code) */
RAPPAPI rapp_Bool rapp_isReleased(rapp_Window* win, rapp_key key); /*!< if key is released (key code) */

/* if a key is pressed and then released, pretty much the same as rapp_isReleased */
RAPPAPI rapp_Bool rapp_isClicked(rapp_Window* win, rapp_key key /*!< key code */);

/*! if a mouse button is pressed */
RAPPAPI rapp_Bool rapp_isMousePressed(rapp_Window* win, rapp_mouseButton button /*!< mouse button code */ );
/*! if a mouse button is held */
RAPPAPI rapp_Bool rapp_isMouseHeld(rapp_Window* win, rapp_mouseButton button /*!< mouse button code */ );
/*! if a mouse button was released */
RAPPAPI rapp_Bool rapp_isMouseReleased(rapp_Window* win, rapp_mouseButton button /*!< mouse button code */ );
/*! if a mouse button was pressed (checks previous state only) */
RAPPAPI rapp_Bool rapp_wasMousePressed(rapp_Window* win, rapp_mouseButton button /*!< mouse button code */ );
/** @} */

/** * @defgroup Clipboard
* @{ */
typedef ptrdiff_t rapp_ssize_t;

RAPPAPI const char* rapp_readClipboard(size_t* size); /*!< read clipboard data */
/*! read clipboard data or send a NULL str to just get the length of the clipboard data */
RAPPAPI rapp_ssize_t rapp_readClipboardPtr(char* str, size_t strCapacity);
RAPPAPI void rapp_wrapp_teClipboard(const char* text, u32 textLen); /*!< wrapp_te text to the clipboard */
/** @} */

/** * @defgroup gamepad
* @{ */

typedef RAPP_ENUM(u8, rapp_gamepadType) {
	rapp_gamepadMicrosoft = 0, rapp_gamepadSony, rapp_gamepadNintendo, rapp_gamepadLogitech, rapp_gamepadUnknown
};

/*! gamepad count starts at 0*/
RAPPAPI u32 rapp_isPressedGamepad(rapp_Window* win, u8 controller, rapp_gamepadCodes button);
RAPPAPI u32 rapp_isReleasedGamepad(rapp_Window* win, u8 controller, rapp_gamepadCodes button);
RAPPAPI u32 rapp_isHeldGamepad(rapp_Window* win, u8 controller, rapp_gamepadCodes button);
RAPPAPI u32 rapp_wasPressedGamepad(rapp_Window* win, u8 controller, rapp_gamepadCodes button);
RAPPAPI rapp_Point rapp_getGamepadAxis(rapp_Window* win, u16 controller, u16 whichAxis);
RAPPAPI const char* rapp_getGamepadName(rapp_Window* win, u16 controller);
RAPPAPI size_t rapp_getGamepadCount(rapp_Window* win);
RAPPAPI rapp_gamepadType rapp_getGamepadType(rapp_Window* win, u16 controller);

/** @} */

/** * @defgroup graphics_API
* @{ */

/*!< make the window the current opengl drawing context

	NOTE:
 	if you want to switch the graphics context's thread,
	you have to run rapp_Window_makeCurrent(NULL); on the old thread
	then rapp_Window_makeCurrent(valid_window) on the new thread
*/
RAPPAPI void rapp_Window_makeCurrent(rapp_Window* win);

/* supports openGL, directX, OSMesa, EGL and software renderapp_ng */
RAPPAPI void rapp_Window_swapBuffers(rapp_Window* win); /*!< swap the renderapp_ng buffer */
RAPPAPI void rapp_Window_vsync(rapp_Window* win, rapp_Bool enable);

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


RAPPAPI void rapp_setTexture(rapp_Texture texture); /* apply texture to drawing */
RAPPAPI void rapp_setProgram(u32 program); /* use shader program for drawing */
RAPPAPI void rapp_setGradient(
                                float* gradient, /* array of gradients */
                                size_t len /* length of array */
                            ); /* apply gradient to drawing, based on color list*/
RAPPAPI void rapp_fill(rapp_Bool fill); /* toggle filling, if fill is false it runs rapp_draw<whatever>_outline instead */
RAPPAPI void rapp_center(rapp_Point3DF center); /* the center of the drawing (or shape), this is used for rotation */

/* args clear after a draw function by default, this toggles that */
RAPPAPI void rapp_setClearArgs(rapp_Bool clearArgs); /* toggles if args are cleared by default or not */
RAPPAPI void rapp_clearArgs(void); /* clears the args */
/* calculate the align a smaller rect with larger rect */
typedef RAPP_ENUM(u8, rapp_alignment) {
    rapp_ALIGN_NONE = RAPP_BIT(0),
    /* horapp_zontal */
    rapp_ALIGN_LEFT = RAPP_BIT(1),
    rapp_ALIGN_CENTER = RAPP_BIT(2),
    rapp_ALIGN_RAPPGHT = RAPP_BIT(3),
    
    /* vertical */
    rapp_ALIGN_UP = RAPP_BIT(4),
    rapp_ALIGN_MIDDLE = RAPP_BIT(5),
    rapp_ALIGN_DOWN = RAPP_BIT(6),

    rapp_ALIGN_HORAPPZONTAL = rapp_ALIGN_LEFT | rapp_ALIGN_CENTER | rapp_ALIGN_RAPPGHT,
    rapp_ALIGN_VERTICAL = rapp_ALIGN_UP | rapp_ALIGN_MIDDLE | rapp_ALIGN_DOWN,
/* ex : alignment = (rapp_ALIGN_LEFT | rapp_ALIGN_MIDDLE) */
};

/* align smaller rect onto larger rect based on a given alignment */
RAPPAPI rapp_rect rapp_alignRect(rapp_Rect larger, rapp_Rect smaller, u16 alignment);
RAPPAPI rapp_rectF rapp_alignRectF(rapp_RectF larger, rapp_RectF smaller, u16 alignment);

typedef struct RAPP_MATRAPPX {
    float m[16];
} RAPP_MATRAPPX;

RAPPAPI RAPP_MATRAPPX rapp_initDrawMatrapp_x(rapp_Point3DF center);
RAPPAPI void rapp_clear(rapp_Color color);
RAPPAPI void rapp_viewport(i32 x, i32 y, i32 w, i32 h);
/* create a texture based on a given bitmap, this must be freed later using rapp_deleteTexture or opengl*/
RAPPAPI rapp_Texture rapp_createTexture(u8* bitmap, rapp_Area memsize,  u8 channels);
/* delete a texture */
RAPPAPI void rapp_deleteTexture(rapp_Texture tex);
/* starts scissorapp_ng */
RAPPAPI void rapp_scissorStart(rapp_rectF scissor);
/* stops scissorapp_ng */
RAPPAPI void rapp_scissorEnd(void);

/*!< draw current batch to the window */
RAPPAPI void rapp_Window_draw(rapp_Window* win);

/*!< clear graphics and update window size info (should be ran before RSGL_draw<x> calls) */
RAPPAPI void rapp_Window_clear(rapp_Window* win, rapp_Color color);

/* custom shader program */
typedef struct rapp_ProgramInfo {
    u32 vShader, fShader, program;
} rapp_ProgramInfo;

RAPPAPI rapp_ProgramInfo rapp_renderCreateProgram(const char* VShaderCode, const char* FShaderCode, const char* posName, const char* texName, const char* colorName);
RAPPAPI void rapp_renderDeleteProgram(rapp_ProgramInfo program);
RAPPAPI void rapp_renderSetShaderValue(u32 program, char* var, float value[], u8 len);

/* these are RFont functions that also must be defined by the renderer

32 RFont_create_atlas(u32 atlasWidth, u32 atlasHeight);
void RFont_bitmap_to_atlas(rapp_rsoft_texture atlas, u8* bitmap, float x, float y, float w, float h);

*/

/* rapp_ translation */
RAPPAPI RAPP_MATRAPPX rapp_matrapp_xMultiply(float left[16], float rapp_ght[16]);
RAPPAPI RAPP_MATRAPPX rapp_rotatef(RAPP_MATRAPPX* matrapp_x, float angle, float x, float y, float z); 
RAPPAPI RAPP_MATRAPPX rapp_translatef(RAPP_MATRAPPX* matrapp_x, float x, float y, float z);
/* 2D shape drawing */
/* in the function names, F means float */

RAPPAPI void rapp_drawPoint(rapp_Point p, rapp_Color c);
RAPPAPI void rapp_drawPointF(rapp_PointF p, rapp_Color c);
RAPPAPI void rapp_plotLines(rapp_PointF* lines, size_t points_count, u32 thickness, rapp_Color c);

RAPPAPI void rapp_drawTrapp_angle(rapp_Trapp_angle t, rapp_Color c);
RAPPAPI void rapp_drawTrapp_angleF(rapp_Trapp_angleF t, rapp_Color c);

RAPPAPI void rapp_drawTrapp_angleHyp(rapp_PointF p, size_t angle, float hypotenuse, rapp_Color color);

RAPPAPI void rapp_drawRect(rapp_rect r, rapp_Color c);
RAPPAPI void rapp_drawRectF(rapp_rectF r, rapp_Color c);


RAPPAPI void rapp_drawRoundRect(rapp_rect r, rapp_Point rounding, rapp_Color c);
RAPPAPI void rapp_drawRoundRectF(rapp_rectF r, rapp_Point rounding, rapp_Color c);

RAPPAPI void rapp_drawPolygon(rapp_rect r, u32 sides, rapp_Color c);
RAPPAPI void rapp_drawPolygonF(rapp_rectF r, u32 sides, rapp_Color c);

RAPPAPI void rapp_drawArc(rapp_rect o, rapp_Point arc, rapp_Color color);
RAPPAPI void rapp_drawArcF(rapp_rectF o, rapp_PointF arc, rapp_Color color);

RAPPAPI void rapp_drawCircle(rapp_Circle c, rapp_Color color);
RAPPAPI void rapp_drawCircleF(rapp_CircleF c, rapp_Color color);

RAPPAPI void rapp_drawOval(rapp_rect o, rapp_Color c);
RAPPAPI void rapp_drawOvalF(rapp_rectF o, rapp_Color c);

RAPPAPI void rapp_drawLine(rapp_Point p1, rapp_Point p2, u32 thickness, rapp_Color c);
RAPPAPI void rapp_drawLineF(rapp_PointF p1, rapp_PointF p2, u32 thickness, rapp_Color c);

/* 2D outlines */

/* thickness means the thickness of the line */

RAPPAPI void rapp_drawTrapp_angleOutline(rapp_Trapp_angle t, u32 thickness, rapp_Color c);
RAPPAPI void rapp_drawTrapp_angleFOutline(rapp_Trapp_angleF t, u32 thickness, rapp_Color c);

RAPPAPI void rapp_drawRectOutline(rapp_rect r, u32 thickness, rapp_Color c);
RAPPAPI void rapp_drawRectFOutline(rapp_rectF r, u32 thickness, rapp_Color c);

RAPPAPI void rapp_drawRoundRectOutline(rapp_rect r, rapp_Point rounding, u32 thickness, rapp_Color c);
RAPPAPI void rapp_drawRoundRectFOutline(rapp_rectF r, rapp_Point rounding, u32 thickness, rapp_Color c);

RAPPAPI void rapp_drawPolygonOutline(rapp_rect r, u32 sides, u32 thickness, rapp_Color c);
RAPPAPI void rapp_drawPolygonFOutline(rapp_rectF r, u32 sides, u32 thickness, rapp_Color c);

RAPPAPI void rapp_drawArcOutline(rapp_rect o, rapp_Point arc, u32 thickness, rapp_Color color);
RAPPAPI void rapp_drawArcFOutline(rapp_rectF o, rapp_PointF arc, u32 thickness, rapp_Color color);

RAPPAPI void rapp_drawCircleOutline(rapp_Circle c, u32 thickness, rapp_Color color);
RAPPAPI void rapp_drawCircleFOutline(rapp_CircleF c, u32 thickness, rapp_Color color);

RAPPAPI void rapp_drawOvalOutline(rapp_rect o, u32 thickness, rapp_Color c);
RAPPAPI void rapp_drawOvalFOutline(rapp_rectF o, u32 thickness, rapp_Color c);

/* format a strapp_ng */
RAPPAPI const char* RAPP_strFmt(const char* strapp_ng, ...);

/* loads a font into rapp_, returns it's index into the rapp_fonts array, this is used as an id in later functions */
RAPPAPI i32 rapp_loadFont(const char* font);
/* (pro) loads a font into rapp_, returns it's index into the rapp_fonts array, this is used as an id in later functions 
    using a given atlasWidth + atlasHeight
*/
RAPPAPI i32 rapp_loadFontPro(const char* font, size_t atlasWidth, size_t atlasHeight);
/* sets font as the current font in use based on index in rapp_font, given when it was loaded */
RAPPAPI void rapp_setFont(i32 font);

/* sets source RFont font as the current font, given when it was loaded */
struct RFont_font;
RAPPAPI void rapp_setRFont(struct RFont_font* font);

RAPPAPI void rapp_drawText_len(const char* text, size_t len, rapp_Circle c, rapp_Color color);
RAPPAPI void rapp_drawText_pro(const char* text, size_t len, float spacing, rapp_Circle c, rapp_Color color);
RAPPAPI void rapp_drawText(const char* text, rapp_Circle c, rapp_Color color);
#define RAPP_drawTextF(text, font, c, color) \
    rapp_setFont(font);\
    rapp_drawText(text, c, color);

/* align text onto larger rect based on a given alignment */
RAPPAPI rapp_Circle rapp_alignText(const char* str, rapp_Circle c, rapp_rectF larger, u8 alignment);
/* align text based on a length */
RAPPAPI rapp_Circle rapp_alignText_len(const char* str, size_t str_len, rapp_Circle c, rapp_rectF larger, u8 alignment);

/* 
    returns the width of a text when rendered with the set font with the size of `fontSize
    stops at `textEnd` or when it reaches '\0'
*/
RAPPAPI rapp_Area rapp_textArea(const char* text, u32 fontSize, size_t textEnd);
RAPPAPI rapp_Area rapp_textLineArea(const char* text, u32 fontSize, size_t textEnd, size_t line);
#define RAPP_textAreaF(text, fontSize, textEnd) \
    rapp_setFont(font);\
    rapp_textAreaF(text, fontSize, textEnd);

/* 
    this creates a texture based on a given image, draws it on a rectangle and then returns the loaded texture 
    
    if the rectangle's width and height are 0 it doesn't draw the image
    the texture is loaded into rapp_Image, this means it doesn't need to be freed
    but you can still free it early
*/

RAPPAPI rapp_Image rapp_loadImage(const char* image);
RAPPAPI rapp_Image rapp_drawImage(rapp_Image, rapp_rect r);
RAPPAPI rapp_Image rapp_drawImageFile(const char* image, rapp_rect r);

/* 
    these two functions can be used before rapp_renderCreateTexture in order to create 
    an swizzle'd texutre or atlas
*/

/* 
*******
extra
*******
*/

/* ** collision functions ** */
RAPPAPI rapp_Bool rapp_CircleCollidePoint(rapp_Circle c, rapp_Point p);
RAPPAPI rapp_Bool rapp_CircleCollideRect(rapp_Circle c, rapp_rect r);
RAPPAPI rapp_Bool rapp_CircleCollide(rapp_Circle cir1, rapp_Circle cir2);
RAPPAPI rapp_Bool rapp_rectCollidePoint(rapp_Rect r, rapp_Point p);
RAPPAPI rapp_Bool rapp_rectCollide(rapp_Rect r, rapp_Rect r2);
RAPPAPI rapp_Bool rapp_PointCollide(rapp_Point p, rapp_Point p2);

RAPPAPI rapp_Bool rapp_CircleCollidePointF(rapp_CircleF c, rapp_PointF p);
RAPPAPI rapp_Bool rapp_CircleCollideRectF(rapp_CircleF c, rapp_rectF r);
RAPPAPI rapp_Bool rapp_CircleCollideF(rapp_CircleF cir1, rapp_CircleF cir2);
RAPPAPI rapp_Bool rapp_rectCollidePointF(rapp_RectF r, rapp_PointF p);
RAPPAPI rapp_Bool rapp_rectCollideF(rapp_RectF r, rapp_RectF r2);
RAPPAPI rapp_Bool rapp_PointCollideF(rapp_PointF p, rapp_PointF p2);

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

	rapp_perapp_od = '.',
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
	rapp_rapp_ght,

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
	rapp_KP_Perapp_od,
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

/** * @defgroup Audio

* @{ */

RAPPAPI i32 rapp_Audio_play(const char* file); 
/** @} */

#endif /* RAPP_HEADER */

#if defined(__cplusplus)
}
#endif
