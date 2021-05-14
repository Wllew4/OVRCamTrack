workspace("OVRCamTrack")
    configurations { "Release" }
    platforms { "Win32", "Win64" }

project "driver_OVRCamTrack"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    targetdir "bin"
    targetname "driver_OVRCamTrack"
    includedirs {
        "src",
        "lib/openvr/headers"
    }

    files { "src/**.h", "src/**.cpp" }

    filter "configurations:Release"
        defines { "RELEASE" }
        symbols "On"

    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"
    
    filter { "platforms:Win64" }
        system "Windows"
        architecture "x86_64"