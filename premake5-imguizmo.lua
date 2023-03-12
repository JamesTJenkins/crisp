project "imguizmo"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	location "Crisp/vendor/ImGuizmo"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files {
		"Crisp/vendor/imguizmo/GraphEditor.h",
		"Crisp/vendor/imguizmo/GraphEditor.cpp",
		"Crisp/vendor/imguizmo/ImCurveEdit.h",
		"Crisp/vendor/imguizmo/ImCurveEdit.cpp",
		"Crisp/vendor/imguizmo/ImGradient.h",
		"Crisp/vendor/imguizmo/ImGradient.cpp",
		"Crisp/vendor/imguizmo/ImGuizmo.h",
		"Crisp/vendor/imguizmo/ImGuizmo.cpp",
		"Crisp/vendor/imguizmo/ImSequencer.h",
		"Crisp/vendor/imguizmo/ImSequencer.cpp",
		"Crisp/vendor/imguizmo/ImZoomSlider.h",
	}

	includedirs {
		"Crisp/vendor/imgui",
	}

	defines {
		"USE_IMGUI_API"
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