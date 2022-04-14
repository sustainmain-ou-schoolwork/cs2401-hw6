#include "othello.h"

Othello::Othello() {
    // clear the board
    for (size_t row = 0; row < NUM_ROWS; ++row) {
        for (size_t col = 0; col < NUM_COLS; ++col) {
            board[row][col] = Space();
        }
    }


    // get the left and top index of the middle square
    size_t left = (NUM_COLS / 2) - 1;  // index of left column in the square
    size_t top = (NUM_ROWS / 2) - 1;   // index of top row in the square

    // set the computer's discs in the square
    board[top][left].setDisc(main_savitch_14::game::COMPUTER);
    board[top + 1][left + 1].setDisc(main_savitch_14::game::COMPUTER);

    // set the human's discs in the square
    board[top + 1][left].setDisc(main_savitch_14::game::HUMAN);
    board[top][left + 1].setDisc(main_savitch_14::game::HUMAN);
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
    // print top border
    std::cout << BORDER_COLOR << LABEL_COLOR;
    std::cout << "    ";
    for (size_t col = 0; col < NUM_COLS; ++col) {
        std::cout << " " + string({(char)('A' + col)}) + "  ";
    }
    std::cout << "   " + RESET + "\n";

    for (size_t row = 0; row < NUM_ROWS; ++row) {
        // print the bar above the row
        if (row == 0) {
            printBar(0);
        }
        else {
            printBar(1);
        }

        // print left border
        std::cout << BORDER_COLOR << LABEL_COLOR;
        std::cout << " " + to_string(row + 1) + " ";
        std::cout << RESET;

        // print each square in the row
        std::cout << BOARD_COLOR << FRAME_COLOR;
        for (size_t col = 0; col < NUM_COLS; ++col) {
            // print left side of square
            std::cout << VERTICAL << " ";

            // print disc
            switch (board[row][col].getDisc()) {
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
        std::cout << VERTICAL;
        
        // print right border
        std::cout << BORDER_COLOR << LABEL_COLOR << "   " << RESET << '\n';
    }

    // print bottom bar
    printBar(2);

    // print bottom border
    std::cout << BORDER_COLOR << LABEL_COLOR;
    std::cout << "    ";
    for (size_t col = 0; col < NUM_COLS; ++col) {
        std::cout << "    ";
    }
    std::cout << "   " + RESET + "\n";
}

void Othello::printBar(int barType) const {
    // print left border
    std::cout << BORDER_COLOR << LABEL_COLOR << "   ";

    // setup the colors
    std::cout << BOARD_COLOR << FRAME_COLOR;

    // print the bar
    switch (barType) {
        case 0:
            // print top bar
            std::cout << TOP_LEFT << HORIZONTAL << HORIZONTAL << HORIZONTAL;
            for (size_t col = 1; col < NUM_COLS; ++col) {
                std::cout << HORIZONTAL_DOWN << HORIZONTAL << HORIZONTAL << HORIZONTAL;
            }
            std::cout << TOP_RIGHT;
            break;
        case 1:
            // print middle bar
            std::cout << VERTICAL_LEFT << HORIZONTAL << HORIZONTAL << HORIZONTAL;
            for (size_t col = 1; col < NUM_COLS; ++col) {
                std::cout << HORIZONTAL_AND_VERTICAL << HORIZONTAL << HORIZONTAL << HORIZONTAL;
            }
            std::cout << VERTICAL_RIGHT;
            break;
        default:
            // print bottom bar
            std::cout << BOTTOM_LEFT << HORIZONTAL << HORIZONTAL << HORIZONTAL;
            for (size_t col = 1; col < NUM_COLS; ++col) {
                std::cout << HORIZONTAL_UP << HORIZONTAL << HORIZONTAL << HORIZONTAL;
            }
            std::cout << BOTTOM_RIGHT;
    }

    // print right border
    std::cout << BORDER_COLOR << LABEL_COLOR << "   " << RESET << '\n';
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