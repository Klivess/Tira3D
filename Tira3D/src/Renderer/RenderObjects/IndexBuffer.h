#include "GL/glew.h"
#include "glfw3.h"
#include "../../Logger/Tira3DLogging.h"
#include <iostream>
#pragma once

//Vertex buffer should only be instantiated/constructed on the render thread (current window set to context)
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	//ID of GPU buffer location 
	unsigned int RendererID;

	unsigned int Count;
};

