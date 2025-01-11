#pragma once

// include the main
#include "inc.hh"

// static vars we are going to use in main.cc
static LPDIRECT3D9 g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS g_d3dpp = {};
static HWND g_pWindow;