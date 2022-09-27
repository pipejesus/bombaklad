//
// Created by Yogi on 26/09/2022.
//

#include "TheSun.h"

TheSun::TheSun(sf::Vector2f sky_size, sf::Vector2f sky_pos, float disc_scale):
    sky_size{sky_size},
    sky_pos{sky_pos},
    disc_scale{disc_scale}
{

}

TheSun::~TheSun() {

}

void TheSun::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.shader = &shader;

    target.draw(sky_box, states);
}
