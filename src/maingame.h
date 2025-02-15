#ifndef MAINGAME_H
#define MAINGAME_H

#include <godot_cpp/classes/node.hpp>
#include "controllers/mastercontroller.h"

namespace godot {
    class MainGame : public Node {
        GDCLASS(MainGame, Node)

        private:
            bool inEditor = true;

        protected:
            static void _bind_methods();

        public:
            MainGame();
            ~MainGame();

            // void _process(double delta) override;
            //instiate singleton and global game logic
            void _ready() override;
        };
}

#endif