cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME "just_audio_windows")
project(${PROJECT_NAME} LANGUAGES CXX)
set(CPPWINRT_VERSION 2.0.210806.1)
set(CMAKE_CXX_STANDARD 17)

# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "just_audio_windows_plugin")

set(NUGET_URL https://dist.nuget.org/win-x86-commandline/latest/nuget.exe)
set(NUGET ${CMAKE_CURRENT_SOURCE_DIR}/nuget.exe)
if (NOT EXISTS ${NUGET})
  file(DOWNLOAD ${NUGET_URL} ${NUGET})
endif()

set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(CPP_WINRT ${LIBS}/Microsoft.Windows.CppWinRT)
if (NOT EXISTS ${CPP_WINRT})
  add_custom_target(CPP_WINRT_DOWNLOAD ALL)
  add_custom_command(
    TARGET CPP_WINRT_DOWNLOAD PRE_BUILD
    COMMAND ${NUGET} install Microsoft.Windows.CppWinRT -Version ${CPPWINRT_VERSION} -ExcludeVersion -OutputDirectory ${LIBS}
    DEPENDS ${NUGET}
  )
endif()

add_library(${PLUGIN_NAME} SHARED
  "just_audio_windows_plugin.cpp"
  "player.hpp"
)
apply_standard_settings(${PLUGIN_NAME})
set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)
target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PLUGIN_NAME} PRIVATE flutter flutter_wrapper_plugin)
target_link_libraries(${PLUGIN_NAME} PRIVATE ${Libs}/Microsoft.Windows.CppWinRT/build/native/Microsoft.Windows.CppWinRT.targets)

# List of absolute paths to libraries that should be bundled with the plugin
set(just_audio_windows_bundled_libraries
  ""
  PARENT_SCOPE
)
