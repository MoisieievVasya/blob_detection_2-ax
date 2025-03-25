cmake_minimum_required(VERSION 3.30)
project(blod_detection_2_ax)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 20)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/c_library_v2)

add_executable(testVideoProc videoProc/testVideoProc.cpp videoProc/videoProc.cpp communication/mavlinkCommand.cpp)
target_link_libraries(testVideoProc ${OpenCV_LIBS} ${REQUIRED_LIBRARIES})

add_executable(testControls videoProc/testVideoProc.cpp videoProc/videoProc.cpp controls/controls.cpp communication/mavlinkCommand.cpp)
target_link_libraries(testControls ${OpenCV_LIBS} ${REQUIRED_LIBRARIES})

add_executable(main main.cpp
        communication/mavlinkCommand.cpp
        communication/mavlinkCommand.h
        controls/controls.cpp
        controls/controls.h
        videoProc/videoProc.cpp
)
target_link_libraries(main ${OpenCV_LIBS} ${REQUIRED_LIBRARIES})

add_subdirectory(videoProc)
add_subdirectory(controls)
add_subdirectory(communication)