file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(SOURCE ${SRC_FILES})

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)
add_executable(TaggedPointer ${SOURCE})

# 为 TaggedPointer 目标添加 /permissive 标志
target_compile_options(TaggedPointer PRIVATE
    # 检查编译器是否为 MSVC
    "$<$<CXX_COMPILER_ID:MSVC>:/permissive>"
)

target_include_directories(TaggedPointer PUBLIC include)
target_link_libraries(TaggedPointer PUBLIC fmt::fmt gtest::gtest benchmark::benchmark_main) 

if(!WIN32)
    target_link_libraries(TaggedPointer PUBLIC pthread)
endif()

set_target_properties(TaggedPointer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

