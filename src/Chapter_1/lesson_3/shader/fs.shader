#version 460 core
out vec4 FragColor;

in vec3 ourColor;// ��OpenGL����������趨�������
in vec3 ourPosition;
void main()
{
    FragColor = vec4(ourColor, 1.0);
}