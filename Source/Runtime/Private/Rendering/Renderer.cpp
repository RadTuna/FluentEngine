
#include "Rendering/Renderer.h"
#include "Core/RuntimeStorage.h"
#include "RHI/Device.h"
#include "RHI/SwapChain.h"
#include "RHI/ConstantBuffer.h"

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
		CreateVertexShaders();
		CreatePixelShaders();
		CreateDepthStencilStates();
		CreateRasterizerStates();
		CreateRenderTargets();

		return true;
	}

	void Renderer::Update(float deltaTime)
	{
		mSwapChain->TempSetColorRed(mDevice);
		
		mSwapChain->Present();
	}

	void Renderer::CreateConstantBuffers()
	{
		mCommonConstantBuffer = std::make_shared<ConstantBuffer>(mDevice);
		mCommonConstantBuffer->CreateBuffer<BufferCommon>();
	}

	void Renderer::CreateVertexShaders()
	{
	}

	void Renderer::CreatePixelShaders()
	{
	}

	void Renderer::CreateDepthStencilStates()
	{
	}

	void Renderer::CreateRasterizerStates()
	{
	}

	void Renderer::CreateRenderTargets()
	{
	}

}
