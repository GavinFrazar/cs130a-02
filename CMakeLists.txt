cmake_minimum_required(VERSION 3.0)
project(main C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADERS
    ${HEADERS}
    src/AVL.h
    src/BTree.h
    )

set(SOURCES
    ${SOURCES}
    src/main.cpp
    src/AVL.cpp
    src/BTree.cpp
    )

include_directories(
    ./src
    )

add_executable(main ${SOURCES} ${HEADERS})

if (UNIX)
    target_link_libraries(main stdc++fs)
endif(UNIX)

# Unit tests
#enable_testing()
# add_executable(TestAVLinsert tests/TestAVLinsert.cpp src/AVL.cpp)
# target_include_directories(TestAVLinsert PRIVATE ${INCLUDES})
# add_test(AVLinsert TestAVLinsert)