#pragma once
#include <vector>
#include "AbstractNotifier.h"

class Notifier : public virtual AbstractNotifier {
protected:
	std::vector<void*> observerFuncVec;
	virtual void notifyObservers();
public:
	Notifier();
	virtual ~Notifier();

	virtual void registerObserver(void* _observerFunc);
};

