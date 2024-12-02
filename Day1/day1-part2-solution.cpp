#include <algorithm> 
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please pass a text file to be parsed");
        exit(-1);
    }

    string arg = argv[1];
    if (arg.find(".txt") == std::string::npos) {
        printf("Please pass a text file to be parsed");
        exit(-1);
    }

    // Store each list
    vector<int> list1;
    vector<int> list2;

    fstream file;
    string fileName = arg;

    file.open(fileName.c_str());

    // Parse the file string by string and add each ID to the proper list
    int i = 0;
    string stringID;
    while(file >> stringID) {
        if (i % 2 == 0) {
            list1.push_back(stoi(stringID));
        } else if (i % 2 == 1) {
            list2.push_back(stoi(stringID));
        }
        i++;
    }

    // Calculate the similarity score
    int simScore = 0;
    for (i = 0; i < list1.size(); i++) {
        simScore += list1.at(i) * count(list2.begin(), list2.end(), list1.at(i));
    }
    
    printf("Similarity score: %d", simScore);
    return 0;
}