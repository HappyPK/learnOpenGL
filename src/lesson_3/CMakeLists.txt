MESSAGE("------------------------Lesson_3.GLSL")

set (Lesson_3 "Lesson_3")

INCLUDE_DIRECTORIES(
	${THIRDPARTY_GLAD_DIR}/include
	${THIRDPARTY_GLFW_DIR}/include
	../Common
	../Camera
	${CONAN_INCLUDE_DIRS_GLM_RELEASE}
)

LINK_DIRECTORIES(
	${THIRDPARTY_GLFW_DIR}/lib/Debug
	${THIRDPARTY_GLFW_DIR}/lib/Release
)

FILE(GLOB PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES}
    *.cpp
	${THIRDPARTY_GLAD_DIR}/src/*.c
    *.h
	../Common/*.h
	../Common/*.cpp
	../Camera/*.h
	./shader/*.shader
    )

ADD_EXECUTABLE(Lesson_3 ${PROJECT_SOURCE_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
TARGET_LINK_LIBRARIES(Lesson_3 debug glfw3d optimized glfw3)
TARGET_LINK_LIBRARIES(Lesson_3 debug opengl32 optimized opengl32)

file(GLOB_RECURSE project_headers *.h)
file(GLOB_RECURSE project_cpps *.cpp)
file(GLOB_RECURSE project_shaders *.shader)
set(all_files ${project_headers} ${project_cpps} ${project_shaders})
SOURCE_GROUP_BY_DIR(all_files)










