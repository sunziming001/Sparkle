#include "SSurfaceRender_OpenGL.h"
#include <map>
#include "glad/glad.h"
#include "SLogger.h"

struct SSurfaceData_OpenGL
{
	GLuint VBO=0;
	GLuint VAO=0;
};

struct SSurfaceRender_OpenGL::Data
{
	GLuint shaderProgram=0;
	std::map<SSurfacePtr, SSurfaceData_OpenGL> mapSurface2Data;
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

SSurfaceRender_OpenGL::SSurfaceRender_OpenGL()
	:SSurfaceRender()
	,d_(new Data())
{
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		SError("SSurfaceRender_OpenGL") << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		SError("SSurfaceRender_OpenGL") << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
	}
	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		SError("SSurfaceRender_OpenGL") << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog ;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	d_->shaderProgram = shaderProgram;
}

SSurfaceRender_OpenGL::~SSurfaceRender_OpenGL()
{
	glDeleteProgram(d_->shaderProgram);
	delete d_;
}

void SSurfaceRender_OpenGL::onAdd(SSurfacePtr surface)
{
	SByteArrayPtr byteArrPtr = nullptr;
	SSurfaceData_OpenGL surfaceData = { 0 };
	if (surface)
	{
		byteArrPtr = surface->toByteArrayPtr();

		float vertices[] = {
	   -0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
		};

		glGenVertexArrays(1, &surfaceData.VAO);
		glGenBuffers(1, &surfaceData.VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(surfaceData.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, surfaceData.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		d_->mapSurface2Data[surface] = surfaceData;
	}
	else {
		SError("SSurfaceRender_OpenGL") << SWS("Add Null surface");
	}
	
}

void SSurfaceRender_OpenGL::onRemove(SSurfacePtr surface)
{
	auto iter = d_->mapSurface2Data.find(surface);
	if (iter != d_->mapSurface2Data.end())
	{
		glDeleteVertexArrays(1, &(iter->second.VAO));
		glDeleteBuffers(1, &(iter->second.VBO));
		d_->mapSurface2Data.erase(iter);
	}
	
}

void SSurfaceRender_OpenGL::onBeforeRenderOnce()
{
	
}

void SSurfaceRender_OpenGL::onRenderSurface(SSurfacePtr surface)
{
	auto iter = d_->mapSurface2Data.find(surface);
	if (iter != d_->mapSurface2Data.end())
	{
		SSurfaceData_OpenGL& data = iter->second;
		glUseProgram(d_->shaderProgram);
		glBindVertexArray(data.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

	}

}

void SSurfaceRender_OpenGL::onAfterRenderOnce()
{
	//glUseProgram(0);
}
