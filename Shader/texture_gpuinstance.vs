#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
uniform mat4 transformMatrices[10];


void main()
{
	int instanceID = gl_InstanceID; // 获取当前实例的ID
    mat4 model = transformMatrices[instanceID]; // 获取当前实例的模型矩阵
    gl_Position =  model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}