#include "pch.h"
#include "Renderer2D.h"

#include "Renderer\RenderCommand.h"
#include "Renderer\VertexBuffer.h"
#include "Renderer\ElementBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\Shader.h"
#include "Renderer\Texture2D.h"

namespace Engine {
	struct Renderer2DData {
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.TextureShader = ShaderFactory::FromFile("assets/shaders/texture.vertex", "assets/shaders/texture.fragment");

		{
			s_Data.WhiteTexture = Texture2D::Create(1, 1);
			uint32_t whiteTextureData = 0xffffffff;
			s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
		}
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene()
	{
		RenderCommand::SetClearColor({ 0.3f, 0.5f, 0.7f, 1.0f });
		RenderCommand::Clear();
	}

	void Renderer2D::DrawQuad(const Math::Vec3& position, const Math::Vec4& color)
	{
		auto elementBuffer = ElementBufferFactory::Create();

		float quadVertices[] = {
			// Position                                                // Color                            // Texture coords
			 0.5f + position.x,  0.5f + position.y, 1.0f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, // Top right
			 0.5f + position.x, -0.5f + position.y, 1.0f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, // Top left
			-0.5f + position.x, -0.5f + position.y, 1.0f + position.z, color.r, color.g, color.b, color.a,  0.0f, 0.0f, // Bottom left
			-0.5f + position.x,  0.5f + position.y, 1.0f + position.z, color.r, color.g, color.b, color.a,  0.0f, 1.0f, // Bottom right
		};

		auto vertexBufferQuad = VertexBufferFactory::Create(quadVertices, sizeof(quadVertices));
		vertexBufferQuad->SetBufferLayout({
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" },
			{ ShaderDataType::Float2, "texCoords" },
		});

		elementBuffer->AddVertexBuffer(vertexBufferQuad);

		uint32_t quadIndices[] = {
			0, 1, 3,
				1, 2, 3,
		};

		auto indexBuffer = IndexBufferFactory::Create(quadIndices, 6);
		elementBuffer->SetIndexBuffer(indexBuffer);

		s_Data.WhiteTexture->Bind(0);
		s_Data.TextureShader->Bind();

		RenderCommand::DrawIndexed(elementBuffer);
	}
}
