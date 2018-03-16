cmake_minimum_required(VERSION 3.0)
project(main C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT_CPPFLAGS} -O2")
endif()

set(HEADERS
    ${HEADERS}
    src/AVLTree.h
    src/BTree.h
    )

set(SOURCES
    ${SOURCES}
    src/main.cpp
    src/AVLTree.cpp
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

# Unit/Integration tests
enable_testing(true)

# Tests insert method
 add_executable(TestAVLinsert tests/TestAVLinsert.cpp src/AVLTree.cpp)
 target_include_directories(TestAVLinsert PRIVATE ${INCLUDES})
 add_test(AVLinsert TestAVLinsert)

# Tests search method
add_executable(TestAVLsearch tests/TestAVLsearch.cpp src/AVLTree.cpp)
target_include_directories(TestAVLsearch PRIVATE ${INCLUDES})
add_test(AVLsearch TestAVLsearch)

# Tests erase method
add_executable(TestAVLerase tests/TestAVLerase.cpp src/AVLTree.cpp)
target_include_directories(TestAVLerase PRIVATE ${INCLUDES})
add_test(AVLerase TestAVLerase)

# # Tests sort method
add_executable(TestAVLsort tests/TestAVLsort.cpp src/AVLTree.cpp)
target_include_directories(TestAVLsort PRIVATE ${INCLUDES})
add_test(AVLsort TestAVLsort)

# # Tests range method
add_executable(TestAVLrange tests/TestAVLrange.cpp src/AVLTree.cpp)
target_include_directories(TestAVLrange PRIVATE ${INCLUDES})
add_test(AVLrange TestAVLrange)

# Tests tree balancing
add_executable(TestAVLbalance tests/TestAVLbalance.cpp src/AVLTree.cpp)
target_include_directories(TestAVLbalance PRIVATE ${INCLUDES})
add_test(AVLbalance TestAVLbalance)

# -----------
# BTree tests

# Tests insert method
add_executable(TestBinsert tests/TestBinsert.cpp src/BTree.cpp)
target_include_directories(TestBinsert PRIVATE ${INCLUDES})
add_test(Binsert TestBinsert)

# # Tests search method
add_executable(TestBsearch tests/TestBsearch.cpp src/BTree.cpp)
target_include_directories(TestBsearch PRIVATE ${INCLUDES})
add_test(Bsearch TestBsearch)

# # Tests erase method
add_executable(TestBerase tests/TestBerase.cpp src/BTree.cpp)
target_include_directories(TestBerase PRIVATE ${INCLUDES})
add_test(Berase TestBerase)

# # Tests sort method
add_executable(TestBsort tests/TestBsort.cpp src/BTree.cpp)
target_include_directories(TestBsort PRIVATE ${INCLUDES})
add_test(Bsort TestBsort)

# # Tests range method
add_executable(TestBrange tests/TestBrange.cpp src/BTree.cpp)
target_include_directories(TestBrange PRIVATE ${INCLUDES})
add_test(Brange TestBrange)

# Test that the BTree satisfies all of its properties
add_executable(TestBproperties tests/TestBproperties src/BTree.cpp)
target_include_directories(TestBproperties PRIVATE ${INCLUDES})
add_test(Bproperties TestBproperties)