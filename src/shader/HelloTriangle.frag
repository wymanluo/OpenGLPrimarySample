const char* shader_hello_triangle_frag = R"(

in vec4 color;
out vec4 FragColor;
uniform vec4 uniformColor;
void main()
{
	gl_FragColor = color;
	// FragColor = outPosition;
}
)";