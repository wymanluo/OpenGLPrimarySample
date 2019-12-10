const char* geometry_shader_gs = R"(
#version 450 core

layout (points) in;
layout (line_strip, max_vertices = 12) out;

//layout (triangles) in;
//layout (triangle_strip, max_vertices = 15) out;

in VS_OUT {
    vec3 color;
} in_color[];

out vec3 fColor;

void create_triangle_by_point(vec4 position)
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

// 生成三角形条带
void create_triangle_strip()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		fColor = in_color[i].color;
		create_triangle_by_point(gl_in[i].gl_Position);
	}
}

// 什么都不做
void create_nothing()
{
}

// 由点生成多边形
void create_primitive_by_points()
{
	fColor = in_color[0].color;
	const float PI = 3.1415926;

    for (int i = 0; i < 12; i++) 
	{
       // Angle between each side in radians
        float ang = PI * 2.0 / 10.0 * i;

        // Offset from center of point (0.3 to accomodate for aspect ratio)
        vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.4, 0.0, 0.0);
        gl_Position = gl_in[0].gl_Position + offset;

        EmitVertex();
	}

    EndPrimitive();
}

// 生成原图形
void create_original_primitive()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		fColor = in_color[i].color;
		EmitVertex();
	}
	EndPrimitive();
}

void main()
{
	create_nothing();
	//create_original_primitive();
	create_primitive_by_points();
	//create_triangle_strip();
}

)";