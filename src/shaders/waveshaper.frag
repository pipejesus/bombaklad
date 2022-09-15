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

float calcDarkness(float y, float h) {
//    if ( y >= (waveYStart) ) {
//        return 1.0f;
//    } else {
        return ( (y) / h) * max(0.8f, sin(seed)*sin(seed)); // * (y / h);// * (y / h);
//    }
}

vec4 calcFinalColor(vec4 color, float darkness) {
    return vec4(color.x * darkness, color.y * darkness, color.z * darkness, color.w);
}

vec4 randomColor() {
    float hash = noise(seed);
    hash = gl_FragCoord.x - seed;
    return vec4( hash, hash, hash, 1.0f);
}



void main()
{
    float darkness = calcDarkness(gl_FragCoord.y - 0.5f, waveHeight);
    float opacity = 1.0f;
    //    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    //    float opacity =  ( 1.0f/ (270.0f /gl_FragCoord.y));
    //    float red = 1.0f - ( 1.0f/ (290.0f /gl_FragCoord.y));
    //    float opacity2 = 1.0f;
    vec4 p = vec4(gl_Color.xyz, opacity);
    vec4 final_color = calcFinalColor(p, darkness);
    gl_FragColor = final_color;
}