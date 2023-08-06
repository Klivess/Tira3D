#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
//VAO should only be instantiated/constructed on the render thread (current window set to context)
class VAO
{
public:
	VAO();
	~VAO();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
private:
	//ID of GPU buffer location 
	unsigned int m_RendererID;
};

