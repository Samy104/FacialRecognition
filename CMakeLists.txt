cmake_minimum_required(VERSION 3.3)
project(FacialRecognition)

#WXWIDEGS Directory
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)

#OpenCV Directory
set(OpenCV_DIR $ENV{OPENCV_BUILD})
find_package(OpenCV REQUIRED)

include(${wxWidgets_USE_FILE})
# Link Directories and include directories

link_directories(
        ${wxWidgets_LIBRARIES}
        ${OpenCV_LIBRARIES}
)

include_directories(
        ${wxWidgets_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        )

set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCE_FILES
        main.cpp
        wxMainFrame.cpp
        RecognitionProcess.cpp
        Image.cpp
        ImageManager.cpp
        )

add_executable(FacialRecognition ${SOURCE_FILES})

target_link_libraries(FacialRecognition
        ${wxWidgets_LIBRARIES}
        ${OpenCV_LIBRARIES}
        )