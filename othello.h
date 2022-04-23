#ifndef OTHELLO_H
#define OTHELLO_H

#include <iostream>
#include "game.h"
#include "space.h"
#include "colors.h"


class Othello:public main_savitch_14::game {
    public:
        /**
         * @brief Construct a new Othello object.
         */
        Othello();

        static const size_t NUM_ROWS = 8;  // the number of rows on the board
        static const size_t NUM_COLS = 8;  // the number of columns on the board

        /**
         * @brief Make a move for the current player.
         * 
         * @param move the string with the column and row to make a move on
         */
        void make_move(const std::string& move);

        /**
         * @brief Restart the game from the beginning.
         */
		void restart();

		/**
		 * @return a pointer to a clone of the Othello object
		 */
		main_savitch_14::game* clone() const;

        /**
         * @brief Compute all the moves that the next player can make.
         * 
         * @param moves the queue of strings to be filled with possible moves
         */
		void compute_moves(std::queue<std::string>& moves) const;

        /**
         * @brief Show the board.
         */
		void display_status() const;

        /**
         * @brief Evaluate a board position (positive values are good for the computer).
         * 
         * @return the score of a position
         */
		int evaluate() const;

        /**
         * @return true if the game is over
         */
		bool is_game_over() const;
        
        /**
         * @param move a move whose legality must be checked
         * @return true if the given move is legal for the next player
         */
		bool is_legal(const std::string& move) const;

    private:
        Space board[NUM_ROWS][NUM_COLS];  // the board used to play the game

        const std::string BOARD_COLOR = B_GREEN;   // background color of the board
        const std::string BORDER_COLOR = B_WHITE;  // background color of the frame around the board
        const std::string FRAME_COLOR = WHITE;     // color of the board's frame
        const std::string LABEL_COLOR = BLACK;     // color of the board's labels
        const std::string HUMAN_COLOR = BLACK;     // color of the human's discs
        const std::string COMPUTER_COLOR = WHITE;  // color of the computer's discs

        const std::string HORIZONTAL = "\u2500";               // char for horizontal line
        const std::string VERTICAL = "\u2502";                 // char for vertical line
        const std::string TOP_LEFT = "\u250c";                 // char for top left corner
        const std::string TOP_RIGHT = "\u2510";                // char for top right corner
        const std::string BOTTOM_LEFT = "\u2514";              // char for bottom left corner
        const std::string BOTTOM_RIGHT = "\u2518";             // char for bottom right corner
        const std::string VERTICAL_LEFT = "\u251c";            // char for vertical line with horizontal line on right half
        const std::string VERTICAL_RIGHT = "\u2524";           // char for vertical line with horizontal line on left half
        const std::string HORIZONTAL_DOWN = "\u252c";          // char for horizontal line with vertical line on bottom half
        const std::string HORIZONTAL_UP = "\u2534";            // char for horizontal line with vertical line on top half
        const std::string HORIZONTAL_AND_VERTICAL = "\u253c";  // char for horizontal line with vertical line

        /**
         * @brief Print a bar in the frame of the board.
         * 
         * @param barType the type of bar to print (0 prints the top bar, 1 prints a middle bar, anything else prints a bottom bar)
         */
        void printBar(int barType) const;

        /**
         * @brief Determine what the row index should be based on the move string provided (defaults to -1).
         * 
         * @param move the move string
         * @return the index of the row indicated by the move string
         */
        int toRow(const std::string& move) const;

        /**
         * @brief Determine what the column index should be based on the move string provided (defaults to -1).
         * 
         * @param move the move string
         * @return the index of the column indicated by the move string
         */
        int toCol(const std::string& move) const;

        /**
         * @brief Return the number of discs that can be flipped in a line.
         * 
         * @param row the row of the disc
         * @param col the column of the disc
         * @param rowChange the direction that the rows change going along the line
         * @param colChange the direction that the columns change going along the line
         * @return the number of discs that can be flipped in that line
         */
        size_t checkLine(size_t row, size_t col, int rowChange, int colChange) const;

        /**
         * @brief Check if any of the lines coming from a given square are flippable.
         * 
         * @param row the row of the disc
         * @param col the column of the disc
         * @return true if any of the lines can be flipped
         */
        bool checkLines(size_t row, size_t col) const;

        /**
         * @brief Flip a line of discs to the current player.
         * 
         * @param row the row of the starting disc
         * @param col the column of the starting disc
         * @param rowChange the direction that the rows change going along the line
         * @param colChange the direction that the columns change going along the line
         * @param count the number of discs that can be flipped in that line
         */
        void flipLine(size_t row, size_t col, int rowChange, int colChange, size_t count);
};

#endif