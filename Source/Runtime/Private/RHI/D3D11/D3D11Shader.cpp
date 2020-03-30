
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/Shader.h"

// External Include
#include <d3dcompiler.h>

// Engine Include
#include "RHI/Device.h"

namespace Fluent
{
	
	Shader::Shader(const std::shared_ptr<Device>& device, EShaderType shaderType) noexcept
	{
		Assert(device && device->IsInitialized());
		mDevice = device;
		mShaderType = shaderType;
	}

	Shader::~Shader() noexcept
	{
		if (mShader != nullptr)
		{
			switch (mShaderType)
			{
				case EShaderType::Vertex:
				{
					ID3D11VertexShader* vertexShader = GetVertexShader();
					D3D11Release(vertexShader);
				}
				case EShaderType::Pixel:
				{
					ID3D11PixelShader* pixelShader = GetPixelShader();
					D3D11Release(pixelShader);
				}
				case EShaderType::Compute:
				{
					ID3D11ComputeShader* computeShader = GetComputeShader();
					D3D11Release(computeShader);
				}
				default:
				{
					Assert(false);
				}
			}
		}
	}

	void Shader::Compile(const std::string& shaderPath)
	{
		uint32 compileFlags = 0;
#ifdef DEBUG
		compileFlags |= D3DCOMPILE_DEBUG | D3DCOMPILE_PREFER_FLOW_CONTROL;
#elif NDEBUG
		compileFlags |= D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

		std::vector<D3D_SHADER_MACRO> shaderDefines =
		{
			D3D_SHADER_MACRO { "COMPILE_VS", mShaderType == EShaderType::Vertex ? "1" : "0" },
			D3D_SHADER_MACRO { "COMPILE_PS", mShaderType == EShaderType::Pixel ? "1" : "0" },
			D3D_SHADER_MACRO { "COMPILE_CS", mShaderType == EShaderType::Compute ? "1" : "0" }
		};

		for (const ShaderDefine& uniDefine : mDefines)
		{
			D3D_SHADER_MACRO tempMacro{ uniDefine.Macro.c_str(), uniDefine.Value.c_str() };
			shaderDefines.emplace_back(tempMacro);
		}

		
		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* shaderBlob = nullptr;
		HRESULT result = S_OK;

		// temp
		WCHAR convertedShaderPath[128];
		MultiByteToWideChar(CP_ACP, 0, shaderPath.c_str(), shaderPath.capacity(), convertedShaderPath, 128);
		// temp
		
		result = D3DCompileFromFile(
			convertedShaderPath,
			shaderDefines.data(),
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			GetEntryPoint(),
			GetTargetProfile(),
			compileFlags,
			0,
			&shaderBlob,
			&errorBlob);

		if (errorBlob)
		{
			// something error message

			errorBlob->Release();
			errorBlob = nullptr;
			return;
		}

		if (FAILED(result))
		{
			// something error message
			return;
		}

		if (shaderBlob)
		{
			switch (mShaderType)
			{
				case EShaderType::Vertex:
				{
					ID3D11VertexShader* vertexShader = GetVertexShader();
					D3D11Release(vertexShader);
						
					result = mDevice->GetDevice()->CreateVertexShader(
						shaderBlob->GetBufferPointer(),
						shaderBlob->GetBufferSize(),
						nullptr,
						&vertexShader);
				}
				case EShaderType::Pixel:
				{
					ID3D11PixelShader* pixelShader = GetPixelShader();
					D3D11Release(pixelShader);
						
					result = mDevice->GetDevice()->CreatePixelShader(
						shaderBlob->GetBufferPointer(),
						shaderBlob->GetBufferSize(),
						nullptr,
						&pixelShader);
				}
				case EShaderType::Compute:
				{
					ID3D11ComputeShader* computeShader = GetComputeShader();
					D3D11Release(computeShader);
						
					result = mDevice->GetDevice()->CreateComputeShader(
						shaderBlob->GetBufferPointer(),
						shaderBlob->GetBufferSize(),
						nullptr,
						&computeShader);
				}
				default:
				{
					Assert(false);
				}
			}
		}

		shaderBlob->Release();
		shaderBlob = nullptr;
	}


}

#endif
