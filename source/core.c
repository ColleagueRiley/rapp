/*
*
*	rapp_lib 0.01-dev
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


#ifndef RAPP_HEADER 
#define RAPP_LIB_SHARED
#include "rapp.h"
#endif

#ifndef RAPP_ALLOC
#include <malloc.h>
#define RAPP_ALLOC malloc
#define RAPP_FREE free
#define RAPP_REALLOC realloc
#endif

#define RSGL_color rapp_color
#define RSGL_area rapp_area

#define RGFW_IMPLEMENTATION
#define RGFW_ALLOC RAPP_ALLOC
#define RGFW_FREE RAPP_FREE
#define RGFW_bool rapp_bool
#define RGFW_point rapp_point
#define RGFW_area rapp_area
#define RGFW_rect rapp_rect
#include "deps/RGFW.h"

#define RSGLDEF
#define RSGL_INT_DEFINED
#define RSGL_BOOL_DEFINED
#define RSGL_MALLOC RAPP_ALLOC
#define RSGL_REALLOC RAPP_REALLOC
#define RSGL_FREE RAPP_FREE
#define RSGL_bool rapp_bool
#define RSGL_color rapp_color
#define RSGL_rect rapp_rect
#define RSGL_rectF rapp_rectF
#define RSGL_point rapp_point
#define RSGL_triangleF rapp_triangleF
#define RSGL_triangle rapp_triangle
#define RSGL_triangle3D rapp_triangle3D
#define RSGL_pointF rapp_pointF
#define RSGL_point3D rapp_point3D
#define RSGL_circle rapp_circle
#define RSGL_circleF rapp_circleF
#define RSGL_mat4 rapp_mat4
#define RSGL_programInfo rapp_programInfo
#define RSGL_texture rapp_texture
#define RFont_texture rapp_texture
#define RFont_font rapp_font
#define RSGL_area rapp_area

typedef u8 b8;

#include "deps/RSGL.h"
#ifdef RAPP_RENDERER_OPENGL
#include "deps/RSGL_gl.h"
#else
#error no renderer defined
#endif

/* */
void rapp_window_draw(rapp_window* win) {
    RSGL_draw();
    rapp_window_swapBuffers(win);
}

void rapp_window_clear(rapp_window* win, rapp_color color) {
    rapp_window_makeCurrent(win);

    RSGL_updateSize(RAPP_AREA(win->r.w, win->r.h));
    RSGL_clear(color);
}

rapp_window* rapp_createWindow(const char* name,  rapp_rect rect,  rapp_windowFlags flags) {
    rapp_window* out = RAPP_ALLOC(sizeof(rapp_window));
    return rapp_createWindowPtr(name, rect, flags, out); 
}

i32 windowCount = 0;

rapp_window* rapp_createWindowPtr(const char* name, rapp_rect rect, rapp_windowFlags flags, rapp_window* win) {    
    win->src = RGFW_createWindow(name, rect, flags);
    win->r = ((RGFW_window*)(RGFW_window*)win->src)->r;

    if (windowCount == 0) {
        #ifdef RAPP_RENDERER_OPENGL
            RSGL_init(RAPP_AREA(win->r.w, win->r.h), rapp_getProcAddress, RSGL_GL_renderer());
        #endif
    }
    
    windowCount++;
    rapp_window_makeCurrent(win);
    return win;
}

void rapp_window_close(rapp_window* win) {
    windowCount--;
    if (windowCount) {
        RSGL_free();
    }

    RGFW_window_close((RGFW_window*)win->src);
}

void rapp_window_swapBuffers(rapp_window* win) {
    RGFW_window_swapBuffers((RGFW_window*)win->src);
}


void rapp_window_vsync(rapp_window* win, rapp_bool enable) {
    RGFW_window_swapInterval((RGFW_window*)win->src, enable);
}

rapp_monitor* rapp_getMonitors(size_t* len) {
    return (rapp_monitor*)RGFW_getMonitors(len);
}

rapp_monitor rapp_getPrimaryMonitor(void) {
    RGFW_monitor mon = RGFW_getPrimaryMonitor();
    rapp_monitor rapp_mon = *(rapp_monitor*)&mon;
    return rapp_mon;
}

rapp_bool rapp_monitor_requestMode(rapp_monitor mon, rapp_monitorMode mode, rapp_modeRequest request) {
    RGFW_monitor rgfw_mon = *(RGFW_monitor*)&mon;
    RGFW_monitorMode rgfw_mode = *(RGFW_monitorMode*)&mode;
    RGFW_modeRequest rgfw_request = *(RGFW_modeRequest*)&request;


    return RGFW_monitor_requestMode(rgfw_mon, rgfw_mode, rgfw_request);
}

