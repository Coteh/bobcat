#pragma once
#include "AbstractNotifier.h"

#define WINDOW_SHOW 1
#define WINDOW_HIDE 0

class AbstractWindower : public virtual AbstractNotifier {
public:
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual const char* getName() = 0;
	virtual bool isVisible() = 0;
	virtual bool isRunning() = 0;
	virtual void setWindowDimensions(int _width, int _height) = 0;
	virtual void setName(const char* _name) = 0;
	virtual void showWindow(int _expression) = 0;
	virtual void init() = 0;
	virtual void updateWindow() = 0;
	virtual void closeWindow() = 0;

	virtual ~AbstractWindower(){}
};