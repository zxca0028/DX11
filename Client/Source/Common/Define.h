#pragma once
#pragma warning(disable : 4005 4819 4101 4305 4996 4715 26498)

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Dxgi.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

namespace CLIENT
{
#define DIRECTINPUT_VERSION 0x0800

#define PI 3.14159f
#define ToRadian(degree) degree * PI / 180.f

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define New DBG_NEW
#endif
#endif

	using byte = char;
	using i8   = char;
	using i16  = short;
	using i32  = int;
	using i64  = long long;
	using u8   = unsigned char;
	using u16  = unsigned short;
	using u32  = unsigned int;
	using u64  = unsigned long long;
	using f32  = float;
	using f64  = double;

	template<class T>
	using vector = std::vector<T>;
	template<class T>
	using stack = std::stack<T>;
	template<class T>
	using queue = std::queue<T>;

	template<class T>
	using SortedSet = std::set<T>;
	template<class T>
	using Hashset = std::unordered_set<T>;
	template<class Key, class Value>
	using SortedDictionary = std::map<Key, Value>;
	template<class Key, class Value>
	using Dictionary = std::unordered_map<Key, Value>;

	template<class T>
	using UniquePtr = std::unique_ptr<T>;
	template<class T>
	using SharedPtr = std::shared_ptr<T>;
	template<class T>
	using WeakPtr   = std::weak_ptr<T>;

	template<class T, class ...Args>
	UniquePtr<T> CreateUniquePtr(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<class T, class ...Args>
	SharedPtr<T> CreateSharedPtr(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	using string  = std::string;
	using wstring = std::wstring;

	extern HINSTANCE ghInst;
	extern HWND      ghWnd;
	extern i32       gScreenWidth;
	extern i32       gScreenHeight;
}