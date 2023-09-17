#include "Minimax.h"

std::pair<int, int>minimax2(GameBoard* game, int player) {
	std::unique_ptr<GameBoard> tempBoard(new GameBoard());
	tempBoard->copyBoard(game);

	int tempValue;
	int maxValue = -MAX_NUMBER;
	bool pass = true;
	int maxDepth = 0;

	time_t start;
	time_t now;
	time(&start);
	time(&now);
	std::pair<int, int> coords;
	while(!(difftime(now, start) >= COMPUTING_TIME || maxDepth > (game->scoreBoard(0)))) {
		//Iterative Deepening
		maxDepth++;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (game->validateMove(i, j, player)) {
					if (game->makeMove(i, j, player)) {
						tempValue = minimize(game, player, -MAX_NUMBER, MAX_NUMBER, maxDepth - 1, start);
						if (tempValue >= maxValue) {
							pass = false;
							coords.first = i;
							coords.second = j;
							maxValue = tempValue;
						}

						game->copyBoard(tempBoard.get());
					}
				}
			}
		}
		time(&now);
	}
	if (pass) {
		//std::cout << "Passed" << std::endl;
		coords.first = -1; // just return something so comp can pass
		coords.second = -1;
	}
	return coords;
}

int maximize(GameBoard* oldBoard, int player, int alpha, int beta, int maxDepth, time_t startingTime) {
	if (oldBoard->fullGame() || (!(oldBoard->canMove(player)) && !(oldBoard->canMove(-player)))) {
		int score1 = oldBoard->scoreBoard(player);
		int score2 = oldBoard->scoreBoard(-player);
		//std::cout << "Aborted " << score1 << " " << score2 << (!oldBoard->canMove(player) && !oldBoard->canMove(-player)) << std::endl;
		if (score1 == score2) {
			return 0;
		}
		else if (score1 > score2) {
			return MAX_NUMBER;
		}
		else {
			return -MAX_NUMBER;
		}
	}

	std::unique_ptr<GameBoard> tempBoard(new GameBoard());
	tempBoard->copyBoard(oldBoard);

	int maxValue = -MAX_NUMBER;
	int tempValue;
	//Stops when gets to maxDepth or when game is over
	time_t now;
	time(&now);

	if (maxDepth <= 0 || difftime(now, startingTime) >= COMPUTING_TIME || !(oldBoard->canMove(player))) {
		return oldBoard->evaluateBoard(player);
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (oldBoard->validateMove(i, j, player)) {
				if (oldBoard->makeMove(i, j, player)) {
					tempValue = minimize(oldBoard, player, alpha, beta, maxDepth-1, startingTime);
					maxValue = std::max(maxValue, tempValue);
					//Alpha-beta pruning
					if (maxValue > beta) {
						return maxValue;
					}
					alpha = std::max(alpha, maxValue);
					oldBoard->copyBoard(tempBoard.get());
				}
			}
		}
	}
	return maxValue;
}

int minimize(GameBoard* oldBoard, int player, int alpha, int beta, int maxDepth, time_t startingTime) {
	if (oldBoard->fullGame() || (!(oldBoard->canMove(player)) && !(oldBoard->canMove(-player)))) {
		int score1 = oldBoard->scoreBoard(player);
		int score2 = oldBoard->scoreBoard(-player);
		//std::cout << "Aborted " << score1 << " " << score2 << (!oldBoard->canMove(player) && !oldBoard->canMove(-player)) << std::endl;
		if (score1 == score2) {
			return 0;
		}
		else if (score1 > score2) {
			return MAX_NUMBER;
		}
		else {
			return -MAX_NUMBER;
		}
	}

	std::unique_ptr<GameBoard> tempBoard(new GameBoard());
	tempBoard->copyBoard(oldBoard);

	int minValue = MAX_NUMBER;
	int tempValue;
	//Stops when gets to maxDepth or when game is over
	time_t now;
	time(&now);
	if (maxDepth <= 0 || difftime(now, startingTime) >= COMPUTING_TIME || !(oldBoard->canMove(player))) {
		return oldBoard->evaluateBoard(player);
	}


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (oldBoard->validateMove(i, j, -player)) {
				if (oldBoard->makeMove(i, j, -player)) {
					tempValue = maximize(oldBoard, player, alpha, beta, maxDepth - 1, startingTime);
					minValue = std::min(minValue, tempValue);
					//Add alpha beta later
					if (minValue < alpha) {
						return minValue;
					}
					beta = std::min(beta, minValue);
					oldBoard->copyBoard(tempBoard.get());
				}
			}
		}
	}
	return minValue;
}