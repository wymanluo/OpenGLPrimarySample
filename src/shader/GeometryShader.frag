const char* geometry_shader_fs = R"(

#version 450 core
in vec3 fColor;
void main()
{
	gl_FragColor = vec4(fColor, 1.0); 
	//gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0); 
}

)";