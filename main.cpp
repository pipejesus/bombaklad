#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "WaveFunctions.h"

#define SCR_W 640
#define SCR_H 480

std::vector<sf::Vector2<float>> points;

int segments_count = 8;
float step_size = 2 * M_PI / segments_count;
float S = 35;
float center_y = SCR_H / 2;

sf::RectangleShape bg;
sf::VertexArray wave;
sf::Color GRAY {29, 31, 54, 225};
sf::Shader shader;

struct Player {
    sf::Vector2f pos {SCR_W / 2, (float)SCR_H /2 };
    float angle {0.0f};
    sf::RectangleShape shape {sf::Vector2f{30.0f,30.0f}};
} player;

void setupPlayer() {
    player.shape.setFillColor(sf::Color{50,60,85, 255});
    player.shape.setPosition(player.pos);
    player.shape.setOrigin(player.shape.getLocalBounds().width / 2, player.shape.getLocalBounds().height / 2);
}

inline float RadToDeg(float Rad)
{
    return Rad / M_PI * 180.f;
}

inline float Dot(sf::Vector2f v1, sf::Vector2f v2) {
    return (v1.x * v2.x + v1.y *v2.y);
}

void updatePlayer(sf::Time t) {
    int segment_width = SCR_W / segments_count;
    int segment = (int)player.pos.x / segment_width;
    auto p1 = points[segment];
    auto p2 = points[segment+1];
    auto vec = p2 - p1;
    float angle = atan2(vec.y, vec.x);

    float A = p2.x - p1.x;
    float B = p2.y - p1.y;
    float Apri = player.pos.x - p1.x;
    float npm = B * Apri / A;
    sf::Vector2f pos {player.pos.x, npm + p1.y + (10.0f * tan(angle) * sin(angle) )};

    player.shape.setPosition(pos);
    player.shape.setRotation(RadToDeg(angle));
}

void drawPlayer(sf::RenderWindow &window) {
    window.draw(player.shape, &shader);
}

void createPoints() {
    int x = 0;

    for (float angle = 0.0f; angle < 2 * M_PI; angle+=step_size) {
        points.push_back(sf::Vector2<float>{
            (640.0f / segments_count) * x,
            sin(angle) * S + center_y
        });

        x++;
    }
}

void createShapes() {
    bg.setFillColor(sf::Color{29, 31, 54, 255});
    bg.setSize(sf::Vector2f{640.0f, 480.0f});

    wave = sf::VertexArray{sf::Triangles, (std::size_t)segments_count * 2 * 3 };
}

void updatePoints(float start_angle = 0.0f) {
    float pos_x = 0.0f;
    int i = 0;

    for (float angle = 0.0f; angle < 2.0f * M_PI; angle += step_size, i++) {
        if ( i > 0 ) {
            pos_x = (640.0f / (segments_count)) * i - 1.0f;
        }

        points[i].x = pos_x;
        points[i].y = WaveFn::PeacefulWave(angle + start_angle, S, center_y);
    }
}

void updateShapes() {
    int t = 0;

    for ( int i = 0; i<segments_count; i++ ) {
        wave[t].position = points[i];
        wave[t+1].position = points[i+1];
        wave[t+2].position = sf::Vector2f{points[i].x, 479.0f };

        wave[t+3].position = points[i+1];
        wave[t+4].position = sf::Vector2f{points[i+1].x, 479.0f };
        wave[t+5].position = sf::Vector2f{points[i].x, 479.0f };

        wave[t].color = GRAY;
        wave[t+1].color = GRAY;
        wave[t+2].color = GRAY;

        wave[t+3].color = GRAY;
        wave[t+4].color = GRAY;
        wave[t+5].color = GRAY;

        t+=6;
    }
}


void drawLines(sf::RenderWindow &window) {
    for (int i = 0; i < points.size() - 1; i++) {
        sf::Vertex line[] = {
                sf::Vertex(points[i]),
                sf::Vertex(points[i+1])
        };
        line->color = sf::Color{59, 61, 84, 55};
        window.draw(line, 2, sf::Lines);
    }
}

void drawW2(sf::RenderWindow &window) {
    window.draw(wave, &shader);
}

void drawShapes(sf::RenderWindow &window) {
    window.draw(bg);
    drawW2(window);
    drawPlayer(window);
    // drawLines(window);
}

int main()
{
    sf::Clock clock;
    createPoints();
    createShapes();
    setupPlayer();
    float angle = 0;

    sf::RenderWindow window(sf::VideoMode(SCR_W, SCR_H), "Shapes");
    window.setFramerateLimit(60);

    sf::ContextSettings settings = window.getSettings();

    std::cout << "depth bits:" << settings.depthBits << std::endl;
    std::cout << "stencil bits:" << settings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
    std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

    if ( !shader.loadFromFile(
            ASSETS_PATH"shaders/vertex_shader.vert",
            ASSETS_PATH"shaders/fragment_shader.frag") ) {
        std::cout << "ERROR LOADING SHADER" << std::endl;
    }

    shader.setUniform("seed", 0.0f);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                player.pos.x+=1.0f;
            }
        }

        shader.setUniform("seed", angle);

        updatePoints(angle);
        updateShapes();
        updatePlayer(clock.getElapsedTime());

        angle = angle + M_PI/(270);
        S+=0.05f;
        if (S> 90.0f) {S=25.0f;}

        window.clear(sf::Color{255, 255, 255, 100});
        drawShapes(window);
        window.display();
    }
}