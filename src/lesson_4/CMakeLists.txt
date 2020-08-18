MESSAGE("------------------------Lesson_4.Texture")

set (Lesson_4 "Lesson_4")

INCLUDE_DIRECTORIES(
	${THIRDPARTY_GLAD_DIR}/include
	${THIRDPARTY_GLFW_DIR}/include
	../Common
	${CONAN_INCLUDE_DIRS_STB_RELEASE}
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
    )

ADD_EXECUTABLE(Lesson_4 ${PROJECT_SOURCE_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
TARGET_LINK_LIBRARIES(Lesson_4 debug glfw3d optimized glfw3)
TARGET_LINK_LIBRARIES(Lesson_4 debug opengl32 optimized opengl32)