rapp_bool rapp_monitor_ModeCompare(rapp_monitorMode mon, rapp_monitorMode mon2, rapp_modeRequest request) {
    RGFW_monitorMode rgfw_mon = *(RGFW_monitorMode*)&mon;
    RGFW_monitorMode rgfw_mon2 = *(RGFW_monitorMode*)&mon2;

    return RGFW_monitorModeCompare(rgfw_mon, rgfw_mon2, request);
}

rapp_mouse* rapp_loadMouse(u8* icon, rapp_area a, i32 channels) {
    return RGFW_loadMouse(icon, a, channels);
}

void rapp_freeMouse(rapp_mouse* mouse) {
    RGFW_freeMouse(mouse);
}

rapp_bool rapp_monitor_scaleToWindow(rapp_monitor mon, rapp_window* win) {
    RGFW_monitor rgfw_mon = *(RGFW_monitor*)&mon;
    return RGFW_monitor_scaleToWindow(rgfw_mon, (RGFW_window*)win->src);
}

void rapp_window_setShouldClose(rapp_window* win, rapp_bool shouldClose) {
    RGFW_window_setShouldClose((RGFW_window*)win->src, shouldClose);
}

RGFW_bool rapp_window_shouldClose(rapp_window* win) {
    return RGFW_window_shouldClose((RGFW_window*)win->src);
}

rapp_area rapp_getScreenSize(void) {
    return RGFW_getScreenSize();
}


rapp_event* rapp_window_checkEvent(rapp_window* win) {
    RGFW_event* ev = RGFW_window_checkEvent((RGFW_window*)win->src);
    if (ev == NULL) return NULL;
    
    win->event = *(rapp_event*)&((RGFW_window*)((RGFW_window*)win->src))->event;
    win->r = ((RGFW_window*)((RGFW_window*)win->src))->r;

    return &win->event;
}

void rapp_window_eventWait(rapp_window* win, u32 waitMS) {
    RGFW_window_eventWait((RGFW_window*)win->src, waitMS);
}

rapp_point rapp_getGlobalMousePoint(void) {
    return RGFW_getGlobalMousePoint();
}

rapp_point rapp_window_getMousePoint(rapp_window* win) {
    return RGFW_window_getMousePoint((RGFW_window*)win->src);
}

void rapp_window_showMouse(rapp_window* win, rapp_bool show) {
    RGFW_window_showMouse((RGFW_window*)win->src, show);
}

rapp_bool rapp_window_mouseHidden(rapp_window* win) {
    return RGFW_window_mouseHidden((RGFW_window*)win->src);
}

rapp_bool rapp_window_isFullscreen(rapp_window* win) {
    return RGFW_window_isFullscreen((RGFW_window*)win->src);
}

rapp_bool rapp_window_isHidden(rapp_window* win) {
    return RGFW_window_isHidden((RGFW_window*)win->src);
}

rapp_bool rapp_window_isMinimized(rapp_window* win) {
    return RGFW_window_isMinimized((RGFW_window*)win->src);
}

rapp_bool rapp_window_isMaximized(rapp_window* win) {
    return RGFW_window_isMaximized((RGFW_window*)win->src);
}

rapp_bool rapp_window_isFloating(rapp_window* win) {
    return RGFW_window_isFloating((RGFW_window*)win->src);
}

rapp_monitor rapp_window_getMonitor(rapp_window* win) {
    RGFW_monitor mon = RGFW_window_getMonitor((RGFW_window*)win->src);
    rapp_monitor rapp_Mon = *(rapp_monitor*)&mon;
    return rapp_Mon;
}


rapp_bool rapp_isPressed(rapp_window* win, rapp_key key) {
    return RGFW_isPressed((RGFW_window*)win->src, key);
}

rapp_bool rapp_wasPressed(rapp_window* win, rapp_key key) {
    return RGFW_wasPressed((RGFW_window*)win->src, key);
}

rapp_bool rapp_isHeld(rapp_window* win, rapp_key key) {
    return RGFW_isHeld((RGFW_window*)win->src, key);
}

rapp_bool rapp_isReleased(rapp_window* win, rapp_key key) {
    return RGFW_isReleased((RGFW_window*)win->src, key);
}

