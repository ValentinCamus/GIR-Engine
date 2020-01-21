cmake_minimum_required(VERSION 3.2)
project(imgui)

set(IMGUI_SOURCES
        "imgui.cpp"
        "imgui_demo.cpp"
        "imgui_draw.cpp"
        "imgui_widgets.cpp")

set(IMGUI_HEADERS
        "imconfig.h"
        "imgui.h"
        "imgui_internal.h"
        "imstb_rectpack.h"
        "imstb_textedit.h"
        "imstb_truetype.h")

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
