#pragma once
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

class Utility
{
    static set<int> WriteHighScore(int score);
    {
        // see if file exists and read the values
        string fileName = "highscores.txt";
        ifstream highscoreFile(fileName);
        ifstream_iterator<int> start(highscoreFile), end;
        set<int> highscores(start, end);
        highscoreFile.close();
        
        // if it's empty, populate and save
        if (highscore.size() == 0)
        {
            highscores.insert(100);
            highscores.insert(50);
            highscores.insert(25);
            highscores.insert(10);
            highscores.insert(5);

            ofstream outfile(fileName);
            ostream_iterator<int> output_iterator(outfile, "\n");
            copy(highscores.begin(), highscores.end(), output_iterator);
            outfile.close();
        }
        
        // write the score
        highscores.insert(score);
        
        // remove the lowest score
        highscores.erase(highscores.begin());

        // write the high scores
        ofstream outfile(fileName);
        ostream_iterator<int> output_iterator(outfile, "\n");
        copy(highscores.begin(), highscores.end(), output_iterator);
        outfile.close();

        return highscores;
    }
};