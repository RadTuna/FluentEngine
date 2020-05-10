
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/Shader.h"

// External Include
#include <d3dcompiler.h>
#include <sstream>

// Engine Include
#include "RHI/Device.h"

namespace Fluent
{
	
	Shader::Shader(const std::shared_ptr<Device>& device, EShaderType shaderType) noexcept
	{
		Assert(device && device->IsInitialized());
		
		mDevice = device->GetDevice();
		mShaderType = shaderType;
	}

	Shader::~Shader() noexcept
	{
		D3D11Release(mVertexShader);
		D3D11Release(mPixelShader);
		D3D11Release(mComputeShader);
	}

	void Shader::CompileInternal(const std::string& shaderPath, EVertexType vertexType)
	{
		u32 compileFlags = 0;
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
			shaderDefines.emplace_back(D3D_SHADER_MACRO { uniDefine.Macro.c_str(), uniDefine.Value.c_str() });
		}
		shaderDefines.emplace_back(D3D_SHADER_MACRO { nullptr, nullptr });

		
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
			std::stringstream stringStream(static_cast<i8*>(errorBlob->GetBufferPointer()));
			std::string stringLine;
			while (std::getline(stringStream, stringLine, '\n'))
			{
				LOG_CONSOLE_STRING(stringLine);
			}
			
			errorBlob->Release();
			errorBlob = nullptr;
			return;
		}

		if (FAILED(result))
		{
			if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			{
				LOG_CONSOLE_FORMAT("Failed to find shader with path \"%s\".", shaderPath.c_str());
			}
			else
			{
				LOG_CONSOLE_FORMAT("An error occurred when trying to load and compile \"%s\"", shaderPath.c_str());
			}
			
			return;
		}

		if (shaderBlob)
		{
			switch (mShaderType)
			{
				case EShaderType::Vertex:
				{
					D3D11Release(mVertexShader);
						
					result = mDevice->CreateVertexShader(
						shaderBlob->GetBufferPointer(),
						shaderBlob->GetBufferSize(),
						nullptr,
						&mVertexShader);
					Assert(SUCCEEDED(result));

					std::vector<D3D11_INPUT_ELEMENT_DESC> inputDescs;
					ToD3D11InputDesc(inputDescs, vertexType);

					const u32 inputDescsNum = static_cast<u32>(inputDescs.size());
					result = mDevice->CreateInputLayout(
						inputDescs.data(),
						inputDescsNum, 
						shaderBlob->GetBufferPointer(), 
						shaderBlob->GetBufferSize(), 
						&mInputLayout);
					Assert(SUCCEEDED(result));
					break;
				}
				case EShaderType::Pixel:
				{
					D3D11Release(mPixelShader);
						
					result = mDevice->CreatePixelShader(
						shaderBlob->GetBufferPointer(),
						shaderBlob->GetBufferSize(),
						nullptr,
						&mPixelShader);
					Assert(SUCCEEDED(result));
					break;
				}
				case EShaderType::Compute:
				{
					D3D11Release(mComputeShader);
						
					result = mDevice->CreateComputeShader(
						shaderBlob->GetBufferPointer(),
						shaderBlob->GetBufferSize(),
						nullptr,
						&mComputeShader);
					Assert(SUCCEEDED(result));
					break;
				}
				default:
				{
					Assert(false);
					break;
				}
			}
		}

		shaderBlob->Release();
		shaderBlob = nullptr;
	}


}

#endif
