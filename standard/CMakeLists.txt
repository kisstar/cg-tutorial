cmake_minimum_required(VERSION 3.0)
project(
	App
	VERSION 0.1.0
	LANGUAGES CXX C
)

# Include the file that defines target_treat_all_warnings_as_errors
# (I do this because I reuse this function across many projects and
# want to keep this main file easy to read).
include(${PROJECT_SOURCE_DIR}/../utils.cmake)

include_directories(${PROJECT_SOURCE_DIR}/../third-party/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/../third-party/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create the App executable target with one source file
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/glfw/lib-x86_64)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/glad/src GLAD_SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(App
	${GLFW_SRC_LIST}
	${GLAD_SRC_LIST}
	${SRC_LIST}
	main.cpp
)
target_link_libraries(App libglfw.3.dylib)

# Use C++17
set_target_properties(App PROPERTIES CXX_STANDARD 17)

# Turn all warnings on and treat them as errors so that are not
# tempted to ignore them (See utils.cmake for details).
target_treat_all_warnings_as_errors(App)
