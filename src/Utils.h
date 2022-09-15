//
// Created by User on 15/09/2022.
//

#ifndef BOMBAKLAD_UTILS_H
#define BOMBAKLAD_UTILS_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

namespace Utils {
    inline float RadToDeg(float Rad)
    {
        return (float)(Rad / M_PI * 180.f);
    }

    inline float Dot(sf::Vector2f v1, sf::Vector2f v2)
    {
        return (v1.x * v2.x + v1.y *v2.y);
    }

    inline void openglDebug(sf::RenderWindow window)
    {
        sf::ContextSettings settings = window.getSettings();

        std::cout << "depth bits:" << settings.depthBits << std::endl;
        std::cout << "stencil bits:" << settings.stencilBits << std::endl;
        std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
    }
}

#endif //BOMBAKLAD_UTILS_H
