
#include <d2d1.h>
#include <dwrite_1.h>
#include <intrin.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#define RET_CHK(x) if ( x != S_OK ) return
Vector2 screen_size = { (float)Global::ScreenHigh, (float)Global::ScreenWidth };
namespace Renderer {
	ID2D1Factory* Interface;
	ID2D1RenderTarget* Canvas;
	IDWriteFactory1* TextEngine;
	IDWriteTextFormat* TextFormat;
	ID2D1SolidColorBrush* SolidColor;
	__forceinline UINT wcslen(const wchar_t* Str) {
		const wchar_t* TempStr = Str;
		for (; *TempStr; ++TempStr);
		return (UINT)(TempStr - Str);
	}
	__declspec(noinline) bool InitRender(IDXGISwapChain* SwapChain)
	{
		static bool initialized; if (!initialized) {
			initialized = true; D2D1_FACTORY_OPTIONS CreateOpt = { D2D1_DEBUG_LEVEL_NONE };
			FC(dwrite, DWriteCreateFactory, DWRITE_FACTORY_TYPE_SHARED, __uuidof(TextEngine), (IUnknown**)&TextEngine);
			FC(d2d1, D2D1CreateFactory, D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &CreateOpt, (void**)&Interface);
			TextEngine->CreateTextFormat(StrW(L"Tahoma"), NULL, DWRITE_FONT_WEIGHT_THIN, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED, 12.f, L"", &TextFormat);
			if (!Interface || !TextEngine || !TextFormat) return false;
		}
		ID3D11Device* d3d_device;
		if (SwapChain->GetDevice(IID_PPV_ARGS(&d3d_device))) return false;
		WORD flagsOffset = *(WORD*)((*(DWORD64**)d3d_device)[38] + 2); //x64
		int& flags = *(INT*)((DWORD64)d3d_device + flagsOffset);
		d3d_device->Release();
		IDXGISurface* d3d_bbuf;
		if (SwapChain->GetBuffer(0, IID_PPV_ARGS(&d3d_bbuf)))
			return false;
		D2D1_RENDER_TARGET_PROPERTIES d2d_prop = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
		flags |= 0x20; HRESULT canvas_state = Interface->CreateDxgiSurfaceRenderTarget(d3d_bbuf, d2d_prop, &Canvas); flags &= ~0x20; d3d_bbuf->Release(); if (canvas_state) return false;
		if (!SolidColor) Canvas->CreateSolidColorBrush({}, &SolidColor); return true;
	}
	__forceinline bool NewFrame(IDXGISwapChain* SwapChain)
	{
		if (!Canvas && !InitRender(SwapChain))
			return false;
		Canvas->BeginDraw();
		return true;
	}
	__forceinline Vector2 CanvasSize() {
		D2D1_SIZE_F Size = Canvas->GetSize();
		return Vector2{ Size.width, Size.height };
	}
	__forceinline void ResetCanvas() {
		if (Canvas) {
			Canvas->Release();
			Canvas = nullptr;
		}
	}
	__forceinline void EndFrame() {
		HRESULT state = Canvas->EndDraw();
		if (state == D2DERR_RECREATE_TARGET)
			ResetCanvas();
	}
	__forceinline void Line(const Vector2& Start, const Vector2& End, const D2D1::ColorF& Clr, float Thick = 1.5f, bool outline = false) {
		if (outline) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick * 1.75);
		}
		SolidColor->SetColor(Clr);
		Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick);
	}
	__forceinline void Circle(const Vector2& Start, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f) {
		SolidColor->SetColor(Clr); Canvas->DrawEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor, Thick);
	}
	__forceinline void FillCircle(const Vector2& Start, const D2D1::ColorF& Clr, float Rad) {
		SolidColor->SetColor(Clr); Canvas->FillEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor);
	}
	__forceinline void Rectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Thick = 1.5f) {
		SolidColor->SetColor(Clr); Canvas->DrawRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor, Thick);
	}
	__forceinline void FillRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr) {
		SolidColor->SetColor(Clr); Canvas->FillRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor);
	}
	__forceinline void RoundedRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f) {
		SolidColor->SetColor(Clr); Canvas->DrawRoundedRectangle({ {Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, Rad, Rad }, SolidColor, Thick);
	}
	__forceinline void FillRoundedRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Rad) {
		SolidColor->SetColor(Clr); Canvas->FillRoundedRectangle({ {Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y}, Rad, Rad }, SolidColor);
	}
	__forceinline void FillGradientRoundedRectangle(const Vector2& Dot, const Vector2& WidthHeight, const D2D1::ColorF& Clr, float Radius, float per) {
		auto kek_g = 1.f - per; auto kek_r = 1.f - kek_g;
		ID2D1GradientStopCollection* pGradientStops = NULL;
		D2D1_GRADIENT_STOP gradientStops[4];
		gradientStops[0].color = D2D1::ColorF{ D2D1::ColorF::Red };
		gradientStops[0].position = 0.f;
		gradientStops[1].color = D2D1::ColorF{ D2D1::ColorF::Red };
		gradientStops[1].position = per;
		gradientStops[2].color = D2D1::ColorF{ D2D1::ColorF::Green };
		gradientStops[2].position = per;
		gradientStops[3].color = D2D1::ColorF{ D2D1::ColorF::Green };
		gradientStops[3].position = 1.f;
		Canvas->CreateGradientStopCollection(
			gradientStops,
			4,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_WRAP,
			&pGradientStops
		);
		ID2D1LinearGradientBrush* m_pLinearGradientBrush;
		Canvas->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(
				D2D1::Point2F(Dot.x, Dot.y),
				D2D1::Point2F(Dot.x + WidthHeight.x, Dot.y + WidthHeight.y)),
			pGradientStops,
			&m_pLinearGradientBrush
		);
		Canvas->FillRoundedRectangle({ {Dot.x, Dot.y, Dot.x + WidthHeight.x, Dot.y + WidthHeight.y}, Radius, Radius }, m_pLinearGradientBrush);
		m_pLinearGradientBrush->Release();
		pGradientStops->Release();
	}
	Vector2 String(const Vector2& pos, const wchar_t* text, const D2D1::ColorF& color, bool outline, bool center = false) {
		if (center) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			IDWriteTextLayout* TextLayout;
			TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 500.f, 100.f, &TextLayout);
			DWRITE_TEXT_METRICS TextInfo;
			TextLayout->GetMetrics(&TextInfo);
			Vector2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
			if (outline) {
				const auto x = pos.x - TextSize.x;
				const auto y = pos.y - TextSize.y;
				Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
			}
			SolidColor->SetColor(color);
			Canvas->DrawTextLayout({ pos.x - TextSize.x, pos.y - TextSize.y }, TextLayout, SolidColor);
			TextLayout->Release();
			return TextSize;
		}
		
		IDWriteTextLayout* TextLayout;
		TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 500.f, 100.f, &TextLayout);
		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		if (outline) {
			const auto x = pos.x;
			const auto y = pos.y;
			Canvas->DrawTextW(text, wcslen(text), TextFormat, { pos.x - 1, pos.y, FLT_MAX, FLT_MAX }, SolidColor);
			Canvas->DrawTextW(text, wcslen(text), TextFormat, { pos.x + 1, pos.y, FLT_MAX, FLT_MAX }, SolidColor);
			Canvas->DrawTextW(text, wcslen(text), TextFormat, { pos.x, pos.y - 1, FLT_MAX, FLT_MAX }, SolidColor);
			Canvas->DrawTextW(text, wcslen(text), TextFormat, { pos.x, pos.y + 1, FLT_MAX, FLT_MAX }, SolidColor);
		}
		SolidColor->SetColor(color);
		Canvas->DrawTextW(text, wcslen(text), TextFormat, { pos.x, pos.y, FLT_MAX, FLT_MAX }, SolidColor);
		TextLayout->Release();
		return { 0,0 };
	}
}
