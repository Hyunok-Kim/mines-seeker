cmake_minimum_required(VERSION 3.16)

project(mines-seeker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets Quick Sql OPTIONAL_COMPONENTS LinguistTools)


qt_standard_project_setup()

qt_add_executable(appmines-seeker
    main.cpp
)
if(Qt6LinguistTools_FOUND)
    qt_add_translation(QM_FILES mines_es.ts)
    target_sources(appmines-seeker PRIVATE ${QM_FILES})
endif()

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.cpp)
list(REMOVE_ITEM SOURCES main.cpp)
file(GLOB QML_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qml)

file(GLOB_RECURSE IMAGE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} images/*.svg images/*.png)
list(REMOVE_ITEM IMAGE_FILES images/Logo512_BG.png)

file(GLOB_RECURSE SOUND_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} sounds/*.wav)
file(GLOB_RECURSE FONT_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} fonts/*.otf fonts/*.ttf)

qt_add_qml_module(appmines-seeker
    URI mines-seeker
    VERSION 1.0
    SOURCES ${SOURCES}
    QML_FILES ${QML_FILES}
    RESOURCES ${IMAGE_FILES}
    RESOURCES ${SOUND_FILES}
    NO_RESOURCE_TARGET_PATH
)

qt_add_resources(appmines-seeker resources
    PREFIX "/"
    FILES images/appIcon.png images/Logo512_BG.png
    FILES ${FONT_FILES}
)

target_link_libraries(appmines-seeker
    PRIVATE Qt6::Widgets Qt6::Quick Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appmines-seeker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
