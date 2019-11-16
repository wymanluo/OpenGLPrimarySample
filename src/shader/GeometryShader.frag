const char* shader_geometry_shader_frag = R"(

in vec4 color;
void main()
{
	//gl_FragColor = color;
	gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0); 
}

)";