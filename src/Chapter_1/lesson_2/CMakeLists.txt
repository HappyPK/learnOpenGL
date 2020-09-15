project(Lesson_1_2)
MESSAGE("------------------------Chapter_1.Lesson_2.triangle")

FILE(GLOB PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES}
    *.cpp
	${THIRDPARTY_GLAD_DIR}/src/*.c
    *.h
	../../Common/*.h
	../../Common/*.cpp
	../../Camera/*.h
    )

ADD_EXECUTABLE(Lesson_1_2 ${PROJECT_SOURCE_FILES})
SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
TARGET_LINK_LIBRARIES(Lesson_1_2 debug glfw3d optimized glfw3)
TARGET_LINK_LIBRARIES(Lesson_1_2 debug opengl32 optimized opengl32)

set_property(TARGET Lesson_1_2 PROPERTY FOLDER "Chapter_1")












