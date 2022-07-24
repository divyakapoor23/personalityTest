// Divya
// Project #2
//
// This program will read an input file containing the response of people to the
// Keirsey Temperament Sorter Test and produce a output file containing the personality types

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int FOUR = 4;

// This function updates the count of A or B answer based on the input character at the entered index
void updateAnswerCount(int noOfAs[],int noOfBs[],char ch, int index) {
    if (ch == 'A' || ch == 'a') {
        noOfAs[index]++;
    } else if(ch == 'B' || ch == 'b') {
        noOfBs[index]++;
    }
}

// This function updates the personlity types for each of the 4 sets depending on the percentages of B
void updatePersonalityTypes(char personalityTypes[], int percentagesOfB[]) {
    if (percentagesOfB[0] > 50) {
        personalityTypes[0] = 'I';
    } else if(percentagesOfB[0] < 50) {
        personalityTypes[0] = 'E';
    } else {
        personalityTypes[0] = 'X';
    }

    if (percentagesOfB[1] > 50) {
        personalityTypes[1] = 'N';
    } else if(percentagesOfB[1] < 50) {
        personalityTypes[1] = 'S';
    } else {
        personalityTypes[1] = 'X';
    }

    if (percentagesOfB[2] > 50) {
        personalityTypes[2] = 'F';
    } else if(percentagesOfB[2] < 50) {
        personalityTypes[2] = 'T';
    } else {
        personalityTypes[2] = 'X';
    }

    if (percentagesOfB[3] > 50) {
        personalityTypes[3] = 'P';
    } else if(percentagesOfB[3] < 50) {
        personalityTypes[3] = 'J';
    } else {
        personalityTypes[3] = 'X';
    }
}

// The function write the final output to the file specified, one line at a time
void writeOutputToFile(ofstream& file,string name,int percentagesOfB[],char personalityTypes[]) {
    file << name << ": [";
    for (int i=0;i<=2;i++) {
        file << percentagesOfB[i] << ", ";
    }
    file << percentagesOfB[3] << "] = ";
    for (int i=0;i<FOUR;i++) {
        file << personalityTypes[i];
    }
    file << endl;
}

// The function write the checkpoint output to the file specified, one line at a time
void writeCheckpointOutputToFile(ofstream& file,string name,int noOfAs[],int noOfBs[]) {
    file << name << ": ";
    for (int i=0;i<FOUR;i++) {
        file << noOfAs[i] << " ";
    }
    for (int i=0;i<FOUR;i++) {
        file << noOfBs[i] << " ";
    }
    file << endl;
}

// the function computes the percentages of B(rounded to next integer) based on the count of A and B responses
void computePercentageOfB(int noOfAs[],int noOfBs[],int percentagesOfB[]) {
    for (int i=0;i<FOUR;i++) {
        int total = noOfAs[i]+noOfBs[i];
        float percentage = (float)noOfBs[i]*100/(float)total;
        percentagesOfB[i] = (int)(percentage + 0.5);
    }
}

int main() {
    ifstream inputFile("personality.txt");
    ofstream checkpointOutputFile("personality(checkpoint).out");
    ofstream outputFile("personality.out");
    string name,answer;
    // read the file till it is empty
    while(getline(inputFile,name)) {
//        int arr[5];
        int noOfAs[FOUR] = {0};
        int noOfBs[FOUR] = {0};
        int percentagesOfB[FOUR] = {0};
        char personalityTypes[FOUR];
        getline(inputFile,answer);
        // read 7 characters at a time
        for (int i=0;i<answer.size();i+=7) {
            // update the count of A or B for the first group
            updateAnswerCount(noOfAs,noOfBs,answer[i],0);

            // update the count of A or B for the second group for the next 2 questions
            updateAnswerCount(noOfAs,noOfBs,answer[i+1],1);
            updateAnswerCount(noOfAs,noOfBs,answer[i+2],1);

            // update the count of A or B for the third group for the next 2 questions
            updateAnswerCount(noOfAs,noOfBs,answer[i+3],2);
            updateAnswerCount(noOfAs,noOfBs,answer[i+4],2);

            // update the count of A or B for the fourth group for the next 2 questions
            updateAnswerCount(noOfAs,noOfBs,answer[i+5],3);
            updateAnswerCount(noOfAs,noOfBs,answer[i+6],3);
        }
        computePercentageOfB(noOfAs,noOfBs,percentagesOfB);
        updatePersonalityTypes(personalityTypes,percentagesOfB);
        writeCheckpointOutputToFile(checkpointOutputFile,name,noOfAs,noOfBs);
        writeOutputToFile(outputFile,name,percentagesOfB,personalityTypes);
    }
    checkpointOutputFile.close();
    outputFile.close();
}
