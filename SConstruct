#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")
mingw_path = '/opt/homebrew/bin'

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/","steamassets/public/"])
if env["platform"] == "macos":
    def AllSources(node='.', pattern='*'):
        result = [AllSources(dir, pattern)
                for dir in Glob(str(node)+'/*')
                if dir.isdir()]
        #need to unwrap the files found in here
        
        result += [source
                for source in Glob(str(node)+'/'+pattern)
                if source.isfile()]
        return result

    sources = AllSources('./src/', '*.c*')
    # print((sources[0][0]).get_contents())
    # print(len(sources))
    # print(len(sources[0]))

    for l in sources:
        print(l)
    
    #src/states/dropletstates/dropletstate.h
    
    env.Append(LIBS=["steam_api"])
    env.Append(LIBPATH=["steamassets/osx"])
    print(env)
    print("MACOS build")
    library = env.SharedLibrary(
        "bin/libgdexample.{}.{}.framework/libgdexample.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "windows":
    def AllSources(node='.', pattern='*'):
        result = [AllSources(dir, pattern)
                for dir in Glob(str(node)+'/*')
                if dir.isdir()]
        result += [source
                for source in Glob(str(node)+'/'+pattern)
                if source.isfile()]
        return result

    sources = AllSources('./src/', '*.c*', '')
    env.Append(LIBS=["steam_api64"])
    env.Append(LIBPATH=["steamassets/windows64"])
    env['CC'] = os.path.join(mingw_path, 'x86_64-w64-mingw32-gcc')  # C compiler
    env['CXX'] = os.path.join(mingw_path, 'x86_64-w64-mingw32-g++')  # C++ compiler
    env['LINK'] = os.path.join(mingw_path, 'x86_64-w64-mingw32-g++')  # Linker (C++ linker)
    env.Append(CCFLAGS=['-march=x86-64'])
    env.Append(LINKFLAGS=['-L/steamassets/windows64', '-lsteam_api64'])
    
    print(env)
    library = env.SharedLibrary(
        "bin/libgdexample.{}.{}.framework/libgdexample.{}.{}.{}.dll".format(
            env["platform"], env["target"], env["platform"], env["target"],env["arch"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "bin/libgdexample.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "bin/libgdexample.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "libgdexample{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
