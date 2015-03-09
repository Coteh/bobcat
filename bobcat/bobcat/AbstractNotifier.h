#pragma once

namespace bobcat {

	/**
	* An abstract class that all Notifiers must derive from and use.
	* A Notifier utilizes the Observer design pattern and allows for registration
	* of observers that want to listen for a notification from the Notifier.
	*/
	class AbstractNotifier {
	protected:
		/**
		* Notify the observers!
		*/
		virtual void notifyObservers() = 0;
	public:
		/**
		* Register an observer that will listen for notifications.
		*/
		virtual void registerObserver(void* _observerFunc) = 0;

		virtual ~AbstractNotifier(){}
	};

}