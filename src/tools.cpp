
#include "tools.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void print(vector<int> const &input)
{
    std::copy(input.begin(),
              input.end(),
              std::ostream_iterator<int>(std::cout, " "));
}

ifstream::pos_type filesize(const char *filename)
{
    ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    ifstream::pos_type ret = in.tellg();
    return ret;
}

void write_vect(vector<int> vect, string name)
{
    fstream f;
    int *arr = &vect[0];
    f.open(name, ios::out | ios::binary);
    if (f)
    {
        f.write(reinterpret_cast<char *>(arr), vect.size() * 4);
        f.close();
    }
    else
    {
        cout << "Error" << endl;
    }
}

vector<int> read_vect(const char *name)
{
    fstream f;
    string loc = name;
    f.open(loc, ios::in | ios::binary);
    int fsize = filesize(loc.c_str());
    vector<int> vect(fsize / 4);
    int *arr = &vect[0];
    if (f)
    {
        f.read(reinterpret_cast<char *>(arr), fsize);
        f.close();
    }
    return vect;
}
vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

vector<vector<string>> readKnownHands()
{
    string input;
    getline(cin, input);

    vector<vector<string>> knownHands;
    vector<string> handsSplit = split(input, ';'); // Split input into individual hands

    for (auto &hand : handsSplit)
    {
        vector<string> handCards = split(hand, ','); // Split each hand into cards
        // Trim spaces if any (optional, but can make input more flexible)
        for (auto &card : handCards)
        {
            card.erase(remove_if(card.begin(), card.end(), ::isspace), card.end());
        }
        knownHands.push_back(handCards);
    }

    return knownHands;
}
vector<string> readCommunityCards()
{
    string input;
    getline(cin, input);
    vector<string> communityCards;
    if (input.empty())
    {
        return communityCards;
    }

    // Split input into individual cards, assuming space (' ') as the delimiter
    communityCards = split(input, ',');

    // Optional: Trim spaces from each card (if any, though splitting by space should inherently remove them)
    for (auto &card : communityCards)
    {
        card.erase(remove_if(card.begin(), card.end(), ::isspace), card.end());
    }

    return communityCards;
}