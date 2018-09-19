#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

int search(string text, string pattern, bool gwiazdka)
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
                for (int z = y; z < patternSize; z++)
                {
                    if (pattern[z] != '*')
                    {
                        return -1;
                    }
                }
                return x;
            }

            if (pattern[y] == '*')
            {
                string newText = text.substr(x + y, textSize - x - y);
                string newPattern = pattern.substr(y + 1, patternSize - y - 1);
                int index = search(newText, newPattern, true);
                if (index == -1)
                {
                    return -1;
                }
                else
                {
                    return x;
                }
            }

            if (pattern[y] != text[x + y + forward] && (pattern[y] != '?' || text[x + y + forward] == ' '))
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

    int beginIndex = 0;
    bool stop = false;
    while (!stop)
    {
        int spaceIndex = text.find(' ', beginIndex);
        if (spaceIndex == -1)
        {
            spaceIndex = text.size() + 1;
            stop = true;
        }
        string newText = text.substr(beginIndex, spaceIndex - beginIndex);
        int index = search(newText, pattern, false);
        if (index >= 0)
        {
            outputFile << "TAK " << index + beginIndex << endl;
            return;
        }

        beginIndex = spaceIndex + 1;

    }

    outputFile << "NIE" << endl;
}

int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    if (argc != 3)
    {
        return 0;
    }

    // while (1)
    //  {
    ifstream inputFile(argv[1]);
    ofstream outputFile;
    outputFile.open(argv[2]);

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
    //       getchar();
    //   }
}