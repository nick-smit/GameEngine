workspace "GameEngine"
	architecture "x64"
	startproject "Sandbox"

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

IncludeDir = {};
IncludeDir["spdlog"] = "Engine/vendor/spdlog/include";
IncludeDir["glfw"] = "Engine/vendor/glfw/include";
IncludeDir["glad"] = "Engine/vendor/glad/include";


group "Dependencies"
	include "Dependencies/glfw"
	include "Dependencies/glad"

group ""

project "Engine"
	location "Engine"
	--kind "StaticLib"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Engine/src/pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glfw}",	
		"%{IncludeDir.glad}",
	}

	links {
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "on"
