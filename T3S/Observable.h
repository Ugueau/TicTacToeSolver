#pragma once
#include "Observer.h";
class Observable
{
	virtual void addObserver(Observer* observer) = 0;
	virtual void notifyObserver() const = 0;
};

