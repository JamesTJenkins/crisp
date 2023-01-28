project "SDLmain"
	kind "StaticLib"
	language "C"

	location "Crisp/vendor/SDL2/VisualC/SDLmain"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"Crisp/vendor/SDL2/include",
	}

	flags {
		"NoRuntimeChecks",
		"NoBufferSecurityCheck"
	}

	vectorextensions "SSE"
	inlining "Explicit"
	ignoredefaultlibraries { "libraries" }

	files {"Crisp/vendor/SDL2/src/main/windows/*.c"}

	-- Windows -- 
	filter "system:windows"
		systemversion "latest"

		defines {
			"WIN32",
			"_WINDOWS"
		}

	filter "configurations:Debug"
		defines "_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "NDEBUG"
		runtime "Release"
		optimize "On"