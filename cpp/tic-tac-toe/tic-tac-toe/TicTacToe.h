#pragma once

#include <vector>
#include <string>
#include <utility>
#include "Player.h"
#include "Board.h"

using namespace std;

class TicTacToe
{
    int current_piece_idx;
    bool exit;
    bool game_over;
    Board board;
    vector<Piece> pieces;
    vector<Player> players;

    void SetPlayers();
    pair<int, int> ParseMove(string);
    void MakeMove();
    bool currentPlayerWon(int, int);

public:
    TicTacToe();
    void Start();
};