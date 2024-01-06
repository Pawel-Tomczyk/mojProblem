#include "People.h"

Agent::Agent() {
    tabaco = nullptr;
    paper = nullptr;
    matches = nullptr;
}

void Agent::updatePrice(Item* item) {
    if (item->gotBought[0] || item->gotBought[1] || item->gotBought[2]) {
        item->last_up += 0.5;
        item->last_down = 0;
        item->price += item->last_up;
    } else if (item->waiting[0] || item->waiting[1] || item->waiting[2]) {
        item->last_up += 0.5;
        item->last_down = 0;
        item->price += item->last_up;
        return;
    } else if(item->price - (item->last_down += 0.5) > 0){
        item->last_down += 0.5;
        item->last_up = 0;
        item->price -= item->last_down;
    }
    std::cout << "Prices: " << std::endl;
    std::cout << "\tTabaco: " << tabaco->price << std::endl;
    std::cout << "\tPaper: " << paper->price << std::endl;
    std::cout << "\tMatches: " << matches->price << std::endl;
}

void Agent::changePrice() {
    updatePrice(this->tabaco);
    updatePrice(this->paper);
    updatePrice(this->matches);
}


Smoker::Smoker(Agent* agent) : agent(agent){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    cash = rand()%100;
    item = new Item(this);
}

double Smoker::getCash() {
    return cash;
}

std::string Smoker::getSelling() {
    return selling;
}

WithTabaco::WithTabaco(Agent* agent) : Smoker(agent){
    selling = "tabaco";
    id = 0;
    agent->tabaco = item;
}

WithPaper::WithPaper(Agent* agent) : Smoker(agent){
    selling = "paper";
    id = 1;
    agent->paper = item;
}

WithMatches::WithMatches(Agent* agent) : Smoker(agent){
    selling = "matches";
    id = 2;
    agent->matches = item;
}

void Smoker::tryToBuy() {
    if(cash >= agent->matches->price + agent->paper->price + agent->tabaco->price - item->price){
        cash -= agent->matches->price + agent->paper->price + agent->tabaco->price - item->price;
        agent->matches->gotBought[id] = true;
        agent->matches->owner->cash += agent->matches->price;
        agent->paper->gotBought[id] = true;
        agent->paper->owner->cash += agent->paper->price;
        agent->tabaco->gotBought[id] = true;
        agent->tabaco->owner->cash += agent->tabaco->price;
        item->gotBought[id] = false;
        cash-=item->price;
        std::cout<< "Smoker with " << selling << " is smoking now..." << std::endl;  
        agent->matches->waiting[id] = true;
        agent->paper->waiting[id] = true;
        agent->tabaco->waiting[id] = true;
        item->waiting[id] = false;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    else{
        agent->matches->gotBought[id] = false;
        agent->paper->gotBought[id] = false;
        agent->tabaco->gotBought[id] = false;
        agent->matches->waiting[id] = false;
        agent->paper->waiting[id] = false;
        agent->tabaco->waiting[id] = false;
    }
}