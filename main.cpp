#include <SFML/Graphics.hpp>
#include "src/shapes/Wave.h"

#define SCR_W 800
#define SCR_H 600

sf::Shader shader;
sf::Shader shader2;
sf::Shader shader3;
sf::Shader sunshader;
sf::Shader papershader;

sf::RectangleShape bg;
float sun_angle = M_PI / 2;

sf::Vector2f scr_res = {SCR_W, SCR_H};

sf::Color GRAY {29, 31, 54, 225};
sf::Color GRAY1 {24, 26, 49, 225};
sf::Color GRAY2 {19, 21, 44, 225};
sf::Color WHITE {255, 255, 255, 225};

std::map<std::string,sf::Color> pal_sea1 {
        {"sea500", sf::Color{5, 102, 141, 255}},
        {"sea400", sf::Color{2, 128, 144, 255}},
        {"sea300", sf::Color{0, 168, 150, 255}},
        {"sea200", sf::Color{2, 195, 154, 255}},
        {"sea100", sf::Color{240, 243, 189, 255}}
};

struct Player {
    sf::Vector2f pos {SCR_W / 2, (float)SCR_H /2 };
    float angle {0.0f};
    sf::Vector2f accel {0.0f, 0.0f};
    sf::RectangleShape shape {sf::Vector2f{30.0f,30.0f}};
} player;

void loadShader()
{
    if ( !shader.loadFromFile(
            SHADERS_PATH"waveshaper.vert",
            SHADERS_PATH"waveshaper.frag") ) {
        std::cout << "ERROR LOADING SHADER" << std::endl;
    }

    if ( !shader2.loadFromFile(
            SHADERS_PATH"waveshaper.vert",
            SHADERS_PATH"waveshaper.frag") ) {
        std::cout << "ERROR LOADING SHADER 2" << std::endl;
    }

    if ( !shader3.loadFromFile(
            SHADERS_PATH"waveshaper.vert",
            SHADERS_PATH"waveshaper.frag") ) {
        std::cout << "ERROR LOADING SHADER 3" << std::endl;
    }

    if ( !sunshader.loadFromFile(
            SHADERS_PATH"waveshaper.vert",
            SHADERS_PATH"sunshaper.frag") ) {
        std::cout << "ERROR LOADING SUNSHAPER" << std::endl;
    }

    if ( !papershader.loadFromFile(
            SHADERS_PATH"waveshaper.vert",
            SHADERS_PATH"papershader.frag") ) {
        std::cout << "ERROR LOADING PAPERSHADER" << std::endl;
    }
}

void setupPlayer()
{
    player.shape.setFillColor(sf::Color{50,60,85, 205});
    player.shape.setPosition(player.pos);
    player.shape.setOrigin(player.shape.getLocalBounds().width / 2, player.shape.getLocalBounds().height / 2);
}

void updatePlayer(Wave &wave, sf::Time dt, sf::Time elapsed)
{
    player.pos.x += player.accel.x * dt.asSeconds() * 40;

    auto pos_and_rot = wave.GetPointPosAndRotation(player.pos);
    pos_and_rot.pos.y +=  sin(pos_and_rot.pos.x / 7) * 40 * dt.asSeconds();

    player.shape.setPosition(pos_and_rot.pos);
    player.shape.setRotation(pos_and_rot.rot);
}

int main()
{
    sf::Clock clock;
    sf::Clock clock2;

    sf::RenderWindow window(sf::VideoMode(SCR_W, SCR_H), "Shapes");
    window.setFramerateLimit(60);

    /**
     * debug inits
     */

    loadShader();
    sunshader.setUniform("seed", sun_angle );
    papershader.setUniform( "u_time", 0.0f );

    Wave wave1{
        8,
        sf::Vector2f{scr_res.x, 140.0f},
        35.0f,
        pal_sea1["sea500"],
        0.0f,
        sun_angle,
        shader,
        scr_res
    };

    wave1.setPosition(0.0f, scr_res.y - 140.0f);

    Wave wave2{
            8,
            sf::Vector2f{scr_res.x, 280.0f},
            65.0f,
            pal_sea1["sea500"],
            -1 * M_PI / 3,
            sun_angle,
            shader2,
            scr_res
    };

    wave2.setPosition(0.0f, scr_res.y - 280.0f);

    Wave wave3{
            8,
            sf::Vector2f{scr_res.x, 330.0f},
            20.0f,
            pal_sea1["sea500"],
            -1 * M_PI / 4,
            sun_angle,
            shader3,
            scr_res
    };

    wave3.setPosition(0.0f, scr_res.y - 330.0f);

    wave1.SetSunAngle(sun_angle);
    wave2.SetSunAngle(sun_angle);
    wave3.SetSunAngle(sun_angle);

    setupPlayer();

    bg.setFillColor(pal_sea1["sea500"]); // sf::Color{29, 31, 54, 255}
    bg.setSize(sf::Vector2f{SCR_W, SCR_H});

    /**
     * end debug inits
     */

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Time elapsed = clock2.getElapsedTime();



        sf::Event event{};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left )
                {
                    player.accel.x = -1;
                }
                if (event.key.code == sf::Keyboard::Right )
                {
                    player.accel.x = 1;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                    player.accel.x = 0;
            }
        }

        wave1.SetSunAngle(sun_angle);
        wave2.SetSunAngle(sun_angle);
        wave3.SetSunAngle(sun_angle);

        wave1.Update(dt, elapsed);
        wave2.Update(dt, elapsed);
        wave3.Update(dt, elapsed);

        updatePlayer(wave2, dt, elapsed);

        window.clear(sf::Color{255, 255, 255, 100});

        window.draw(bg, &sunshader);
        window.draw(wave3, &shader3);
        window.draw(wave2, &shader2);
        window.draw(wave1, &shader);

        papershader.setUniform("u_time", elapsed.asSeconds());

        window.draw(player.shape, &papershader);

        sun_angle -= (M_PI / 180.0f) * 20.0f * dt.asSeconds();
        sunshader.setUniform("seed", sun_angle);
        sunshader.setUniform("res", scr_res);

        window.display();
    }
}