#pragma once
#include "../../vendor/glew.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	bool normalised;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:			return sizeof(float);
		case GL_UNSIGNED_INT:	return sizeof(unsigned int);
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> Elements;
	unsigned int Stride;
public:
	VertexBufferLayout()
		:Stride(0) {};

	template<typename T>
	void Push(unsigned int count) {
		static_assert(true);
	}

	template<>
	void Push<float>(unsigned int count) {
		VertexBufferElement element;
		element.type = GL_FLOAT;
		element.count = count;
		element.normalised = GL_FALSE;
		Elements.push_back(element);
		Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		VertexBufferElement element;
		element.type = GL_UNSIGNED_INT;
		element.count = count;
		element.normalised = GL_FALSE;
		Elements.push_back(element);
		Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		VertexBufferElement element;
		element.type = GL_UNSIGNED_BYTE;
		element.count = count;
		element.normalised = GL_TRUE;
		Elements.push_back(element);
		Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}


	inline const std::vector<VertexBufferElement> GetElements() const& { return Elements; };
	inline unsigned int GetStride() const { return Stride; }
};
