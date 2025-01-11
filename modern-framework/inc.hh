#pragma once

// basic includes
#include <windows.h>
#include <windowsx.h>
#include <memory>
#include <sstream>
#include <iostream>
#include <functional>
#include <WinUser.h>
#include <string_view>
#include <map>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <deque>
#include <mutex>
#include <optional>

// resource data
#define IDS_APP_TITLE 103
#define IDR_MAINFRAME 128
#define IDD_GUITEST_DIALOG 102
#define IDD_ABOUTBOX 103
#define IDM_ABOUT 104
#define IDM_EXIT 105
#define IDI_GUITEST 107
#define IDI_SMALL 108
#define IDC_GUITEST 109
#define IDC_MYICON 2
#ifndef IDC_STATIC
#define IDC_STATIC -1
#endif

// directx includes
#include <d3d9.h>
#include <d3dx9.h>

// needed libs
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "freetype.lib")

// if i were to make this a year ago i would pragma disable the warnings
// but i learnt that you can disable them from the project settings, so i wont do that anymore

// imgui includes
#include "deps/imgui/imgui.h"
#include "deps/imgui/imgui_impl_dx9.h"
#include "deps/imgui/imgui_internal.h"
#include "deps/imgui/imgui_impl_win32.h"
#include "deps/imgui/imgui_freetype.h"

#include "utils/math.hh"