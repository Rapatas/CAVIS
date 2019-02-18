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
	graphics window system
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
	${${PROJECT_NAME}_src}
)

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
		PUBLIC_HEADER
			"${${PROJECT_NAME}_headers}"
)

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
		${SFML_LIBRARIES}
		${SFML_DEPENDENCIES}
)
# }}}

# Packaging {{{

include(CMakePackageConfigHelpers)

set(destination lib/cmake/${PROJECT_NAME})

write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/cmake/configs/${PROJECT_NAME}Config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION ${destination}
)

install(
	FILES
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	DESTINATION ${destination}
)

install(
	TARGETS       ${PROJECT_NAME}
	EXPORT        ${PROJECT_NAME}Targets

	LIBRARY       DESTINATION lib                     COMPONENT Runtime
	RUNTIME       DESTINATION bin                     COMPONENT Runtime
	BUNDLE        DESTINATION bin                     COMPONENT Runtime

	ARCHIVE       DESTINATION lib                     COMPONENT Development
	PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} COMPONENT Development
)

install(
	EXPORT      ${PROJECT_NAME}Targets
	FILE        ${PROJECT_NAME}Targets.cmake
	NAMESPACE   ${PROJECT_NAME}::
	DESTINATION ${destination}
)
# }}}

