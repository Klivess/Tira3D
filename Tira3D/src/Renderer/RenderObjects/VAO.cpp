#include "VAO.h"
#include "../../Logger/Tira3DLogging.h"

VAO::VAO()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VAO::~VAO()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VAO::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VAO::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VAO::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	GLCall(glBindVertexArray(m_RendererID));
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type,
			element.normalised, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
