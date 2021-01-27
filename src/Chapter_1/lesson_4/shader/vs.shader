#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor; // 向片段着色器输出一个颜色
out vec3 ourPosition;
out vec2 TexCoord;

void main()
{
    ourColor = aColor;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourPosition = aPos;
    TexCoord = aTexCoord;
}