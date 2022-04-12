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

        static const size_t NUM_COLS = 8;  // the number of columns on the board
        static const size_t NUM_ROWS = 8;  // the number of rows on the board

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
};

#endif