//
// Created by Yogi on 26/09/2022.
//

#ifndef BOMBAKLAD_THESUN_H
#define BOMBAKLAD_THESUN_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>

class TheSun : public sf::Drawable, public sf::Transformable {
public:
    TheSun(sf::Vector2f sky_size, sf::Vector2f sky_pos, float disc_scale);
    ~TheSun();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f sky_size;
    sf::Vector2f sky_pos;
    float disc_scale;
    sf::RectangleShape sky_box;
    sf::Shader shader;
};


#endif //BOMBAKLAD_THESUN_H
