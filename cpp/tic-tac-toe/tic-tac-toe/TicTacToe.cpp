#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <utility>
#include <algorithm>
#include "TicTacToe.h"

using namespace std;

TicTacToe::TicTacToe()
{
    current_piece_idx = 0;
    game_over = false;
    pieces = {Piece('X'), Piece('O')};
    board = Board(3, Piece('-'));
    exit = false;
}

void TicTacToe::SetPlayers()
{
    string name;
    for (Piece piece : pieces)
    {
        cout << piece.GetPieceType() << " ";
        cin >> name;
        cin.ignore();
        Player player(name);
        players.push_back(player);
    }
}

pair<int, int> TicTacToe::ParseMove(string line)
{
    int i = 0, x = 0, y = 0;

    while (i < line.size() && isspace(line[i]))
        i++;
    while (i < line.size() && isdigit(line[i]))
    {
        x = x * 10 + line[i] - '0';
        i++;
    }

    while (i < line.size() && isspace(line[i]))
        i++;
    while (i < line.size() && isdigit(line[i]))
    {
        y = y * 10 + line[i] - '0';
        i++;
    }

    if ((i < line.size() && !isspace(line[i])))
    {
        x = y = 0;
    }

    return {x, y};
}

void TicTacToe::MakeMove()
{

    string line;
    getline(cin, line);

    if (line == "exit")
    {
        exit = true;
        return;
    }

    // ignore input
    if (game_over)
        return;

    pair<int, int> coords = ParseMove(line);
    int x = coords.first, y = coords.second;
    try{
        board.SetCell(x, y, pieces[current_piece_idx]);
    }
    catch(logic_error& e){
        cerr << e.what() << endl;
    }
    board.Print();

    if (currentPlayerWon(x, y))
    {
        cout << players[current_piece_idx].GetName() << " won the game" << endl;
        game_over = true;
    }
    else if (board.IsFull())
    {
        cout << "Game Over" << endl;
        game_over = true;
        return;
    }

    current_piece_idx++;
    current_piece_idx %= pieces.size();
}

bool TicTacToe::currentPlayerWon(int x, int y)
{
    bool ret = true;
    Piece piece = pieces[current_piece_idx];
    int board_size = board.GetSize();

    // check row
    if (board.GetCell(x, 1) == piece)
    {
        for (int j = 2; j <= board_size && ret; j++)
        {
            if (board.GetCell(x, j) != piece)
                ret = false;
        }
        if (ret)
            return true;
    }

    // check col
    if (board.GetCell(1, y) == piece)
    {
        ret = true;
        for (int i = 2; i <= board_size && ret; i++)
        {
            if (board.GetCell(i,y) != piece)
                ret = false;
        }
        if (ret)
            return true;
    }

    // check diagonals
    if (board.GetCell(1, 1) == piece)
    {
        ret = true;
        for (int i = 2; i <= board_size && ret; i++)
        {
            if (board.GetCell(i,i) != piece)
            {
                ret = false;
            }
        }
        if (ret)
            return true;
    }

    if (board.GetCell(1,board_size) == piece)
    {
        ret = true;
        for (int i = 2; i <= board_size && ret; i++)
        {
            if (board.GetCell(i, board_size - i + 1) != piece)
            {
                ret = false;
            }
        }
        if (ret)
            return true;
    }

    return false;
}

void TicTacToe::Start()
{
    SetPlayers();
    board.Print();
    while (!exit)
    {
        MakeMove();
    }
}