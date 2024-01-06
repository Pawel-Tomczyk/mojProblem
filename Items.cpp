#include "Items.h"

Item::Item(Smoker* owner) : owner(owner){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    price = rand()%100;
    last_up = 0;
    last_down = 0;
    for (int i = 0; i < 3; i++)
    {
        gotBought[i] = false;
    }
    for (int i = 0; i < 3; i++)
    {
        waiting[i] = false;
    }
    
}