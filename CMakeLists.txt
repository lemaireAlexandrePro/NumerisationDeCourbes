cmake_minimum_required(VERSION 2.6)

project(NumerisationDeCourbes)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS interfaces)

find_package(Qt4 4.8.7 REQUIRED QtCore QtGui)

qt4_wrap_cpp(MOC_FILES
    include/EcranPrincipal.h
    include/FenetreDocumentation.h
    include/FenetreGraphique.h
    include/FenetreParametresAffichage.h
    include/FenetreParametresConversion.h
    include/FenetreParametresExport.h
    include/FenetreParametresRecherche.h
    include/VueGraphiqueEtude.h)

add_executable(NumerisationDeCourbes
    source/EcranPrincipal.cpp
    source/Etude.cpp
    source/FenetreDocumentation.cpp
    source/FenetreGraphique.cpp
    source/FenetreParametresAffichage.cpp
    source/FenetreParametresConversion.cpp
    source/FenetreParametresExport.cpp
    source/FenetreParametresRecherche.cpp
    source/Image.cpp
    source/NumerisationDeCourbes.cpp
    source/Outils.cpp
    source/ParametresAffichage.cpp
    source/ParametresAxe.cpp
    source/ParametresConversion.cpp
    source/Parametres.cpp
    source/ParametresExport.cpp
    source/ParametresFichiers.cpp
    source/ParametresGraphique.cpp
    source/ParametresPoint.cpp
    source/ParametresRecherche.cpp
    source/ParametresTrait.cpp
    source/Point.cpp
    source/Repere.cpp
    source/VueGraphiqueEtude.cpp
    interfaces/EcranPrincipal.ui
    interfaces/FenetreDocumentation.ui
    interfaces/FenetreGraphique.ui
    interfaces/FenetreParametresAffichage.ui
    interfaces/FenetreParametresConversion.ui
    interfaces/FenetreParametresExport.ui
    interfaces/FenetreParametresRecherche.ui
    resources/Ressources.qrc
    ${MOC_FILES})

target_link_libraries(NumerisationDeCourbes PUBLIC Qt4::QtCore Qt4::QtGui)

target_include_directories(NumerisationDeCourbes PUBLIC include)

install(TARGETS NumerisationDeCourbes DESTINATION bin)

# Qwt (optional)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(FindQwt)
if(QWT_FOUND)
    add_compile_definitions(ENABLE_QWT)
    target_link_libraries(NumerisationDeCourbes PUBLIC ${QWT_LIBRARIES})
    target_include_directories(NumerisationDeCourbes PUBLIC ${QWT_INCLUDE_DIRS})
endif(QWT_FOUND)
