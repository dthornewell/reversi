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

void tmaxValue(GameBoard* b, int player, int alpha, int beta, int depth, int maxDepth, time_t start, int* result);

int minValue(GameBoard* oldBoard, int player, int alpha, int beta, int depth, int maxDepth, time_t startingTime);
int maxValue(GameBoard* oldBoard, int player, int alpha, int beta, int depth, int maxDepth, time_t startingTime);
std::pair<int, int> minimax(GameBoard* game, int player);


