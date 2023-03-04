project "yaml-cpp"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	location "Crisp/vendor/yaml-cpp"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files {
		"Crisp/vendor/yaml-cpp/src/**.h",
		"Crisp/vendor/yaml-cpp/src/**.cpp",
		"Crisp/vendor/yaml-cpp/include/**.h"
	}

	includedirs {
		"Crisp/vendor/yaml-cpp/include"
	}

	defines {
		"YAML_CPP_STATIC_DEFINE",
	}

	-- Window Build Settings --
		
	filter "system:windows"
		systemversion "latest"
			
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