#include "player.h"

unsigned int Player::_count = 0;

Player::Player() : Entity(1,1), speed(0.0), still(true), dir(d), alive(true) {
	_count++;
}

Player::~Player() {
	--_count;
}

void Player::calcDirection(const bool(* const keys)[1024]) {
    //get direction player is currently going in
    Dir direction = (Dir)dir;

    Player::still = false;
 
    if ((*keys)[GLFW_KEY_W]) {
        direction = Dir::w;
        if ((*keys)[GLFW_KEY_A]) {
            direction = Dir::wa;
        }
        else if ((*keys)[GLFW_KEY_D]) {
            direction = Dir::wd;
        }
    }
    else if ((*keys)[GLFW_KEY_S]) {
        direction = Dir::s;
        if ((*keys)[GLFW_KEY_A]) {
            direction = Dir::sa;
        }
        else if ((*keys)[GLFW_KEY_D]) {
            direction = Dir::sd;
        }
    }
    else if ((*keys)[GLFW_KEY_A]) {
        direction = Dir::a;
    }
    else if ((*keys)[GLFW_KEY_D]) {
        direction = Dir::d;
    }
    else Player::still = true;

    dir = (unsigned int)direction;
}