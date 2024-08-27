add_executable(back_camera_assist main.cpp dynamics.cpp video_viz.cpp) 

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package((Curses REQUIRED))
include_directories(${CURSES_INCLUDE_DIR})

target_include_directories(back_camera_assist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(back_camera_assist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dynamics.h ${OpenCV_LIBS})

target_link_libraries(back_camera_assist PUBLIC ${PYTHON_LIBRARIES})
target_link_libraries(back_camera_assist ${CURSES_LIBRARIES})