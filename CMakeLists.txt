cmake_minimum_required(VERSION 3.3)
project(FacialRecognition)

# Linker options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)

# Link Directories and include directories
link_directories($ENV{WXWIDGETS_HOME}/lib)

include_directories($ENV{WXWIDGETS_HOME}/include
                    $ENV{OPENCV_HOME}/build/include)



add_executable(FacialRecognition ${SOURCE_FILES})

find_package(wxWidgets COMPONENTS net gl core base)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    # and for each of your dependent executable/library targets:
    target_link_libraries(<YourTarget> ${wxWidgets_LIBRARIES})
endif()

# Linking the libraries
TARGET_LINK_LIBRARIES(FacialRecognition
        ${OpenCV_LIBS}
        wxWidgets)