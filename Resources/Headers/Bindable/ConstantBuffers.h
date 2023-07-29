#pragma once
#include <Bindable.h>
#include <GraphicsThrowMacros.h>

template<typename C>
class ConstantBuffer :public Bindable {
public:
	void Update(Graphics& gfx, const C& consts) {
		INFOMAN(gfx);
		D3D11_MAPPED_SUBRESOURCE MappedSubResource;
		GFX_THROW_INFO(GetContext(gfx)->Map(
			pConstantBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&msr
		));
		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}
	ConstantBuffer(Graphics& gfx, const C& consts) {
		INFOMAN(gfx);
		D3D11_BUFFER_DESC ConstantBuffDesc = {};
		ConstantBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstantBuffDesc.Usage = D3D11_USAGE_DEFAULT;
		ConstantBuffDesc.CPUAccessFlags = 0u;
		ConstantBuffDesc.MiscFlags = 0u;
		ConstantBuffDesc.ByteWidth = sizeof(ConstantBuffer);
		ConstantBuffDesc.StructureByteStride = 0u;
		D3D11_SUBRESOURCE_DATA ConstantSubData = {};
		ConstantSubData.pSysMem = &consts;
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&ConstantBuffDesc, &ConstantSubData, &pConstantBuffer));
	}

	ConstantBuffer(Graphics& gfx) {
		INFOMAN(gfx);
		D3D11_BUFFER_DESC ConstantBuffDesc = {};
		ConstantBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstantBuffDesc.Usage = D3D11_USAGE_DEFAULT;
		ConstantBuffDesc.CPUAccessFlags = 0u;
		ConstantBuffDesc.MiscFlags = 0u;
		ConstantBuffDesc.ByteWidth = sizeof(ConstantBuffer);
		ConstantBuffDesc.StructureByteStride = 0u;
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&ConstantBuffDesc, nullptr, &pConstantBuffer));
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) noexcept override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) noexcept override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};
