cmake_minimum_required(VERSION 3.16)
project(sir VERSION 0.1.0)

include(CTest)
find_package(SFML 2.5 
  COMPONENTS 
    window graphics  REQUIRED
  )


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")


string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

add_executable(sir main.cpp  src/sir.cpp src/epidemic.cpp src/automaton.cpp  src/io.cpp src/graph.cpp)

target_include_directories(sir PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(sir PRIVATE sfml-graphics sfml-window) 

if (BUILD_TESTING)
  ## vedi perchè non funzia più
  add_executable(test-sir test.cpp src/sir.cpp src/epidemic.cpp src/automaton.cpp src/io.cpp )
  target_include_directories(test-sir PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
  add_test(NAME test-sir COMMAND test-sir WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

endif()