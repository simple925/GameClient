#pragma once
#include "pch.h"
// Directx11 라이브러리 함수를 이용해서
// GPU를 제어할 수 있는 클래스
class Device
	: public singleton<Device>
{
	SINGLE(Device);
private:
	ID3D11Device*				m_Device;				// GPU 메모리 관리
	ID3D11DeviceContext*		m_Context;				// GPU 제어 및 랜더링, GPGPU(General Purpose) - ComputeShader 명령

	IDXGISwapChain*				m_SwapChain;			//
	ID3D11Texture2D*			m_RenderTarget;			//
	ID3D11Texture2D*			m_DepthStencilTarget;	//

	ID3D11RenderTargetView*		m_RTV;					//
	ID3D11DepthStencilView*		m_DSV;					//

	ID3D11SamplerState*			m_arrSampler[2];		//

	ID3D11RasterizerState*		m_RSState;				//
	ID3D11DepthStencilState*	m_DSState;				//
	ID3D11BlendState*			m_BBState;				//
public:
	int Init(HWND _hwnd, POINT _Resolution);

};