
#ifndef MONTECARLOPOKER_CARDS_H
#define MONTECARLOPOKER_CARDS_H

#include <vector>
#include <string>
using namespace std;

vector<int> convert_hand(vector<string> &s_hand);
void print_hand(vector<int> hand);
double calc_error(double prop, int N);
vector<int> gen_combo_table(int N, int k);
int decode_card(string hand);
vector<vector<int>> convert_multiple_hands(vector<vector<string>> known_hands_str);

#endif // MONTECARLOPOKER_CARDS_H
