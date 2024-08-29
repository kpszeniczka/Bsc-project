workspace "Wzorcowanie Termopar"
    architecture "x64"
    startproject "Wzorcowanie Termopar"

    configurations {
        "Debug",
        "Release"
    }

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

    OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    include "Wzorcowanie Termopar/premake5.lua"