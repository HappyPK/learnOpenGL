project(Lesson_1_10)
MESSAGE("------------------------Chapter_1.Lesson_9.Camera_Class")

FILE(GLOB PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES}
    *.cpp
	${THIRDPARTY_GLAD_DIR}/src/*.c
    *.h
	./shader/*.*
	./camera/*.*
    )
	
file(GLOB_RECURSE project_headers *.h)
file(GLOB_RECURSE project_cpps *.cpp)
file(GLOB_RECURSE project_shaders *.shader)
set(all_files ${project_headers} ${project_cpps} ${project_shaders})
SOURCE_GROUP_BY_DIR(all_files)

ADD_EXECUTABLE(Lesson_1_10 ${PROJECT_SOURCE_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
TARGET_LINK_LIBRARIES(Lesson_1_10 debug glfw3d optimized glfw3)
TARGET_LINK_LIBRARIES(Lesson_1_10 debug opengl32 optimized opengl32)

set_property(TARGET Lesson_1_10 PROPERTY FOLDER "Chapter_1")












