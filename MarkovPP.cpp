//***********************************
// CS471  Final Project Option 3
// ***********************************

// add includes here
#include <map>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include <string>
using namespace std;
map<string, float> probs;//Probabilities of  Words from part1 of the project
map<string, float> probs2;//Probabilities of  Words from output file and part 2 of the project.
map<string, int> cvWordCount;//Word count map for words in covid related texts

/********************************************** PART 1 functions *******************************************************/

//calculates the probability of each, P(word) = word count/ words total
void calculatecvWordProbability(int wordCount){
    map<string, int>::iterator it;
    for ( it = cvWordCount.begin(); it != cvWordCount.end(); it++ )
    {
        probs[it->first] = it->second/(wordCount + .0);
    }
}

//Calculates the probability of P(word1word2) = P(word1) * P(word2)
float calculateWordPairProbability(string word1, string word2){
    return probs[word1] * probs[word2];
}

//Initializes word probability map of words used in the program
void initializecvWordProbabilitiesMap(){
    cvWordCount["COVID-19"] +=  0;
    cvWordCount["positive"] +=  0;
    cvWordCount["deaths"] +=  0;
    cvWordCount["test"] +=  0;
    cvWordCount["coughs"] +=  0;
    cvWordCount["droplets"] +=  0;
    cvWordCount["severe"] +=  0;
    cvWordCount["mild"] +=  0;
    cvWordCount["fever"] +=  0;
    cvWordCount["pneumonia"] +=  0;
    cvWordCount["asymptomatic"] +=  0;
}

//Prints the probabilities stored in map/dictionary for part1
void printcvWordProbabiities() {
    cout << "The probabilities:" << endl;
    map<string, float>::iterator it;
    for ( it = probs.begin(); it != probs.end(); it++ )
    {
        cout << "P(" << it->first << ")" << " = " << it->second << endl; //Display key and value
    }
    cout << endl;
}



//Prints the word counts stored in map/dictionary
void printcvWordCount(int wordCount) {
    cout << "The word count:" << endl;
    cout << "Total word count = " << wordCount << endl;
    //iterate through word count map
    map<string, int>::iterator it;
    for ( it = cvWordCount.begin(); it != cvWordCount.end(); it++ )
    {
        cout << it->first << " word count = " << it->second << endl; //Display key and value
    }
    cout << endl;
}

//Creates output file containing the probabilities of the words
void createOutputFileProbabilities(){
    ofstream myFile("wordProbs.txt");
    //write to file
    if (myFile.is_open()){
        myFile << "COVID-19" << " " << probs["COVID-19"] << endl;
        myFile << "positive" << " " << probs["positive"] << endl;
        myFile << "deaths" << " " << probs["deaths"] << endl;
        myFile << "test" << " " << probs["test"] << endl;
        myFile << "coughs" << " " << probs["coughs"] << endl;
        myFile << "droplets" << " " << probs["droplets"] << endl;
        myFile << "severe" << " " << probs["severe"] << endl;
        myFile << "mild" << " " << probs["mild"] << endl;
        myFile << "fever" << " " << probs["fever"] << endl;
        myFile << "pneumonia" << " " << probs["pneumonia"] << endl;
        myFile << "asymptomatic" << " " << probs["asymptomatic"] << endl;
    } else {
        cout << "Could not open file" << endl;
        exit(1);
    }
}

//Reads the output file for the second part of the project.
void readOutputFileProbabilities(string fileName){
    ifstream myFile(fileName.c_str());
    string line;
    string delim = " ";
    string token;
    float probability = 0;
    //read through file
    if(myFile.is_open()){//If file open
        while(getline(myFile, line)){
            size_t pos = 0;
            while ((pos = line.find(delim)) != std::string::npos) {//stores key and value from .txt to map
                token = line.substr(0, pos);
                line.erase(0, pos + delim.length());
            }
            probability = atof(line.c_str());
            probs2[token] = probability;
        }
    }
}

/************************************************* PART 2 functions ***************************************************/
//Initializes the values of the map of our words given the output file from part 2.
void readProbsfromFile(string fileName){
    string line;
    string delim = " ";
    string token;
    float probability = 0;
    //read from file
    ifstream myFile(fileName.c_str());
    if(myFile.is_open()){//If file open
        while(getline(myFile, line)){
            size_t pos = 0;
            while ((pos = line.find(delim)) != std::string::npos) {//stores key and value from .txt to map
                token = line.substr(0, pos);
                line.erase(0, pos + delim.length());
            }
            probability = atof(line.c_str());
            probs2[token] = probability;
        }
    } else {//Else exit
        cout << "Could not open file." << endl;
        exit(1);
        
    }
}

//Prints the probabilities stored in map/dictionary for part 2
void printWordProbabiities2() {
    cout << "The probabilities:" << endl;
    //iterate through map used in part2 of project.
    map<string, float>::iterator it;
    for ( it = probs2.begin(); it != probs2.end(); it++ )
    {
        cout << "P(" << it->first << ")" << " = " << it->second << endl; //Display key and value
    }
    cout << endl;
}

