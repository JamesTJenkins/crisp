project "imgui"
	kind "StaticLib"
	language "C++"

	location "Crisp/vendor/imgui"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files {
		"Crisp/vendor/imgui/imconfig.h",
		"Crisp/vendor/imgui/imgui.h",
		"Crisp/vendor/imgui/imgui.cpp",
		"Crisp/vendor/imgui/imgui_demo.cpp",
		"Crisp/vendor/imgui/imgui_draw.cpp",
		"Crisp/vendor/imgui/imgui_internal.h",
		"Crisp/vendor/imgui/imgui_tables.cpp",
		"Crisp/vendor/imgui/imgui_widgets.cpp",
		"Crisp/vendor/imgui/imstb_rectpack.h",
		"Crisp/vendor/imgui/imstb_textedit.h",
		"Crisp/vendor/imgui/imstb_truetype.h",
	}

	-- Windows -- 
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"