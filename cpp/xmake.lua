add_rules("mode.debug", "mode.release")
set_languages("c++20")

-- add_addons("dotnet-cppcli")
includes("@addon/dotnet-cppcli/desc")

add_requires("hidapi 0.14.0", {configs = {runtimes = "MD"}})

target("VL.Mcro.Devices.SpaceMouse.Cpp")
    add_rules("@addon/dotnet-cppcli/cppcli")
    set_dotnet_version("8.0")
    set_kind("shared")
    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    add_packages("hidapi")
    add_nuget_packages(
        {"VL.Core", "2025.7.4"},
        {"Stride.Core.Mathematics", "4.3.0.2507"}
    )
    add_cppcli_step("install_lib", { triggered_by = "after_build"}, function(ctx)
        local output = path.absolute("../lib/net" .. ctx.dotnet.version)
        if os.exists(output) then
            os.rmdir(output)
        end
        os.cp(path.absolute(ctx.target:targetdir()), output)
    end)
