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
)

# Qt's Meta-Object Compiler (moc) for headers
qt5_wrap_cpp(MOC_HEADERS ${HEADERS})

add_executable(CypherVault ${SOURCES} ${MOC_HEADERS})

target_include_directories(CypherVault PRIVATE src)

# Link the libraries for Widgets and Svg
target_link_libraries(CypherVault Qt5::Widgets Qt5::Svg)
