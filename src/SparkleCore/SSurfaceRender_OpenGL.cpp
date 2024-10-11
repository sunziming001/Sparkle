#include "SSurfaceRender_OpenGL.h"
#include <map>
#include "glad/glad.h"
#include "SLogger.h"
#include "SpkFileHelper.h"

struct SSurfaceData_OpenGL
{
	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint EBO = 0;
	GLuint texture = 0;
};

struct SSurfaceRender_OpenGL::Data
{
	GLuint shaderProgram=0;
	std::map<SSurfacePtr, SSurfaceData_OpenGL> mapSurface2Data;
	SByteArray vertexShaderSource;
	SByteArray fragmentShaderSource;
};


SSurfaceRender_OpenGL::SSurfaceRender_OpenGL()
	:SSurfaceRender()
	,d_(new Data())
{
	d_->vertexShaderSource = SpkFileHelper::getInstance()->getRes(SWS("core\\opengl\\shader\\common.vs"));
	d_->fragmentShaderSource = SpkFileHelper::getInstance()->getRes(SWS("core\\opengl\\shader\\common.fs"));
	
	initShader();
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
		byteArrPtr = surface->getVertexData();

		glGenVertexArrays(1, &surfaceData.VAO);
		glGenBuffers(1, &surfaceData.VBO);

		glGenBuffers(1, &surfaceData.EBO);

		glGenTextures(1, &surfaceData.texture);


		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(surfaceData.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, surfaceData.VBO);
		glBufferData(GL_ARRAY_BUFFER, byteArrPtr->size(), byteArrPtr->data(), GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surfaceData.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, surface->getVertexDrawOrderSize(), surface->getVertexDrawOrder(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		//texture
		glBindTexture(GL_TEXTURE_2D, surfaceData.texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (surface->getTextureChannels() == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 
				0, 
				GL_RGB, 
				surface->getTextureWidth(), 
				surface->getTextureHeight(),
				0, 
				GL_RGB, 
				GL_UNSIGNED_BYTE, 
				surface->getTextureData());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (surface->getTextureChannels() == 4)
		{
			glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RGBA,
				surface->getTextureWidth(),
				surface->getTextureHeight(),
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				surface->getTextureData());
			glGenerateMipmap(GL_TEXTURE_2D);
		}


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
		glDeleteBuffers(1, &(iter->second.EBO));
		glDeleteTextures(1, &(iter->second.texture));


		d_->mapSurface2Data.erase(iter);
	}
	
}

void SSurfaceRender_OpenGL::onBeforeRenderOnce()
{
	glUseProgram(d_->shaderProgram);
}

void SSurfaceRender_OpenGL::onRenderSurface(SSurfacePtr surface)
{
	auto iter = d_->mapSurface2Data.find(surface);
	if (iter != d_->mapSurface2Data.end())
	{
		size_t drawOrderCnt = surface->getVertexDrawOrderCnt();
		SSurfaceData_OpenGL& data = iter->second;
		glBindTexture(GL_TEXTURE_2D, data.texture);
		glBindVertexArray(data.VAO);
		//glDrawArrays(GL_TRIANGLES, 0, surface->getVertexCnt());
		glDrawElements(GL_TRIANGLES, drawOrderCnt, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

}

void SSurfaceRender_OpenGL::onAfterRenderOnce()
{
	glUseProgram(0);
}

void SSurfaceRender_OpenGL::initShader()
{

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	char* vertexShaderSource = (char*)calloc(1, d_->vertexShaderSource.size() + 1);
	memcpy(vertexShaderSource, d_->vertexShaderSource.data(), d_->vertexShaderSource.size());
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
	char* fragmentShaderSource = (char*)calloc(1, d_->fragmentShaderSource.size() + 1);
	memcpy(fragmentShaderSource, d_->fragmentShaderSource.data(), d_->fragmentShaderSource.size());
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
		SError("SSurfaceRender_OpenGL") << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	d_->shaderProgram = shaderProgram;

	free(vertexShaderSource);
	free(fragmentShaderSource);
}
