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

#define RSGL_color rapp_Color
#define RSGL_area rapp_Area

#define RGFW_IMPLEMENTATION
#define RGFW_ALLOC RAPP_ALLOC
#define RGFW_FREE RAPP_FREE
#define RGFW_bool rapp_Bool
#define RGFW_point rapp_Point
#define RGFW_area rapp_Area
#define RGFW_rect rapp_Rect
#include "deps/RGFW.h"



/* prviate API */
rapp_Window* rapp_createWindowSrc(const char* name, rapp_Rect rect, rapp_WindowFlags flags, rapp_Window* win);
void rapp_Window_closeSrc(rapp_Window* win);

/* RGFW */
void RSGL_draw(void);
void RSGL_updateSize(RSGL_area r);
void RSGL_free();
void RSGL_init(RSGL_area r, void* proc);
void RSGL_clear(RSGL_color color);

/* */
void rapp_Window_draw(rapp_Window* win) {
    RSGL_draw();
    rapp_Window_swapBuffers(win);
}

void rapp_Window_clear(rapp_Window* win, rapp_Color color) {
    rapp_Window_makeCurrent(win);

    RSGL_updateSize(RAPP_AREA(win->r.w, win->r.h));
    RSGL_clear(color);
}

rapp_Window* rapp_createWindow(const char* name,  rapp_Rect rect,  rapp_WindowFlags flags) {
    rapp_Window* out = RAPP_ALLOC(sizeof(rapp_Window));
    return rapp_createWindowPtr(name, rect, flags, out); 
}

i32 windowCount = 0;

rapp_Window* rapp_createWindowPtr(const char* name, rapp_Rect rect, rapp_WindowFlags flags, rapp_Window* win) {    
    win = rapp_createWindowSrc(name, rect, flags, win);
    
    if (windowCount == 0) {
        RSGL_init(RAPP_AREA(win->r.w, win->r.h), rapp_getProcAddress);
        rapp_Audio_init();
    }
    
    windowCount++;
    rapp_Window_makeCurrent(win);
    return win;
}

void rapp_Window_close(rapp_Window* win) {
    windowCount--;
    if (windowCount) {
        RSGL_free();
        rapp_Audio_free();
    }

    rapp_Window_closeSrc(win);
}

void rapp_Window_swapBuffers(rapp_Window* win) {
    RGFW_window_swapBuffers((RGFW_window*)win->src);
}


void rapp_Window_vsync(rapp_Window* win, rapp_Bool enable) {
    RGFW_window_swapInterval((RGFW_window*)win->src, enable);
}

rapp_Monitor* rapp_getMonitors(size_t* len) {
    return (rapp_Monitor*)RGFW_getMonitors(len);
}

rapp_Monitor rapp_getPrapp_maryMonitor(void) {
    RGFW_monitor mon = RGFW_getPrapp_maryMonitor();
    rapp_Monitor rapp_mon = *(rapp_Monitor*)&mon;
    return rapp_mon;
}

rapp_Bool rapp_Monitor_requestMode(rapp_Monitor mon, rapp_MonitorMode mode, rapp_modeRequest request) {
    RGFW_monitor rgfw_mon = *(RGFW_monitor*)&mon;
    RGFW_monitorMode rgfw_mode = *(RGFW_monitorMode*)&mode;
    RGFW_modeRequest rgfw_request = *(RGFW_modeRequest*)&request;


    return RGFW_monitor_requestMode(rgfw_mon, rgfw_mode, rgfw_request);
}

rapp_Bool rapp_Monitor_ModeCompare(rapp_MonitorMode mon, rapp_MonitorMode mon2, rapp_modeRequest request) {
    RGFW_monitorMode rgfw_mon = *(RGFW_monitorMode*)&mon;
    RGFW_monitorMode rgfw_mon2 = *(RGFW_monitorMode*)&mon2;

    return RGFW_monitorModeCompare(rgfw_mon, rgfw_mon2, request);
}

rapp_mouse* rapp_loadMouse(u8* icon, rapp_Area a, i32 channels) {
    return RGFW_loadMouse(icon, a, channels);
}

