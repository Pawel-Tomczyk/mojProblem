#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "People.h"
#include "Items.h"

int main(){
    using namespace std;
    Agent* agent = new Agent;
    Smoker* tabaco = new WithTabaco(agent);
    Smoker* paper = new WithPaper(agent);
    Smoker* matches = new WithMatches(agent);


    while(true){
        std::thread t1(&Smoker::tryToBuy, tabaco);
        std::thread t2(&Smoker::tryToBuy, paper);
        std::thread t3(&Smoker::tryToBuy, matches);

        t1.detach();
        t2.detach();
        t3.detach();

        std::thread t4(&Agent::changePrice, agent);
        t4.join();
    }

    return 0;
}
