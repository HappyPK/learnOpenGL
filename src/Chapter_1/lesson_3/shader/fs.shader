#version 460 core
out vec4 FragColor;

in vec3 ourColor;// 在OpenGL程序代码中设定这个变量
in vec3 ourPosition;
void main()
{
    FragColor = vec4(ourColor, 1.0);
}