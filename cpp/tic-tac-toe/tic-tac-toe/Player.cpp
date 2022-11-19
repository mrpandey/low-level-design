#include <string>
#include "Player.h"

using namespace std;

Player::Player(string s) : name(s) {}

string Player::GetName()
{
    return name;
}