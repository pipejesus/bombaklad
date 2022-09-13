//
// Created by User on 13/09/2022.
//

#ifndef BOMBAKLAD_WAVEFUNCTIONS_H
#define BOMBAKLAD_WAVEFUNCTIONS_H

#include <cmath>

namespace WaveFn {

    auto PeacefulWave = [](float angle, float scale, float center_y) {
        return sin((angle) / 2.0f ) * sin((angle) / 2.0f ) * scale + center_y;
    };
}

//                sin((angle + start_angle) / 2.0f ) * sin((angle + start_angle) / 2.0f ) * S + center_y;
//        pos_y = sin((angle + start_angle) / 1.24f) * S + center_y;
//        + center_y - ( cos(start_angle * 2.0f) * 15);


#endif //BOMBAKLAD_WAVEFUNCTIONS_H
