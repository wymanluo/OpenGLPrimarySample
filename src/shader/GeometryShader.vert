const char* geometry_shader_vs = R"(

#version 450 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 incolor;

out VS_OUT {
    vec3 color;
} out_color;

void main()
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	gl_PointSize = 3.5;
    out_color.color = incolor;
}
)";