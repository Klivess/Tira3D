#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION    
#include "../../vendor/stb_image.h"

//https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
bool hasEnding(std::string const& fullString, std::string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

Texture::Texture()
{
}

Texture::Texture(const std::string& path)
	:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	//This flips the texture upside down. We need to do this because OpenGL expects the texture pixels to root from the bottom left.
	//However pixels in the PNG format start from the top in scanlines, thus requires flipping. 
	stbi_set_flip_vertically_on_load(1);

	//Loads texture file into stbi, and sets m_Width, m_Height and m_BPP to width and height and 'bits per pixel' of loaded texture.
	//4 is number of colour values, and as we are using 4 values per colour (vec4), we specify 4.
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };

	//Specifications to load texture
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//Different types of texture wrapping: https://learnopengl.com/img/getting-started/texture_wrapping.png
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
	GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));


	if (m_LocalBuffer)
	{
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//GL_RGBA8 because we have 8 bits per RGBA value
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		Tira3DLogging::LogToConsole("Failed to load texture: " + m_FilePath);
	}
	Unbind();
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
