include(ExternalProject)

find_package(Git REQUIRED)

include(cleanCppExtensions)

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
# Assimp
# ExternalDownloadNowGit(assimp "https://github.com/assimp/assimp.git" "origin/master")
# add_subdirectory(assimp/src/assimp_download)





