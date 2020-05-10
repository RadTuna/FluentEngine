#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3D11Sampler.h"
#include "Core/Core.h"


namespace Fluent
{

	class Sampler final :
#ifdef API_GRAPHICS_D3D11
		public D3D11Sampler
#endif
	{
	public:

		explicit Sampler(
			const std::shared_ptr<Device>& device,
			ESamplerFilter minFilter,
			ESamplerFilter magFilter,
			ESamplerFilter mipFilter,
			ESamplerAddressMode addressMode,
			EComparisonFunction comparison,
			bool bEnableAnisotropy,
			bool bEnableComparison) noexcept;

		virtual ~Sampler() noexcept;


		[[nodiscard]]
		ESamplerFilter GetMinFilter() const { return mMinFilter; }

		[[nodiscard]]
		ESamplerFilter GetMagFilter() const { return mMagFilter; }

		[[nodiscard]]
		ESamplerFilter GetMipFilter() const { return mMipFilter; }

		[[nodiscard]]
		ESamplerAddressMode GetAddressMode() const { return mAddressMode; }

		[[nodiscard]]
		EComparisonFunction GetComparison() const { return mComparisonFunction; }

		[[nodiscard]]
		bool IsEnableAnisotropy() const { return mbEnableAnisotropy; }

		[[nodiscard]]
		bool IsEnableComparison() const { return mbEnableComparison; }
		
	private:

		ESamplerFilter mMinFilter = ESamplerFilter::Point;
		ESamplerFilter mMagFilter = ESamplerFilter::Point;
		ESamplerFilter mMipFilter = ESamplerFilter::Point;
		ESamplerAddressMode mAddressMode = ESamplerAddressMode::Wrap;
		EComparisonFunction mComparisonFunction = EComparisonFunction::Always;
		bool mbEnableAnisotropy = false;
		bool mbEnableComparison = false;
		
	};
	
}