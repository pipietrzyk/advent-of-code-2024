#include <algorithm> 
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const string DIGITS = "0123456789";

bool isDigit(char m) {
    if (DIGITS.find(m) != string::npos)
        return true;
    return false;
}

bool isComma(char m) {
    if (m == ',') {
        return true;
    }
    return false;
}

bool isParentheses(char m) {
    if (m == ')') {
        return true;
    }
    return false;
}

void set_doMul(string mem, bool &doMul) {
    int indexOfLatestDo = 0;
    int indexOfLatestDont = 0; 
    int cutoff = 0;
    int tempDo = 0;
    int tempDont = 0;

    do {
        tempDo = mem.find("do()", cutoff);
        tempDont = mem.find("don't()", cutoff);

        if (tempDo != string::npos)
            indexOfLatestDo = tempDo;

        if (tempDont != string::npos) 
            indexOfLatestDont = tempDont;


        cutoff = min(indexOfLatestDo, indexOfLatestDont);
        
    } while (tempDo != string::npos && tempDont != string::npos);

    if (indexOfLatestDo > indexOfLatestDont) 
        doMul = 1;

    if (indexOfLatestDont > indexOfLatestDo) 
        doMul = 0;
}


int checkValidMul(string memory) {
    string strFirst, strSecond;
    int index = 4;
    char curChar = memory[index];

    if ( !(isDigit(curChar)) ) {
        return 0;
    }
    strFirst += curChar;

    // After the first digit there can only be a maximum of 2 more and then 1 comma (so this for loop only runs three times)
    for (int i = 0; i < 3; i++) {
        index++;
        curChar = memory[index];

        if (isComma(curChar)) {
            break;
        }

        if (! (isDigit(curChar)) ) {
            return 0;
        }

        strFirst += curChar;
    }

    // Now retrieve the second number after the comma
    for (int i = 0; i < 4; i++) {
        index++;
        curChar = memory[index];

        if (isParentheses(curChar)) {
            break;
        }

        if (! (isDigit(curChar)) ) {
            return 0;
        }

        strSecond += curChar;
    }

    if (strFirst.size() > 3 || strFirst.size() < 1)
        return 0;
    
    if (strSecond.size() > 3 || strSecond.size() < 1)
        return 0;

    int first = stoi(strFirst);
    int second = stoi(strSecond);

    return first * second;
}

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


    
    string m;
    string memory;

    ifstream file;
    string fileName = arg;
    file.open(fileName.c_str());

    // Parse the file into a string
    while(!file.eof()) {
	    getline(file, m);
	    memory += m + "\n";
	
    }
    file.close();


    bool doMul = 1;
    int sum = 0;
    // Find the first instance of 'mul(' in the string and delete everything before it
    int indexOfMul = memory.find("mul("); 

    while(indexOfMul != string::npos) {
        set_doMul(memory.substr(0, indexOfMul), doMul);

        memory = memory.erase(0, indexOfMul);

        if (doMul)
            sum += checkValidMul(memory);

        memory = memory.erase(0, 4);
        indexOfMul = memory.find("mul(");
    }

    printf("Total sum: %d\n", sum);

    return 0;
}