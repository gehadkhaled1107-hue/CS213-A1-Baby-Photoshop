cmake_minimum_required(VERSION 3.19)
project(BabyPhoto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(BabyPhoto
    WIN32 MACOSX_BUNDLE
    main.cpp
    resources.qrc
    widget.cpp widget.h widget.ui
    filterwindow.cpp filterwindow.h filterwindow.ui
    filters.h
)

target_include_directories(BabyPhoto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(BabyPhoto
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS BabyPhoto
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BabyPhoto
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})