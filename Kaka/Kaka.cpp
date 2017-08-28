#include <iostream>
#include <array>

constexpr size_t x_size = 20;
constexpr size_t y_size = 100;

using board_t = std::array<std::array<bool, y_size>, x_size>;

void drawBoard(const board_t& board) {
	for (size_t y = 0; y < y_size + 2; ++y) {
		std::cout << "-";
	}

	std::cout << std::endl;

	for (size_t x = 0; x < x_size; ++x) {
		std::cout << "|";
		for (size_t y = 0; y < y_size; ++y) {
			std::cout << (board[x][y] ? 'x' : ' ');
		}
		std::cout << "|" << std::endl;
	}

	for (size_t y = 0; y < y_size + 2; ++y) {
		std::cout << "-";
	}

	std::cout << std::endl;
}

board_t applyRules(const board_t& board) {
	board_t newBoard = { false };

	for (size_t x = 0; x < x_size; ++x) {
		for (size_t y = 0; y < y_size; ++y) {
			size_t liveNeighbours = 0;

			if (x != 0 && y != 0 &&                   board[x - 1][y - 1]) { ++liveNeighbours; }
			if (x != 0 &&                             board[x - 1][y])     { ++liveNeighbours; }
			if (x != 0 && y != y_size - 1 &&          board[x - 1][y + 1]) { ++liveNeighbours; }
			if (y != 0 &&                             board[x][y - 1])     { ++liveNeighbours; }
			if (y != y_size - 1 &&                    board[x][y + 1])     { ++liveNeighbours; }
			if (x != x_size - 1 && y != 0 &&          board[x + 1][y - 1]) { ++liveNeighbours; }
			if (x != x_size - 1 &&                    board[x + 1][y])     { ++liveNeighbours; }
			if (x != x_size - 1 && y != y_size - 1 && board[x + 1][y + 1]) { ++liveNeighbours; }

			if (board[x][y]) {
				switch (liveNeighbours) {
				case 0: 
				case 1:
					newBoard[x][y] = false; break;
				case 2:
				case 3:
					newBoard[x][y] = true; break;
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
					newBoard[x][y] = false; break;
				}
			}
			else if(liveNeighbours == 3) {
				newBoard[x][y] = true;
			}
		}
	}

	return newBoard;
}

int main() {
	board_t board = { false };

	board[5][4] = true;
	board[5][5] = true;
	board[5][6] = true;
	board[4][6] = true;
	board[3][5] = true;
	board[4][3] = true;

	while (std::cin.get() != 'q') {
		drawBoard(board);
		board = applyRules(board);
	}
}