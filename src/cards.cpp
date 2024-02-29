
#include "cards.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> hands = {"HIGH CARD", "ONE PAIR", "TWO PAIR", "THREE OF A KIND", "STRAIGHT",
                        "FLUSH", "FULL HOUSE", "FOUR OF A KIND", "STRAIGHT FLUSH", "ROYAL FLUSH"};

vector<string> val = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

vector<string> suit = {"c", "d", "h", "s"}; // clubs, diamonds, hearts, spades
vector<string> suit_stylized = {"♣", "♦", "♥", "♠"};

string card_string(int ix)
{
    return val[ix % 13] + suit_stylized[ix / 13];
}

int get_index(vector<string> &vec, string key)
{
    auto it = find(vec.begin(), vec.end(), key);

    return (it != vec.end() ? it - vec.begin() : -1);
}

int decode_card(string card)
{
    int val_ix = get_index(val, card.substr(0, card.size() - 1));
    int suit_ix = get_index(suit, card.substr(card.size() - 1, card.size()));
    return (val_ix != -1 && suit_ix != -1) ? suit_ix * 13 + val_ix : -1;
}

vector<int> convert_hand(vector<string> &s_hand)
{
    vector<int> hand;
    for (string card : s_hand)
    {
        hand.push_back(decode_card(card));
    }
    sort(hand.begin(), hand.end());

    return hand;
}
vector<vector<int>> convert_multiple_hands(vector<vector<string>> known_hands_str)
{
    vector<vector<int>> known_hands;

    for (vector<string> known_hand_str : known_hands_str)
    {
        known_hands.push_back(convert_hand(known_hand_str));
    }
    return known_hands;
}

void print_hand(vector<int> hand)
{
    for (int card : hand)
    {
        cout << card_string(card) << " ";
    }
}

void print_score(int score)
{
    score /= pow(13, 5);

    int n2 = score % 13;
    score /= 13;
    int n1 = score % 13;
    score /= 13;
    int m = score;

    printf("%s ", hands[m].c_str());
    if (m == 2 || m == 6)
    {
        printf("with %s & %s", val[n1].c_str(), val[n2].c_str());
    }
    else if (!(m > 3 && m != 7))
    {
        printf("with %s", val[n1].c_str());
    }
    cout << endl;
}

double calc_error(double prop, int N)
{
    return 1.96 * sqrt(prop * (1 - prop) / N);
}

int pascal(vector<int> &table, int N, int k)
{
    int combos;
    int ix = 53 * k + N;
    if (N < k)
    {
        return 0;
    }
    else if (table[ix] != 0)
    {
        return table[ix];
    }

    combos = pascal(table, N - 1, k - 1) + pascal(table, N - 1, k);
    table[ix] = combos;
    return combos;
}

vector<int> gen_combo_table(int N, int k)
{
    vector<int> c_table((k + 1) * (N + 1));
    for (int m = 0; m <= N; ++m)
    {
        c_table[m] = 1;
    }

    for (int i = 1; i <= k; ++i)
    {
        for (int j = i; j <= N; ++j)
        {
            pascal(c_table, j, i);
        }
    }

    return c_table;
}
