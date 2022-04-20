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
    // TODO
    int row = toRow(move);
    int col = toCol(move);

    // set the disc indicated by the move
    board[row][col].setDisc(game::next_mover());

    // flip the other disc
    if (col > 3) {
        board[4][4].setDisc(game::next_mover());
    }
    else {
        board[3][3].setDisc(game::next_mover());
    }

    game::make_move(move);  // increment move_number
}

void Othello::restart() {
    Othello();        // clear board
    game::restart();  // set move_number to 0
}

main_savitch_14::game* Othello::clone() const {
    // TODO
    return new Othello();
}

void Othello::compute_moves(std::queue<std::string>& moves) const {
    // TODO
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
    int row = toRow(move);
    int col = toCol(move);

    // check if each line is flippable
    for (int rowChange = -1; rowChange <= 1; rowChange++) {
        for (int colChange = -1; colChange <= 1; colChange++) {
            // if the current line is flippable, return true
            if (checkLine(row, col, rowChange, colChange)) {
                return true;
            }
        }
    }

    // if none of the lines were flippable, return false
    return false;
}

int Othello::toCol(const std::string& move) const {
    int col = -1;

    if (move.length() > 0) {
        col = toupper(move[0]) - 'A';
    }

    return col;
}

int Othello::toRow(const std::string& move) const {
    int row = -1;

    if (move.length() > 1) {
        try {
            row = stoi(move.substr(1, (move.length() - 1))) - 1;
        }
        catch (const std::invalid_argument& ia) {
        }
    }

    return row;
}

bool Othello::checkLine(size_t row, size_t col, int rowChange, int colChange) const {
    // set default bounds
    size_t rowMin = 0;
    size_t rowMax = static_cast<int>(NUM_ROWS) - 1;
    size_t colMin = 0;
    size_t colMax = static_cast<int>(NUM_COLS) - 1;

    switch (rowChange) {
        case -1:
            rowMin = 2;
            break;
        case 1:
            rowMax = rowMax - 2;
            break;
    }

    switch (colChange) {
        case -1:
            colMin = 2;
            break;
        case 1:
            colMax = colMax - 2;
            break;
    }

    // make sure the move is in the board
    if (row < rowMin || row > rowMax || col < colMin || col > colMax) {
        return false;
    }

    // make sure the row or column will change as the function checks along the line
    if (rowChange == 0 && colChange == 0) {
        return false;
    }

    // if the next disc is the opposite player
    if (board[row + rowChange][col + colChange].getDisc() == last_mover()) {
        // check the rest of discs along the line
        size_t r = row + (rowChange * 2);
        size_t c = col + (colChange * 2);
        while (r > rowMin && r < rowMax && c > colMin && c < colMax) {
            if (board[r][c].getDisc() == next_mover()) {
                // if the line is capped by the current player, it can be flipped
                return true;
            }
            else if (board[r][c].getDisc() == game::NEUTRAL) {
                // if the line is capped by an empty square, it cannot be flipped
                return false;
            }

            c += colChange;
            r += rowChange;
        }
    }

    // if a valid line wasn't found, return false
    return false;
}