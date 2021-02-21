#version 460 core
out vec4 FragColor;

//uniform vec3 objectColor;
//uniform vec3 lightColor;

in vec2 TexCoord;
// texture sampler
uniform sampler2D texture1;
void main()
{
    //FragColor = vec4(lightColor * objectColor, 1.0);
    FragColor = texture(texture1, TexCoord);
}