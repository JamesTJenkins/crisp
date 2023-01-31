project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "On"

	location "Crisp/vendor/GLAD"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files {
		"Crisp/vendor/GLAD/include/glad/glad.h",
		"Crisp/vendor/GLAD/include/KHR/khrplatform.h",
		"Crisp/vendor/GLAD/src/glad.c"
	}

	includedirs {
		"Crisp/vendor/GLAD/include"
	}

	-- Windows -- 
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		runtime "Release"
		optimize "on"