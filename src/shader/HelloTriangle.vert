const char* shader_hello_triangle_vert = R"(

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 incolor;
out vec4 color;
void main()
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    color = vec4(incolor, 1.0f);
}
)";