//
// Created by User on 15/09/2022.
//

#ifndef BOMBAKLAD_WAVE_H
#define BOMBAKLAD_WAVE_H

#define WAVE_VERTICES_PER_SEGMENT 6

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>
#include <iostream>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../WaveFunctions.h"
#include "../Utils.h"

class Wave : public sf::Drawable, public sf::Transformable {

public:

    Wave(int segments_count, sf::Vector2f size, float amplitude, sf::Color flat_color, float init_angle, sf::Shader &shader);

    ~Wave() override;

    WaveFn::PosAndRot GetPointPosAndRotation(sf::Vector2f point);

    float GetAngle();

    void SetAmplitude(float new_amplitude);

    void SetSize(sf::Vector2f new_size);

    void SetColor(sf::Color new_color);

    void Update();

private:

    int segments_count;
    float amplitude;
    float step_size;
    float segment_width;
    float main_angle {0.0f};

    sf::Color flat_color;
    sf::VertexArray wave;
    std::vector<sf::Vector2f> points;
    sf::Vector2f size;
    sf::Shader &shader;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void initShape();

    void initPoints();

    void updateShape();

    void updateColor();

    void updatePoints();
};


#endif //BOMBAKLAD_WAVE_H
