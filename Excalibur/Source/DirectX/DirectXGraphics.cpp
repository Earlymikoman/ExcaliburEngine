
// Basic Windows include
#define WIN32_LEAN_AND_MEAN

#include "DirectXGraphics.h"

#include "../Core/Mesh.h"
#include "../Core/Texture.h"
#include "../../../SharedDependencies/Source/Vector.h"
#include "../../../SharedDependencies/Source/CustomStringFunctions.h"
//#include "../Core/Enums.h"

// *** Object definitions *************************************************************************

// *** Variable definitions ***********************************************************************

// The handle of the application window
// = nullptr;

// D3D objects that must be stored for the life of the program and then released

#pragma region DirectXData Static Field Initialization

HWND DirectXData::WindowHandle = 0;

// Device, used to create resources
ID3D11Device* DirectXData::Device = nullptr;
// Device context, an interface with rendering commands
ID3D11DeviceContext* DirectXData::DeviceContext = nullptr;
// Swap chain, hold the buffers for storing rendered data before presenting it to the output
IDXGISwapChain* DirectXData::SwapChain = nullptr;
// Render target view
ID3D11RenderTargetView* DirectXData::RenderTargetView = nullptr;
// Vertex shader resource
ID3D11VertexShader* DirectXData::VertexShader = nullptr;
// Pixel shader resource for drawing without textures
ID3D11PixelShader* DirectXData::PixelShader = nullptr;
// Pixel shader resource for drawing with textures
ID3D11PixelShader* DirectXData::PixelTextureShader = nullptr;
// Input layout, the definition of how data is given to the vertex shader
ID3D11InputLayout* DirectXData::InputLayout = nullptr;
// Constant buffer resource
ID3D11Buffer* DirectXData::PerObjectBuffer = nullptr;
// Blend state, which controls how colors from multiple meshes are blended together
ID3D11BlendState* DirectXData::BlendState = nullptr;
// Sampler state, which controls how a texture is sampled
ID3D11SamplerState* DirectXData::SamplerState = nullptr;
// Vertex buffer resource for a single mesh
ID3D11Buffer* DirectXData::VertexBuffer = nullptr;
// Texture resource for a single texture
ID3D11Texture2D* DirectXData::Texture = nullptr;
// Texture resource view for a single texture
ID3D11ShaderResourceView* DirectXData::TexResourceView = nullptr;

// Other variables

// The stored view matrix
DirectX::XMMATRIX DirectXData::ViewMatrix = DirectX::XMMatrixIdentity();
// The stored projection matrix
DirectX::XMMATRIX DirectXData::ProjectionMatrix = DirectX::XMMatrixIdentity();
// Current camera position
float DirectXData::CameraPosition[] = { 0.0f, 0.0f, -10.f };
// Data for the constant buffer
cbPerObject DirectXData::ConstantBuffer;

#pragma endregion

// *** Function declarations **********************************************************************

//DirectXData::DirectXData(HWND windowHandle)
//{
//	DirectXData::WindowHandle = windowHandle;
//	ViewMatrix = DirectX::XMMatrixIdentity();
//	ProjectionMatrix = DirectX::XMMatrixIdentity();
//
//	InitializeGraphics();
//}

//DirectXData* DirectXData::GetInstance()
//{
//	static DirectXData instance = DirectXData();
//
//	return &instance;
//}

bool DirectXData::UpdateWorldView()
{
	// Get the window size from the window itself (this will account for title bar, borders, etc.)
	RECT rect;
	GetClientRect(WindowHandle, &rect);
	float windowWidth = (float)(rect.right - rect.left);
	float windowHeight = (float)(rect.bottom - rect.top);

	// The eye position is the camera position
	DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(CameraPosition[0], CameraPosition[1], CameraPosition[2], 0.0f);
	// The focus position is the camera position, with Z being 0
	DirectX::XMVECTOR focusPosition = DirectX::XMVectorSet(CameraPosition[0], CameraPosition[1], 0.0f, 0.0f);
	// The up direction is a unit vector with a positive Y value
	DirectX::XMVECTOR upDirection = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Create a view matrix with the eye position, focus position, and up direction and save it
	ViewMatrix = DirectX::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	// Create an orthographic projection matrix and save it
	ProjectionMatrix = DirectX::XMMatrixOrthographicOffCenterLH(
		CameraPosition[0] - (windowWidth * 0.5f),   // Left edge (camera X minus half window width)
		CameraPosition[0] + (windowWidth * 0.5f),   // Right edge (camera X plus half window width)
		CameraPosition[1] - (windowHeight * 0.5f),  // Bottom edge (camera Y minus half window height)
		CameraPosition[1] + (windowHeight * 0.5f),  // Top edge (camera Y plus half window height)
		1.0f,                                       // Minimum Z
		1000.0f                                     // Maximum Z
	);

	// Save the world matrix as the transpose of view * projection in a temporary DirectX vector
	DirectX::XMFLOAT4X4 tempVector;
	DirectX::XMStoreFloat4x4(&tempVector, DirectX::XMMatrixTranspose(ViewMatrix * ProjectionMatrix));

	// Copy the data into the world view projection matrix in the constant buffer
	memcpy(ConstantBuffer.WorldMatrix, tempVector.m, sizeof(float) * 16);

	// Set the input layout
	DeviceContext->IASetInputLayout(InputLayout);
	// Set the render target
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, NULL);

	// Everything succeeded, return true
	return true;
}