rapp_bool rapp_isClicked(rapp_window* win, rapp_key key) {
    return RGFW_isClicked((RGFW_window*)win->src, key);
}

rapp_bool rapp_isMousePressed(rapp_window* win, rapp_mouseButton button) {
    return RGFW_isMousePressed((RGFW_window*)win->src, button);
}

rapp_bool rapp_isMouseHeld(rapp_window* win, rapp_mouseButton button) {
    return RGFW_isMouseHeld((RGFW_window*)win->src, button);
}

rapp_bool rapp_isMouseReleased(rapp_window* win, rapp_mouseButton button) {
    return RGFW_isMouseReleased((RGFW_window*)win->src, button);
}

rapp_bool rapp_wasMousePressed(rapp_window* win, rapp_mouseButton button) {
    return RGFW_wasMousePressed((RGFW_window*)win->src, button);
}



const char* rapp_readClipboard(size_t* size) {
    return RGFW_readClipboard(size);
}

rapp_ssize_t rapp_readClipboardPtr(char* str, size_t strCapacity) {
    return RGFW_readClipboardPtr(str, strCapacity);
}

void rapp_writeClipboard(const char* text, u32 textLen) {
    RGFW_writeClipboard(text, textLen);
}

size_t rapp_getGamepadCount(rapp_window* win) {
    return RGFW_getGamepadCount((RGFW_window*)win->src);
}

rapp_gamepadType rapp_getGamepadType(rapp_window* win, u16 controller) {
    return RGFW_getGamepadType((RGFW_window*)win->src, controller);
}

double rapp_getTime(void) {
    return RGFW_getTime();
}

u64 rapp_getTimeNS(void) {
    return RGFW_getTimeNS();
}

void rapp_sleep(u64 milisecond) {
    RGFW_sleep(milisecond);
}

void rapp_setTime(double time) {
    RGFW_setTime(time);
}

u64 rapp_getTimerValue(void) {
    return RGFW_getTimerValue();
}

u64 rapp_getTimerFreq(void) {
    return RGFW_getTimerFreq();
}


u32 rapp_checkFPS(double startTime, u32 frameCount, u32 fpsCap) {
    return RGFW_checkFPS(startTime, frameCount, fpsCap);
}

rapp_proc rapp_getProcAddress(const char* procname) {
    return RGFW_getProcAddress(procname);
}

void rapp_setGLHint(rapp_glHints hint, i32 value) {
    RGFW_setGLHint(hint, value);
}

void rapp_window_makeCurrent(rapp_window* win) {
    RGFW_window_makeCurrent((RGFW_window*)win->src);
}

const char* rapp_getGamepadName(rapp_window* win, u16 controller) {
    return RGFW_getGamepadName((RGFW_window*)win->src, controller);
}

rapp_point rapp_getGamepadAxis(rapp_window* win, u16 controller, u16 whichAxis) {
    return RGFW_getGamepadAxis((RGFW_window*)win->src, controller, whichAxis);
}

u32 rapp_wasPressedGamepad(rapp_window* win, u8 controller, rapp_gamepadCodes button) {
    return RGFW_wasPressedGamepad((RGFW_window*)win->src, controller, button);
}

u32 rapp_isHeldGamepad(rapp_window* win, u8 controller, rapp_gamepadCodes button) {
    return RGFW_isHeldGamepad((RGFW_window*)win->src, controller, button);
}

u32 rapp_isReleasedGamepad(rapp_window* win, u8 controller, rapp_gamepadCodes button) {
    return RGFW_isReleasedGamepad((RGFW_window*)win->src, controller, button);
}

u32 rapp_isPressedGamepad(rapp_window* win, u8 controller, rapp_gamepadCodes button) {
    return RGFW_isPressedGamepad((RGFW_window*)win->src, controller, button);
}

void rapp_window_scaleToMonitor(rapp_window* win) {
    RGFW_window_scaleToMonitor((RGFW_window*)win->src);
}

void rapp_window_moveMouse(rapp_window* win, rapp_point v) {
    RGFW_window_moveMouse((RGFW_window*)win->src, v);
}

void rapp_window_show(rapp_window* win) {
    RGFW_window_show((RGFW_window*)win->src);
}

void rapp_window_hide(rapp_window* win) {
    RGFW_window_hide((RGFW_window*)win->src);
}

void rapp_window_mouseUnhold(rapp_window* win) {
    RGFW_window_mouseUnhold((RGFW_window*)win->src);
}

