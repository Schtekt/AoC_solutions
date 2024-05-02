require("vscode")
require("clean")
workspace "AoC"
    language "C++"
    configurations{"Debug", "Release"}
    toolset "msc"
    cppdialect "C++17"
    platforms{"Win64"}
    project "AoC"
        kind "ConsoleApp"
        targetdir "Build/bin/%{prj.name}"
        objdir "Build/bin-int/%{prj.name}"
        files{"src/**.cpp", "src/**.h", "include/**.cpp", "include/**.h"}

        filter {"configurations:Debug", "platforms:Win64"}
            architecture "x64"
            includedirs{"include"}
            defines { "DEBUG" }
            symbols "On"

        filter {"configurations:Release", "platforms:Win64"}
            architecture "x64"
            includedirs{"include"}
            defines { "NDEBUG" }
            optimize "On"

filter "system:windows"
    platforms {"Win64"}