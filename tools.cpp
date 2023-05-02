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
    string filename = "soc-sign-bitcoinotc.csv";
    std::filesystem::path basePath("./graph_data");
    basePath /= filename;

    
    ifstream myfile(basePath);
    Graph graph(5881);
    if (myfile.is_open()) {
        int count = 0;
        while (getline(myfile, line) && count++ <= 32000) {
            vector<string> tokens;
            stringstream ss(line);
            string token;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            int source = stoi(tokens[0]);
            int target = stoi(tokens[1]);
            int value = stof(tokens[2]);
            value = value >=0 ? value: -value;
            graph.add_edge(source, target, value);
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