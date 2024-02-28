#pragma once
#include <vector>
using std::vector;
class Observer {
public:
    virtual void update() = 0;

};

class Observable {
    vector<Observer*> ups;
    
public:
    void notify() {
        for (auto u : ups) {
            u->update();
        }
    }
    void addObs(Observer* o) {
        ups.push_back(o);
    }
    void delObs(Observer* o) {
        ups.erase(std::remove(ups.begin(), ups.end(), o));
    }
};