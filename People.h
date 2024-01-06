#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#include "Items.h"

class Item;

class Agent{
public:
    Item* tabaco;
    Item* paper;
    Item* matches;
private:
    void updatePrice(Item* item);
public:
    Agent();
    void changePrice();
};

class Smoker{
public:
    int id;
    double cash;
    std::string selling;
    Item* item;
    Agent* agent;

public:
    Smoker(Agent* agent);
    double getCash();
    std::string getSelling();
    void tryToBuy();

};

class WithTabaco : public Smoker{
public:
    WithTabaco(Agent* agent);
};

class WithPaper : public Smoker{
public:
    WithPaper(Agent* agent);
};

class WithMatches : public Smoker{
public:
    WithMatches(Agent* agent);
};