//Calculates the conditional probability P(word1|word2) given two words/string.
void calcConditionalProbability(string word1, string word2){
    cout << "P(" << word1 << "|" << word2 << ") = " <<
    "P(" << word1 << word2 << ") / " << "P(" << word2 << ")" << endl;
    cout << "= " << calculateWordPairProbability(word1, word2) << " / " << probs2[word2] << endl;
    cout << "= " << calculateWordPairProbability(word1, word2) / probs2[word2];
}
int main()
{
    /**************************************** PART 1 of the project *******************************************/
    std::cout << "Collecting data from corpus... " <<std::endl;//Begin collecting corpus data
    cout << endl << "Words program is using: " << endl;
    cout << "COVID-19, positive, deaths, test, coughs, droplets, severe, mild, fever, pneumonia, asymptomatic" << endl;
    string fileName = "trainingCorpus.txt"; //The file name of the training corpus
    cout << endl;
    // Read in the trigram probabilties
    string line;
    string delim = " ";
    string token;
    //float probability = 0;
    
    ifstream myFile(fileName.c_str());
    int wordCount = 0;//The word count of the corpus.
    initializecvWordProbabilitiesMap();//Initialized Word Probabilities map before collecting data.
    //read from file
    if(myFile.is_open()){//If file is open/open file
        while(getline(myFile, line)){
            size_t pos = 0;
            while ((pos = line.find(delim)) != std::string::npos) {//stores key and value from .txt to map
                token = line.substr(0, pos);
                line.erase(0, pos + delim.length());
                wordCount = wordCount + 1;
                if(token.find("COVID-19") != std::string::npos || token.find("Covid-19") != std::string::npos){
                    cvWordCount["COVID-19"] +=  1;
                } else if(token.find("positive") != std::string::npos || token.find("Positive") != std::string::npos){
                    cvWordCount["positive"] +=  1;
                } else if(token.find("deaths") != std::string::npos || token.find("Deaths") != std::string::npos){
                    cvWordCount["deaths"] +=  1;
                } else if(token.find("test") != std::string::npos || token.find("Test") != std::string::npos){
                    cvWordCount["test"] +=  1;
                } else if(token.find("coughs") != std::string::npos || token.find("Coughs") != std::string::npos){
                    cvWordCount["coughs"] +=  1;
                } else if(token.find("droplets") != std::string::npos || token.find("Droplets") != std::string::npos){
                    cvWordCount["droplets"] +=  1;
                } else if(token.find("severe") != std::string::npos || token.find("Severe") != std::string::npos){
                    cvWordCount["severe"] +=  1;
                } else if(token.find("mild") != std::string::npos || token.find("Mild") != std::string::npos){
                    cvWordCount["mild"] +=  1;
                } else if(token.find("fever") != std::string::npos || token.find("Fever") != std::string::npos){
                    cvWordCount["fever"] +=  1;
                } else if(token.find("pneumonia") != std::string::npos || token.find("Pneumonia") != std::string::npos){
                    cvWordCount["pneumonia"] +=  1;
                } else if(token.find("asympytomatic") != std::string::npos || token.find("Asympytomatic") != std::string::npos){
                    cvWordCount["asymptomatic"] +=  1;
                }
            }
            //probability = atof(line.c_str());
            //probs[token] = probability;
        }
    } else {//Else exit
        cout << "Could not open file." << endl;
        exit(1);
        
    }
    printcvWordCount(wordCount);//Print the word counts of our words
    calculatecvWordProbability(wordCount);//Calculate the probabilities of our words
    printcvWordProbabiities();//Print our word probabilities
    createOutputFileProbabilities();//Output our probabilities to test file "wordProbs.txt".
    
    //Prompt user to calc P(word1word2)
    while(true){
        cout << "Please provide two words to find P(word1word2) or * to quit: ";
        string word1;
        cin >> word1;
        if(word1.compare("*") == 0){
            break;
        }
        string word2;
        cin >> word2;
        if(word2.compare("*") == 0){
            break;
        }
        cout << "P(" << word1 << word2 << ") = " << "P(" << word1 << ") * P(" << word2 << ") = " << calculateWordPairProbability(word1, word2) << endl;
    }
    
    /**************************************** PART 2 of the project *******************************************/
    cout << endl << "/****************** PART 2 of the project **********/" << endl << endl;
    readProbsfromFile("wordProbs.txt");
    printWordProbabiities2();
    //Prompt user to calc P(word1|word2)
    while(true){
        cout << "Please provide two words to find P(word1|word2) or * to quit: ";
        string word1;
        cin >> word1;
        if(word1.compare("*") == 0){
            break;
        }
        string word2;
        cin >> word2;
        if(word2.compare("*") == 0){
            break;
        }
        cout << endl;
        calcConditionalProbability(word1, word2);
        cout << endl << endl;
    }
    
};


