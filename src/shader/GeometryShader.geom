const char* shader_geometry_shader_geom = R"(
#version 450 core

layout (triangles) in;
//layout (points) in;
layout (triangle_strip, max_vertices = 15) out;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 incolor;
out vec4 color;

void build_house_by_point(vec4 position)
{    
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:左下
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:右下
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:左上
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:右上
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:顶部
    EmitVertex();
    EndPrimitive();
}

void build_house_by_triangle()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		build_house_by_point(gl_in[i].gl_Position);
	}
}

void main()
{
	build_house_by_triangle();
	color = vec4(incolor, 1.0f);
}

)";