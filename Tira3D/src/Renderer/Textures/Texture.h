#pragma once

#include <string>
#include "../../Logger/Tira3DLogging.h"

class Texture
{
private:
	unsigned int m_RendererID;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	std::string m_FilePath;

	Texture();
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};

