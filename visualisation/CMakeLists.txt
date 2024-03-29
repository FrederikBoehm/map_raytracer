#project(visualisation LANGUAGES CXX)

set(SOURCE_FILES visualisation.cpp src/gl_visualiser.cpp src/image_writer.cpp)
set(HEADER_FILES visualisation.hpp include/gl_visualiser.hpp include/image_writer.hpp)

add_library(visualisation STATIC ${SOURCE_FILES} ${HEADER_FILES})

#install(TARGETS visualisation DESTINATION lib)

#set_target_properties(visualisation PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(visualisation PRIVATE include)
target_include_directories(visualisation PRIVATE "../3rdparty/glm")
if (GUI)
target_include_directories(visualisation PRIVATE "../3rdparty/glad")
target_include_directories(visualisation PRIVATE "../3rdparty/glfw")
endif()
target_include_directories(visualisation PRIVATE "../3rdparty/stb")
target_include_directories(visualisation PRIVATE "../common")

target_link_libraries(visualisation PRIVATE glm)
if (GUI)
target_link_libraries(visualisation PRIVATE glad)
target_link_libraries(visualisation PRIVATE glfw)
endif()

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SOURCE_FILES} ${HEADER_FILES})

if (GUI)
target_compile_definitions(visualisation PRIVATE GUI_PLATFORM)
endif()
target_compile_features(visualisation PRIVATE cxx_std_17)
