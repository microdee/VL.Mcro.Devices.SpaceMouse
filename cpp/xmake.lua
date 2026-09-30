add_rules("mode.debug", "mode.release")
set_languages("c++20")

-- add_addons("dotnet-cppcli")
includes("@addon/dotnet-cppcli/desc")

add_requires("hidapi 0.14.0", {configs = {runtimes = "MD"}})

target("VL.Mcro.Devices.SpaceMouse.Cpp")
    add_rules("@addon/dotnet-cppcli/cppcli")
    set_kind("shared")
    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    add_packages("hidapi")
    add_nuget_packages(
        {"VL.Core", "2026.8.0-0131-g2f3a63d2aa"},
        {"Stride.Core.Mathematics", "4.3.0.2507"}
    )
    after_build(function(target)
        os.ln(path.absolute(target:targetdir()), path.absolute("../lib"))
    end)
