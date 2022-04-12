#ifndef SPACE_H
#define SPACE_H

#include "game.h"

class Space {
    public:
        /**
         * @brief Construct a new Space object.
         * 
         * @param pDisc the value of disc in the space
         */
        Space(main_savitch_14::game::who pDisc = main_savitch_14::game::NEUTRAL) {disc = pDisc;}

        /**
         * @return the value of the disc in the Space
         */
        main_savitch_14::game::who getDisc() const {return disc;}

        /**
         * @brief Set the value of disc.
         * 
         * @param pDisc the new value to set disc to
         */
        void setDisc(main_savitch_14::game::who pDisc) {disc = pDisc;}

    private:
        main_savitch_14::game::who disc;  // the value of the disc in the space
};

#endif