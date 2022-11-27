#include "Helpers.h"

vector<string> SplitString(string str){
    vector<string> ret;
    string word;

    istringstream iss(str);
    while(iss >> word){
        ret.push_back(word);
    }

    return ret;
}

vector<string> SplitStringByUnderscore(string str){
    vector<string> ret;
    for(int i=0, j; i<str.size();){
        j = i;
        while(j<str.size() && str[j]!='_') j++;
        ret.push_back(str.substr(i, j-i));
        i = j+1;
    }
    return ret;
}

string JoinStringsByUnderscore(vector<string> vec) {
    string ret = "";
    for(string str: vec){
        ret += str;
    }
    return ret;
}