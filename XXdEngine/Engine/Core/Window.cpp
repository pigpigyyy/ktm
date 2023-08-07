#include "Window.h"

#if defined(XXD_PLATFORM_APPLE)
    #include "Mac/MacWindow.h"
#elif defined(XXD_PLATFORM_WINDOWS)

#endif

bool xxd::Window::bisInitialized = false;

xxd::Window* xxd::Window::Create(const WindowProps& props)
{
#if defined(XXD_PLATFORM_APPLE)
    return new MacWindow(props);
#elif defined(XXD_PLATFORM_WINDOWS)
		
#endif 
}

void xxd::Window::Init()
{
#if defined(XXD_PLATFORM_APPLE)
    MacWindow::MacCocoaInit();
#elif defined(XXD_PLATFORM_WINDOWS)
		
#endif 
}

void xxd::Window::PollEvent()
{
#if defined(XXD_PLATFORM_APPLE)
    MacWindow::MacCocoaPollEvent();
#elif defined(XXD_PLATFORM_WINDOWS)
		
#endif 
}

void xxd::Window::Quit()
{
#if defined(XXD_PLATFORM_APPLE)
	MacWindow::Quit();
#elif defined(XXD_PLATFORM_WINDOWS)
		
#endif 
}
