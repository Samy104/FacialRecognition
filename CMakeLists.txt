cmake_minimum_required(VERSION 3.3)
project(FacialRecognition)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})
# Link Directories and include directories
link_directories($ENV{WXWIN}/lib/gcc_lib)

include_directories(${wxWidgets_INCLUDE_DIRS}
        $ENV{WXWIN}/lib/gcc_lib/mswu
        $ENV{OPENCV_HOME}/build/include)

# Linker options
set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCE_FILES
        main.cpp
        wxMainFrame.cpp wxMainFrame.h RecognitionProcess.cpp RecognitionProcess.h Image.cpp Image.h ImageManager.cpp ImageManager.h)

add_executable(FacialRecognition  ${SOURCE_FILES} main.cpp)
target_link_libraries(FacialRecognition ${wxWidgets_LIBRARIES})