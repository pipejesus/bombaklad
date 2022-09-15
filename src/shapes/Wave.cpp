//
// Created by User on 15/09/2022.
//

#include "Wave.h"

Wave::Wave(int segments_count, sf::Vector2f size, float amplitude, sf::Color flat_color, float init_angle, sf::Shader &shader):

segments_count{segments_count},
size{size},
amplitude{amplitude},
flat_color{flat_color},
main_angle{init_angle},
shader{shader}

{
    step_size = (float)(M_PI * 2 / segments_count);
    segment_width = size.x / (float)segments_count;
    shader.setUniform("seed", main_angle);

    Wave::initPoints();
    Wave::initShape();
    Wave::updateShape();
    Wave::updateColor();
}

Wave::~Wave() {

}

void Wave::initShape()
{
    wave = sf::VertexArray{sf::Triangles, (std::size_t)segments_count * WAVE_VERTICES_PER_SEGMENT };
}

void Wave::initPoints()
{
    int i = 0;

    for (float angle = 0.0f; angle < 2 * M_PI; angle+=step_size)
    {
        points.emplace_back(sf::Vector2f{
                segment_width * (float)i,
                WaveFn::PeacefulWave(angle, amplitude)
        });

        i++;
    }
}

void Wave::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(wave, states);
}

void Wave::SetAmplitude(float new_amplitude)
{
    amplitude = new_amplitude;
}

void Wave::SetSize(sf::Vector2f new_size)
{
    size = new_size;
}

void Wave::SetColor(sf::Color new_color)
{
    flat_color = new_color;
}

void Wave::updatePoints() {
    float pos_x = 0.0f;
    int i = 0;

    for (float angle = 0.0f; angle < 2 * M_PI; angle += step_size, i++)
    {
        if ( i > 0 )
        {
            pos_x = (size.x / (float)segments_count) * (float)i;
        }

        points[i].x = pos_x;
        points[i].y = WaveFn::PeacefulWave(angle + main_angle, amplitude);
    }
}

void Wave::updateColor() {
    int t = 0;

    for (int i = 0; i < segments_count; i++)
    {
        wave[t].color = flat_color;
        wave[t + 1].color = flat_color;
        wave[t + 2].color = flat_color;

        wave[t + 3].color = flat_color;
        wave[t + 4].color = flat_color;
        wave[t + 5].color = flat_color;

        t += WAVE_VERTICES_PER_SEGMENT;
    }
}

void Wave::updateShape() {
    int t = 0;
    float bottom_y = size.y;

    for (int i = 0; i < segments_count; i++)
    {
        wave[t].position = points[i];
        wave[t + 1].position = points[i + 1];
        wave[t + 2].position = {points[i].x, bottom_y};

        wave[t + 3].position = points[i + 1];
        wave[t + 4].position = {points[i + 1].x, bottom_y};
        wave[t + 5].position = {points[i].x, bottom_y};

        t += WAVE_VERTICES_PER_SEGMENT;
    }
}

void Wave::Update()
{
    auto current_wave_pos = getPosition();
    main_angle += M_PI / 270.0f;

    shader.setUniform("seed", main_angle);
    shader.setUniform("waveHeight", size.y);
    shader.setUniform("waveYStart", 480.0f - current_wave_pos.y);

    std::cout << "W height: " << size.y << " W start: " << 480.0f - current_wave_pos.y << std::endl;

    updatePoints();
    updateShape();
}

WaveFn::PosAndRot Wave::GetPointPosAndRotation(sf::Vector2f point) {
    int in_segment = (int)(point.x / segment_width);
    auto p1 = points[in_segment];
    auto p2 = points[in_segment+1];
    auto vec = p2 - p1;
    float rotation = atan2(vec.y, vec.x);

    float A = p2.x - p1.x;
    float B = p2.y - p1.y;
    float Apri = point.x - p1.x;
    float npm = B * Apri / A;

    auto current_wave_pos = getPosition();
    return WaveFn::PosAndRot{{ point.x, npm + current_wave_pos.y + p1.y }, Utils::RadToDeg(rotation) };
}

float Wave::GetAngle() {
    return main_angle;
}
