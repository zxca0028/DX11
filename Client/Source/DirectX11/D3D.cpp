#include "pch.h"
#include "D3D.h"
#include "Window/Window.h"

namespace CLIENT
{
	void CLIENT::D3D::Init()
	{
		HWND hWnd		  = GlobalInstance::Instance<Window>()->GetWindowDesc().hWnd;
		u32  screenWidth  = GlobalInstance::Instance<Window>()->GetWindowDesc().Width;
		u32  screenHeight = GlobalInstance::Instance<Window>()->GetWindowDesc().Height;

		// ��ġ ����, ���ΰ�ħ ���� ������
		#pragma region FACTORY

		IDXGIFactory*     factory         = nullptr;
		IDXGIAdapter*     adapter         = nullptr;
		IDXGIOutput*      adapterOutput   = nullptr;
		DXGI_MODE_DESC*   displayModeList = nullptr;
		ID3D11Texture2D*  backBufferPtr   = nullptr;
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
			if (displayModeList[i].Width == screenWidth)
			{
				if (displayModeList[i].Height == screenHeight)
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


		// ����ü��
		#pragma region SWAPCHAIN

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		{
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

			swapChainDesc.BufferCount                        = 1;
			swapChainDesc.BufferDesc.Width                   = screenWidth;
			swapChainDesc.BufferDesc.Height                  = screenHeight;
			swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferDesc.RefreshRate.Numerator   = numerator;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
			swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.OutputWindow                       = hWnd;
			swapChainDesc.SampleDesc.Count					 = 1;
			swapChainDesc.SampleDesc.Quality				 = 0;
			swapChainDesc.Windowed							 = true;
			swapChainDesc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapChainDesc.BufferDesc.Scaling			     = DXGI_MODE_SCALING_UNSPECIFIED;
			swapChainDesc.SwapEffect						 = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags								 = 0;

			D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
			
			ThrowIfFailed(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, mSwapChain.GetAddressOf(), mDevice.GetAddressOf(), NULL, mDeviceContext.GetAddressOf()));

			mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);

			ThrowIfFailed(mDevice->CreateRenderTargetView(backBufferPtr, NULL, mRenderTargetView.GetAddressOf()));

			backBufferPtr->Release();
			backBufferPtr = 0;
		}

		LOG_INFO("Complete to create Device");
		LOG_INFO("Complete to create SwapChain");
		LOG_INFO("Complete to create RenderTargetView");

#pragma endregion
		

		// ���̹���Desc �ۼ�
		#pragma region DEPTH_BUFFER_DESC

		D3D11_TEXTURE2D_DESC depthBufferDesc;
		{
			ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

			depthBufferDesc.Width              = screenWidth;
			depthBufferDesc.Height             = screenHeight;
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


		// ����-���ٽ� ���� ���� ����
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


		// ����-���ٽ� �� ����
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
		

		// �����Ͷ����� ���� Desc �ۼ�
		#pragma region RASTERIZER_STATE

		D3D11_RASTERIZER_DESC rasterDesc;
		{
			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode			     = D3D11_CULL_BACK;
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


		// ����Ʈ ����
		#pragma region VIEWPORT

		D3D11_VIEWPORT viewport;
		{
			viewport.Width    = (f32)screenWidth;
			viewport.Height   = (f32)screenHeight;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0.0f;
			viewport.TopLeftY = 0.0f;

			mDeviceContext->RSSetViewports(1, &viewport);
		}
		
#pragma endregion
		
		
		// Proj, World, Ortho ��� ����
		#pragma region MATRIX_SETTING

		f32 fieldOfView  = 3.14 / 4.0f;
		f32 screenAspect = (f32)screenWidth / (f32)screenHeight;

		mProj  = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, 0.1f, 1000.0f);
		mWorld = XMMatrixIdentity();
		mOrtho = XMMatrixOrthographicLH((f32)screenWidth, (f32)screenHeight, 0.1f, 1000.0f);

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
		color[2] = 1.0f;
		color[3] = 0.0f;

		mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), color);
		mDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 10.f, 0);
	}

	void CLIENT::D3D::EndScene()
	{
		mSwapChain->Present(0, 0);
	}
}