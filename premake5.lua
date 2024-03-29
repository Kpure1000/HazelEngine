
-- Workspace Hazel ------------------------------

workspace "Hazel"
	architecture "x64"

	startproject "AsteroidBelt"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist" 
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
dynamicdef = "HZ_DYNAMIC_LIB"
staticdef = "HZ_STATIC_LIB"

-- GLFW -----------------------------------------

IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["GLAD"] = "Hazel/vendor/GLAD/include"
IncludeDir["ImGui"] = "Hazel/vendor/imgui"
IncludeDir["glm"] = "Hazel/vendor/glm"
IncludeDir["stb"] = "Hazel/vendor/stb"
IncludeDir["freetype"] = "Hazel/vendor/freetype/include"
-- include outher premake config
include "Hazel/vendor/GLFW" 
include "Hazel/vendor/GLAD"
include "Hazel/vendor/imgui"
include "Hazel/vendor/stb"
--include "Hazel/vendor/freetype"

-- Hazel ----------------------------------------

project "Hazel"
	location "Hazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.freetype}",
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"stb",
		"Hazel/vendor/freetype/libs/freetype.lib",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			staticdef,
			"STB_IMAGE_IMPLEMENTATION",
			"STB_IMAGE_WRITE_IMPLEMENTATION",
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

-- SandBox --------------------------------------

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src",
		-- "%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		-- "%{IncludeDir.freetype}",
	}

	links
	{
		"Hazel",
		"ImGui",
		-- "Hazel/vendor/freetype/libs/freetype.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			staticdef
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

-- AsteroidBelt --------------------------------------

project "AsteroidBelt"
	location "AsteroidBelt"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src",
		-- "%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		-- "%{IncludeDir.freetype}",
	}

	links
	{
		"Hazel",
		"ImGui",
		-- "Hazel/vendor/freetype/libs/freetype.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			staticdef
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

