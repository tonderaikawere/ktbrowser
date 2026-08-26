cmake_minimum_required(VERSION 3.20)
project(KTBrowser VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql Network)
find_package(Qt6 OPTIONAL_COMPONENTS WebEngineWidgets)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/codebrowser
)

set(PROJECT_RESOURCES resources/codebrowser.qrc)

set(PROJECT_SOURCES
    src/main.cpp
    
    # Browser Core
    src/browser/BrowserWindow.cpp
    src/browser/BrowserTab.cpp
    src/browser/TabManager.cpp
    src/browser/NavigationController.cpp
    
    # UI Components
    src/ui/AddressBar.cpp
    src/ui/BrowserToolbar.cpp
    src/ui/TabBar.cpp
    src/ui/NewTabPage.cpp
    src/ui/BookmarkManagerWidget.cpp
    src/ui/HistoryManagerWidget.cpp
    src/ui/DownloadsWidget.cpp
    
    # AdBlock & Tracking Interception
    src/adblock/AdBlockEngine.cpp
    src/adblock/FilterParser.cpp
    src/adblock/FilterRule.cpp
    src/adblock/FilterListManager.cpp
    src/adblock/BlockStatistics.cpp
    src/adblock/WebEngineUrlRequestInterceptor.cpp
    
    # Privacy
    src/privacy/PrivacyManager.cpp
    src/privacy/PrivacyDashboard.cpp
    src/privacy/TrackerProtection.cpp
    src/privacy/PermissionsManagerWidget.cpp
    
    # Database Layer
    src/database/Database.cpp
    src/database/HistoryRepository.cpp
    src/database/BookmarkRepository.cpp
    src/database/SettingsRepository.cpp
    
    # Downloads & Settings
    src/downloads/DownloadManager.cpp
    src/settings/SettingsWindow.cpp
)

set(PROJECT_HEADERS
    include/codebrowser/browser/BrowserWindow.h
    include/codebrowser/browser/BrowserTab.h
    include/codebrowser/browser/TabManager.h
    include/codebrowser/browser/NavigationController.h
    
    include/codebrowser/ui/AddressBar.h
    include/codebrowser/ui/BrowserToolbar.h
    include/codebrowser/ui/TabBar.h
    include/codebrowser/ui/NewTabPage.h
    include/codebrowser/ui/BookmarkManagerWidget.h
    include/codebrowser/ui/HistoryManagerWidget.h
    include/codebrowser/ui/DownloadsWidget.h
    
    include/codebrowser/adblock/AdBlockEngine.h
    include/codebrowser/adblock/FilterParser.h
    include/codebrowser/adblock/FilterRule.h
    include/codebrowser/adblock/FilterListManager.h
    include/codebrowser/adblock/BlockStatistics.h
    include/codebrowser/adblock/WebEngineUrlRequestInterceptor.h
    
    include/codebrowser/privacy/PrivacyManager.h
    include/codebrowser/privacy/PrivacyDashboard.h
    include/codebrowser/privacy/TrackerProtection.h
    include/codebrowser/privacy/PermissionsManagerWidget.h
    
    include/codebrowser/database/Database.h
    include/codebrowser/database/HistoryRepository.h
    include/codebrowser/database/BookmarkRepository.h
    include/codebrowser/database/SettingsRepository.h
    
    include/codebrowser/downloads/DownloadManager.h
    include/codebrowser/settings/SettingsWindow.h
)

set(WEBENGINE_LIBS "")
if (Qt6WebEngineWidgets_FOUND)
    add_compile_definitions(CODEBROWSER_HAS_WEBENGINE=1)
    set(WEBENGINE_LIBS Qt6::WebEngineWidgets)
endif()

# WIN32 flag prevents terminal window from opening
add_executable(ktbrowser WIN32 ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_RESOURCES})

if (MINGW OR GNU)
    target_link_options(ktbrowser PRIVATE -mwindows -static-libgcc -static-libstdc++)
endif()

target_link_libraries(ktbrowser PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    ${WEBENGINE_LIBS}
)

# Enable Testing
enable_testing()

add_executable(test_adblock
    tests/adblock/TestAdBlock.cpp
    src/adblock/AdBlockEngine.cpp
    src/adblock/FilterParser.cpp
    src/adblock/FilterRule.cpp
    src/adblock/FilterListManager.cpp
    src/adblock/BlockStatistics.cpp
    include/codebrowser/adblock/AdBlockEngine.h
    include/codebrowser/adblock/BlockStatistics.h
)
target_link_libraries(test_adblock PRIVATE Qt6::Core Qt6::Network)
add_test(NAME AdBlockTest COMMAND test_adblock)

add_executable(test_database
    tests/database/TestDatabase.cpp
    src/database/Database.cpp
    src/database/HistoryRepository.cpp
    src/database/BookmarkRepository.cpp
    src/database/SettingsRepository.cpp
)
target_link_libraries(test_database PRIVATE Qt6::Core Qt6::Sql)
add_test(NAME DatabaseTest COMMAND test_database)

# CPack Installer Configuration
set(CPACK_PACKAGE_NAME "KTBrowser")
set(CPACK_PACKAGE_VENDOR "Kawerify Tech")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "KT Browser by Kawerify Tech - Fast, Clean, Security-Focused Web Browser")
set(CPACK_GENERATOR "ZIP;NSIS")
include(CPack)
