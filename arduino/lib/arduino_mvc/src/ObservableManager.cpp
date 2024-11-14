#include "ObservableManager.h"

void ObservableManager::addObservable(Observable *observable)
{
    if (currentIndex < 50)
    {
        this->observables[currentIndex++] = observable;
    }
}

void ObservableManager::update()
{
    for (int i = 0; i < currentIndex; i++)
    {
        this->observables[i]->update(this->controller);
    }
}