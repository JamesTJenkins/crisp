workspace "Crisp"
	architecture "x64"
	startproject "Game"
	
	-- Configuration Settings --
		
	configurations {
		"Debug",
		"Release",
		"Distribution"	-- Distribution is alike release but more heavily stripped --
	}
		
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"	
	
	include "premake5-SDL.lua"
	include "premake5-SDLmain.lua"
	include "premake5-GLAD.lua"
	include "premake5-imgui.lua"
	
	project "Crisp"
		location "Crisp"
		kind "SharedLib"
		language "C++"
		staticruntime "Off"
		
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("build/" .. outputdir .. "/%{prj.name}")
		
		pchheader "CrispPCH.h"
		-- PCH source is needed for vs studio, will be ingnored by other platforms --
		pchsource "Crisp/src/CrispPCH.cpp"
	
		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.c",
			"%{prj.name}/src/**.cpp"
		}
		
		includedirs {
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{prj.name}/vendor/SDL2/include",
			"%{prj.name}/vendor/GLAD/include",
			"%{prj.name}/vendor/imgui",
		}
	
		links {
			"SDL",
			"SDLmain",
			"GLAD",
			"imgui"
		}
		
		-- Window Build Settings --
		
		filter "system:windows"
			cppdialect "C++20"
			systemversion "latest"
			
			defines {
				"CRISP_PLATFORM_WINDOWS",
				"CRISP_BUILD_DLL",
				"IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
			}
			
			postbuildcommands {
				("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Game/\"")
			}
			
		-- Configuration Settings --
			
		filter "configurations:Debug"
			defines "CRISP_DEBUG"
			runtime "Debug"
			symbols "On"
			
		filter "configurations:Release"
			defines "CRISP_RELEASE"
			runtime "Release"
			optimize "On"
			
		filter "configurations:Distribution"
			defines "CRISP_DISTRIBUTION"
			runtime "Release"
			optimize "On"
	
	project "Game"
		location "Game"
		kind "ConsoleApp"
		language "C++"
		staticruntime "Off"
		
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("build/" .. outputdir .. "/%{prj.name}")
		
		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.c",
			"%{prj.name}/src/**.cpp"
		}
		
		includedirs {
			"Crisp/vendor/spdlog/include",
			"Crisp/vendor/SDL2/include",
			"Crisp/src"
		}
		
		links {
			"Crisp",
			"SDL",
			"SDLmain"
		}
		
		-- Window Build Settings --
		
		filter "system:windows"
			cppdialect "C++20"
			systemversion "latest"
			
			defines {
				"CRISP_PLATFORM_WINDOWS"
			}
			
		-- Configuration Settings --
			
		filter "configurations:Debug"
			defines "CRISP_DEBUG"
			runtime "Debug"
			symbols "On"
			
		filter "configurations:Release"
			defines "CRISP_RELEASE"
			runtime "Release"
			optimize "On"
			
		filter "configurations:Distribution"
			defines "CRISP_DISTRIBUTION"
			runtime "Release"
			optimize "On"