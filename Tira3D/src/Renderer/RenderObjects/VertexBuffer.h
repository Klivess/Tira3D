#include "GL/glew.h"
#include "glfw3.h"
#include "../../Logger/Tira3DLogging.h"

#pragma once

//Vertex buffer should only be instantiated/constructed on the render thread (current window set to context)
class VertexBuffer
{
public:
	VertexBuffer(const void* data);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	//ID of GPU buffer location 
	unsigned int RendererID;
};

