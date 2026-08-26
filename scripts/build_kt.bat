@echo off
echo Building KT Browser by Kawerify Tech...
set PATH=C:\Users\Tonde\AppData\Local\Programs\KTCompiler;C:\Users\Tonde\AppData\Local\Programs\KTCompiler\bin;%PATH%
set GCC_EXEC_PREFIX=C:\Users\Tonde\AppData\Local\Programs\KTCompiler\bin\

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
  -lQt6Widgets -lQt6Network -lQt6Sql -lQt6Gui -lQt6Core ^
  -o "C:\Users\Tonde\AppData\Local\Programs\KTBrowser\ktbrowser.exe"

echo KT Browser compilation complete!
