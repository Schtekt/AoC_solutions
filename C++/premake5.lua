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
            includedirs{"ExternalLibraries/curl/debug_x64/include", "include"}
            libdirs{"ExternalLibraries/curl/debug_x64/lib"}
            links{"libcurl_a_debug.lib", "Ws2_32.lib", "Crypt32.lib", "Wldap32.lib", "Normaliz.lib"}
            defines { "DEBUG" }
            symbols "On"

        filter {"configurations:Release", "platforms:Win64"}
            architecture "x64"
            includedirs{"ExternalLibraries/curl/release_x64/include", "include"}
            libdirs{"ExternalLibraries/curl/release_x64/lib"}
            links{"libcurl_a.lib", "Ws2_32.lib", "Crypt32.lib", "Wldap32.lib", "Normaliz.lib"}
            defines { "NDEBUG" }
            optimize "On"

filter "system:windows"
    platforms {"Win64"}