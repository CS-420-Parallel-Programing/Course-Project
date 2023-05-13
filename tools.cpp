#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "tools.h"
#include <filesystem>

using namespace std;

Graph getGraph(){
    string line;
    string filename = "Email-Enron.txt";

    // ifstream myfile(".\\graph_data\\" + filename);
    // ifstream myfile("graph_data/Email-Enron.txt");
    ifstream myfile("graph_data/Email-Enron.txt");
    Graph graph(36692, false);
    // Graph graph(4039, false);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            vector<string> tokens;
            stringstream ss(line);
            string token;

            // while (getline(ss, token, '	')) {
            //     tokens.push_back(token);
            // }
            while (getline(ss, token, '	')) {
                tokens.push_back(token);
            }

            int source = stoi(tokens[0]);
            int target = stoi(tokens[1]);
            graph.add_edge(source, target, 1);
            // cout << "var1: " << source << ", var2: " << target << ", var3: " << value << endl;
        }
        cout << "Find file: " << filename <<endl;
        myfile.close();
    }
    else {
        cout << "Unable to open file";
    }
    return graph;
}