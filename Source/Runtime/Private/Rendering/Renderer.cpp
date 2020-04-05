
// Primary Include
#include "Rendering/Renderer.h"

// Engine Include
#include "Core/RuntimeStorage.h"
#include "RHI/Device.h"
#include "RHI/SwapChain.h"
#include "RHI/ConstantBuffer.h"
#include "RHI/Shader.h"
#include "RHI/DepthStencilState.h"
#include "RHI/RasterizerState.h"
#include "RHI/Texture2D.h"


namespace Fluent
{

	Renderer::Renderer(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept
		: ISubSystem(inStorage)
	{
	}

	Renderer::~Renderer()
	{
	}

	bool Renderer::Initialize()
	{
		mDevice = std::make_shared<Device>();
		if (!mDevice->IsInitialized())
		{
			return false;
		}

		mSwapChain = std::make_shared<SwapChain>(mDevice, mStorage->mWindowData);
		if (!mSwapChain->IsInitialized())
		{
			return false;
		}

		mSwapChain->TempSetRenderTarget(mDevice);

		CreateConstantBuffers();
		CreateShaders();
		CreateDepthStencilStates();
		CreateRasterizerStates();
		CreateRenderTargets();

		if (!mbIsInitialized)
		{
			mbIsInitialized = true;
		}

		return true;
	}

	void Renderer::Update(float deltaTime)
	{
		mSwapChain->TempSetColorRed(mDevice);
		
		mSwapChain->Present();
	}

	void Renderer::CreateConstantBuffers()
	{
		mConstantBuffers.resize(ConstantBufferTypesNum);
		
		mConstantBuffers[EConstantBufferType::FrameBuffer] = std::make_shared<ConstantBuffer>(mDevice);
		mConstantBuffers[EConstantBufferType::FrameBuffer]->CreateBuffer<BufferCommon>();
	}

	void Renderer::CreateShaders()
	{
		mShaders.resize(RenderShaderTypesNum);

		mShaders[ERenderShaderType::VS_Common] = std::make_shared<Shader>(mDevice, EShaderType::Vertex);
		mShaders[ERenderShaderType::VS_Common]->Compile("TempPath");

		mShaders[ERenderShaderType::PS_Common] = std::make_shared<Shader>(mDevice, EShaderType::Pixel);
		mShaders[ERenderShaderType::PS_Common]->Compile("TempPath");
	}

	void Renderer::CreateDepthStencilStates()
	{
		mDepthStencilStates.resize(DepthStencilStateTypesNum);

		mDepthStencilStates[EDepthStencilStateType::Enable_Write] = std::make_shared<DepthStencilState>(mDevice, true, true, false);
		mDepthStencilStates[EDepthStencilStateType::Enable_NoWrite] = std::make_shared<DepthStencilState>(mDevice, true, false, false);
		mDepthStencilStates[EDepthStencilStateType::Disable] = std::make_shared<DepthStencilState>(mDevice, false, false, false);
	}

	void Renderer::CreateRasterizerStates()
	{
		mRasterizerStates.resize(RasterizerStateTypesNum);

		mRasterizerStates[ERasterizerStateType::CullBack_Solid] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Back, ERenderFillMode::Solid, false, false, false, false);
		mRasterizerStates[ERasterizerStateType::CullBack_Solid_NoClip] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Back, ERenderFillMode::Solid, true, false, false, false);
		mRasterizerStates[ERasterizerStateType::CullFront_Solid] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Front, ERenderFillMode::Solid, false, false, false, false);
		mRasterizerStates[ERasterizerStateType::CullNone_Solid] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::None, ERenderFillMode::Solid, false, false, false, false);
		mRasterizerStates[ERasterizerStateType::CullBack_WireFrame] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Back, ERenderFillMode::WireFrame, false, false, false, true);
		mRasterizerStates[ERasterizerStateType::CullFront_WireFrame] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Front, ERenderFillMode::WireFrame, false, false, false, true);
		mRasterizerStates[ERasterizerStateType::CullNone_WireFrame] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::None, ERenderFillMode::WireFrame, false, false, false, true);
	}

	void Renderer::CreateRenderTargets()
	{
		const u32 width = mStorage->mWindowData.ScreenWidth;
		const u32 height = mStorage->mWindowData.ScreenHeight;

		if ((width / 4) == 0 || (height / 4) == 0)
		{
			return;
		}

		mRenderTargets.resize(RenderTargetTypesNum);
		
		mRenderTargets[ERenderTargetType::Albedo] =
			std::make_shared<Texture2D>(mDevice, width, height, EPixelFormat::R8G8B8A8_Unorm);
	}

}
