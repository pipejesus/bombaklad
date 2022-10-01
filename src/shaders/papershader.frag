#version 120

uniform float u_time;

// y = smoothstep(0.499, 0.501, sin(x * 1901.488 + mod(u_time,10.0) ));

float map(float value, float min1, float max1, float min2, float max2)
{
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float grand(vec2 pos) {
    return smoothstep(0.488, 0.489, fract(
        mod( u_time, 1.0f ) + sin( dot( pos, vec2( 100.0f, 1.0f ) ) ) * 100000.0f
    ));
}

void main()
{
    vec2 res = vec2(640.0f, 480.0f);
    vec2 pos = gl_FragCoord.xy / res;
    float r_color = grand( pos );

    vec3 col = vec3(r_color);
    vec3 mixed = mix(gl_Color.xyz, col, 0.009f);

    gl_FragColor = vec4(mixed, 1.0f);
}