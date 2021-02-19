INCLUDE_DIRECTORIES(
	${THIRDPARTY_GLAD_DIR}/include
	${THIRDPARTY_GLFW_DIR}/include
	../Common
	../Camera
	${CONAN_INCLUDE_DIRS_STB_RELEASE}
	${CONAN_INCLUDE_DIRS_GLM_RELEASE}
)

LINK_DIRECTORIES(
	${THIRDPARTY_GLFW_DIR}/lib/Debug
	${THIRDPARTY_GLFW_DIR}/lib/Release
)

add_subdirectory(lesson_1)
add_subdirectory(lesson_2)
add_subdirectory(lesson_3)
add_subdirectory(lesson_4)
add_subdirectory(lesson_5)
add_subdirectory(lesson_6)
add_subdirectory(lesson_7)
add_subdirectory(lesson_8)
add_subdirectory(lesson_9)