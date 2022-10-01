#version 120
#define MM_PI 3.1415926535897932384626433832795

varying vec2 fragTexCoord;
varying vec4 fragColor;
uniform float seed;
uniform float sun_seed;
uniform float waveHeight;
uniform float waveYStart;
uniform float u_time;

float grand(vec2 pos) {
    return smoothstep(0.488, 0.489, fract(
        mod( u_time, 1.0f ) + sin( dot( pos, vec2( 100.0f, 1.0f ) ) ) * 100000.0f
    ));
}

float map(float value, float min1, float max1, float min2, float max2)
{
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float calcDarkness(float y)
{
    float wave_ratio = waveHeight / 480.0f;
    float y_ratio = y / 480.0f;
    float y_to_wave = y_ratio / wave_ratio;

    float t = map(y_to_wave, 0.0f, 1.0f, -12.0f, 3.0f);
    float lo2 = 1.0f - (1 / (1+ pow(2.718281828459045f, t) ));
//    float lo3 = smoothstep(0.001f, 1.0f, lo2);

//    return lo3;
    return map(lo2, 0.0f, 1.0f, 0.4f, 1.0f);
}

vec4 addShine(float y, vec4 src_color)
{
    float rot_radius = 150.0f;
    float M_PI = 3.1415926535897932384626433832795;

    vec4 sun_pos = vec4(
        cos(sun_seed) * rot_radius + 320.0f, // + sin(seed * 1.5f) * 10.0f
        sin(sun_seed) * rot_radius + 240.0f,
        1.0f,
        1.0f
    );

    float vis = max(0.0f, sin(sun_seed));

    float wave_ratio = waveHeight / 480.0f;
    float y_ratio = y / 480.0f;
    float y_to_wave = y_ratio / wave_ratio;

    float dist = abs(gl_FragCoord.x - sun_pos.x);
    float shine_width = (rot_radius / 2 + pow(sin(seed),2) * 60) * (1.0f - map(y_to_wave, 0.0f, 1.0f, 0.0f, 0.35f));

    if (dist > shine_width) {
        return src_color;
    }

    float shine_strength = map( 1.0f - max(abs( dist/shine_width ), 0.25f), 0.0f, 1.0f, 0.0f, 0.15f); // 0.09f
    vec4 yello = vec4(1.0f, 1.0f, 1.0f, 1.0f);


    vec4 shiny_color = mix(src_color, yello, shine_strength * vis);
    return shiny_color;
}

vec4 calcFinalColor()
{
    float darkness = calcDarkness(gl_FragCoord.y - 0.5f);

    vec4 darken_color = vec4(darkness, darkness, darkness, gl_Color.w);

    vec4 darkened_color = gl_Color * darken_color;

    vec4 final = addShine(gl_FragCoord.y - 0.5f, darkened_color);

    vec2 res = vec2(640.0f, 480.0f);
    vec2 pos = gl_FragCoord.xy / res;
    float r_color = grand( pos );
    vec4 col = vec4(vec3(r_color), 1.0);

    return mix(final, col, 0.015);
    return final;
}


void main()
{
    //    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = calcFinalColor();
}