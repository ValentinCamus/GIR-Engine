# https://cmake.org/cmake/help/latest/manual/ctest.1.html
# https://cmake.org/Wiki/CMake/Testing_With_CTest
# https://cmake.org/cmake/help/latest/command/add_test.html?

include(CTest)

# Convenience targets for fast testing, they depends on binaries (so the build
# is triggered, when sources were changed).
add_custom_target(check
    COMMAND echo [----] Running tests
    USES_TERMINAL
    COMMAND ${CMAKE_CTEST_COMMAND}  --output-on-failure -C Debug
    DEPENDS GIR_Engine unittests)

add_custom_target(checkVerbose
    COMMAND echo [----] Running tests
    USES_TERMINAL
    COMMAND ${CMAKE_CTEST_COMMAND}  -V --output-on-failure -C Debug
    DEPENDS GIR_Engine unittests)

#------------------------------------------------------------------------------
# CTest Test suite
#
# Test suite is defined here, when executed Test fails (returns not 0), Test
# failed. There are more options, check CMake documentation. 
#
# Good to use to integration Test, run whole program with parameters,
# check if it will crash, produce correct results, etc.

# Basic runable tests (will not crash)
add_test(NAME "Is_Runable "
    COMMAND $<TARGET_FILE:GIR_Engine>)

add_test(NAME "Is_Runable-v"
    COMMAND $<TARGET_FILE:GIR_Engine> -v)

add_test(NAME "Is_Runable-h"
    COMMAND $<TARGET_FILE:GIR_Engine> -h)

## Add unit Test to CTest suite as one of the tests
## unit Test build is located in Sources/UnitTest/CMakeLists.txt
#add_test(NAME "catch_unit_tests"
#    COMMAND $<TARGET_FILE:UnitTest>
#    USES_TERMINAL
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

