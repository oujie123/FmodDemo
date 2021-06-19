cmake_minimum_required(VERSION 3.4.1)  #最低支持的Cmake版本

# TODO 引入头文件,该头文件是相对CMakeList.txt的
include_directories("inc")

# 批量导入所有源文件
file(GLOB allCpp *.c *.h *.cpp)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${allCpp})

# 引入库文件,设置环境变量
# 引入的库一定放在jniLibs目录中
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

# 查找库，防止多次寻找库
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

target_link_libraries( # Specifies the target library.
        #总库名字
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        fmod
        fmodL #链接到总so库中
        )