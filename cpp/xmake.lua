add_addons("dotnet-cppcli")

add_rules("mode.debug", "mode.release")
set_languages("c++20")

add_requires("hidapi 0.14.0", {configs = {runtimes = "MD"}})
add_requires(
    "nuget::VL.Core 2025.7.4",
    "nuget::Stride.Core.Mathematics 4.3.0"
)

target("VL.Mcro.Devices.SpaceMouse.Cpp")
    set_kind("shared")
    add_rules("@addon/dotnet-cppcli/cppcli")
    set_values("dotnet.version", "8.0")
    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    add_packages(
        "hidapi",
        "nuget::VL.Core",
        "nuget::Stride.Core.Mathematics"
    )
    on_load(function(target)
        import("@addon.dotnet-cppcli.cppcli")(target).steps
            :add("install_lib",
                { triggered_by = "after_build"},
                function(ctx)
                    local output = path.absolute("../lib/net" .. ctx.dotnet.version)
                    if os.exists(output) then
                        os.rmdir(output)
                    end
                    os.cp(path.absolute(ctx.target:targetdir()), output)
                end
            )
    end)
