cmake_minimum_required(VERSION 3.3)
project(FacialRecognition)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

#WXWIDGETS Directory
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)

#OpenCV Directory
set(OpenCV_DIR $ENV{OPENCV_BUILD})
find_package(OpenCV COMPONENTS opencv_core opencv_highgui opencv_face REQUIRED)

include(${wxWidgets_USE_FILE})

include_directories(
        ${wxWidgets_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

link_directories(
        ${wxWidgets_LIBRARIES}
        ${OpenCV_LIBRARIES}
)

set(CMAKE_CXX_FLAGS "-std=c++11 -static")

set(SOURCE_FILES
        main.cpp
        wxMainFrame.cpp
        RecognitionProcess.cpp
        Image.cpp
        ImageManager.cpp
        ImagePanel.cpp VideoPanel.cpp VideoPanel.h Directory.cpp Directory.h)

add_executable(FacialRecognition ${SOURCE_FILES})

target_link_libraries(FacialRecognition
        ${wxWidgets_LIBRARIES}
        ${OpenCV_LIBRARIES}
        )