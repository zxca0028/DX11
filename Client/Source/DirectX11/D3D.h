#pragma once

#include "Core.h"

namespace CLIENT
{
	class D3D
	{
	private:
		bool mVSYNC_Enable;
		char mVideoCardDescription[128];
		i32  mVideoCardMemory;
	private:
		ComPtr<IDXGISwapChain>          mSwapChain;
		ComPtr<ID3D11RenderTargetView>  mRenderTargetView;
		ComPtr<ID3D11DepthStencilView>  mDepthStencilView;
		ComPtr<ID3D11DepthStencilState> mDepthStencilState;
		ComPtr<ID3D11Texture2D>         mDepthStencilBuffer;
		ComPtr<ID3D11RasterizerState>   mRasterState;
	private:
		ComPtr<ID3D11Device>            mDevice;
		ComPtr<ID3D11DeviceContext>     mDeviceContext;
	private:
		XMMATRIX mWorld;
		XMMATRIX mProj;
		XMMATRIX mOrtho;
	public:
		void Init();
		void Render();
		void Destroy();
	public:
		void BeginScene();
		void EndScene();
	public:
		ID3D11Device* GetDevice() const
		{
			return mDevice.Get();
		}
		ID3D11DeviceContext* GetDeviceContext() const
		{
			return mDeviceContext.Get();
		}
	public:
		void GetProj(XMMATRIX& proj)
		{
			proj = mProj;
		}
		void GetWorld(XMMATRIX& world)
		{
			world = mWorld;
		}
		void GetOrtho(XMMATRIX& ortho)
		{
			ortho = mOrtho;
		}
	public:
		void GetVideoCardInfo(char* cardName, int& memory)
		{
			strcpy_s(cardName, 128, mVideoCardDescription);
			memory = mVideoCardMemory;
		}
	};
}