#pragma once

#include "Renderer\Texture2D.h"

namespace Engine {

	class OpenGLTexture2D : public Texture2D 
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void Bind(uint32_t slot) override;
		virtual void Unbind(uint32_t slot) override;

		virtual void SetData(void* data, size_t size) override;

		virtual bool OpenGLTexture2D::operator==(const Texture2D& other) const override
		{
			return m_TextureID == ((OpenGLTexture2D&)other).m_TextureID;
		};

	private:
		uint32_t GetOpenGLDataFormat(TextureDataFormat format, bool internalFormat) const;

	private:
		uint32_t m_TextureID;
		uint32_t m_Width, m_Height;
		size_t m_Size;

		TextureDataFormat m_DataFormat;
	};

}
