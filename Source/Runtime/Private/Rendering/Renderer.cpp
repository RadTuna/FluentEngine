
// Primary Include
#include "Rendering/Renderer.h"

// Engine Include
#include "Core/EngineStorage.h"
#include "Rendering/ConstantBufferTypes.h"
#include "RHI/Device.h"
#include "RHI/SwapChain.h"
#include "RHI/ConstantBuffer.h"
#include "RHI/Shader.h"
#include "RHI/DepthStencilState.h"
#include "RHI/RasterizerState.h"
#include "RHI/Texture2D.h"
#include "RHI/BlendState.h"
#include "RHI/CommandList.h"
#include "RHI/Sampler.h"
#include "Resource/GeometryGenerator.h"

// temp include
#include "Math/Vector.h"
#include "Math/Math.h"


namespace Fluent
{

	Renderer::Renderer(const std::shared_ptr<EngineStorage>& inStorage) noexcept
		: ISubModule(inStorage)
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

		// Creation resources
		CreateConstantBuffers();
		CreateShaders();
		CreateDepthStencilStates();
		CreateRasterizerStates();
		CreateRenderTargets();
		CreateBlendState();
		CreateSampler();
		CreateCommandLists();
		CreateRenderResource();
		
		
		if (!mbIsInitialized)
		{
			mbIsInitialized = true;
		}

