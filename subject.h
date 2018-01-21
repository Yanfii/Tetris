#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <iostream>
#include <memory>
#include "state.h"

struct Info;
class Observer;
class Subject {
	std::vector<std::shared_ptr<Observer>> observers;
	State state;
public:
	void setState(State newS);
	void attach(std::shared_ptr<Observer> o);
  	void notifyObservers();
  	virtual Info getInfo() const = 0;
  	State getState() const;
};
#endif

