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
    const std::string BOARD_COLOR = B_GREEN;
    const std::string FRAME_COLOR = WHITE;
    const std::string HUMAN_COLOR = BLACK;
    const std::string COMPUTER_COLOR = WHITE;


    // print each row
    for (size_t row = 0; row < NUM_ROWS; ++row) {
        // print horizontal bar
        std::cout << BOARD_COLOR << FRAME_COLOR;
        for (size_t col = 0; col < NUM_COLS; ++col) {
            std::cout << "+---";
        }
        // print final plus in the bar
        std::cout << '+' << RESET << '\n';

        // print each square in the row
        for (size_t col = 0; col < NUM_COLS; ++col) {
            // print left side of square
            std::cout << BOARD_COLOR << FRAME_COLOR;
            std::cout << "| ";

            // print disc
            switch (board[row][col]) {
                case main_savitch_14::game::HUMAN:
                    std::cout << HUMAN_COLOR << "\u25cf" << FRAME_COLOR << BOARD_COLOR;
                    break;
                case main_savitch_14::game::COMPUTER:
                    std::cout << COMPUTER_COLOR << "\u25cf" << FRAME_COLOR << BOARD_COLOR;
                    break;
                default:
                    std::cout << " ";
                    break;
            }
            
            // print right space
            std::cout << " ";
        }
        // print final barline for the row
        std::cout << '|' << RESET << '\n';
    }

    // print bottom horizontal bar
    std::cout << BOARD_COLOR << FRAME_COLOR;
    for (size_t col = 0; col < NUM_COLS; ++col) {
        std::cout << "+---";
    }
    // print final plus in the bar
    std::cout << '+' << RESET << '\n';
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