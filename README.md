> My personal fork was to use this alongside a native plugin for the Unity game engine. It is still licensed under the LGPL as before. Primarily, I made some modifications to allow compiling to a Windows x64 DLL.

libnoise
========

This is a fork of libnoise which includes noiseutils in the building and installing process.
It also contains FindLibNoise.cmake

> This is a fork of libnoise which changes the build system from static Makefiles to cmake.

A portable, open-source, coherent noise-generating library for C++

libnoise is a portable C++ library that is used to generate coherent noise, a type of smoothly-changing noise.
libnoise can generate Perlin noise, ridged multifractal noise, and other types of coherent-noise.

Coherent noise is often used by graphics programmers to generate natural-looking textures, planetary terrain,
and other things. The mountain scene shown above was rendered in Terragen with a terrain file generated by libnoise.
You can also view some other examples of what libnoise can do.

In libnoise, coherent-noise generators are encapsulated in classes called noise modules.
There are many different types of noise modules. Some noise modules can combine or modify the outputs
of other noise modules in various ways; you can join these modules together to generate very complex coherent noise.

Compiling
---------

cmake supports 'out of source' builds by default, to use it do this:

```shell
mkdir build
cd build
cmake ..
make
```

this should create everything into the `build/` directory

Installing
----------

this is covered by cmake:

```shell
make install
```

Usage
-----

If you want to use this library, there are two ways of doing this (see examples for further details):

* Linker

 1. you need to supply the library `-lnoise` to the linker
 2. the includes to the compile with `-I /usr/include/noise`

* CMake

use the provided FindLibNoise.cmake

A comment on performance
------------------------

Using compiler optimizations for libnoise is *strongly recommended*.  Using the
unoptimized library is roughly a fifth as fast as using -O3 on my test
computer.

This cmake build by default (if not in developer mode; hence release build) will build with `-O3`

see:
CMAKE_BUILD_TYPE

Type of build (Debug, Release, ...)

If you want to disable optimizations, pass the following to the cmake arguments:
```"-DBUILD_SPEED_OPTIMIZED=OFF"```

