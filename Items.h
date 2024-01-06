#pragma once
#include "People.h"

class Smoker;

class Item {
public:
    double price;
    double last_up;
    double last_down;
    Smoker* owner;
    bool gotBought[3];
    bool waiting[3];

    Item(Smoker* owner);
};
