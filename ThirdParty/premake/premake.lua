-- Copyright(c) 2019-2020 RadTuna

-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
-- copies of the Software, and to permit persons to whom the Software is furnished
-- to do so, subject to the following conditions :

-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.

-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
-- FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
-- COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
-- IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
-- CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


-- Variables declear
ROOT_DIR			= _ARGS[1]
GRAPHICS_API			= _ARGS[2]
SOLUTION_NAME			= "FluentEngine"
EDITOR_NAME			= "Editor"
RUNTIME_NAME			= "Runtime"
SHADER_NAME			= "Shader"
TARGET_NAME			= "FluentEngine" -- Name of executable
DEBUG_FORMAT			= "c7"
EDITOR_DIR			= ROOT_DIR .. "/Source/" .. EDITOR_NAME
RUNTIME_DIR			= ROOT_DIR .. "/Source/" .. RUNTIME_NAME
SHADER_DIR			= ROOT_DIR .. "/Shaders/"
INTERMEDIATE_DIR			= ROOT_DIR .. "/Intermediate"
PROJECT_DIR			= INTERMEDIATE_DIR .. "/Projects"
TARGET_DIR_RELEASE  		= ROOT_DIR .. "/Binaries/Release"
TARGET_DIR_DEBUG   		= ROOT_DIR .. "/Binaries/Debug"

-- Solution
solution (SOLUTION_NAME)
	location (ROOT_DIR)
	systemversion "latest"
	cppdialect "C++17"
	language "C++"
	platforms "x64"
	configurations { "Release", "Debug" }

	filter { "platforms:x64" }
		system "Windows"
		architecture "x64"

		
	-- Debug
	filter "configurations:Debug"
		defines { "DEBUG", GRAPHICS_API }
		flags { "MultiProcessorCompile", "LinkTimeOptimization" }
		symbols "On"				
		
	-- Release	
	filter "configurations:Release"
		defines { "NDEBUG", GRAPHICS_API }
		flags { "MultiProcessorCompile" }
		symbols "Off"	
		optimize "Full"

-- Runtime
project (RUNTIME_NAME)
	location (PROJECT_DIR)
	objdir (INTERMEDIATE_DIR)
	kind "StaticLib"
	staticruntime "On"
	
	-- Files
	files 
	{ 
		RUNTIME_DIR .. "/**.h",
		RUNTIME_DIR .. "/**.cpp",
		RUNTIME_DIR .. "/**.hpp",
		RUNTIME_DIR .. "/**.inl",
	}

	-- Includes
	includedirs { (RUNTIME_DIR) }
	includedirs { (RUNTIME_DIR) .. "/Public" }
	
	-- Libraries
	libdirs (LIBRARY_DIR)

	-- Debug
	filter "configurations:Debug"
		targetdir (TARGET_DIR_DEBUG)
		debugdir (TARGET_DIR_DEBUG)
		debugformat (DEBUG_FORMAT)

			
	-- Release
	filter "configurations:Release"
		targetdir (TARGET_DIR_RELEASE)
		debugdir (TARGET_DIR_RELEASE)


-- Editor
project (EDITOR_NAME)
	location (PROJECT_DIR)
	links { RUNTIME_NAME }
	dependson { RUNTIME_NAME }
	targetname ( TARGET_NAME )
	objdir (INTERMEDIATE_DIR)
	kind "WindowedApp"
	staticruntime "On"

	-- Files
	files 
	{ 
		EDITOR_DIR .. "/**.rc",
		EDITOR_DIR .. "/**.h",
		EDITOR_DIR .. "/**.cpp",
		EDITOR_DIR .. "/**.hpp",
		EDITOR_DIR .. "/**.inl"
	}
	
	-- Includes
	includedirs { (EDITOR_DIR) }
	includedirs { (EDITOR_DIR) .. "/Public" }
	includedirs { (RUNTIME_DIR) }
	includedirs { (RUNTIME_DIR) .. "/Public" }
	
	-- Libraries
	libdirs (LIBRARY_DIR)

	-- "Debug"
	filter "configurations:Debug"
		targetdir (TARGET_DIR_DEBUG)	
		debugdir (TARGET_DIR_DEBUG)
		debugformat (DEBUG_FORMAT)		
				
	-- "Release"
	filter "configurations:Release"
		targetdir (TARGET_DIR_RELEASE)
		debugdir (TARGET_DIR_RELEASE)

-- Shader
project (SHADER_NAME)
	location (PROJECT_DIR)
	objdir (INTERMEDIATE_DIR)
	kind "None"

	-- Files
	files { SHADER_DIR .."/**.hlsl" }

	-- Includes
	includedirs { (SHADER_DIR) }
	includedirs { (SHADER_DIR) .. "/Public" }

	-- exclude files
	filter "files:/**.hlsl"
  		flags { "ExcludeFromBuild" }