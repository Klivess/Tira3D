#include "../../vendor/glew.h"
#include "../../vendor/glfw3.h"
#include "../../Logger/Tira3DLogging.h"
#include <iostream>
#include <vector>

#pragma once

//Vertex buffer should only be instantiated/constructed on the render thread (current window set to context)
class VertexBuffer
{
private:
public:
	//ID of GPU buffer location 
	unsigned int RendererID;
	//Pass positions array as 'data'. Positions array must be of Float datatype.
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

