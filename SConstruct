#!python
import os
import sys
import glob

opts = Variables([], ARGUMENTS)

# Gets the standard flags CC, CCX, etc.
env = DefaultEnvironment()

if sys.platform.startswith('linux'):
    host_platform = 'linux'
elif sys.platform == 'win32' or sys.platform == 'msys':
    host_platform = 'windows'
else:
    raise ValueError(
        'Could not detect platform automatically, please specify with '
        'platform=<platform>'
    )

# Define our options
opts.Add(EnumVariable('target', "Compilation target", 'debug', ['debug', 'release']))
opts.Add(EnumVariable('platform', "Compilation platform", host_platform, ['windows', 'linux']))
opts.Add(BoolVariable('use_llvm', "Use the LLVM / Clang compiler", 'no'))
opts.Add(PathVariable('target_path', 'The path where the lib is installed.', 'gdnative/'))
opts.Add(PathVariable('target_name', 'The library name.', 'libgdnative', PathVariable.PathAccept))

opts.Add(EnumVariable(
    'bits',
    'Target platform bits',
    '64',
    ['64']
))

# Local dependency paths, adapt them to your setup
godot_headers_path = "godot-cpp/godot-headers/"
cpp_bindings_path = "godot-cpp/"
cpp_library = "libgodot-cpp"

obelisk_bindings_path = "obelisk/"
obelisk_library = "libobelisk"

# Updates the environment with the option variables.
opts.Update(env)

# Process some arguments
if env['use_llvm']:
    env['CC'] = 'clang'
    env['CXX'] = 'clang++'

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# Check our platform specifics
if env['platform'] == 'linux':
    env['target_path'] += 'linux.' + env['bits'] + '/'
    cpp_library += '.linux'
    env.Append(CCFLAGS=['-fPIC'])
    env.Append(CXXFLAGS=['-std=c++17'])
    if env['target'] == 'debug':
        env.Append(CCFLAGS=['-g3', '-Og'])
    else:
        env.Append(CCFLAGS=['-g', '-O3'])
        env.Append(CPPDEFINES=['NDEBUG'])

    env.Append(CCFLAGS=['-m64'])
    env.Append(LINKFLAGS=['-m64'])

    env['target_name'] += '.so'

elif env['platform'] == "windows":
    env['CC'] = 'x86_64-w64-mingw32-gcc'
    env['CXX'] = 'x86_64-w64-mingw32-g++'
    env['AR'] = "x86_64-w64-mingw32-ar"
    env['RANLIB'] = "x86_64-w64-mingw32-ranlib"
    env['LINK'] = "x86_64-w64-mingw32-g++"
    env['target_path'] += 'windows.' + env['bits'] + '/'
    cpp_library += '.windows'
    # This makes sure to keep the session environment variables on windows,
    # that way you can run scons in a vs 2017 prompt and it will find all the required tools
    env.Append(ENV=os.environ)

    env.Append(CXXFLAGS=['-std=c++17'])

    env.Append(LINKFLAGS=[
        '--static',
        '-Wl,--no-undefined',
        '-static-libgcc',
        '-static-libstdc++',
    ])

    env.Append(CPPDEFINES=['WIN32', '_WIN32', '_WINDOWS', '_CRT_SECURE_NO_WARNINGS'])
    #env.Append(CCFLAGS=['-W3', '-GR'])
    if env['target'] == 'debug':
        env.Append(CPPDEFINES=['_DEBUG'])
        #env.Append(CCFLAGS=['-EHsc', '-MDd', '-ZI'])
        env.Append(LINKFLAGS=['-DEBUG'])
    else:
        env.Append(CPPDEFINES=['NDEBUG'])
        #env.Append(CCFLAGS=['-O2', '-EHsc', '-MD'])
        env.Append(CCFLAGS=['-O2'])

    env['target_name'] += '.dll'

if env['target'] == 'debug':
    cpp_library += '.debug'
else:
    cpp_library += '.release'

cpp_library += '.' + str(env['bits'])

# make sure our binding library is properly includes
env.Append(CPPPATH=['.', obelisk_bindings_path + 'include/', godot_headers_path, cpp_bindings_path + 'include/', cpp_bindings_path + 'include/core/', cpp_bindings_path + 'include/gen/'])
env.Append(LIBPATH=[cpp_bindings_path + 'bin/', obelisk_bindings_path + 'bin/'])
env.Append(LIBS=[cpp_library, obelisk_library])

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=['src/'])
sources = glob.glob('src/**/*.cpp', recursive=True)
sources += glob.glob('src/**/*.c', recursive=True)

library = env.SharedLibrary(target=env['target_path'] + env['target_name'] , source=sources)

Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))
