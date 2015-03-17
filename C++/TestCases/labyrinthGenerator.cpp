/**
 * Author: Lihang Li
 * Solution: Generate a labyrinth randomly
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    // Use default output file name - map.txt
    string outputFileName = "map.txt";

    if(argc == 2) {
        outputFileName = argv[1];
    }

    // Initial random seed
    srand(time(NULL));

    int labyRow, labyCol;
    vector<vector<char> > labyMap;
    char tmpChar;

    // Generate map
    labyRow = rand() % 10 + 1;
    labyCol = rand() % 10 + 1;
    for(int i = 0; i < labyRow; ++i) {
        vector<char> row;
        labyMap.push_back(row);
        for(int j = 0; j < labyCol; ++j) {
            tmpChar = (rand() % 2 == 0)?'.':'#';
            labyMap[i].push_back(tmpChar);
        }
    }

    // Output to file
    ofstream labyMapFile(outputFileName.c_str());
    if(!labyMapFile.is_open()){
        cout<<"Error opening "<<outputFileName<<endl;
        exit(1);
    }
    
    labyMapFile<<labyRow<<" "<<labyCol<<endl;
    for(int i = 0; i < labyRow; ++i) {
        for(int j = 0; j < labyCol; ++j) {
            labyMapFile<<labyMap[i][j];
        }
        labyMapFile<<endl;
    }

    labyMapFile.close();

    return 0;
}