void rapp_freeMouse(rapp_mouse* mouse) {
    RGFW_freeMouse(mouse);
}

rapp_Bool rapp_Monitor_scaleToWindow(rapp_Monitor mon, rapp_Window* win) {
    RGFW_monitor rgfw_mon = *(RGFW_monitor*)&mon;
    return RGFW_monitor_scaleToWindow(rgfw_mon, (RGFW_window*)win->src);
}

rapp_Window* rapp_createWindowSrc(const char* name, rapp_Rect rect, rapp_WindowFlags flags, rapp_Window* win) {    
    win->src = RGFW_createWindow(name, rect, flags);
    win->r = ((RGFW_window*)(RGFW_window*)win->src)->r;
    return win;
}

void rapp_Window_closeSrc(rapp_Window* win) {
    RGFW_window_close((RGFW_window*)win->src);
}

void rapp_Window_setShouldClose(rapp_Window* win, rapp_Bool shouldClose) {
    RGFW_window_setShouldClose((RGFW_window*)win->src, shouldClose);
}

RGFW_bool rapp_Window_shouldClose(rapp_Window* win) {
    return RGFW_window_shouldClose((RGFW_window*)win->src);
}

rapp_Area rapp_getScreenSize(void) {
    return RGFW_getScreenSize();
}


rapp_Event* rapp_Window_checkEvent(rapp_Window* win) {
    RGFW_event* ev = RGFW_window_checkEvent((RGFW_window*)win->src);
    if (ev == NULL) return NULL;
    
    win->event = *(rapp_Event*)&((RGFW_window*)((RGFW_window*)win->src))->event;
    win->r = ((RGFW_window*)((RGFW_window*)win->src))->r;

    return &win->event;
}

void rapp_Window_eventWait(rapp_Window* win, u32 waitMS) {
    RGFW_window_eventWait((RGFW_window*)win->src, waitMS);
}

rapp_Point rapp_getGlobalMousePoint(void) {
    return RGFW_getGlobalMousePoint();
}

rapp_Point rapp_Window_getMousePoint(rapp_Window* win) {
    return RGFW_window_getMousePoint((RGFW_window*)win->src);
}

void rapp_Window_showMouse(rapp_Window* win, rapp_Bool show) {
    RGFW_window_showMouse((RGFW_window*)win->src, show);
}

rapp_Bool rapp_Window_mouseHidden(rapp_Window* win) {
    return RGFW_window_mouseHidden((RGFW_window*)win->src);
}

rapp_Bool rapp_Window_isFullscreen(rapp_Window* win) {
    return RGFW_window_isFullscreen((RGFW_window*)win->src);
}

rapp_Bool rapp_Window_isHidden(rapp_Window* win) {
    return RGFW_window_isHidden((RGFW_window*)win->src);
}

rapp_Bool rapp_Window_isMinimized(rapp_Window* win) {
    return RGFW_window_isMinimized((RGFW_window*)win->src);
}

rapp_Bool rapp_Window_isMaximized(rapp_Window* win) {
    return RGFW_window_isMaximized((RGFW_window*)win->src);
}

rapp_Bool rapp_Window_isFloating(rapp_Window* win) {
    return RGFW_window_isFloating((RGFW_window*)win->src);
}

rapp_Monitor rapp_Window_getMonitor(rapp_Window* win) {
    RGFW_monitor mon = RGFW_window_getMonitor((RGFW_window*)win->src);
    rapp_Monitor rapp_Mon = *(rapp_Monitor*)&mon;
    return rapp_Mon;
}


rapp_Bool rapp_isPressed(rapp_Window* win, rapp_key key) {
    return RGFW_isPressed((RGFW_window*)win->src, key);
}

rapp_Bool rapp_wasPressed(rapp_Window* win, rapp_key key) {
    return RGFW_wasPressed((RGFW_window*)win->src, key);
}

rapp_Bool rapp_isHeld(rapp_Window* win, rapp_key key) {
    return RGFW_isHeld((RGFW_window*)win->src, key);
}

rapp_Bool rapp_isReleased(rapp_Window* win, rapp_key key) {
    return RGFW_isReleased((RGFW_window*)win->src, key);
}

