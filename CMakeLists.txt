cmake_minimum_required(VERSION 3.10)
project(imgui-plot)

# Conan dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


add_library(imgui-plot
  include/imgui_plot.h
  src/imgui_plot.cpp
  )

target_include_directories(imgui-plot SYSTEM PUBLIC include)
target_include_directories(imgui-plot SYSTEM PUBLIC .)
# target_link_libraries(imgui-sfml PUBLIC sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
# target_link_libraries(imgui-sfml PUBLIC "-lGL")


# Rule to install the compiled library
install(TARGETS imgui-plot DESTINATION lib)
# Rule to install the headers
install(FILES
  include/imgui_plot.h
  DESTINATION include
  )

# Rule to install the source -> Usually this is not necessary, but since imgui
# uses the source as documentation we also install the source in the conan cache
install(FILES
  src/imgui_plot.cpp
  DESTINATION src
  )
