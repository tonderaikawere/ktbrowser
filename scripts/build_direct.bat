@echo off
echo Building KT Browser Native GUI by Kawerify Tech...
set PATH=C:\msys64\ucrt64\share\qt6\bin;C:\msys64\ucrt64\bin;C:\msys64\ucrt64\lib\gcc\x86_64-w64-mingw32\16.2.0;%PATH%

mkdir build_moc 2>nul

moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/browser/BrowserWindow.h -o build_moc/moc_BrowserWindow.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/browser/BrowserTab.h -o build_moc/moc_BrowserTab.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/browser/TabManager.h -o build_moc/moc_TabManager.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/ui/AddressBar.h -o build_moc/moc_AddressBar.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/ui/BrowserToolbar.h -o build_moc/moc_BrowserToolbar.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/ui/TabBar.h -o build_moc/moc_TabBar.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/ui/NewTabPage.h -o build_moc/moc_NewTabPage.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/ui/BookmarkManagerWidget.h -o build_moc/moc_BookmarkManagerWidget.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/ui/HistoryManagerWidget.h -o build_moc/moc_HistoryManagerWidget.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/ui/DownloadsWidget.h -o build_moc/moc_DownloadsWidget.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/adblock/AdBlockEngine.h -o build_moc/moc_AdBlockEngine.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/adblock/BlockStatistics.h -o build_moc/moc_BlockStatistics.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/privacy/PrivacyManager.h -o build_moc/moc_PrivacyManager.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/privacy/PrivacyDashboard.h -o build_moc/moc_PrivacyDashboard.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/privacy/PermissionsManagerWidget.h -o build_moc/moc_PermissionsManagerWidget.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/downloads/DownloadManager.h -o build_moc/moc_DownloadManager.cpp
moc -Iinclude -Iinclude/ktbrowser include/ktbrowser/settings/SettingsWindow.h -o build_moc/moc_SettingsWindow.cpp

g++ -std=gnu++20 -mwindows -DUNICODE -D_UNICODE ^
  -Iinclude -Iinclude/ktbrowser ^
  -IC:/msys64/ucrt64/include/qt6 ^
  -IC:/msys64/ucrt64/include/qt6/QtCore ^
  -IC:/msys64/ucrt64/include/qt6/QtWidgets ^
  -IC:/msys64/ucrt64/include/qt6/QtGui ^
  -IC:/msys64/ucrt64/include/qt6/QtNetwork ^
  -IC:/msys64/ucrt64/include/qt6/QtSql ^
  src/main.cpp ^
  src/browser/BrowserWindow.cpp ^
  src/browser/BrowserTab.cpp ^
  src/browser/TabManager.cpp ^
  src/browser/NavigationController.cpp ^
  src/ui/AddressBar.cpp ^
  src/ui/BrowserToolbar.cpp ^
  src/ui/TabBar.cpp ^
  src/ui/NewTabPage.cpp ^
  src/ui/BookmarkManagerWidget.cpp ^
  src/ui/HistoryManagerWidget.cpp ^
  src/ui/DownloadsWidget.cpp ^
  src/ui/SettingsPage.cpp ^
  src/adblock/AdBlockEngine.cpp ^
  src/adblock/FilterParser.cpp ^
  src/adblock/FilterRule.cpp ^
  src/adblock/FilterListManager.cpp ^
  src/adblock/BlockStatistics.cpp ^
  src/adblock/WebEngineUrlRequestInterceptor.cpp ^
  src/privacy/PrivacyManager.cpp ^
  src/privacy/PrivacyDashboard.cpp ^
  src/privacy/TrackerProtection.cpp ^
  src/privacy/PermissionsManagerWidget.cpp ^
  src/database/Database.cpp ^
  src/database/HistoryRepository.cpp ^
  src/database/BookmarkRepository.cpp ^
  src/database/SettingsRepository.cpp ^
  src/downloads/DownloadManager.cpp ^
  src/settings/SettingsWindow.cpp ^
  build_moc/moc_BrowserWindow.cpp ^
  build_moc/moc_BrowserTab.cpp ^
  build_moc/moc_TabManager.cpp ^
  build_moc/moc_AddressBar.cpp ^
  build_moc/moc_BrowserToolbar.cpp ^
  build_moc/moc_TabBar.cpp ^
  build_moc/moc_NewTabPage.cpp ^
  build_moc/moc_BookmarkManagerWidget.cpp ^
  build_moc/moc_HistoryManagerWidget.cpp ^
  build_moc/moc_DownloadsWidget.cpp ^
  build_moc/moc_AdBlockEngine.cpp ^
  build_moc/moc_BlockStatistics.cpp ^
  build_moc/moc_PrivacyManager.cpp ^
  build_moc/moc_PrivacyDashboard.cpp ^
  build_moc/moc_PermissionsManagerWidget.cpp ^
  build_moc/moc_DownloadManager.cpp ^
  build_moc/moc_SettingsWindow.cpp ^
  -lQt6Widgets -lQt6Network -lQt6Sql -lQt6Gui -lQt6Core ^
  -o "C:\Users\Tonde\AppData\Local\Programs\KTBrowser\ktbrowser.exe"

echo Done!
