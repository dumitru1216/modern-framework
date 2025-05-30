#include "main.hh"

void                ResetDevice( );
void                CleanupDeviceD3D( );
BOOL                CreateDeviceD3D( HWND );
void                SetupRenderStates( std::function< void( ) > ); /* Thanks ImGui */
ATOM                MyRegisterClass( HINSTANCE, LPCTSTR );
BOOL                InitWindow( HINSTANCE, LPCTSTR, LPCTSTR );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );

// this is a dogshit i coded, it contains awfull code
void draw_magnified_rect(int x, int y, int width, int height, math_wraper::c_color color, int rounding, float magnification_factor, math_wraper::c_vector_2d mouse_position) {
	float magnification_range = 30.0f;

	ImVec2 top_left(x, y);
	ImVec2 top_right(x + width, y);
	ImVec2 bottom_left(x, y + height);
	ImVec2 bottom_right(x + width, y + height);

	auto magnify_corner = [&](ImVec2 corner) -> ImVec2 {
		float distance = sqrt(pow(mouse_position.x - corner.x, 2) + pow(mouse_position.y - corner.y, 2));
		if (distance < magnification_range) {
			float factor = 1.0f + (magnification_factor - 1.0f) * (1.0f - distance / magnification_range);
			return ImVec2(corner.x + (corner.x - mouse_position.x) * (factor - 1.0f), corner.y + (corner.y - mouse_position.y) * (factor - 1.0f));
		}
		return corner;
	};

	top_left = magnify_corner(top_left);
	top_right = magnify_corner(top_right);
	bottom_left = magnify_corner(bottom_left);
	bottom_right = magnify_corner(bottom_right);

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	draw_list->AddQuadFilled(top_left, top_right, bottom_right, bottom_left, color.transform());
}

int main( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	/* Hide console window */
	ShowWindow( GetConsoleWindow( ), SW_SHOW );

	/* Register main class */
	LPCTSTR lpzClass = "modern-framework";
	if ( !MyRegisterClass( hInstance, lpzClass ) ) {
		return 0;
	}

	/* Initialize our main window */
	if ( !InitWindow( hInstance, lpzClass, "modern-framework" ) ) {
		return 0;
	}

	/* Create our D3D9 Device */
	if ( !CreateDeviceD3D( g_pWindow ) ) {
		CleanupDeviceD3D( );
		UnregisterClass( lpzClass, hInstance );
		return 0;
	}

	/* Show window */
	ShowWindow( g_pWindow, SW_SHOWDEFAULT );
	UpdateWindow( g_pWindow );

	framework::draw->initialize(g_pd3dDevice, g_pWindow);

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	while ( msg.message != WM_QUIT ) {

		if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
			continue;
		}

		ImGui_ImplDX9_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );
		{
			framework::globals::m_draw_list = ImGui::GetBackgroundDrawList();

			// font testing
			// framework::fonts->font_awesome.draw(10, 10, ICON_FA_USER, math_wraper::c_color());
			framework::fonts->menu_default.draw(100, 100, "This is a basic text!", math_wraper::c_color());
			framework::fonts->menu_default.draw(100, 120, "This is an outlined text!", math_wraper::c_color(), framework::modifiers::font_flags::outline);
			framework::fonts->menu_default.draw(100, 140, "This is a dropshadow test text!", math_wraper::c_color(), framework::modifiers::font_flags::drop_shadow);
			framework::fonts->menu_default.draw(100, 160, "This is a dropshadow", math_wraper::c_color(), framework::modifiers::font_flags::drop_shadow,
				framework::modifiers::default_shadow, true, "double layered test text", math_wraper::c_color(255, 0, 0));
			framework::fonts->menu_default.draw(100, 180, "This is a outlined", math_wraper::c_color(), framework::modifiers::font_flags::outline,
				framework::modifiers::default_shadow, true, "double layered test text", math_wraper::c_color(255, 0, 0));

			framework::container->run();
		}
		ImGui::EndFrame( );

		/* Rendering */
		g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, false );
		g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
		g_pd3dDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, false );
		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 30, 30, 30, 0 ), 1.0f, 0 );

		if ( g_pd3dDevice->BeginScene( ) >= 0 )
		{
			SetupRenderStates( [=]( ) {
				ImGui::Render( );
				ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
			} );

			/* UNLOAD Key */
			if ( GetAsyncKeyState( VK_END ) ) {
				ExitProcess( -1 );
			}

			g_pd3dDevice->EndScene( );
		}

		/* Handle loss of D3D9 device */
		HRESULT result = g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
		if ( result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET )
			ResetDevice( );

	}

	/* Release D3D9 Device */
	CleanupDeviceD3D( );

	/* Unregister class */
	DestroyWindow( g_pWindow );
	UnregisterClass( lpzClass, hInstance );

	return 0;
}


