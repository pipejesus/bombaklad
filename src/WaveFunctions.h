//
// Created by User on 13/09/2022.
//

#ifndef BOMBAKLAD_WAVEFUNCTIONS_H
#define BOMBAKLAD_WAVEFUNCTIONS_H


#include <cmath>

namespace WaveFn {

    struct PosAndRot {
        sf::Vector2f pos {};
        float rot {0.0f};
    };

    auto inline PeacefulWave = [](float angle, float amplitude) {
        return powf(sin((angle) / 2.0f ), 2) * amplitude;
    };
}

//                sin((angle + start_angle) / 2.0f ) * sin((angle + start_angle) / 2.0f ) * amplitude + center_y;
//        pos_y = sin((angle + start_angle) / 1.24f) * amplitude + center_y;
//        + center_y - ( cos(start_angle * 2.0f) * 15);


#endif //BOMBAKLAD_WAVEFUNCTIONS_H
