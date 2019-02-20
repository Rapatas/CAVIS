cmake_minimum_required(VERSION 3.0)

project(
	CAVIS
	VERSION 1.3.0
	LANGUAGES CXX
)

# Dependencies {{{

list(APPEND CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/cmake/modules"
)

# SFML
find_package(
	SFML 2 REQUIRED
	window system
)

# }}}

# Definitions {{{

set(
	${PROJECT_NAME}_src
	./src/pixels.cpp
	./src/window.cpp
	./src/cavis.cpp
	./src/grid.cpp
)

set(
	${PROJECT_NAME}_headers
	./include/cavis.h
	./include/pixels.h
	./include/grid.h
	./include/agent.h
	./include/window.h
	./include/cellular_automaton.h
)

add_library(
	${PROJECT_NAME}
	STATIC
	${${PROJECT_NAME}_src}
)

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
		${SFML_LIBRARIES}
		${SFML_DEPENDENCIES}
)
# }}}

# Install {{{

set(destination lib/cmake/${PROJECT_NAME})

# Packaging {{{

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY ExactVersion
)

install(
	FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION ${destination}
)

configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/cmake/configs/${PROJECT_NAME}Config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION ${destination}
)

install(
	FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	DESTINATION ${destination}
)

# }}}

install(
	FILES ${${PROJECT_NAME}_headers}
	DESTINATION include
)

install(
	TARGETS ${PROJECT_NAME}
	EXPORT  ${PROJECT_NAME}Targets
	ARCHIVE DESTINATION lib COMPONENT Development
)

install(
	EXPORT      ${PROJECT_NAME}Targets
	FILE        ${PROJECT_NAME}Targets.cmake
	NAMESPACE   ${PROJECT_NAME}::
	DESTINATION ${destination}
)
# }}}
