project "Wzorcowanie Termopar"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("../bin-int/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/vendor/glad/glad.h",
		"src/vendor/glad/glad.c",
		"src/vendor/glm/glm/**.hpp",
		"src/vendor/glm/glm/**.cpp",
		"src/vendor/KHR/**.h",
		"src/vendor/GLFW/**.h",
		"src/vendor/stb/**.h",
		"src/vendor/stb/**.cpp",
		"src/vendor/imgui-master/imgui.h",
    	"src/vendor/imgui-master/imgui.cpp",
    	"src/vendor/imgui-master/imgui_draw.cpp",
    	"src/vendor/imgui-master/imgui_tables.cpp",
    	"src/vendor/imgui-master/imgui_widgets.cpp",
   		"src/vendor/imgui-master/backends/imgui_impl_glfw.h",
    	"src/vendor/imgui-master/backends/imgui_impl_glfw.cpp",
   		"src/vendor/imgui-master/backends/imgui_impl_opengl3.h",
   		"src/vendor/imgui-master/backends/imgui_impl_opengl3.cpp",
		"src/vendor/implot-master/implot.h",
		"src/vendor/implot-master/implot.cpp",
		"src/vendor/implot-master/implot_items.h",
		"src/vendor/implot-master/implot_items.cpp"
	}

	includedirs
	{
		"src",
		"src/vendor",
		"src/vendor/stb",
		"src/vendor/imgui-master",
		"src/vendor/imgui-master/backends",
		"src/vendor/implot-master"
	}

	libdirs 
	{ 
		"../Biblioteki/lib"
	}

	links 
	{ 
		"glfw3.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"