project(Lesson_1_3)
MESSAGE("------------------------Chapter_1.Lesson_3.GLSL")

set (Lesson_3 "Lesson_3")

FILE(GLOB PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES}
    *.cpp
	${THIRDPARTY_GLAD_DIR}/src/*.c
    *.h
	../../Common/*.h
	../../Common/*.cpp
	../../Camera/*.h
	./shader/*.shader
    )

ADD_EXECUTABLE(Lesson_1_3 ${PROJECT_SOURCE_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
TARGET_LINK_LIBRARIES(Lesson_1_3 debug glfw3d optimized glfw3)
TARGET_LINK_LIBRARIES(Lesson_1_3 debug opengl32 optimized opengl32)

file(GLOB_RECURSE project_headers *.h)
file(GLOB_RECURSE project_cpps *.cpp)
file(GLOB_RECURSE project_shaders *.shader)
set(all_files ${project_headers} ${project_cpps} ${project_shaders})
SOURCE_GROUP_BY_DIR(all_files)

set_property(TARGET Lesson_1_3 PROPERTY FOLDER "Chapter_1")











