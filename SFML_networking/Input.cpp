#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

void Input::setKeyUp(int key)
{
	keys[key] = false;
}

void Input::setKeyDown(int key)
{
	keys[key] = true;
}

bool Input::isKeyDown(int key)
{
	return keys[key];
}

void Input::setMouseDown(int button)
{
	buttons[button] = true;
}

void Input::setMouseUp(int button)
{
	buttons[button] = false;
}

bool Input::isButtonDown(int button)
{
	return buttons[button];
}

void Input::setMouseX(int x)
{
	mouse.x = x;
}

void Input::setMouseY(int y)
{
	mouse.y = y;
}

void Input::setMousePos(int x, int y)
{
	mouse.x = x;
	mouse.y = y;
}

int Input::getMouseX()
{
	return mouse.x;
}

int Input::getMouseY()
{
	return mouse.y;
}