bool DirectXData::InitializeGraphics()
{
    // Initializes the COM library for use by the calling thread, sets the thread's concurrency model,
    // and creates a new apartment for the thread
    (void)CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    // *******************************************************************************************
    // Create the D3D device
    // *******************************************************************************************

    // Save the flags we want to use
    UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
    // If in debug mode, add the debug flag
#if defined(DEBUG) || defined(_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // Create swap chain description struct and set the memory to zero
    DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = WindowHandle;
    swapChainDesc.Windowed = true;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    // Create the D3D device and swap chain
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        NULL,                       // Optional pointer to a video adapter
        D3D_DRIVER_TYPE_HARDWARE,   // Use a hardware-based renderer
        NULL,                       // Optional handle to a software rasterizer
        flags,                      // The flags variable
        NULL,                       // Use the default feature levels
        0,                          // Number of elements in the previous parameter
        D3D11_SDK_VERSION,          // SDK version to use
        &swapChainDesc,             // Adddress of the struct you just created
        &SwapChain,                 // Address of the swap chain resource variable
        &Device,                    // Address of the device resource variable
        nullptr,                    // Optional parameter to check the feature level
        &DeviceContext              // Address of the device context resource variable
    );
    // Check if there was an error
    if (FAILED(hr))
    {
        // Assert for debugging
        assert(false);
        // Return false to indicate something went wrong
        return false;
    }


    // *******************************************************************************************
    // Intialize the shaders
    // *******************************************************************************************

    // Create the vertex shader from the compiled header
    hr = Device->CreateVertexShader(
        gVShader,           // Variable for the compiled shader
        sizeof(gVShader),   // Size of the shader
        nullptr,            // Optional parameter
        &VertexShader       // Address of the shader resource variable
    );
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    // Create the pixel shader to use without textures from the compiled header
    hr = Device->CreatePixelShader(
        gPShader,
        sizeof(gPShader),
        nullptr,
        &PixelShader
    );
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    // Create the pixel shader to use with textures from the compiled header
    hr = Device->CreatePixelShader(
        gPTexShader,
        sizeof(gPTexShader),
        nullptr,
        &PixelTextureShader
    );
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    // Set the shaders on the device context
    DeviceContext->VSSetShader(VertexShader, NULL, 0);
    DeviceContext->PSSetShader(PixelTextureShader, NULL, 0);

    // Create an array of input element description structs
    // This has to match the data in the vertex struct
    D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    // Create and save the input layout
    hr = Device->CreateInputLayout(
        inputElementDesc,               // The array of structs
        ARRAYSIZE(inputElementDesc),    // The size of the array
        gVShader,                       // The compiled vertex shader
        sizeof(gVShader),               // The size of the shader
        &InputLayout                    // The address of the input layout resource variable
    );
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }


    // *******************************************************************************************
    // Create the render target
    // *******************************************************************************************

    // Create a temporary variable to store the frame buffer
    ID3D11Texture2D* frameBuffer;
    // Get the first buffer from the swap chain
    hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&frameBuffer);
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    // Create a render target view description struct and set the memory to zero
    D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
    ZeroMemory(&rtDesc, sizeof(rtDesc));
    rtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;             // The data format to use
    rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;   // Which view dimension to use
    // Create and save the render target view
    hr = Device->CreateRenderTargetView(frameBuffer, &rtDesc, &RenderTargetView);
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    // Release the frame buffer
    frameBuffer->Release();


    // *******************************************************************************************
    // Create the blend state
    // *******************************************************************************************

    // Create a render target blend description struct and set the memory to zero
    D3D11_RENDER_TARGET_BLEND_DESC rtbd = { 0 };
    // The following settings will result in normal transparency
    rtbd.BlendEnable = true;                        // Enable blending
    rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;          // Use alpha from the pixel shader output to blend
    rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;     // Use 1-alpha on the current value in the render target
    rtbd.BlendOp = D3D11_BLEND_OP_ADD;              // Use addition for the blend operation
    rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;           // Blend operation on the pixel shader output alpha
    rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;         // Blend operation on the render target current alpha
    rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;         // Use addition for the alpha blend
    rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    // Create a blend descriptor struct and set the memory to zero
    D3D11_BLEND_DESC blendDesc = { 0 };
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.RenderTarget[0] = rtbd;

    // Create and save the blend state
    hr = Device->CreateBlendState(&blendDesc, &BlendState);
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    // Set the blend state on the device context
    DeviceContext->OMSetBlendState(BlendState, NULL, 0xffffffff);


    // *******************************************************************************************
    // Create the constant buffer
    // *******************************************************************************************

    // Create a constant buffer descriptor struct and set the memory to zero
    D3D11_BUFFER_DESC cbBufferDesc = { 0 };
    cbBufferDesc.Usage = D3D11_USAGE_DEFAULT;               // Default usage
    cbBufferDesc.ByteWidth = sizeof(cbPerObject);           // Size of the constant buffer
    cbBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;    // Bind as a constant buffer

    // Create and save the constant buffer resource
    hr = Device->CreateBuffer(&cbBufferDesc, NULL, &PerObjectBuffer);
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    // Initialize the data to zero on the constant buffer variable
    memset(&ConstantBuffer, 0, sizeof(cbPerObject));
    // Set the world matrix to identity
    ConstantBuffer.WorldMatrix[0][0] = 1;
    ConstantBuffer.WorldMatrix[1][1] = 1;
    ConstantBuffer.WorldMatrix[2][2] = 1;
    ConstantBuffer.WorldMatrix[3][3] = 1;
    // Set the rotation matrix to identity
    ConstantBuffer.Rotation[0][0] = 1;
    ConstantBuffer.Rotation[1][1] = 1;
    ConstantBuffer.Rotation[2][2] = 1;
    ConstantBuffer.Rotation[3][3] = 1;
    // Set the alpha to 1
    ConstantBuffer.Alpha = 1.0f;


    // *******************************************************************************************
    // Create the sampler
    // *******************************************************************************************

    // Create a sampler description struct and set the memory to zero
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    // The following settings will create a sampler with linear filtering and clamping the texture
    // Other common settings are point filtering and wrapping or mirroring the texture
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    // Create and save the sampler state
    hr = Device->CreateSamplerState(&sampDesc, &SamplerState);
    // Check if there was an error, assert for debugging and return false to indicate an error
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    // Set the sampler state on the device context
    DeviceContext->PSSetSamplers(0, 1, &SamplerState);


    // *******************************************************************************************
    // Set the viewport
    // *******************************************************************************************

    // Get the rect data for this window
    RECT winRect;
    GetClientRect(WindowHandle, &winRect);

    // Create a viewport struct and set the memory to zero
    D3D11_VIEWPORT viewport = { 0 };
    viewport.Height = (float)(winRect.bottom - winRect.top);
    viewport.Width = (float)(winRect.right - winRect.left);
    viewport.MaxDepth = 1.0f;

    // Set the viewport on the device context
    DeviceContext->RSSetViewports(1, &viewport);


    // *******************************************************************************************
    // Create a mesh
    // *******************************************************************************************

    //// Create six vertices for a square mesh
    //VertexList[0] = VertexData(-0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 0.0f, 1.0f);
    //VertexList[1] = VertexData(-0.5f, 0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 0.0f, 0.0f);
    //VertexList[2] = VertexData(0.5f, 0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 1.0f, 0.0f);
    //VertexList[3] = VertexData(-0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 0.0f, 1.0f);
    //VertexList[4] = VertexData(0.5f, 0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 1.0f, 0.0f);
    //VertexList[5] = VertexData(0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 1.0f, 1.0f);

    //// Create a vertex buffer description struct and set the memory to zero
    //D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
    //vertexBufferDesc.ByteWidth = sizeof(VertexData) * VertexCount;  // The size of all the vertex data
    //vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;                   // Default usage
    //vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;          // Bind as a vertex buffer

    //// Create a subresource data struct and set the memory to zero
    //D3D11_SUBRESOURCE_DATA srData = { 0 };
    //srData.pSysMem = VertexList.data();    // The array of vertex data

    //// Create and save the vertex buffer resource
    //hr = Device->CreateBuffer(
    //    &vertexBufferDesc,      // The address of the description struct
    //    &srData,                // The address of the subresource struct
    //    &VertexBuffer           // The address of the vertex buffer resource variable
    //);
    //// Check if there was an error, assert for debugging and return false to indicate an error
    //if (FAILED(hr))
    //{
    //    assert(false);
    //    return false;
    //}


    // *******************************************************************************************
    // Load a texture
    // *******************************************************************************************

	/*::Texture* balltexture = LoadTexture(L"Assets/Ball.png");
	::Texture* milktexture = LoadTexture(L"Assets/Milk.png");
	SetTexture(balltexture);
	SetTexture(milktexture);
	SetTexture(balltexture);*/

    // *******************************************************************************************
    // Update the world view
    // NOTE: This must be re-done every time the camera position or window size changes
    // *******************************************************************************************

	return UpdateWorldView();
}

