# CodeBrowser

**CodeBrowser** is a fast, clean, modern, privacy-focused native desktop web browser built with **C++20**, **Qt 6**, **Qt WebEngine**, **CMake**, and **SQLite**.

## Key Features

- **Native Qt 6 Desktop Interface**: Modern, lightweight, fast, with clean rounded controls and custom theme engine (Light, Dark, System Sync).
- **Request-Level Ad & Tracker Blocking**: Built-in `AdBlockEngine` using native `QWebEngineUrlRequestInterceptor` to block ads, third-party trackers, analytics, and fingerprinting scripts before network dispatch.
- **Privacy Dashboard**: Native visual dashboard tracking total ads blocked, trackers stopped, HTTPS ratio, active cookies, and site permissions.
- **SQLite Persistence**: Complete persistent storage for browsing history, bookmarks, bookmark folders, download history, search history, custom filter lists, and site permissions.
- **Tab & Window Management**: Full tab lifecycle (Create, Close, Switch, Duplicate, Restore Closed Tab), favicon support, and native `NewTabPage`.
- **Search Engine Selection**: Configurable defaults (Google, Bing, DuckDuckGo, Brave Search, Custom URL).

## Building CodeBrowser

### Prerequisites
- C++20 Compiler (GCC 12+, Clang 14+, or MSVC 2022)
- Qt 6 (Core, Widgets, WebEngineWidgets, Sql, Network)
- CMake 3.20+
- Ninja build system

### Build Steps

```bash
mkdir build
cd build
cmake -G Ninja ..
cmake --build .
./codebrowser
```
