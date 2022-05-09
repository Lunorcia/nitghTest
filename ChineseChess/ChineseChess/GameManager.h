#pragma once
#include <iostream>
#include <vector>
#include "Chess.h"
#include "Viewer.h"
#include "Board.h"
using namespace std;
class GameManager
{
	vector<Chess> on_board;
	int current_player;
	Board board;
	Viewer viewer;
};