void DirectXData::ShutDownGraphics()
{
    // Release all D3D objects if they exist

    if (VertexBuffer) VertexBuffer->Release();
    if (Texture) Texture->Release();
    if (TexResourceView) TexResourceView->Release();
    if (SamplerState) SamplerState->Release();
    if (BlendState) BlendState->Release();
    if (PerObjectBuffer) PerObjectBuffer->Release();
    if (InputLayout) InputLayout->Release();
    if (PixelTextureShader) PixelTextureShader->Release();
    if (PixelShader) PixelShader->Release();
    if (VertexShader) VertexShader->Release();
    if (RenderTargetView) RenderTargetView->Release();
    if (SwapChain) SwapChain->Release();
    if (DeviceContext) DeviceContext->Release();
    if (Device) Device->Release();

    CoUninitialize();
}

void DirectXData::StartDrawing()
{
	// Clear the render target with the background color
	/*float backgroundColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	DeviceContext->ClearRenderTargetView(RenderTargetView, backgroundColor);*/
	// Set the input layout
	DeviceContext->IASetInputLayout(InputLayout);
	// Set the render target
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, NULL);
}

void DirectXData::Draw(Mesh const* MeshToDraw, DrawMode const& Mode)
{
	// Clear the render target with the background color
	//float backgroundColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	//DeviceContext->ClearRenderTargetView(RenderTargetView, backgroundColor);
	//// Set the input layout
	//DeviceContext->IASetInputLayout(InputLayout);
	//// Set the render target
	//DeviceContext->OMSetRenderTargets(1, &RenderTargetView, NULL);

	HRESULT hr;

	// Create a vertex buffer description struct and set the memory to zero
	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(VertexData) * (UINT)MeshToDraw->GetVertices().size();  // The size of all the vertex data
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;                   // Default usage
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;          // Bind as a vertex buffer

	// Create a subresource data struct and set the memory to zero
	D3D11_SUBRESOURCE_DATA srData = { 0 };
	srData.pSysMem = MeshToDraw->GetVertices().data();    // The array of vertex data

	// Create and save the vertex buffer resource
	hr = Device->CreateBuffer(
	    &vertexBufferDesc,      // The address of the description struct
	    &srData,                // The address of the subresource struct
	    &VertexBuffer           // The address of the vertex buffer resource variable
	);
	// Check if there was an error, assert for debugging and return false to indicate an error
	if (FAILED(hr))
	{
	    assert(false);
	    //return false;
	}

    // *******************************************************************************************
    // Draw the mesh without a texture
    // *******************************************************************************************
 
    // Set the primitive topology for this mesh 
    // See the D3D_PRIMITIVE_TOPOLOGY enum for all options
    // The most common are:
    //      D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST 
    //      D3D11_PRIMITIVE_TOPOLOGY_LINELIST 
    //      D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP
    //      D3D11_PRIMITIVE_TOPOLOGY_POINTLIST  
    //      D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
    DeviceContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)MeshToDraw->GetMeshType());

    // Set the vertex buffer for this mesh
    UINT vertex_stride = sizeof(VertexData);
    UINT vertex_offset = 0;
    DeviceContext->IASetVertexBuffers(
        0,                  // The starting index
        1,                  // The number of vertex buffers
        &VertexBuffer,      // The address of the vertex buffer resource variable
        &vertex_stride,     // The address of a UINT with the size of each vertex data
        &vertex_offset      // The address of a UNIT with the size of the vertex offset
    );

    // Update the constant buffer resource
    DeviceContext->UpdateSubresource(PerObjectBuffer, 0, NULL, &ConstantBuffer, 0, 0);
    // Set the constant buffer
    DeviceContext->VSSetConstantBuffers(0, 1, &PerObjectBuffer);

    // Set the texture resource for the shader
    DeviceContext->PSSetShaderResources(0, 1, &TexResourceView);

	//Determine way in which to draw mesh (ex: texture vs no texture)
	switch (Mode)
	{
	case DrawMode::PIXEL:
	{
		DeviceContext->PSSetShader(PixelShader, NULL, 0);

		break;
	}

	case DrawMode::TEXTURE:
	{
		DeviceContext->PSSetShader(PixelTextureShader, NULL, 0);

		break;
	}
	}

	// Draw the current data, passing in the number of vertices to draw
	DeviceContext->Draw((UINT)MeshToDraw->GetVertices().size(), 0);

    // *******************************************************************************************
    // Finish the drawing pass
    // *******************************************************************************************
    
    // Send the current render data to be displayed
    /*SwapChain->Present(1, 0);*/
}

