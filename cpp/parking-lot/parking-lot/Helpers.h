#pragma once
#include<string>
#include<vector>
#include<sstream>

using namespace std;

vector<string> SplitString(string str);

vector<string> SplitStringByUnderscore(string str);

string JoinStringsByUnderscore(vector<string> vec);