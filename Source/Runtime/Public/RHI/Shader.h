#pragma once

// External Include
#include <memory>
#include <string>
#include <vector>

// Engine Include
#include "D3D11/D3D11Shader.h"
#include "Core/Core.h"


namespace Fluent
{
	
	struct ShaderDefine
	{
		std::string Macro;
		std::string Value;
	};
	
	class Shader final :
#ifdef API_GRAPHICS_D3D11
		public D3D11Shader
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

		EShaderType mShaderType = EShaderType::Unknown;
		std::vector<ShaderDefine> mDefines;
		
	};
	
}
