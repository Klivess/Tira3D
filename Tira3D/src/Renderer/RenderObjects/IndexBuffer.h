#include "GL/glew.h"
#include "glfw3.h"
#include "../../Logger/Tira3DLogging.h"
#include <iostream>
#pragma once

//Vertex buffer should only be instantiated/constructed on the render thread (current window set to context)
class IndexBuffer
{
public:
	//ID of GPU buffer location 
	unsigned int RendererID;
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	unsigned int Count;
};

