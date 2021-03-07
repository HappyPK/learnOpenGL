INCLUDE_DIRECTORIES(
	${THIRDPARTY_GLAD_DIR}/include
	${THIRDPARTY_GLFW_DIR}/include
	${CONAN_INCLUDE_DIRS_STB_RELEASE}
	${CONAN_INCLUDE_DIRS_GLM_RELEASE}
)

LINK_DIRECTORIES(
	${THIRDPARTY_GLFW_DIR}/lib/Debug
	${THIRDPARTY_GLFW_DIR}/lib/Release
)

add_subdirectory(lesson_2_1)
add_subdirectory(lesson_2_2)
add_subdirectory(lesson_2_3)
add_subdirectory(lesson_2_4)
add_subdirectory(lesson_2_5)
add_subdirectory(lesson_2_6)
add_subdirectory(lesson_2_7)
add_subdirectory(lesson_2_8)
