#include <iostream>
#include "ChildrensGame.hpp"

//this is the main file, accepts input from user and generates appropriate output
int main() {
    ChildrenGame game;

    while (true) {
        std::string command;
        std::cin >> command;

        if (command == "SPAWN") {
            double x, y;
            std::cin >> x >> y;
            bool success = game.spawnChild(x, y);
            game.printResult(success);
        } else if (command == "TIME") {
            double t;
            std::cin >> t;
            game.moveChildren(t);
            int numChildren = game.countChildren();
            game.printResult(numChildren);
        } else if (command == "NUM") {
            int numChildren = game.countChildren();
            game.printResult(numChildren);
        } else if (command == "OVER") {
            int numChildren = game.countChildren();
            if (numChildren > 0) {
                std::cout << "the players win" << std::endl;
            } else {
                std::cout << "the wolf wins" << std::endl;
            }
            break;
        } else if (command == "PRT") {
            double D;
            std::cin >> D;
            game.PRT(D);
        }
    }

    return 0;
}