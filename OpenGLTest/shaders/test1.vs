#version 460 core

precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aTangent;
layout (location = 5) in vec3 aBitangent;
layout (location = 6) in vec4 aBoneID;
layout (location = 7) in vec4 aWeights;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform vec3 uniColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.);
    //ourColor = aColor * uniColor.yzx;
    ourColor = aColor;
    TexCoord = aTexCoord;
    FragPos = vec3(model * vec4(aPos, 1.));
    Normal = mat3(transpose(inverse(model))) * aNormal;
}