		return true;
	}

	void Renderer::Update(float deltaTime)
	{
		if (!mbIsInitialized)
		{
			return;
		}
		
		Assert(mCommandLists.size() != 0);
		std::shared_ptr<CommandList>& commandList = mCommandLists[0];


		// Start rendering
		mbIsRendering = true;

		// Pre-setup render states
		SetupGlobalConstantBufferAndSampler();

		UpdateViewport();
		UpdateFrameBuffer();
		PassSimpleQuad(commandList);
		// PassComposition(commandList);
		
		mSwapChain->Present();
		
		mbIsRendering = false;
		// End rendering
	}

	void Renderer::CreateConstantBuffers()
	{
		mConstantBuffers.resize(ConstantBufferTypesNum);

		bool result = true;
		mConstantBuffers[EConstantBufferType::FrameBuffer] = std::make_shared<ConstantBuffer>(mDevice);
		result &= mConstantBuffers[EConstantBufferType::FrameBuffer]->CreateBuffer<BufferFrame>();

		Assert(result);
	}

	void Renderer::CreateShaders()
	{
		mShaders.resize(RenderShaderTypesNum);

		mShaders[ERenderShaderType::VS_Quad] = std::make_shared<Shader>(mDevice, EShaderType::Vertex);
		mShaders[ERenderShaderType::VS_Quad]->Compile<VertexPosTex>("../../Shaders/Quad.hlsl");

		mShaders[ERenderShaderType::PS_Quad] = std::make_shared<Shader>(mDevice, EShaderType::Pixel);
		mShaders[ERenderShaderType::PS_Quad]->Compile<VertexPosTex>("../../Shaders/Quad.hlsl");
	}

	void Renderer::CreateDepthStencilStates()
	{
		mDepthStencilStates.resize(DepthStencilStateTypesNum);
		
		mDepthStencilStates[EDepthStencilStateType::Enable_Write] = std::make_shared<DepthStencilState>(mDevice, true, true, EComparisonFunction::LessEqual, false);
		mDepthStencilStates[EDepthStencilStateType::Enable_NoWrite] = std::make_shared<DepthStencilState>(mDevice, true, false, EComparisonFunction::LessEqual, false);
		mDepthStencilStates[EDepthStencilStateType::Disable] = std::make_shared<DepthStencilState>(mDevice, false, false, EComparisonFunction::LessEqual, false);
	}

	void Renderer::CreateRasterizerStates()
	{
		mRasterizerStates.resize(RasterizerStateTypesNum);

		mRasterizerStates[ERasterizerStateType::CullBackSolid] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Back, ERenderFillMode::Solid, true, false, false, false);

		mRasterizerStates[ERasterizerStateType::CullBackSolidNoClip] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Back, ERenderFillMode::Solid, false, false, false, false);

		mRasterizerStates[ERasterizerStateType::CullFrontSolid] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Front, ERenderFillMode::Solid, true, false, false, false);

		mRasterizerStates[ERasterizerStateType::CullNoneSolid] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::None, ERenderFillMode::Solid, true, false, false, false);

		mRasterizerStates[ERasterizerStateType::CullNoneSolidNoClip] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::None, ERenderFillMode::Solid, false, false, false, false);

		mRasterizerStates[ERasterizerStateType::CullBackWireFrame] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Back, ERenderFillMode::WireFrame, true, false, false, true);

		mRasterizerStates[ERasterizerStateType::CullFrontWireFrame] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::Front, ERenderFillMode::WireFrame, true, false, false, true);

		mRasterizerStates[ERasterizerStateType::CullNoneWireFrame] =
			std::make_shared<RasterizerState>(mDevice, ERenderCullMode::None, ERenderFillMode::WireFrame, true, false, false, true);
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

		// Create render targets
		mRenderTargets[ERenderTargetType::Albedo] =
			std::make_shared<Texture2D>(mDevice, width, height, EPixelFormat::R8G8B8A8_Unorm);
		
		mRenderTargets[ERenderTargetType::Material] =
			std::make_shared<Texture2D>(mDevice, width, height, EPixelFormat::R8G8B8A8_Unorm);
		
		mRenderTargets[ERenderTargetType::Normal] =
			std::make_shared<Texture2D>(mDevice, width, height, EPixelFormat::R16G16B16A16_Float);

		// Create depth-stencil
		mDepthStencil = std::make_shared<Texture2D>(mDevice, width, height, EPixelFormat::D32_Float);
	}

	void Renderer::CreateBlendState()
	{
		mBlendStates.resize(BlendStateTypesNum);
		
		mBlendStates[EBlendStateType::Disable] = std::make_shared<BlendState>(mDevice, false,
			ERenderBlend::SrcAlpha, ERenderBlend::InvSrcAlpha, ERenderBlendOperation::Add,
			ERenderBlend::One, ERenderBlend::One, ERenderBlendOperation::Add, 0.0f);

		mBlendStates[EBlendStateType::Enable] = std::make_shared<BlendState>(mDevice, true,
			ERenderBlend::SrcAlpha, ERenderBlend::InvSrcAlpha, ERenderBlendOperation::Add,
			ERenderBlend::One, ERenderBlend::One, ERenderBlendOperation::Add, 0.0f);

		mBlendStates[EBlendStateType::ColorAdd] = std::make_shared<BlendState>(mDevice, true,
			ERenderBlend::One, ERenderBlend::One, ERenderBlendOperation::Add,
			ERenderBlend::One, ERenderBlend::One, ERenderBlendOperation::Add, 0.0f);

		mBlendStates[EBlendStateType::Bloom] = std::make_shared<BlendState>(mDevice, true,
			ERenderBlend::SrcAlpha, ERenderBlend::InvSrcAlpha, ERenderBlendOperation::Add,
			ERenderBlend::One, ERenderBlend::One, ERenderBlendOperation::Add, 0.5f);
	}

	void Renderer::CreateSampler()
	{
		mSamplers.resize(SamplerTypesNum);

		mSamplers[ESamplerType::PointClamp] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Point, ESamplerFilter::Point, ESamplerFilter::Point,
			ESamplerAddressMode::Clamp, EComparisonFunction::Always, false, false);

		mSamplers[ESamplerType::PointWrap] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Point, ESamplerFilter::Point, ESamplerFilter::Point,
			ESamplerAddressMode::Wrap, EComparisonFunction::Always, false, false);

		mSamplers[ESamplerType::BilinearClamp] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Linear, ESamplerFilter::Linear, ESamplerFilter::Point,
			ESamplerAddressMode::Clamp, EComparisonFunction::Always, false, false);

		mSamplers[ESamplerType::BilinearWrap] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Linear, ESamplerFilter::Linear, ESamplerFilter::Point,
			ESamplerAddressMode::Wrap, EComparisonFunction::Always, false, false);

		mSamplers[ESamplerType::TrilinearClamp] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Linear, ESamplerFilter::Linear, ESamplerFilter::Linear,
			ESamplerAddressMode::Clamp, EComparisonFunction::Always, false, false);

		mSamplers[ESamplerType::TrilinearWrap] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Linear, ESamplerFilter::Linear, ESamplerFilter::Linear,
			ESamplerAddressMode::Wrap, EComparisonFunction::Always, false, false);

		mSamplers[ESamplerType::AnisotropyClamp] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Linear, ESamplerFilter::Linear, ESamplerFilter::Linear,
			ESamplerAddressMode::Clamp, EComparisonFunction::Always, true, false);

		mSamplers[ESamplerType::AnisotropyWrap] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Linear, ESamplerFilter::Linear, ESamplerFilter::Linear,
			ESamplerAddressMode::Wrap, EComparisonFunction::Always, true, false);

		mSamplers[ESamplerType::CompareDepth] = std::make_shared<Sampler>(mDevice,
			ESamplerFilter::Linear, ESamplerFilter::Linear, ESamplerFilter::Point,
			ESamplerAddressMode::Clamp, EComparisonFunction::Greater, false, true);
	}

	void Renderer::CreateCommandLists()
	{
		// temp // only single thread
		std::shared_ptr<CommandList> newCommandList = std::make_shared<CommandList>(mDevice);
		mCommandLists.emplace_back(newCommandList);
	}

	void Renderer::CreateRenderResource()
	{
		const f32 screenWidth = static_cast<f32>(mStorage->mWindowData.ScreenWidth);
		const f32 screenHeight = static_cast<f32>(mStorage->mWindowData.ScreenHeight);
		
		//mQuadMesh = GeometryGenerator::CreateQuad(0.0f, 0.0f, screenWidth, screenHeight, 0.0f);
		mQuadMesh = GeometryGenerator::CreateBox(10.0f, 10.0f, 10.0f);

		// temp
		mQuadMesh.CreateBuffers(mDevice);
		// temp
	}

	void Renderer::SetupGlobalConstantBufferAndSampler()
	{
		// temp
		mCommandLists[MAIN_THREAD_INDEX]->SetConstantBuffer(0, EShaderType::Vertex, mConstantBuffers[EConstantBufferType::FrameBuffer]);
		mCommandLists[MAIN_THREAD_INDEX]->SetConstantBuffer(0, EShaderType::Pixel, mConstantBuffers[EConstantBufferType::FrameBuffer]);

		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(0, mSamplers[ESamplerType::PointClamp]);
		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(1, mSamplers[ESamplerType::PointWrap]);
		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(2, mSamplers[ESamplerType::BilinearClamp]);
		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(3, mSamplers[ESamplerType::BilinearWrap]);
		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(4, mSamplers[ESamplerType::TrilinearClamp]);
		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(5, mSamplers[ESamplerType::TrilinearWrap]);
		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(6, mSamplers[ESamplerType::AnisotropyClamp]);
		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(7, mSamplers[ESamplerType::AnisotropyWrap]);
		mCommandLists[MAIN_THREAD_INDEX]->SetSampler(8, mSamplers[ESamplerType::CompareDepth]);
	}

	void Renderer::UpdateViewport()
	{
		// temp
		mViewport.X = 0.0f;
		mViewport.Y = 0.0f;
		mViewport.Width = static_cast<f32>(mStorage->mWindowData.ScreenWidth);
		mViewport.Height = static_cast<f32>(mStorage->mWindowData.ScreenHeight);
		mViewport.Near = 0.0f;
		mViewport.Far = 1.0f;
		// temp
	}

	void Renderer::UpdateFrameBuffer()
	{
		// Map
		BufferFrame* bufferFrame = reinterpret_cast<Fluent::BufferFrame*>(mConstantBuffers[EConstantBufferType::FrameBuffer]->Map());
		Assert(bufferFrame != nullptr);

		// temp
		const f32 aspectRatio = static_cast<f32>(mStorage->mWindowData.ScreenWidth) / static_cast<f32>(mStorage->mWindowData.ScreenHeight);
		const f32 cameraNear = 1.0f;
		const f32 cameraFar = 1000.0f;
		const Vector cameraPosition = Vector::SetVector4(0.0f, 0.0f, -50.0f, 0.0f);
		const Vector targetPosition = Vector::SetVector4(0.0f, 0.0f, 0.0f, 0.0f);
		const Vector upVector = Vector::SetVector4(0.0f, 1.0f, 0.0f, 0.0f);
		const Matrix viewMatrix = Matrix::CreateLookAtLH(cameraPosition, targetPosition, upVector);
		const Matrix projMatrix = Matrix::CreatePerspectiveFovLH(Math::Deg2Rad(60.0f), aspectRatio, cameraNear, cameraFar);
		// temp

		// Apply frame buffer data
		bufferFrame->CameraNear = cameraNear;
		bufferFrame->CameraFar = cameraFar;
		bufferFrame->WorldMatrix = Matrix4x4::Identity;
		Matrix::StoreMatrix4X4(viewMatrix, &bufferFrame->ViewMatrix);
		Matrix::StoreMatrix4X4(projMatrix, &bufferFrame->ProjectionMatrix);

		// Unmap
		mConstantBuffers[EConstantBufferType::FrameBuffer]->Unmap();
	}

	void Renderer::PassSimpleQuad(const std::shared_ptr<CommandList>& commandList)
	{	
		// Set render state
		commandList->SetVertexShader(mShaders[ERenderShaderType::VS_Quad]);
		commandList->SetPixelShader(mShaders[ERenderShaderType::PS_Quad]);
		commandList->SetBlendState(mBlendStates[EBlendStateType::Disable]);
		commandList->SetRasterizerState(mRasterizerStates[ERasterizerStateType::CullBackSolid]);
		commandList->SetDepthStencilState(mDepthStencilStates[EDepthStencilStateType::Enable_Write]);
		//commandList->SetRenderTargets(mRenderTargets, mDepthStencil);
		commandList->SetSwapChainBuffer(mSwapChain, mDepthStencil);
		commandList->SetViewport(mViewport);
		commandList->SetPrimitiveTopology(EPrimitiveTopology::TriangleList);

		// Clear render targets and depth-stencil
		std::vector<Vector4> renderTargetClear;
		renderTargetClear.reserve(1 /*RenderTargetTypesNum*/);
		for (u32 index = 0; index < 1 /*RenderTargetTypesNum*/; ++index)
		{
			renderTargetClear.emplace_back(Vector4::Zero);
		}
		commandList->ClearRenderTargetAndDepth(renderTargetClear, 1.0f);

		commandList->SetVertexBuffer(mQuadMesh.GetVertexBuffer());
		commandList->SetIndexBuffer(mQuadMesh.GetIndexBuffer());
		commandList->DrawIndexed(mQuadMesh.GetIndicesNum());
		commandList->Execute();
	}

	void Renderer::PassComposition(const std::shared_ptr<CommandList>& commandList)
	{
		// pass
	}
	
}
