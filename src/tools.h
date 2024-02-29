
#ifndef TOOLS_H
#define TOOLS_H
#include <vector>
#include <string>

using namespace std;

void print(vector<int> const &input);
void print_score(int score);
void write_vect(vector<int> vect, string name);
vector<int> read_vect(const char *name);
vector<string> split(const string &s, char delimiter);
vector<vector<string>> readKnownHands();
vector<string> readCommunityCards();

#endif