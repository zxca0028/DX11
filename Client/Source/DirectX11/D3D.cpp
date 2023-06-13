#include "pch.h"
#include "D3D.h"
#include "Window/Window.h"

namespace CLIENT
{
	void CLIENT::D3D::Init()
	{
		// 장치 조사, 새로고침 비율 얻어오기
		#pragma region FACTORY

		IDXGIFactory*     factory         = nullptr;
		IDXGIAdapter*     adapter         = nullptr;
		IDXGIOutput*      adapterOutput   = nullptr;
		DXGI_MODE_DESC*   displayModeList = nullptr;
		DXGI_ADAPTER_DESC adapterDesc;

		u32 numModes;
		u32 numerator;
		u32 denominator;

		ThrowIfFailed(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));

		factory->EnumAdapters(0, &adapter);

		adapter->EnumOutputs(0, &adapterOutput);

		adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);

		displayModeList = new DXGI_MODE_DESC[numModes];

		adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);

		for (u32 i = 0; i < numModes; ++i)
		{
			if (displayModeList[i].Width == gScreenWidth)
			{
				if (displayModeList[i].Height == gScreenHeight)
				{
					numerator = displayModeList[i].RefreshRate.Numerator;
					denominator = displayModeList[i].RefreshRate.Denominator;
				}
			}
		}

		adapter->GetDesc(&adapterDesc);

		mVideoCardMemory = (i32)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
		
		int strSize = WideCharToMultiByte(CP_ACP, 0, adapterDesc.Description, -1, NULL, 0, NULL, NULL);

		WideCharToMultiByte(CP_ACP, 0, adapterDesc.Description, -1, mVideoCardDescription, strSize, 0, 0);

		delete[] displayModeList;
		displayModeList = 0;

		adapterOutput->Release();
		adapterOutput = 0;

		adapter->Release();
		adapter = 0;

		factory->Release();
		factory = 0;

		LOG_INFO("Complete to create DXGIFactory");
		LOG_INFO(mVideoCardDescription);

#pragma endregion


		// 스왑체인
		#pragma region SWAPCHAIN

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		{
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

			swapChainDesc.BufferCount                        = 1;
			swapChainDesc.BufferDesc.Width                   = gScreenWidth;
			swapChainDesc.BufferDesc.Height                  = gScreenHeight;
			swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferDesc.RefreshRate.Numerator   = numerator;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
			swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.OutputWindow                       = ghWnd;
			swapChainDesc.SampleDesc.Count					 = 1;
			swapChainDesc.SampleDesc.Quality				 = 0;
			swapChainDesc.Windowed							 = true;
			swapChainDesc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapChainDesc.BufferDesc.Scaling			     = DXGI_MODE_SCALING_UNSPECIFIED;
			swapChainDesc.SwapEffect						 = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags								 = 0;

			D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
			
			ThrowIfFailed(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, mSwapChain.GetAddressOf(), mDevice.GetAddressOf(), NULL, mDeviceContext.GetAddressOf()));

			ID3D11Texture2D* backBufferPtr = nullptr;

			//mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
			mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferPtr));

			ThrowIfFailed(mDevice->CreateRenderTargetView(backBufferPtr, NULL, mRenderTargetView.GetAddressOf()));

			backBufferPtr->Release();
			backBufferPtr = 0;
		}

		LOG_INFO("Complete to create Device");
		LOG_INFO("Complete to create SwapChain");
		LOG_INFO("Complete to create RenderTargetView");

#pragma endregion
		

		// 깊이버퍼Desc 작성
		#pragma region DEPTH_BUFFER_DESC

		D3D11_TEXTURE2D_DESC depthBufferDesc;
		{
			ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

			depthBufferDesc.Width              = gScreenWidth;
			depthBufferDesc.Height             = gScreenHeight;
			depthBufferDesc.MipLevels          = 1;
			depthBufferDesc.ArraySize          = 1;
			depthBufferDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthBufferDesc.SampleDesc.Count   = 1;
			depthBufferDesc.SampleDesc.Quality = 0;
			depthBufferDesc.Usage			   = D3D11_USAGE_DEFAULT;
			depthBufferDesc.BindFlags		   = D3D11_BIND_DEPTH_STENCIL;
			depthBufferDesc.CPUAccessFlags     = 0;
			depthBufferDesc.MiscFlags          = 0;

			ThrowIfFailed(mDevice->CreateTexture2D(&depthBufferDesc, NULL, mDepthStencilBuffer.GetAddressOf()));
		}

		LOG_INFO("Complete to create DepthBufferDesc");

