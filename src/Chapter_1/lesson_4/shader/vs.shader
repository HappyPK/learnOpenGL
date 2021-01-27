#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor; // ��ɫ����������λ��ֵΪ 1
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor; // ��Ƭ����ɫ�����һ����ɫ
out vec3 ourPosition;
out vec2 TexCoord;

void main()
{
    ourColor = aColor;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourPosition = aPos;
    TexCoord = aTexCoord;
}