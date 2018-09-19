#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

int search(string text, string pattern)
{
    int patternSize = pattern.size();
    int textSize = text.size();
    for (int x = 0; x < textSize; x++)
    {
        bool good = true;
        int forward = 0;
        for (int y = 0; y < patternSize; y++)
        {
            if (x + y + forward >= textSize)
            {
                return -1;
            }

            if (pattern[y] == '*')
            {
                string newText = text.substr(x + y, textSize - x - y);
                string newPattern = pattern.substr(y + 1, patternSize - y - 1);
                int index = search(newText, newPattern);
                if (index == -1)
                {
                    good = false;
                    break;
                }
                else
                {
                    int spaceIndex = newText.find(' ');
                    if (spaceIndex < index && spaceIndex != -1)
                    {
                        good = false;
                        break;
                    }
                    return x;
                }
            }

//            pattern[y] != text[x + y + forward] && (pattern[y] == '?' && text[x+y+forward] != ' ')
            if (pattern[y] != text[x + y + forward] && (pattern[y] != '?' || text[x+y+forward] == ' '))
            {
                good = false;
                break;
            }
        }
        if (good)
        {
            return x;
        }
    }
    return -1;
}

void doIt(ifstream &inputFile, ofstream &outputFile)
{
    string text;
    string pattern;
    getline(inputFile, text);
    getline(inputFile, pattern);
    int index = search(text, pattern);
    if (index == -1)
    {
        cout << "NIE" << endl;
        outputFile << "NIE" << endl;
    }
    else
    {
        cout << "TAK " << index << endl;
        outputFile << "TAK " << index << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 0;
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile;
    outputFile.open (argv[2]);
    
    int z = 0;
    string line;

    if (inputFile.is_open())
    {
        getline(inputFile, line);
    }
    else
    {
        return 0;
    }

    z = atoi(line.c_str());
    while (z--)
    {
        doIt(inputFile, outputFile);
    }
    inputFile.close();
    outputFile.close();
}