#pragma endregion


		// 깊이-스텐실 상태 변수 생성
		#pragma region DEPTH_STENCIL_STATE

		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		{
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

			depthStencilDesc.DepthEnable			      = true;
			depthStencilDesc.DepthWriteMask			      = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc				      = D3D11_COMPARISON_LESS;
			depthStencilDesc.StencilEnable			      = true;
			depthStencilDesc.StencilReadMask		      = 0xFF;
			depthStencilDesc.StencilWriteMask		      = 0xFF;

			depthStencilDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;

			depthStencilDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;

			ThrowIfFailed(mDevice->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.GetAddressOf()));
			mDeviceContext->OMSetDepthStencilState(mDepthStencilState.Get(), 1);
		}

		LOG_INFO("Complete to create DepthStencilDesc");

#pragma endregion


		// 깊이-스텐실 뷰 생성
		#pragma region DEPTH_STENCIL_VIEW

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		{
			ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

			depthStencilViewDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilViewDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDesc.Texture2D.MipSlice = 0;

			ThrowIfFailed(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), &depthStencilViewDesc, mDepthStencilView.GetAddressOf()));
			mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
		}

		LOG_INFO("Complete to create DepthStencilView");

#pragma endregion
		

		// 레스터라이저 상태 Desc 작성
		#pragma region RASTERIZER_STATE

		D3D11_RASTERIZER_DESC rasterDesc;
		{
			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode			     = D3D11_CULL_NONE;
			rasterDesc.DepthBias		     = 0;
			rasterDesc.DepthBiasClamp	     = 0.0f;
			rasterDesc.DepthClipEnable	     = true;
			rasterDesc.FillMode				 = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable     = false;
			rasterDesc.ScissorEnable         = false;
			rasterDesc.SlopeScaledDepthBias  = 0.0f;

			ThrowIfFailed(mDevice->CreateRasterizerState(&rasterDesc, mRasterState.GetAddressOf()));
			mDeviceContext->RSSetState(mRasterState.Get());
		}

		LOG_INFO("Complete to create Rasterizer");

#pragma endregion


		// 뷰포트 설정
		#pragma region VIEWPORT

		D3D11_VIEWPORT viewport;
		{
			viewport.Width    = (f32)gScreenWidth;
			viewport.Height   = (f32)gScreenHeight;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0.0f;
			viewport.TopLeftY = 0.0f;

			mDeviceContext->RSSetViewports(1, &viewport);
		}
		
#pragma endregion
		
		// Proj, World, Ortho 행렬 설정
		#pragma region MATRIX_SETTING

		f32 fieldOfView  = 3.14 / 4.0f;
		f32 screenAspect = (f32)gScreenWidth / (f32)gScreenHeight;

		mProj  = matrix::Convert(XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, 0.1f, 1000.0f));
		mWorld = matrix::Convert(XMMatrixIdentity());
		mOrtho = matrix::Convert(XMMatrixOrthographicLH((f32)gScreenWidth, (f32)gScreenHeight, 0.1f, 1000.0f));

#pragma endregion
	}

	void CLIENT::D3D::Render()
	{
	}

	void CLIENT::D3D::Destroy()
	{
		mSwapChain->SetFullscreenState(false, NULL);
	}

	void CLIENT::D3D::BeginScene()
	{
		float color[4];

		color[0] = 0.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
		color[3] = 0.0f;

		mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);

		mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), color);
		mDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.f, 0);
	}

	void CLIENT::D3D::EndScene()
	{
		mSwapChain->Present(0, 0);
	}

	void D3D::ClearRenderTarget()
	{
		if (mRenderTargetView)
		{
			mRenderTargetView->Release();
		}
	}

	void D3D::CreateRenderTarget(u32 width, u32 height)
	{
		ID3D11Texture2D* backBufferPtr;

		mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferPtr));

		mDevice->CreateRenderTargetView(backBufferPtr, nullptr, mRenderTargetView.GetAddressOf());

		backBufferPtr->Release();
		backBufferPtr = 0;

		/*D3D11_TEXTURE2D_DESC depthBufferDesc;
		{
			ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

			depthBufferDesc.Width              = width;
			depthBufferDesc.Height             = height;
			depthBufferDesc.MipLevels          = 1;
			depthBufferDesc.ArraySize          = 1;
			depthBufferDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthBufferDesc.SampleDesc.Count   = 1;
			depthBufferDesc.SampleDesc.Quality = 0;
			depthBufferDesc.Usage              = D3D11_USAGE_DEFAULT;
			depthBufferDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
			depthBufferDesc.CPUAccessFlags     = 0;
			depthBufferDesc.MiscFlags          = 0;

			ThrowIfFailed(mDevice->CreateTexture2D(&depthBufferDesc, NULL, mDepthStencilBuffer.GetAddressOf()));
		}*/
	}

	void D3D::ResizeBuffer(u32 bufferCount, u32 width, u32 height, DXGI_FORMAT newFormat, u32 swapChainFlags)
	{
		mSwapChain->ResizeBuffers(bufferCount, width, height, newFormat, swapChainFlags);
	}
}