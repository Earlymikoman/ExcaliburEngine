#pragma once

#include "../Core/Enums/DrawMode.h"

// D3D11 header
#include <d3d11.h>
// DirectX math, used for creating view matrices and matrix math operations
#include <DirectXMath.h>
// Microsoft's WIC texture loader for D3D11
#include "WICTextureLoader11.h"
// Header files created when compiling .hlsl files
#include "PShader.h"
#include "PTexShader.h"
#include "VShader.h"

// D3D lib files
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
// Lib used for the WIC texture loader
#pragma comment(lib, "windowscodecs.lib")

#include <Windows.h>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::wstring;

class Mesh;
class Texture;

template<unsigned int Dimensions>
class Vector;

// Data used for each vertex in a mesh
// This must match the "vs_in" struct in the vertex shader
typedef struct VertexData
{
	VertexData() {}
	VertexData(float posX, float posY, float R, float G, float B, float A, float texU, float texV)
	{
		Position[0] = posX;
		Position[1] = posY;
		Color[0] = R;
		Color[1] = G;
		Color[2] = B;
		Color[3] = A;
		TexCoord[0] = texU;
		TexCoord[1] = texV;
	}

	float Position[2] = { 0 };      // Position data for the X and Y coordinates of the vertex
	float Color[4] = { 0 };         // Color data in RGBA 0.0-1.0 formatc
	float TexCoord[2] = { 0 };      // U and V texture coordinates for this vertex
} VertexData;

// Data used for the constant buffer which is accessed by the vertex shader
// This must match the "cbuffer" definition in the vertex shader 
struct cbPerObject
{
	float WorldMatrix[4][4];    // The world view projection matrix used to translate the mesh's world position
	// into the screen coordinates needed for display
	float Scale[2];             // The X and Y scale to apply to the mesh
	float TexOffset[2];         // The texture offset values used to adjust the mesh's texture coordinates
	float Rotation[4][4];       // The rotation matrix to apply to the mesh
	float Position[2];          // The X and Y coordinates of the mesh's position in the world
	float Alpha;                // An alpha value to modify the transparency with
	float padding;              // The size of the constant buffer must be a multiple of 16
	// This variable is unused but required to match the size restriction
};

//template <typename Platform>
class DirectXData
{
private:

	DirectXData(/*HWND windowHandle*/) = default;

public:

	DirectXData(DirectXData const& rhs) = delete;

	DirectXData& operator=(DirectXData const& rhs) = delete;

	static DirectXData* GetInstance();

	static bool InitializeGraphics();

	static void ShutDownGraphics();

	static void StartDrawing();

	static void Draw(Mesh const* MeshToDraw, DrawMode const& Mode);

	static void FinishDrawing();

	static void ScreenToWorld(float screenX, float screenY, float* worldX, float* worldY);

	static bool UpdateWorldView();

	static Texture* LoadTexture(string const& fileName);

	static void SetTexture(Texture const* texture);

	static void SetScale(Vector<3> const& Scale);

	static void SetPosition(Vector<3> const& Position);
	//void SetPosition(Vector<3> const& Position);

	static void SetWindow(HWND const& windowHandle) { WindowHandle = windowHandle; }

private:

	static HWND WindowHandle;

	// Device, used to create resources
	static ID3D11Device* Device;
	// Device context, an interface with rendering commands
	static ID3D11DeviceContext* DeviceContext;
	// Swap chain, hold the buffers for storing rendered data before presenting it to the output
	static IDXGISwapChain* SwapChain;
	// Render target view
	static ID3D11RenderTargetView* RenderTargetView;
	// Vertex shader resource
	static ID3D11VertexShader* VertexShader;
	// Pixel shader resource for drawing without textures
	static ID3D11PixelShader* PixelShader;
	// Pixel shader resource for drawing with textures
	static ID3D11PixelShader* PixelTextureShader;
	// Input layout, the definition of how data is given to the vertex shader
	static ID3D11InputLayout* InputLayout;
	// Constant buffer resource
	static ID3D11Buffer* PerObjectBuffer;
	// Blend state, which controls how colors from multiple meshes are blended together
	static ID3D11BlendState* BlendState;
	// Sampler state, which controls how a texture is sampled
	static ID3D11SamplerState* SamplerState;
	// Vertex buffer resource for a single mesh
	static ID3D11Buffer* VertexBuffer;
	// Texture resource for a single texture
	static ID3D11Texture2D* Texture;
	// Texture resource view for a single texture
	static ID3D11ShaderResourceView* TexResourceView;

	// Other variables

	// The stored view matrix
	static DirectX::XMMATRIX ViewMatrix;
	// The stored projection matrix
	static DirectX::XMMATRIX ProjectionMatrix;
	// Current camera position
	static float CameraPosition[3];
	// Data for the constant buffer
	static cbPerObject ConstantBuffer;

};
