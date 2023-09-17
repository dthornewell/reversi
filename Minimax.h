#pragma once
#include "Reversi Game.h"
#include <time.h>
#include <iostream>
#include <thread>
#include <list>

#define COMPUTING_TIME 30
#define MAX_NUMBER 8192

class threadObject {
public:
	GameBoard board;
	std::pair<int, int> coord;
	std::thread threadObj;
	int score;

	threadObject(std::pair<int, int>& c);

	void run(GameBoard* game, int player, int maxDepth, time_t start);

	void join();
};

std::pair<int, int>minimax2(GameBoard* game, int player);
int minimize(GameBoard* oldBoard, int player, int alpha, int beta, int maxDepth, time_t startingTime);
int maximize(GameBoard* oldBoard, int player, int alpha, int beta, int maxDepth, time_t startingTime);
