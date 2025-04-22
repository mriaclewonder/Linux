cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 设置输出目录
set(OUTPUT_DIR ${PROJECT_BINARY_DIR}/bin)

# 创建输出目录
file(MAKE_DIRECTORY ${OUTPUT_DIR})


# 为第一个程序创建可执行文件
add_executable(rwlock src/rwlock.c ${SHARED_SOURCES})

# 为第二个程序创建可执行文件
add_executable(DeadLock src/DeadLock.c ${SHARED_SOURCES})

# 设置可执行文件的输出目录
set_target_properties(rwlock PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_target_properties(DeadLock PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# 如果需要链接库，可以使用 target_link_libraries
# target_link_libraries(main1 pthread)
# target_link_libraries(main2 pthread)