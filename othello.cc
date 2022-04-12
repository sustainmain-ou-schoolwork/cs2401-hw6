#include "othello.h"

Othello::Othello() {
    // clear the board
    for (size_t row = 0; row < NUM_ROWS; ++row) {
        for (size_t col = 0; col < NUM_COLS; ++col) {
            board[row][col] = main_savitch_14::game::NEUTRAL;
        }
    }


    // get the left and top index of the middle square
    size_t left = (NUM_COLS / 2) - 1;  // index of left column in the square
    size_t top = (NUM_ROWS / 2) - 1;   // index of top row in the square

    // set the computer's discs in the square
    board[left][top] = main_savitch_14::game::COMPUTER;
    board[left + 1][top + 1] = main_savitch_14::game::COMPUTER;

    // set the human's discs in the square
    board[left + 1][top] = main_savitch_14::game::HUMAN;
    board[left][top + 1] = main_savitch_14::game::HUMAN;
}

void Othello::make_move(const std::string& move) {

}

void Othello::restart() {

}

main_savitch_14::game* Othello::clone() const {
    // TODO
    return new Othello();
}

void Othello::compute_moves(std::queue<std::string>& moves) const {

}

void Othello::display_status() const {
    for (size_t row = 0; row < NUM_ROWS; ++row) {
        for (size_t col = 0; col < NUM_COLS; ++col) {
            std::cout << board[row][col];
        }
        std::cout << '\n';
    }
}

int Othello::evaluate() const {
    // TODO
    return 0;
}

bool Othello::is_game_over() const {
    // TODO
    return false;
}

bool Othello::is_legal(const std::string& move) const {
    // TODO
    return false;
}