#include "graph.hpp"
#include <fstream>

int main() {
    Graph* graph = new Graph();
    while (true) {
        std::string command;
        std::cin >> command;

        if (command == "INSERT") {
            int a, b;
            double d, s;
            std::cin >> a >> b >> d >> s;

            try {
                graph->insert(a, b, d, s);
                std::cout << "success" << std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
            }

        }else if (command == "LOAD"){
            std::string filename;
            std::cin >> filename;

            std::ifstream file(filename);
            int a, b;
            double d, s;

             //setting a flag to avoid printing success multiple times
            bool flag = false;

            while (file >> a >> b >> d >> s) {
                graph->insert(a, b, d, s);
                flag = true;
            }

            if (flag) {
                std::cout << "success" << std::endl;
            }

        } else if (command == "PRINT") {
            int a;
            std::cin >> a;

            try {
                graph->print(a);
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
            }

        } else if (command == "DELETE") {
            int a;
            std::cin >> a;

            try {
                graph->deleteVertex(a);
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
            }

        } else if (command == "TRAFFIC"){
            int a, b;
            double A;
            std::cin >> a >> b >> A;

            try {
                bool done = graph->traffic(a, b, A);
                if (done){
                    std::cout << "success" << std::endl;
                }else{
                    std::cout << "failure" << std::endl;
                }
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
            }

        } else if (command == "UPDATE"){
            std::string filename;
            std::cin >> filename;
            graph->update(filename);
        } 
        
        else if (command == "LOWEST"){
            int a, b;
            std::cin >> a >> b;

            try {
                graph->lowest(a, b);
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command == "END") {
            break;
        }else if (command == "PATH"){
            int a, b;
            std::cin >> a >> b;

            try {
                graph->path(a, b);
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    delete graph;
    return 0;
}