rapp_Bool rapp_isClicked(rapp_Window* win, rapp_key key) {
    return RGFW_isClicked((RGFW_window*)win->src, key);
}

rapp_Bool rapp_isMousePressed(rapp_Window* win, rapp_mouseButton button) {
    return RGFW_isMousePressed((RGFW_window*)win->src, button);
}

rapp_Bool rapp_isMouseHeld(rapp_Window* win, rapp_mouseButton button) {
    return RGFW_isMouseHeld((RGFW_window*)win->src, button);
}

rapp_Bool rapp_isMouseReleased(rapp_Window* win, rapp_mouseButton button) {
    return RGFW_isMouseReleased((RGFW_window*)win->src, button);
}

rapp_Bool rapp_wasMousePressed(rapp_Window* win, rapp_mouseButton button) {
    return RGFW_wasMousePressed((RGFW_window*)win->src, button);
}



const char* rapp_readClipboard(size_t* size) {
    return RGFW_readClipboard(size);
}

rapp_ssize_t rapp_readClipboardPtr(char* str, size_t strCapacity) {
    return RGFW_readClipboardPtr(str, strCapacity);
}

void rapp_wrapp_teClipboard(const char* text, u32 textLen) {
    RGFW_wrapp_teClipboard(text, textLen);
}

size_t rapp_getGamepadCount(rapp_Window* win) {
    return RGFW_getGamepadCount((RGFW_window*)win->src);
}

