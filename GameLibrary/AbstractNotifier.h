#pragma once

class AbstractNotifier {
protected:
	virtual void notifyObservers() = 0;
public:
	virtual void registerObserver(void* _observerFunc) = 0;

	virtual ~AbstractNotifier(){}
};