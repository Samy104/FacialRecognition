cmake_minimum_required(VERSION 3.3)
project(FacialRecognition)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

#WXWIDGETS Directory
if(WIN32)
    set(wxWidgets_ROOT_DIR $ENV{WXWIN})
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

else()
    set(wxWidgets_ROOT_DIR $ENV{WXWIDGETS_HOME})
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()
find_package(wxWidgets COMPONENTS core base REQUIRED)

#OpenCV Directory
set(OpenCV_DIR $ENV{OPENCV_BUILD})
find_package(OpenCV COMPONENTS core highgui face REQUIRED)

include(${wxWidgets_USE_FILE})

include_directories(
        ${wxWidgets_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        $ENV{WEBSOCKETPP_HOME}
        $ENV{WEBSOCKETPP_HOME}/include
        $ENV{BOOST_HOME}
        $ENV{BOOST_HOME}/boost
)

link_directories(
        ${wxWidgets_LIBRARIES}
        ${OpenCV_LIBRARIES}
        $ENV{BOOST_HOME}/lib/gcc
)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCE_FILES
        main.cpp
        wxMainFrame.cpp
        RecognitionProcess.cpp
        Image.cpp
        ImageManager.cpp
        ImagePanel.cpp
        VideoPanel.cpp
        Directory.cpp
        WebSocketConnector.cpp
        )

add_executable(FacialRecognition ${SOURCE_FILES})

target_link_libraries(FacialRecognition
        ${wxWidgets_LIBRARIES}
        ${OpenCV_LIBS}
        boost_thread-mgw51-mt-1_59
        boost_system-mgw51-mt-1_59
        )