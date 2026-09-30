# `VL.Mcro.Devices.SpaceMouse`

A port of [Open Unreal Space Mouse](https://github.com/microdee/OpenUnrealSpaceMouse) for vvvv-gamma. This is the third SpaceMouse integration for vvvv as of time of writing. There's one which is working with official drivers, one which is working from HID but with limited device support and this one which is also working with HID but supports all 3DConnexion Space Mice.

This repository can also serve as a template for developing C++/CLI libraries for vvvv with a "totally bareable" developer experience with the help of [xmake](https://xmake.io).

## Install

Get it via nuget manager in vvvv. For regular usage the sections below can be ignored.

## Build

```pwsh
cd .\cpp

# The extra addons only require manual installation until they're canonized in xrepo. Need to be done only once
xmake addon --install github:microdee/xmake.rats-utils
xmake addon --install github:microdee/xmake.dotnet-cppcli

xmake config -m release -v -D
xmake build
```

xmake will automatically link resulting binaries in `lib` subfolder.

### Understanding the workflow

I chose xmake in particular because I grew fond of its focus on developer experience for C++. Especially for its excellent handling of 3rd party libraries and many chores which tend to be painful in other build tools. However xmake itself doesn't know about C++/CLI, that's where `dotnet-cppcli` addon comes in. It adds the proper compiler flags, gather dotnet runtime assemblies and manages dependencies from nuget. This is already way more than MSBuild does for you.

All C++ sources are found in `cpp/src` subfolder, and its configuration in `cpp/xmake.lua`. Build artifacts and intermediate files should also stay inside cpp folder (except linking the build results to `lib` in project root). You can enable adequate auto-complete in VS Code and Visual Studio, both for managed assemblies and regular C++ code, with the following commands:

```pwsh
cd .\cpp

xmake project -k compile_commands .vscode       # VS Code
xmake project -k vsxmake2026 -m "debug,release" # Visual Studio
```

If you install the xmake VS Code extension it supposedly auto-generate `compile_commands.json` for you. VS Code is slightly better for developing as it doesn't rely on a virtual project workspace, how a Visual Studio solution would. However attaching a debugger is only working in Visual Studio without much hassle.

### Debugging

Configure xmake in debug mode, then build. vvvv must be closed during this.

```pwsh
cd .\cpp

xmake config -m debug -v -D
xmake build
```

no need to change references in VL file (`lib` folder is linking to the debug output now). When attaching a debugger set both `Native` and `Managed` modes (or older versions may refer to it as "Mixed Mode" debugging).