void rapp_window_mouseHold(rapp_window* win, rapp_area area) {
    RGFW_window_mouseHold((RGFW_window*)win->src, area);
}

rapp_bool rapp_window_setMouseDefault(rapp_window* win) {
    return RGFW_window_setMouseDefault((RGFW_window*)win->src);
}

rapp_bool rapp_window_setMouseStandard(rapp_window* win, u8 mouse) {
    return RGFW_window_setMouseStandard((RGFW_window*)win->src, mouse);
}

void rapp_window_setMouse(rapp_window* win, rapp_mouse* mouse) {
    RGFW_window_setMouse((RGFW_window*)win->src, mouse);
}

rapp_bool rapp_window_setIconEx(rapp_window* win, u8* icon, rapp_area a, i32 channels, u8 type) {
    return RGFW_window_setIconEx((RGFW_window*)win->src, icon, a, channels, type);
}

rapp_bool rapp_window_setIcon(rapp_window* win, u8* icon, rapp_area a, i32 channels) {
    return RGFW_window_setIcon((RGFW_window*)win->src, icon, a, channels);
}

void rapp_window_setName(rapp_window* win, const char* name) {
    RGFW_window_setName((RGFW_window*)win->src, name);
}

void rapp_window_setMousePassthrough(rapp_window* win, rapp_bool passthrough) {
    RGFW_window_setMousePassthrough((RGFW_window*)win->src, passthrough);
}

rapp_bool rapp_window_allowsDND(rapp_window* win) {
    return RGFW_window_allowsDND((RGFW_window*)win->src);
}

void rapp_window_setDND(rapp_window* win, rapp_bool allow) {
    RGFW_window_setDND((RGFW_window*)win->src, allow);
}

rapp_bool rapp_window_borderless(rapp_window* win) {
    return RGFW_window_borderless((RGFW_window*)win->src);
}

void rapp_window_setBorder(rapp_window* win, rapp_bool border) {
    RGFW_window_setBorder((RGFW_window*)win->src, border);
}

void rapp_window_setOpacity(rapp_window* win, u8 opacity) {
    RGFW_window_setOpacity((RGFW_window*)win->src, opacity);
}

void rapp_window_setFloating(rapp_window* win, rapp_bool floating) {
    RGFW_window_setFloating((RGFW_window*)win->src, floating);
}

void rapp_window_restore(rapp_window* win) {
    RGFW_window_restore((RGFW_window*)win->src);
}

void rapp_window_minimize(rapp_window* win) {
    RGFW_window_minimize((RGFW_window*)win->src);
}

void rapp_window_center(rapp_window* win) {
    RGFW_window_center((RGFW_window*)win->src);
}

void rapp_window_setFullscreen(rapp_window* win, rapp_bool fullscreen) {
    RGFW_window_setFullscreen((RGFW_window*)win->src, fullscreen);
}

void rapp_window_maximize(rapp_window* win) {
    RGFW_window_maximize((RGFW_window*)win->src);
}

void rapp_window_raise(rapp_window* win) {
    RGFW_window_raise((RGFW_window*)win->src);
}

rapp_bool rapp_window_isInFocus(rapp_window* win) {
    return RGFW_window_isInFocus((RGFW_window*)win->src);
}

void rapp_window_focus(rapp_window* win) {
    RGFW_window_focus((RGFW_window*)win->src);
}

void rapp_window_setMaxSize(rapp_window* win, rapp_area a) {
    RGFW_window_setMaxSize((RGFW_window*)win->src, a);
}

void rapp_window_setMinSize(rapp_window* win, rapp_area a) {
    RGFW_window_setMinSize((RGFW_window*)win->src, a);
}

void rapp_window_setAspectRatio(rapp_window* win, rapp_area a) {
    RGFW_window_setAspectRatio((RGFW_window*)win->src, a);
}

void rapp_window_resize(rapp_window* win, rapp_area size) {
    RGFW_window_resize((RGFW_window*)win->src, size);
}

void rapp_window_moveToMonitor(rapp_window* win, rapp_monitor m) {
    RGFW_window_moveToMonitor((RGFW_window*)win->src, *(RGFW_monitor*)(&m));
}

void rapp_window_move(rapp_window* win, rapp_point v) {
    RGFW_window_move((RGFW_window*)win->src, v);
}

void rapp_stopCheckEvents(void) {
    RGFW_stopCheckEvents();
}

void rapp_window_setFlags(rapp_window* win, rapp_windowFlags flags) {
    RGFW_window_setFlags((RGFW_window*)win->src, flags);
}