void DirectXData::FinishDrawing()
{
	SwapChain->Present(1, 0);
}

void DirectXData::ScreenToWorld(float screenX, float screenY, float* worldX, float* worldY)
{
    // Get the window size from the window itself (this will account for title bar, borders, etc.)
    RECT rect;
    GetClientRect(WindowHandle, &rect);
    float windowWidth = (float)(rect.right - rect.left);
    float windowHeight = (float)(rect.bottom - rect.top);

    // Get the determinant of the view matrix * projection matrix
    DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(ViewMatrix * ProjectionMatrix);
    // Get the inverse of the view matrix * projection matrix
    DirectX::XMMATRIX invProjView = DirectX::XMMatrixInverse(&det, (ViewMatrix * ProjectionMatrix));

    // Adjust the screen position
    DirectX::XMVECTOR adjScreenPos = DirectX::XMVectorSet(
        ((2.0f * screenX) / windowWidth) - 1,
        -(((2.0f * screenY) / windowHeight) - 1),
        1.0f, 0.0f);

    // Multiply the adjusted screen position by the inverse projection view matrix
    DirectX::XMFLOAT4 transformedPos;
    DirectX::XMStoreFloat4(&transformedPos, DirectX::XMVector3Transform(adjScreenPos, invProjView));

    *worldX = transformedPos.x;
    *worldY = transformedPos.y;
}

