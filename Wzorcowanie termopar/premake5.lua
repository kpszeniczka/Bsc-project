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
		"src/vendor/imgui/**.h",
    	"src/vendor/imgui/**.cpp",
   		"src/vendor/imgui/backends/**.h",
    	"src/vendor/imgui/backends/**.cpp",
		"src/vendor/implot/**.h",
		"src/vendor/implot/**.cpp",
	}

	includedirs
	{
		"src",
		"src/vendor",
		"src/vendor/stb",
		"src/vendor/imgui",
		"src/vendor/imgui/backends",
		"src/vendor/implot"
	}

	libdirs 
	{ 
		"src/vendor/dependecies/lib"
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