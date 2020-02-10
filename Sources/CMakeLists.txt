# Adds convenience methods, see CMake/cleanCppExtensions.CMake
include(CleanCppExtensions)

# Creates options to turn on sanitizers, see CMake/sanitizers.CMake
include(Sanitizers)

# Enable helpfull warnings and C++14 for all files
if (MSVC)
    add_compile_options(/std:c++14 /W3)
else ()
    add_compile_options(-std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -pedantic)
endif ()

#------------------------------------------------------------------------------
# Libraries dependencies
find_package(OpenGL REQUIRED)

#-------------------------------------------------------------------------------
# GIR_Engine executable setup

set(ICON_RESOURCE "")
if (WIN32) #windows icon resource file, provided from /Packaging directory
    set(ICON_RESOURCE "${PROJECT_BINARY_DIR}/GIR_Engine.icon.rc")
elseif (APPLE) #osx icon ressource file, provided from /Packaging directory
    set(ICON_RESOURCE "${PROJECT_SOURCE_DIR}/Packaging/GIR_Engine.icns" IO/Loader/TextureLoader.cpp IO/Loader/TextureLoader.hpp IO/FileSystem/FileSystem.hpp)
endif ()

file(GLOB_RECURSE ENGINE_SRCS "*.cpp" "*.hpp" ".inl")

add_executable(GIR_Engine MACOSX_BUNDLE ${ICON_RESOURCE} ${ENGINE_SRCS})

target_include_directories(GIR_Engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(APPLE)
set_target_properties(GIR_Engine PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "GIR_Engine")
set_target_properties(GIR_Engine PROPERTIES MACOSX_BUNDLE_BUNDLE_GUI_IDENTIFIER "com.GIR_Engine.GIR_Engine")
set_target_properties(GIR_Engine PROPERTIES MACOSX_BUNDLE_ICON_FILE GIR_Engine.icns)
set_target_properties(GIR_Engine PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/Packaging/MacOSXBundleInfo.plist.in)
set_source_files_properties(${PROJECT_SOURCE_DIR}/Packaging/GIR_Engine.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

install(TARGETS GIR_Engine BUNDLE DESTINATION "." RUNTIME DESTINATION bin)

# Using macro from CMake/CleanCpppExtensions.cpp included on the top
# Provides GIR_Engine-run and GIR_Engine-dbg
addRunAndDebugTargets(GIR_Engine)

# Short convenience target from CMake/CleanCpppExtensions.cpp
add_custom_target(run DEPENDS GIR_Engine-run)

#-------------------------------------------------------------------------------
# Target compile definitions

target_compile_definitions(GIR_Engine PUBLIC PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

#-------------------------------------------------------------------------------
# Target link libraries

target_link_libraries (GIR_Engine glfw)
target_link_libraries (GIR_Engine glad)
target_link_libraries (GIR_Engine stb)
target_link_libraries (GIR_Engine glm)
target_link_libraries (GIR_Engine imgui)
target_link_libraries (GIR_Engine spdlog)

target_link_libraries(GIR_Engine ${OPENGL_gl_LIBRARY})
target_link_libraries(GIR_Engine ${OPENGL_glu_LIBRARY})
target_link_libraries(GIR_Engine ${OPENGL_LIBRARIES})

target_link_libraries(GIR_Engine ${CMAKE_DL_LIBS})

#-------------------------------------------------------------------------------
# Copy MINGW needed libraries for building on windows

if (MINGW)
message(STATUS "MinGW detected")
get_filename_component(GCC_PATH ${CMAKE_C_COMPILER} PATH)
if(${GCC_PATH} MATCHES "mingw64/bin")
set(libgcc "libgcc_s_seh-1.dll") #64bit
message(STATUS "  64bit dlls is building")
else()
set(libgcc "libgcc_s_dw2-1.dll") #32bit
message(STATUS "  32bit dlls is building")
endif()

install(FILES ${GCC_PATH}/${libgcc}
${GCC_PATH}/libwinpthread-1.dll
${GCC_PATH}/libstdc++-6.dll
DESTINATION ./bin/
)
endif(MINGW)

#------------------------------------------------------------------------------
# Other MISC targets

# Adds misc targets: format, cppcheck, tidy, see CMake/cleanCppExtensions.CMake
addMiscTargets()


