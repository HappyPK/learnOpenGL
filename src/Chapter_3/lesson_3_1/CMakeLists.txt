project(Lesson_3_1)
MESSAGE("------------------------Chapter_3.Lesson_3_1 Mesh")

FILE(GLOB PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES}
    *.cpp
	${THIRDPARTY_GLAD_DIR}/src/*.c
    *.h
	./shader/*.*
	./camera/*.*
	./model/*.*
    )
INCLUDE_DIRECTORIES(
	.
	./shader/
	./camera/
	./model/
)
file(GLOB_RECURSE project_headers *.h)
file(GLOB_RECURSE project_cpps *.cpp)
file(GLOB_RECURSE project_shaders *.shader)
set(all_files ${project_headers} ${project_cpps} ${project_shaders})
SOURCE_GROUP_BY_DIR(all_files)

ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} debug glfw3d           optimized glfw3)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} debug opengl32         optimized opengl32)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} debug assimp-vc142-mtd optimized assimp-vc142-mt)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Chapter_3")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${THIRDPARTY_ASSIMP_DIR}/lib/debug/assimp-vc142-mtd.dll  ${BIN_DIR}/debug/assimp-vc142-mtd.dll)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${THIRDPARTY_ASSIMP_DIR}/lib/release/assimp-vc142-mt.dll  ${BIN_DIR}/release/assimp-vc142-mt.dll)











