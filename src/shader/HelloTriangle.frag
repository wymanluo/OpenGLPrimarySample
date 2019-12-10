const char* hello_triangle_fs = R"(

in vec4 color;
out vec4 FragColor;
uniform vec4 uniformColor;
void main()
{
	gl_FragColor = color;
	//gl_FragColor = uniformColor;
}

)";