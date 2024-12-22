cmake_minimum_required(VERSION 3.16)
project(CypherVault)

set(CMAKE_CXX_STANDARD 17)

# Find Qt packages (Widgets and Svg)
find_package(Qt5 REQUIRED COMPONENTS Widgets Svg)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/ThemeManager.cpp
    src/SettingsPage.cpp
    src/MainContentPage.cpp
    src/Utils.cpp
    src/TitleBar.cpp
    src/SvgManager.cpp
    src/SideBar.cpp
    src/OSDetector.cpp
    src/ConfigManager.cpp
    src/Globals.cpp
    src/ExitConfirmationDialog.cpp
    src/TrayManager.cpp
)

set(HEADERS
    src/MainWindow.h
    src/ThemeManager.h
    src/SettingsPage.h
    src/MainContentPage.h
    src/Utils.h
    src/TitleBar.h
    src/SvgIcons.h
    src/SvgManager.h
    src/SideBar.h
    src/OSDetector.h
    src/ConfigManager.h
    src/Globals.h
    src/ExitConfirmationDialog.h
    src/TrayManager.h
)

# Add the resource file to the project
set(RESOURCE_FILE src/resources.qrc)

# Qt's Meta-Object Compiler (moc) for headers
qt5_wrap_cpp(MOC_HEADERS ${HEADERS})

# Process the .qrc file with qt5_add_resources
qt5_add_resources(RESOURCES ${RESOURCE_FILE})

# Add the executable and include the resource files
add_executable(CypherVault ${SOURCES} ${MOC_HEADERS} ${RESOURCES})

target_include_directories(CypherVault PRIVATE src dependencies/toml++)

# Link the libraries for Widgets and Svg
target_link_libraries(CypherVault Qt5::Widgets Qt5::Svg)
