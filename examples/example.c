#include "rapp.h"
int main() {
    rapp_window* window = rapp_createWindow("window", RAPP_RECT(0, 0, 800, 600), rapp_windowCenter);
    
//    rapp_window_vsync(window, RAPP_TRUE);

    while (rapp_window_shouldClose(window) == RAPP_FALSE) {
        while (rapp_window_checkEvent(window)) {

        }
        
        rapp_clear(RAPP_RGB(70, 75, 115));

        rapp_drawRect(RAPP_RECT(200, 200, 200, 200), RAPP_RGB(255, 0, 0));

        rapp_window_draw(window);
    }

    rapp_window_close(window);
}
