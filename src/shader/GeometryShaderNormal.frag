const char* geometry_shader_normal_fs = R"(

#version 450 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}

)";