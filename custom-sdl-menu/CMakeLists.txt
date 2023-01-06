# CMakeList.txt : projet CMake pour sdl-start-menu, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

find_package(SDL2 REQUIRED) 
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(pugixml REQUIRED) 

# Detect the platform
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
else()
    set(ARCH "x32")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building for Linux")
    # Set Linux-specific options and libraries here
    set(PLATFORM_LINK_LIBS X11)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Building for Windows")
    # Set Windows-specific options and libraries here
    set(PLATFORM_LINK_LIBS user32)

    add_custom_target(libs ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/json ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
        DEPENDS ${MY_TARGET}
        COMMENT "Copy libs to binary dir.")
endif()

add_custom_target(fonts ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/fonts ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${MY_TARGET}
    COMMENT "Copy fonts to binary dir.")
add_custom_target(images ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/images ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${MY_TARGET}
    COMMENT "Copy images to binary dir.")
add_custom_target(json ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/libs/${ARCH} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${MY_TARGET}
    COMMENT "Copy json to binary dir.")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (${PROJECT_NAME} "main.cpp"  "Button.h" "Button.cpp" "Menu.h" "Menu.cpp" "Logger.h" "Logger.cpp" "constants.h" "ScreenSize.cpp" "MySDL.h" "MySDL.cpp")

#target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image pugixml::pugixml ${PLATFORM_LINK_LIBS})
target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image ${PLATFORM_LINK_LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
