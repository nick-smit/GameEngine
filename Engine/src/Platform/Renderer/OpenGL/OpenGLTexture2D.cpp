#include "pch.h"
#include "OpenGLTexture2D.h"

#include <glad\glad.h>
#include <stb_image.cpp>

namespace Engine {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height), m_DataFormat(TextureDataFormat::RGBA)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, GL_RGBA8, width, height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		stbi_uc* data; 
		{
			data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		}
		GE_CORE_ASSERT(data, "Failed to load texture!");

		m_Width = width;
		m_Height = height;

		switch (nrChannels) {
		case 3:
			m_DataFormat = TextureDataFormat::RGB;
			break;
		case 4:
			m_DataFormat = TextureDataFormat::RGBA;
			break;
		default: GE_CORE_ASSERT(false, "Unusable number of channels");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, GetOpenGLDataFormat(m_DataFormat, true), m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GetOpenGLDataFormat(m_DataFormat, false), GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}
	
	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, m_TextureID);
	}
	
	void OpenGLTexture2D::Unbind(uint32_t slot)
	{
		glBindTextureUnit(slot, 0);
	}
	
	void OpenGLTexture2D::SetData(void* data, size_t size)
	{
		GE_CORE_ASSERT(size == m_Width * m_Height * (m_DataFormat == TextureDataFormat::RGB ? 3 : 4), "Data must be entire texture!");

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GetOpenGLDataFormat(m_DataFormat, false), GL_UNSIGNED_BYTE, data);
	}
	uint32_t OpenGLTexture2D::GetOpenGLDataFormat(TextureDataFormat format, bool internalFormat) const
	{
		switch (m_DataFormat) {
		case TextureDataFormat::RGB:
			return internalFormat ? GL_RGB8 : GL_RGB;
		case TextureDataFormat::RGBA:
			return internalFormat ? GL_RGBA8 : GL_RGBA;
		}

		GE_CORE_ASSERT(false, "Data type not yet implemented!");
		return 0;
	}
}
