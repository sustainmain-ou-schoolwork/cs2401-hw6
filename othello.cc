#include "othello.h"

std::string stringToUpper(std::string input) {
    string output = "";
    for (size_t i = 0; i < input.length(); ++i) {
        output += toupper(input.at(i));
    }

    return output;
}

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

main_savitch_14::game::who Othello::winning() const {
    int value = evaluate();

    if (value > 0) {
        return main_savitch_14::game::COMPUTER;
    }
    else if (value < 0) {
        return main_savitch_14::game::HUMAN;
    }
    else {
        return main_savitch_14::game::NEUTRAL;
    }
}

void Othello::make_move(const std::string& move) {
    // place discs only if the move isn't a skip
    if (stringToUpper(move) != "SKIP") {
        int row = toRow(move);
        int col = toCol(move);

        // flip all the possible lines
        for (int rowChange = -1; rowChange <= 1; ++rowChange) {
            for (int colChange = -1; colChange <= 1; ++colChange) {
                // if the current line is flippable, return true
                size_t discCount = checkLine(row, col, rowChange, colChange);
                if (discCount > 0) {
                    flipLine(row, col, rowChange, colChange, discCount);
                }
            }
        }

        // set the disc indicated by the move
        board[row][col].setDisc(game::next_mover());
    }

    // increment move_number
    game::make_move(move);  
}

void Othello::restart() {
    Othello();        // clear board
    game::restart();  // set move_number to 0
}

Othello* Othello::clone() const {
    return new Othello(*this);
}

void Othello::compute_moves(std::queue<std::string>& moves) const {
    // add all the possible moves
    for (size_t row = 0; row < NUM_ROWS; ++row) {
        for (size_t col = 0; col < NUM_COLS; ++col) {
            if (checkLines(row, col)) {
                moves.push(to_string('A' + col) + to_string(row + 1));
            }
        }
    }

    // add skip if no moves are possible
    if (moves.empty()) {
        moves.push("SKIP");
    }
}

void Othello::display_status() const {
    // print score
    std::cout << "BLACK (P1): " << countDiscs(main_savitch_14::game::HUMAN) << '\n';
    std::cout << "WHITE (P2): " << countDiscs(main_savitch_14::game::COMPUTER) << '\n';

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
                    // display a dotted circle if the current square is a potential move
                    if (checkLines(row, col)) {
                        // select the right color for the dotted circle
                        if (next_mover() == main_savitch_14::game::HUMAN) {
                            std::cout << HUMAN_COLOR;
                        }
                        else {
                            std::cout << COMPUTER_COLOR;
                        }
                        std::cout << "\u25cc" << FRAME_COLOR << BOARD_COLOR;
                    }
                    else {
                        // display a space if the current square is not a potential move
                        std::cout << " ";
                    }
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
    return static_cast<int>(countDiscs(main_savitch_14::game::COMPUTER) - countDiscs(main_savitch_14::game::HUMAN));
}

bool Othello::is_game_over() const {
    // check if the current player can move
    if (nextPlayerCanMove()) {
        return false;
    }

    // check if the player after that can move
    Othello* tmp = clone();
    tmp -> make_move("SKIP");
    if (tmp -> nextPlayerCanMove()) {
        return false;
    }

    // if no valid moves were found for either player, return true
    return true;
}

bool Othello::is_legal(const std::string& move) const {
    if (stringToUpper(move) == "SKIP") {
        // check if any moves are possible
        return !nextPlayerCanMove();
    }
    else {
        int row = toRow(move);
        int col = toCol(move);

        // check if any lines are flippable from the disc position
        return checkLines(row, col);
    }
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

size_t Othello::checkLine(size_t row, size_t col, int rowChange, int colChange) const {
    // start with 0 discs flippable; add them later
    size_t count = 0;
    
    // set default bounds
    size_t originalRowMin = 0;
    size_t originalRowMax = NUM_ROWS - 1;
    size_t originalColMin = 0;
    size_t originalColMax = NUM_COLS - 1;
    size_t rowMin = originalRowMin;
    size_t rowMax = originalRowMax;
    size_t colMin = originalColMin;
    size_t colMax = originalColMax;

    switch (rowChange) {
        case -1:
            rowMin += 2;
            break;
        case 1:
            rowMax -= 2;
            break;
    }

    switch (colChange) {
        case -1:
            colMin += 2;
            break;
        case 1:
            colMax -= 2;
            break;
    }

    // if the move is outside of the board, return 0
    if (row < rowMin || row > rowMax || col < colMin || col > colMax) {
        return 0;
    }

    // if the square is already occupied, return 0
    if (board[row][col].getDisc() != main_savitch_14::game::NEUTRAL) {
        return 0;
    }

    // if neither the row nor the column will change as the function runs along the line 
    if (rowChange == 0 && colChange == 0) {
        return 0;
    }

    // if the next disc is the opposite player
    if (board[row + rowChange][col + colChange].getDisc() == last_mover()) {
        count = 1;  // the first disc can be flipped
        // check the rest of discs along the line
        int r = row + (rowChange * 2);
        int c = col + (colChange * 2);
        while (r >= static_cast<int>(originalRowMin) && r <= static_cast<int>(originalRowMax) && c >= static_cast<int>(originalColMin) && c <= static_cast<int>(originalColMax)) {
            if (board[r][c].getDisc() == last_mover()) {
                // if the current disc is the same player, increase the count and continue along the line
                count++;
            }
            else if (board[r][c].getDisc() == next_mover()) {
                // if the line is capped by the current player, it can be flipped
                return count;
            }
            else if (board[r][c].getDisc() == game::NEUTRAL) {
                // if the line is capped by an empty square, it cannot be flipped
                return 0;
            }

            c += colChange;
            r += rowChange;
        }
    }

    // if a valid line wasn't found, return 0
    return 0;
}

bool Othello::checkLines(size_t row, size_t col) const {
    for (int rowChange = -1; rowChange <= 1; ++rowChange) {
        for (int colChange = -1; colChange <= 1; ++colChange) {
            // if the current line is flippable, return true
            if (checkLine(row, col, rowChange, colChange) > 0) {
                return true;
            }
        }
    }

    // if no lines were flippable, return false
    return false;
}

void Othello::flipLine(size_t row, size_t col, int rowChange, int colChange, size_t count) {
    size_t r = row + rowChange;
    size_t c = col + colChange;

    for (size_t i = 0; i < count; ++i) {
        board[r][c] = next_mover();

        c += colChange;
        r += rowChange;
    }
}

size_t Othello::countDiscs(main_savitch_14::game::who player) const {
    size_t count = 0;

    for (size_t row = 0; row < NUM_ROWS; ++row) {
        for (size_t col = 0; col < NUM_COLS; ++col) {
            if(board[row][col].getDisc() == player) {
                count++;
            }
        }
    }

    return count;
}

bool Othello::nextPlayerCanMove() const {
    std::queue<std::string> moves;
    compute_moves(moves);
    if (moves.front() == "SKIP") {
        return false;
    }
    else {
        return true;
    }
}