
cmake_minimum_required(VERSION 3.0)

# Required for YCM to work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
	CAVIS
	VERSION 0.0.0
	LANGUAGES CXX
)

# ===========
# Definitions
#============

add_library(
	${PROJECT_NAME}
	./source/cavis.cpp
)

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)

# =======
# Testing
# =======

# run "cmake .. && make && make test"
# OR  "cmake .. && make && ctest"

include(CTest)
if (BUILD_TESTING)

	add_executable(
		test_${PROJECT_NAME}
		./tests/main.cpp
	)

	target_link_libraries(
		test_${PROJECT_NAME}
		PRIVATE
			${PROJECT_NAME}
			${SFML_LIBRARIES}
			${SFML_DEPENDENCIES}
	)

	add_test(
		NAME test_${PROJECT_NAME}
		COMMAND test_${PROJECT_NAME}
	)

endif()

