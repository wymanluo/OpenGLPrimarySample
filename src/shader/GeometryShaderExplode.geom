const char* geometry_shader_explode_gs = R"(

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
} gs_in[];

out vec2 TexCoords; 

uniform float normalScale;

vec4 explode(vec4 position, vec3 normal)
{
	vec3 direction = normal * normalScale; 
    return position + vec4(direction, 0.0);
	//return position;
}

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	
    return normalize(cross(a, b));
}

void main() {    
    vec3 normal = GetNormal();

	for (int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = explode(gl_in[i].gl_Position, normal);
		TexCoords = gs_in[i].texCoords;
		EmitVertex();
	}

    EndPrimitive();
}

)";