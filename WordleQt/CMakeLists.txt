cmake_minimum_required(VERSION 3.5)

project(WordleQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the path to the icon resource in the build directory
set(ICON_RESOURCE "${CMAKE_SOURCE_DIR}/resources/wordle-icon.ico")

# Add the icon to the executable (Windows-specific)
if(WIN32)
    # Set the path where the icon will be copied in the build directory
    set(ICON_PATH "${ICON_RESOURCE}")

    # Copy the icon file to the build directory (no need to copy if it's already there)
    configure_file(${ICON_PATH} ${ICON_PATH} COPYONLY)

    # Add the copied icon file to the list of EXTRA_FILES
    set(EXTRA_FILES ${EXTRA_FILES} ${ICON_PATH})
endif()
message("ICON_RESOURCE: ${ICON_RESOURCE}")


set(PROJECT_SOURCES
    fiveLetterWords.txt
    Game.cpp
    Game.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    wordle-icon.ico
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(WordleQt ${PROJECT_SOURCES} ${EXTRA_FILES}
)

# Set the WIN32_EXECUTABLE property to specify the icon (Windows-specific)
if(WIN32)
    set_target_properties(WordleQt PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

target_link_libraries(WordleQt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.WordleQt)
endif()
set_target_properties(WordleQt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
)

include(GNUInstallDirs)
install(TARGETS WordleQt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(WordleQt)
endif()
