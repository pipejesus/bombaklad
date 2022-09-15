#version 120

varying vec2 fragTexCoord;
varying vec4 fragColor;
uniform float seed;
uniform float waveHeight;
uniform float waveYStart;

float rand(float n){return fract(sin(n) * 43758.5453123);}

float noise(float p){
    float fl = floor(p);
    float fc = fract(p);

    return mix(rand(fl), rand(fl + 1.0), fc);
}

float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float calcDarkness(float y) {
    float wave_ratio = waveHeight / 480.0f;
    float y_ratio = y / 480.0f;
    float y_to_wave = y_ratio / wave_ratio;

    float t = map(y_to_wave, 0.0f, 1.0f, -12.0f, 3.0f);
    float lo2 = 1.0f - (1 / (1+ pow(2.718281828459045f, t) ));
    return map(lo2, 0.0f, 1.0f, 0.4f, 1.0f);
}

vec4 calcFinalColor(vec4 color, float darkness) {
    vec4 darken = vec4(darkness, darkness, darkness, color.w);
    return color * darken;
}

vec4 randomColor() {
    float hash = noise(seed);
    hash = gl_FragCoord.x - seed;
    return vec4( hash, hash, hash, 1.0f);
}



void main()
{
    float darkness = calcDarkness(gl_FragCoord.y - 0.5f);
    float opacity = 1.0f;
    //    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    //    float opacity =  ( 1.0f/ (270.0f /gl_FragCoord.y));
    //    float red = 1.0f - ( 1.0f/ (290.0f /gl_FragCoord.y));
    //    float opacity2 = 1.0f;
    vec4 p = vec4(gl_Color.xyz, opacity);
    vec4 final_color = calcFinalColor(p, darkness);
    gl_FragColor = final_color;
}