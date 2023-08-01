#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "XXd.h"

namespace xxd
{
class XXD_API Application
{
public:
	Application();
	virtual ~Application();
	virtual void Run() = 0;
};

Application* CreateApplication();

}

#endif