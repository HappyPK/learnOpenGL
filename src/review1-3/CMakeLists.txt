INCLUDE_DIRECTORIES(
	${THIRDPARTY_GLAD_DIR}/include
	${THIRDPARTY_GLFW_DIR}/include
	${THIRDPARTY_ASSIMP_DIR}/include
	${CONAN_INCLUDE_DIRS_STB_RELEASE}
	${CONAN_INCLUDE_DIRS_GLM_RELEASE}
)

LINK_DIRECTORIES(
	${THIRDPARTY_GLFW_DIR}/lib/Debug
	${THIRDPARTY_GLFW_DIR}/lib/Release
	
	${THIRDPARTY_ASSIMP_DIR}/lib/Debug
	${THIRDPARTY_ASSIMP_DIR}/lib/Release
)

add_subdirectory(review1)
add_subdirectory(review2)
add_subdirectory(review3)

