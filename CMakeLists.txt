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

set(PROJECT_RESOURCES resources/ktbrowser.qrc)
if (WIN32)
    list(APPEND PROJECT_RESOURCES resources/ktbrowser.rc)
endif()

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
    include/ktbrowser/browser/BrowserWindow.h
    include/ktbrowser/browser/BrowserTab.h
    include/ktbrowser/browser/TabManager.h
    include/ktbrowser/browser/NavigationController.h
    
    include/ktbrowser/ui/AddressBar.h
    include/ktbrowser/ui/BrowserToolbar.h
    include/ktbrowser/ui/TabBar.h
    include/ktbrowser/ui/NewTabPage.h
    include/ktbrowser/ui/BookmarkManagerWidget.h
    include/ktbrowser/ui/HistoryManagerWidget.h
    include/ktbrowser/ui/DownloadsWidget.h
    
    include/ktbrowser/adblock/AdBlockEngine.h
    include/ktbrowser/adblock/FilterParser.h
    include/ktbrowser/adblock/FilterRule.h
    include/ktbrowser/adblock/FilterListManager.h
    include/ktbrowser/adblock/BlockStatistics.h
    include/ktbrowser/adblock/WebEngineUrlRequestInterceptor.h
    
    include/ktbrowser/privacy/PrivacyManager.h
    include/ktbrowser/privacy/PrivacyDashboard.h
    include/ktbrowser/privacy/TrackerProtection.h
    include/ktbrowser/privacy/PermissionsManagerWidget.h
    
    include/ktbrowser/database/Database.h
    include/ktbrowser/database/HistoryRepository.h
    include/ktbrowser/database/BookmarkRepository.h
    include/ktbrowser/database/SettingsRepository.h
    
    include/ktbrowser/downloads/DownloadManager.h
    include/ktbrowser/settings/SettingsWindow.h
)

set(WEBENGINE_LIBS "")
if (Qt6WebEngineWidgets_FOUND)
    add_compile_definitions(KTBROWSER_HAS_WEBENGINE=1)
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
    include/ktbrowser/adblock/AdBlockEngine.h
    include/ktbrowser/adblock/BlockStatistics.h
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

add_executable(test_privacy
    tests/privacy/TestPrivacy.cpp
    src/privacy/PrivacyManager.cpp
    src/privacy/TrackerProtection.cpp
)
target_link_libraries(test_privacy PRIVATE Qt6::Core Qt6::Network)
add_test(NAME PrivacyTest COMMAND test_privacy)

add_executable(test_downloads
    tests/downloads/TestDownloads.cpp
    src/downloads/DownloadManager.cpp
)
target_link_libraries(test_downloads PRIVATE Qt6::Core)
add_test(NAME DownloadsTest COMMAND test_downloads)

add_executable(test_browser
    tests/browser/TestBrowser.cpp
    src/browser/NavigationController.cpp
    src/database/Database.cpp
    src/database/SettingsRepository.cpp
)
target_link_libraries(test_browser PRIVATE Qt6::Core Qt6::Sql)
add_test(NAME BrowserTest COMMAND test_browser)

add_executable(test_settings
    tests/settings/TestSettings.cpp
    src/database/Database.cpp
    src/database/SettingsRepository.cpp
)
target_link_libraries(test_settings PRIVATE Qt6::Core Qt6::Sql)
add_test(NAME SettingsTest COMMAND test_settings)

add_executable(test_ui
    tests/ui/TestUI.cpp
    src/ui/AddressBar.cpp
    src/ui/BrowserToolbar.cpp
    src/ui/TabBar.cpp
    src/ui/NewTabPage.cpp
    src/database/Database.cpp
    src/database/SettingsRepository.cpp
    src/browser/NavigationController.cpp
    src/adblock/BlockStatistics.cpp
)
target_link_libraries(test_ui PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql Qt6::Network)
add_test(NAME UITest COMMAND test_ui)

# CPack Installer Configuration
set(CPACK_PACKAGE_NAME "KTBrowser")
set(CPACK_PACKAGE_VENDOR "Kawerify Tech")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "KT Browser by Kawerify Tech - Fast, Clean, Security-Focused Web Browser")
set(CPACK_GENERATOR "ZIP;NSIS")
include(CPack)