::Texture* DirectXData::LoadTexture(string const& Name)
{
	HRESULT hr;

	// Create a temporary variable to store the resource pointer
	ID3D11Resource* temp;

	string fileName = string(TEXTURES_PATH) + Name;

	// Create the texture using the WIC texture loader
	hr = DirectX::CreateWICTextureFromFile(
		Device,             // The device resource variable
		(const wchar_t*)wstring(fileName.begin(), fileName.end()).c_str(),        // The path to the texture file
		&temp,              // The address of the temporary resource pointer 
		&TexResourceView    // The address of the texture resource view resource variable
	);
	// Check if there was an error, assert for debugging and return false to indicate an error
	if (FAILED(hr))
	{
		assert(nullptr && "Failed to load texture by filename. Check DirectXGraphics.cpp/LoadTexture().");
		return nullptr;
	}

	// Save the texture in the texture resource variable
	//Texture = (ID3D11Texture2D*)temp;

	return new ::Texture(Name, temp, TexResourceView);
}

void DirectXData::SetTexture(::Texture const* texture)
{
	//Texture = (ID3D11Texture2D*)texture->GetResource();//TODO: Verify whether this is necessary or not.
	TexResourceView = texture->GetResourceView();
}

void DirectXData::SetScale(Vector<3> const& Scale)
{
	ConstantBuffer.Scale[0] = Scale.X();
	ConstantBuffer.Scale[1] = Scale.Y();
}

void DirectXData::SetPosition(Vector<3> const& Position)
{
	ConstantBuffer.Position[0] = Position.X();
	ConstantBuffer.Position[1] = Position.Y();
}


