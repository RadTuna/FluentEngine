#pragma once

// External Include
#include <memory>
#include <string>
#include <vector>

// Engine Include
#include "D3D11/D3DShader.h"
#include "Core/Core.h"


namespace Fluent
{
	
	struct ShaderDefine
	{
		std::string Macro;
		std::string Value;
	};
	
	enum class EShaderType
	{
		Unknown,
		Vertex,
		Pixel,
		Compute
	};
	
	class Shader final :
#ifdef API_GRAPHICS_D3D11
		public D3DShader
#endif
	{
	public:

		explicit Shader(const std::shared_ptr<Device>& device, EShaderType shaderType) noexcept;
		virtual ~Shader() noexcept;

		void Compile(const std::string& shaderPath);

		[[nodiscard]]
		const char* GetEntryPoint() const;
		[[nodiscard]]
		const char* GetTargetProfile() const;

	private:

		std::shared_ptr<Device> mDevice = nullptr;
		EShaderType mShaderType = EShaderType::Unknown;
		std::vector<ShaderDefine> mDefines;
		
	};
	
}
