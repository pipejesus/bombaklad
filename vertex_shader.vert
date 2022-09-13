#version 120


attribute vec2 vertexTexCoord;

void main()
{


    vec4 z = vec4(1.0f,1.0f - 1.0f / 290.0f / gl_Vertex.y,1.0f,1.0f);
    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex * z;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
}