#version 460 core
out vec4 FragColor;

in vec3 ourColor;// 在OpenGL程序代码中设定这个变量
in vec3 ourPosition;
in vec2 TexCoord;

uniform float mixValue;

uniform sampler2D ourTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
}