void ResetDevice( )
{
	HRESULT hr = g_pd3dDevice->Reset( &g_d3dpp );
	if ( hr != D3DERR_INVALIDCALL ) {
	}
}

void CleanupDeviceD3D( )
{
	if ( g_pd3dDevice ) {
		g_pd3dDevice->Release( );
		g_pd3dDevice = NULL;
	}

	if ( g_pD3D ) {
		g_pD3D->Release( );
		g_pD3D = NULL;
	}
}

BOOL CreateDeviceD3D( HWND hWnd )
{
	if ( ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL )
		return FALSE;

	/* Create the D3DDevice */
	ZeroMemory( &g_d3dpp, sizeof( g_d3dpp ) );
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; /* Present with vsync */
	if ( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice ) < 0 )
		return FALSE;

	return TRUE;
}

void SetupRenderStates( std::function< void( ) > func ) {

	/* Backup the DX9 state */
	IDirect3DStateBlock9* d3d9_state_block = NULL;
	if ( g_pd3dDevice->CreateStateBlock( D3DSBT_ALL, &d3d9_state_block ) < 0 )
		return;

	/* Get Client DisplaySize */
	RECT rect;
	GetClientRect( g_pWindow, &rect );
	math_wraper::c_vector_2d DisplaySize = math_wraper::c_vector_2d( ( float )( rect.right - rect.left ), ( float )( rect.bottom - rect.top ) );

	g_pd3dDevice->SetPixelShader( NULL );
	g_pd3dDevice->SetVertexShader( NULL );
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, false );
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, false );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, false );
	g_pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_SCISSORTESTENABLE, true );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	/* Setup viewport */
	D3DVIEWPORT9 vp;
	vp.X = vp.Y = 0;
	vp.Width = ( DWORD )DisplaySize.x;
	vp.Height = ( DWORD )DisplaySize.y;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	g_pd3dDevice->SetViewport( &vp );

	/* Setup orthographic projection matrix */ {
		const float L = 0.5f, R = DisplaySize.x + 0.5f, T = 0.5f, B = DisplaySize.y + 0.5f;
		D3DMATRIX mat_identity = { { 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f } };
		D3DMATRIX mat_projection =
		{
			2.0f / ( R - L ),   0.0f,         0.0f,  0.0f,
			0.0f,         2.0f / ( T - B ),   0.0f,  0.0f,
			0.0f,         0.0f,         0.5f,  0.0f,
			( L + R ) / ( L - R ),  ( T + B ) / ( B - T ),  0.5f,  1.0f,
		};
		g_pd3dDevice->SetTransform( D3DTS_WORLD, &mat_identity );
		g_pd3dDevice->SetTransform( D3DTS_VIEW, &mat_identity );
		g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &mat_projection );
	}

	func( );

	/* Restore the DX9 state */
	d3d9_state_block->Apply( );
	d3d9_state_block->Release( );
}

ATOM MyRegisterClass( HINSTANCE hInstance, LPCTSTR ClassName )
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_GUITEST ) );
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = MAKEINTRESOURCE( IDC_GUITEST );
	wcex.lpszClassName = ClassName;
	wcex.hIconSm = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	return RegisterClassEx( &wcex );
}

BOOL InitWindow( HINSTANCE hInstance, LPCTSTR ClassName, LPCTSTR Title )
{
	/* get position on screen */
	RECT screen_rect;
	GetWindowRect( GetDesktopWindow( ), &screen_rect );

	/* on the whole screen */
	g_pWindow = CreateWindowEx( WS_EX_APPWINDOW, ClassName, Title, WS_POPUP, screen_rect.left, screen_rect.top, screen_rect.right /* width */, screen_rect.bottom /* height */, NULL, NULL, hInstance, NULL );

	if ( !g_pWindow ) {
		return FALSE;
	}

	return TRUE;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp )
{
	if ( ImGui_ImplWin32_WndProcHandler( hwnd, msg, wp, lp ) )
		return true;

	return DefWindowProcA( hwnd, msg, wp, lp );
}