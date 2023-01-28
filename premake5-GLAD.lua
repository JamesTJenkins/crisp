project "GLAD"
	kind "StaticLib"
	language "C"

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
		staticruntime "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"