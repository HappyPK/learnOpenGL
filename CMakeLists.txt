cmake_minimum_required(VERSION 3.12.0)

project(Learn.opengl)

##use conan
set(USE_CONAN ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
MACRO( OPTION_WITH_DEFAULT OPTION_NAME OPTION_STRING OPTION_DEFAULT )
	IF( NOT DEFINED ${OPTION_NAME} )
		SET( ${OPTION_NAME} ${OPTION_DEFAULT} )
	ENDIF( NOT DEFINED ${OPTION_NAME} )
	OPTION( ${OPTION_NAME} "${OPTION_STRING}" ${${OPTION_NAME}} )
ENDMACRO( OPTION_WITH_DEFAULT OPTION_NAME OPTION_STRING OPTION_DEFAULT )

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
set(USE_CONAN ON)


############################
# Check 32/64 bit platform #
if (${CMAKE_SIZEOF_VOID_P} MATCHES "8") # It is 64bit, otherwise 32 bit systems match 4
	set(PlatformName x64)
else (${CMAKE_SIZEOF_VOID_P} MATCHES "4")
	set(PlatformName x86)
endif(${CMAKE_SIZEOF_VOID_P} MATCHES "8")

message(STATUS "Build ${PlatformName}")

if(UNIX)
    SET(CMAKE_C_FLAGS "-std=c17 -fPIC")
    SET(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -lstdc++fs")
else(UNIX)
    SET(CMAKE_CXX_STANDARD 17)
endif(UNIX)

set (BIN_DIR "${CMAKE_SOURCE_DIR}/bin/vc16/${PlatformName}")
set (THIRDPARTY_GLAD_DIR "${CMAKE_SOURCE_DIR}/3rdParty/glad")
set (THIRDPARTY_GLFW_DIR "${CMAKE_SOURCE_DIR}/3rdParty/GLFW")
set (THIRDPARTY_ASSIMP_DIR "${CMAKE_SOURCE_DIR}/3rdParty/assimp5.0.1")
message("--------------------------------")
message("${BIN_DIR}")
message("--------------------------------")

LINK_DIRECTORIES(${BIN_DIR})
# ------------------------------------------------------------------------------
# OpenMP - used in voxel algorithm
# ------------------------------------------------------------------------------
find_package(OpenMP)
if (OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

MACRO(SOURCE_GROUP_BY_DIR source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
			
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
ENDMACRO(SOURCE_GROUP_BY_DIR)

add_subdirectory(src/Chapter_1)
add_subdirectory(src/Chapter_2)
add_subdirectory(src/Chapter_3)
add_subdirectory(src/review1-3)

























































