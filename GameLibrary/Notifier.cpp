#include "Notifier.h"

Notifier::Notifier() {

}

Notifier::~Notifier() {

}

void Notifier::notifyObservers() {
	for (size_t i = 0; i < observerFuncVec.size(); i++){
		((void(*)(void))observerFuncVec[i])();
	}
}

void Notifier::registerObserver(void* _observerFunc) {
	observerFuncVec.push_back(_observerFunc);
}