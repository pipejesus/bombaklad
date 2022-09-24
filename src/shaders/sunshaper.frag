#version 120

varying vec2 fragTexCoord;
varying vec4 fragColor;
uniform float seed;

float rand(float n){return fract(sin(n) * 43758.5453123);}

float noise(float p){
    float fl = floor(p);
    float fc = fract(p);

    return mix(rand(fl), rand(fl + 1.0), fc);
}

float map(float value, float min1, float max1, float min2, float max2)
{
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

vec4 calcFinalColor(vec4 color)
{
    float rot_radius = 150.0f;

    vec4 sun_pos = vec4(
      cos(seed) * rot_radius + 320.0f,
      sin(seed) * rot_radius + 240.0f,
      1.0f,
      1.0f
    );

    vec4 frag_dist_from_sun = sun_pos - gl_FragCoord;
    float dist = sqrt(pow(frag_dist_from_sun.x,2) + pow(frag_dist_from_sun.y,2));

    float brightness = max(0.37f, dist / rot_radius);
    vec4 white = vec4(brightness, brightness, brightness, 1.0f);

    if (dist < rot_radius) {
        return color * brightness;
    }

    return color;
}

void main()
{
    vec4 final_color = calcFinalColor(gl_Color);
    gl_FragColor = final_color;
}