#include "screensize.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <X11/Xlib.h>
#endif

ScreenSize getScreenSize() {
#ifdef _WIN32
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
#else
	Display* display = XOpenDisplay(NULL);
	Screen* screen = XDefaultScreenOfDisplay(display);
	int screenWidth = XWidthOfScreen(screen);
	int screenHeight = XHeightOfScreen(screen);
#endif
	ScreenSize screenSize;
	screenSize.width = screenWidth;
	screenSize.height = screenHeight;
	return screenSize;
}
