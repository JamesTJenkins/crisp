workspace "Crisp"
	architecture "x64"
	
	-- Configuration Settings --
	
	configurations {
		"Debug",
		"Release",
		"Distribution"	-- Distribution is alike release but more heavily stripped --
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"	

project "Crisp"
	location "Crisp"
	kind "SharedLib"
	language "C++"
	
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
		"%{prj.name}/vendor/spdlog/include"
	}
	
	-- Window Build Settings --
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"CRISP_PLATFORM_WINDOWS",
			"CRISP_BUILD_DLL"
		}
		
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}
		
	-- Configuration Settings --
		
	filter "configurations:Debug"
		defines "CRISP_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "CRISP_RELEASE"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "CRISP_DISTRIBUTION"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	
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
		"Crisp/src"
	}
	
	links {
		"Crisp"
	}
	
	-- Window Build Settings --
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"CRISP_PLATFORM_WINDOWS"
		}
		
	-- Configuration Settings --
		
	filter "configurations:Debug"
		defines "CRISP_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "CRISP_RELEASE"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "CRISP_DISTRIBUTION"
		optimize "On"