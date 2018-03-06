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

set(INCLUDES
    ${INCLUDES}
    src
    )
    
include_directories(
    ${INCLUDES}
    )

source_group("Source files" FILES ${SOURCES})
source_group("Header files" FILES ${HEADERS})

add_executable(main ${SOURCES} ${HEADERS})

if (UNIX)
    target_link_libraries(main stdc++fs)
endif(UNIX)

# Unit tests
enable_testing()

# Tests insert method
 add_executable(TestAVLinsert tests/TestAVLinsert.cpp src/AVL.cpp)
 target_include_directories(TestAVLinsert PRIVATE ${INCLUDES})
 add_test(AVLinsert TestAVLinsert)

# Tests search method
add_executable(TestAVLsearch tests/TestAVLsearch.cpp src/AVL.cpp)
target_include_directories(TestAVLsearch PRIVATE ${INCLUDES})
add_test(AVLsearch TestAVLsearch)

# Tests delete method
add_executable(TestAVLdelete tests/TestAVLdelete.cpp src/AVL.cpp)
target_include_directories(TestAVLdelete PRIVATE ${INCLUDES})
add_test(AVLdelete TestAVLdelete)

# Tests tree balancing
add_executable(TestAVLbalance tests/TestAVLbalance.cpp src/AVL.cpp)
target_include_directories(TestAVLbalance PRIVATE ${INCLUDES})
add_test(AVLbalance TestAVLbalance)