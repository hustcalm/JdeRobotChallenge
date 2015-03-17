/**
 * Author: Lihang Li
 * Solution: Labyrinth, find the largest pathway
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

#define DEBUG 0

void usage()
{
    cout<<"Usage: labyrinth map.txt"<<endl;
}

int dirNum = 4;
int dirX[] = {-1, 0, 1,  0};
int dirY[] = { 0, 1, 0, -1};

void DFS(int x, int y, vector<vector<char> > &labyMap, vector<vector<bool> > &visited, int &curLen, bool outputMap)
{
    if(outputMap) {
        labyMap[x][y] = curLen + '0';
    }

    for(int i = 0; i < dirNum; ++i) {
            // Move along 4 directions as [up, right, down, left]
            int newX = x + dirX[i];
            int newY = y + dirY[i];
            if(newX >= 0 && newX < labyMap.size() &&
               newY >=0  && newY < labyMap[0].size() &&
               labyMap[newX][newY] == '.' &&
               visited[newX][newY] == false) {
                // Visit the node
                if(DEBUG) {
                    cout<<"Now visiting: ("<<newX<<","<<newY<<")."<<endl;
                }

                visited[newX][newY] = true;
                curLen = curLen + 1;
                DFS(newX, newY, labyMap, visited, curLen, outputMap);
            }
    }
}

int main(int argc, char* argv[])
{
    // Default input name - map.txt
    string inputFileName = "map.txt";

    if(argc == 2) {
        inputFileName = argv[1];
    }

    // Read in the Labyrinth
    ifstream mapFile(inputFileName.c_str());
    if(!mapFile.is_open()) {
        cout<<"Error opening the map file "<<argv[1]<< " ..."<<endl;
        exit(1);
    }

    int labyRow, labyCol;
    vector<vector<char> > labyMap;
    char tmpChar;
    mapFile>>labyRow>>labyCol;
    for(int i = 0; i < labyRow; ++i) {
        vector<char> row;
        labyMap.push_back(row);

        for(int j = 0; j < labyCol; ++j) {
            mapFile>>tmpChar;
            labyMap[i].push_back(tmpChar);
        }
    }

    mapFile.close();

    // Backup for output
    vector<vector<char> > outputMap = labyMap;

    cout<<"The Labyrinth input is like follows:"<<endl;
    cout<<labyRow<<" "<<labyCol<<endl;
    for(int i = 0; i < labyRow; ++i) {
        for(int j = 0; j < labyCol; ++j) {
            cout<<labyMap[i][j];
        }
        cout<<endl;
    }

    // Now solve the labyrinth problem using DFS, it's like finding connected components
    vector<vector<bool> > visited;
    for(int i = 0; i < labyRow; ++i) {
            vector<bool> row;
            visited.push_back(row);

            for(int j = 0; j < labyCol; ++j) {
                visited[i].push_back(false);
            }
    }

    // Backup for output
    vector<vector<bool> > outputVisited = visited;

    int maxLen = 0;
    int curLen;
    int startX, startY;
    for(int i = 0; i < labyRow; ++i) {
        for( int j = 0; j < labyCol; ++j) {
            if(labyMap[i][j] == '#' || visited[i][j] == true) continue;
            if(DEBUG) {
                cout<<"Visiting position:"<<i<<" "<<j<<endl;
                if(labyMap[i][j] == '#') {
                    cout<<"It is a block #."<<endl;
                }
                else if(visited[i][j] == true) {
                    cout<<"It is already visited."<<endl;
                }
                else{
                    cout<<"Start DFS from ("<<i<<","<<j<<")..."<<endl;
                }
            }

            // Now we have a '.' and not visited yet, do a DFS from here and track the pathway
            curLen = 1;
            visited[i][j] = true;
            DFS(i ,j, labyMap, visited, curLen, false);

            if(DEBUG) {
                cout<<"This DFS len is: "<<curLen<<endl;
            }

            if(curLen > maxLen) {
                maxLen = curLen;
                startX = i;
                startY = j;

                if(DEBUG) {
                    cout<<"New max len is: "<<maxLen<<endl;
                }
            }
        }
    }

    if(DEBUG) {
        cout<<"The length of the largest pathway is: "<<maxLen<<endl;
    }

    // Now restore the map and do a final DFS to get the result
    curLen = 1;
    outputVisited[startX][startY] = true;
    DFS(startX, startY, outputMap, outputVisited, curLen, true);

    cout<<"The output is as follows:"<<endl;
    for(int i = 0; i < labyRow; ++i) {
        for(int j = 0; j < labyCol; ++j) {
            cout<<outputMap[i][j];
        }
        cout<<endl;
    }

    return 0;
}
