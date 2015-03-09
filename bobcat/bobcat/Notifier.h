#pragma once
#include <vector>
#include "AbstractNotifier.h"

namespace bobcat {

	/**
	* Notifier is a concrete representation of AbstractNotifier. Holds a collection of observer methods and can notify them all upon command.
	*/
	class Notifier : public virtual AbstractNotifier {
	protected:
		std::vector<void*> observerFuncVec;
		virtual void notifyObservers();
	public:
		Notifier();
		virtual ~Notifier();

		virtual void registerObserver(void* _observerFunc);
	};

}