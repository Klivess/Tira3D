#pragma once
#include "../../vendor/glew.h"
#include "../../vendor/glfw3.h"
#include "../../Logger/Tira3DLogging.h"
#include <iostream>

//Vertex buffer should only be instantiated/constructed on the render thread (current window set to context)
class IndexBuffer
{
public:
	//this is a bad idea and will be removed in the future.
	const unsigned int* m_indices;
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	//ID of GPU buffer location 
	unsigned int RendererID;

	unsigned int Count;
};

