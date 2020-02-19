include(ExternalProject)

find_package(Git REQUIRED)

include(CleanCppExtensions)

set(GLM_TEST_ENABLE OFF CACHE BOOL "Disable GLM unit tests build.")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable Assimp unit tests build.")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Disable Assimp applications build.")

#------------------------------------------------------------------------------
# Convenience update all, dependencies are added in ExternalHeaderOnly_Add
add_custom_target(update COMMENT "Updated all external projects")

#------------------------------------------------------------------------------
# Catch - Unit Test header only library
ExternalHeaderOnly_Add(Catch "https://github.com/catchorg/Catch2.git" "origin/master" "single_include/catch2")

#------------------------------------------------------------------------------
# stb-image
add_library(stb STATIC ${CMAKE_CURRENT_SOURCE_DIR}/stb/src/stb_image.cpp)
target_include_directories(stb SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/stb/include)

#------------------------------------------------------------------------------
# spdlog
ExternalHeaderOnly_Add(spdlog "https://github.com/gabime/spdlog.git" "v1.x" "include")

#------------------------------------------------------------------------------
# GLFW
ExternalDownloadNowGit(glfw "https://github.com/glfw/glfw.git" "origin/master")
add_subdirectory(glfw/src/glfw_download)

#------------------------------------------------------------------------------
# glm
ExternalHeaderOnly_Add(glm "https://github.com/g-truc/glm.git" "master" "")

#------------------------------------------------------------------------------
# glad
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

#------------------------------------------------------------------------------
# imgui
add_library(imgui STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_impl_gl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_impl_glfw.cpp)
target_include_directories(imgui SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/include)
target_link_libraries (imgui glad)
target_link_libraries (imgui glfw)

#------------------------------------------------------------------------------
# imgui
add_library(imguizmo STATIC ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo/ImGuizmo.cpp)
target_include_directories(imguizmo SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo/include)
target_link_libraries (imguizmo imgui)

#------------------------------------------------------------------------------
# Assimp
ExternalDownloadNowGit(assimp "https://github.com/assimp/assimp.git" "origin/master")
add_subdirectory(assimp/src/assimp_download)

#------------------------------------------------------------------------------
# target_link_libraries (exampleApp PRIVATE json)
# #include <nlohmann/json.hpp>
ExternalHeaderOnly_Add(json "https://github.com/nlohmann/json.git" "master" "single_include")
