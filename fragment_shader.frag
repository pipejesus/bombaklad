#version 120

varying vec2 fragTexCoord;
varying vec4 fragColor;

void main()
{

//    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float opacity = 1.0 - ( 0.8f/ (480.0f /gl_FragCoord.y));
float red = 1.0f - ( 1.0f/ (290.0f /gl_FragCoord.y));
    float opacity2 =1.0f;
    vec4 p = vec4(sin(red), gl_Color.yz, opacity);

    // multiply it by the color
    gl_FragColor = p;
}