#pragma once
class Input
{

	struct Mouse {
		int x, y;
	};
public:
	Input();
	~Input();

	void setKeyUp(int key);
	void setKeyDown(int key);
	
	bool isKeyDown(int key);

	void setMouseDown(int button);
	void setMouseUp(int button);
	bool isButtonDown(int button);

	void setMouseX(int x);
	void setMouseY(int y);
	void setMousePos(int x, int y);

	int getMouseX();
	int getMouseY();

private:

	bool keys[256]{ false };
	bool buttons[3]{ false };

	Mouse mouse;


};

