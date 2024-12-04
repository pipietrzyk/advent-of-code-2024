#include <algorithm> 
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

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

    vector<vector<int>> reports;

    fstream file;
    string fileName = arg;

    file.open(fileName.c_str());
    string line;
    while (getline(file, line)) {
        // Vector to hold the numbers in the current line
        vector<int> currentLine;

        // Use a stringstream to parse the line
        stringstream ss(line);
        int number;

        while (ss >> number) {
            currentLine.push_back(number);
        }

        // Add the parsed line to the reports vector
        reports.push_back(currentLine);
    }

    // Close the file
    file.close();

    reports = {{7,5,7,8,9}, {1,5,7,8,9}, {1,2,7,8,9}};
    // TODO: REWRITE THE WHOLE ALGORITHM!!!!!!!!!!

    //printf("Safe reports: %d", safeReports);
    return 0;
}