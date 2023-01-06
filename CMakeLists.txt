# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8) 

set(PROJECT_NAME "custom-sdl-menu")

project (${PROJECT_NAME})

# Incluez les sous-projets.
add_subdirectory (${PROJECT_NAME})