rapp_gamepadType rapp_getGamepadType(rapp_Window* win, u16 controller) {
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

void rapp_Window_makeCurrent(rapp_Window* win) {
    RGFW_window_makeCurrent((RGFW_window*)win->src);
}

const char* rapp_getGamepadName(rapp_Window* win, u16 controller) {
    return RGFW_getGamepadName((RGFW_window*)win->src, controller);
}

rapp_Point rapp_getGamepadAxis(rapp_Window* win, u16 controller, u16 whichAxis) {
    return RGFW_getGamepadAxis((RGFW_window*)win->src, controller, whichAxis);
}

u32 rapp_wasPressedGamepad(rapp_Window* win, u8 controller, rapp_gamepadCodes button) {
    return RGFW_wasPressedGamepad((RGFW_window*)win->src, controller, button);
}

u32 rapp_isHeldGamepad(rapp_Window* win, u8 controller, rapp_gamepadCodes button) {
    return RGFW_isHeldGamepad((RGFW_window*)win->src, controller, button);
}

u32 rapp_isReleasedGamepad(rapp_Window* win, u8 controller, rapp_gamepadCodes button) {
    return RGFW_isReleasedGamepad((RGFW_window*)win->src, controller, button);
}

u32 rapp_isPressedGamepad(rapp_Window* win, u8 controller, rapp_gamepadCodes button) {
    return RGFW_isPressedGamepad((RGFW_window*)win->src, controller, button);
}

void rapp_Window_scaleToMonitor(rapp_Window* win) {
    RGFW_window_scaleToMonitor((RGFW_window*)win->src);
}

void rapp_Window_moveMouse(rapp_Window* win, rapp_Point v) {
    RGFW_window_moveMouse((RGFW_window*)win->src, v);
}

void rapp_Window_show(rapp_Window* win) {
    RGFW_window_show((RGFW_window*)win->src);
}

void rapp_Window_hide(rapp_Window* win) {
    RGFW_window_hide((RGFW_window*)win->src);
}

void rapp_Window_mouseUnhold(rapp_Window* win) {
    RGFW_window_mouseUnhold((RGFW_window*)win->src);
}

void rapp_Window_mouseHold(rapp_Window* win, rapp_Area area) {
    RGFW_window_mouseHold((RGFW_window*)win->src, area);
}

rapp_Bool rapp_Window_setMouseDefault(rapp_Window* win) {
    return RGFW_window_setMouseDefault((RGFW_window*)win->src);
}

rapp_Bool rapp_Window_setMouseStandard(rapp_Window* win, u8 mouse) {
    return RGFW_window_setMouseStandard((RGFW_window*)win->src, mouse);
}

void rapp_Window_setMouse(rapp_Window* win, rapp_mouse* mouse) {
    RGFW_window_setMouse((RGFW_window*)win->src, mouse);
}

rapp_Bool rapp_Window_setIconEx(rapp_Window* win, u8* icon, rapp_Area a, i32 channels, u8 type) {
    return RGFW_window_setIconEx((RGFW_window*)win->src, icon, a, channels, type);
}

rapp_Bool rapp_Window_setIcon(rapp_Window* win, u8* icon, rapp_Area a, i32 channels) {
    return RGFW_window_setIcon((RGFW_window*)win->src, icon, a, channels);
}

void rapp_Window_setName(rapp_Window* win, const char* name) {
    RGFW_window_setName((RGFW_window*)win->src, name);
}

void rapp_Window_setMousePassthrough(rapp_Window* win, rapp_Bool passthrough) {
    RGFW_window_setMousePassthrough((RGFW_window*)win->src, passthrough);
}

rapp_Bool rapp_Window_allowsDND(rapp_Window* win) {
    return RGFW_window_allowsDND((RGFW_window*)win->src);
}

void rapp_Window_setDND(rapp_Window* win, rapp_Bool allow) {
    RGFW_window_setDND((RGFW_window*)win->src, allow);
}

rapp_Bool rapp_Window_borderless(rapp_Window* win) {
    return RGFW_window_borderless((RGFW_window*)win->src);
}

void rapp_Window_setBorder(rapp_Window* win, rapp_Bool border) {
    RGFW_window_setBorder((RGFW_window*)win->src, border);
}

void rapp_Window_setOpacity(rapp_Window* win, u8 opacity) {
    RGFW_window_setOpacity((RGFW_window*)win->src, opacity);
}

void rapp_Window_setFloating(rapp_Window* win, rapp_Bool floating) {
    RGFW_window_setFloating((RGFW_window*)win->src, floating);
}

void rapp_Window_restore(rapp_Window* win) {
    RGFW_window_restore((RGFW_window*)win->src);
}

void rapp_Window_minimize(rapp_Window* win) {
    RGFW_window_minimize((RGFW_window*)win->src);
}

void rapp_Window_center(rapp_Window* win) {
    RGFW_window_center((RGFW_window*)win->src);
}

void rapp_Window_setFullscreen(rapp_Window* win, rapp_Bool fullscreen) {
    RGFW_window_setFullscreen((RGFW_window*)win->src, fullscreen);
}

void rapp_Window_maximize(rapp_Window* win) {
    RGFW_window_maximize((RGFW_window*)win->src);
}

void rapp_Window_raise(rapp_Window* win) {
    RGFW_window_raise((RGFW_window*)win->src);
}

rapp_Bool rapp_Window_isInFocus(rapp_Window* win) {
    return RGFW_window_isInFocus((RGFW_window*)win->src);
}

void rapp_Window_focus(rapp_Window* win) {
    RGFW_window_focus((RGFW_window*)win->src);
}

void rapp_Window_setMaxSize(rapp_Window* win, rapp_Area a) {
    RGFW_window_setMaxSize((RGFW_window*)win->src, a);
}

void rapp_Window_setMinSize(rapp_Window* win, rapp_Area a) {
    RGFW_window_setMinSize((RGFW_window*)win->src, a);
}

void rapp_Window_setAspectRatio(rapp_Window* win, rapp_Area a) {
    RGFW_window_setAspectRatio((RGFW_window*)win->src, a);
}

void rapp_Window_resize(rapp_Window* win, rapp_Area size) {
    RGFW_window_resize((RGFW_window*)win->src, size);
}

void rapp_Window_moveToMonitor(rapp_Window* win, rapp_Monitor m) {
    RGFW_window_moveToMonitor((RGFW_window*)win->src, *(RGFW_monitor*)(&m));
}

void rapp_Window_move(rapp_Window* win, rapp_Point v) {
    RGFW_window_move((RGFW_window*)win->src, v);
}

void rapp_stopCheckEvents(void) {
    RGFW_stopCheckEvents();
}

void rapp_Window_setFlags(rapp_Window* win, rapp_WindowFlags flags) {
    RGFW_window_setFlags((RGFW_window*)win->src, flags);
}
