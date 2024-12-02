require("vscode")
require("clean")
workspace "AoC"
    location "Generated"
    targetBuildPath = path.getdirectory(_SCRIPT) .. "/Build/target"
    objBuildPath = path.getdirectory(_SCRIPT) .. "/Build/obj"

    language "C++"
    configurations{"Debug", "Release"}
    toolset "msc"
    cppdialect "C++17"
    platforms{"Win64"}

    project "AoC"
        kind "ConsoleApp"
        targetdir(targetBuildPath .. "/%{prj.name}")
        objdir(objBuildPath .. "/%{prj.name}")
        files{"src/**.cpp", "src/**.h", "include/**.cpp", "include/**.h"}

        architecture "x64"
        includedirs{"include"}

        filter {"configurations:Debug", "platforms:Win64"}
            defines { "DEBUG" }
            symbols "On"

        filter {"configurations:Release", "platforms:Win64"}
            defines { "NDEBUG" }
            optimize "On"