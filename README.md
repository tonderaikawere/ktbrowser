# 🚀 KT Browser (by Kawerify Tech)

[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://kawerifytech.com)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Qt](https://img.shields.io/badge/Qt-6.x-brightgreen.svg)](https://www.qt.io/)
[![Python](https://img.shields.io/badge/Python-3.13%2B-blue.svg)](https://www.python.org/)
[![Developer](https://img.shields.io/badge/Developer-Kawerify%20Tech-orange.svg)](https://kawerifytech.com)

**KT Browser** (short for **Kawerify Tech Browser**) is a fast, lightweight, security-first web browser built with a pixel-identical **KT Browser design by Kawerify Tech**, powered by Qt 6 WebEngine and Chromium core.

Created and maintained by **Kawerify Tech** ([https://kawerifytech.com](https://kawerifytech.com) | **@kawerifytech** on all social media platforms).

---

## ✨ Features

- **🎨 KT Browser Custom Theme**: Pixel-identical light blue tab strip (`#4a80cb`), soft toolbar (`#dee1e6`), white omnibox search pill, and custom Google New Tab Page.
- **⚡ High Performance & Multi-Tab Engine**: Smooth tab switching, fast page rendering, and low memory consumption powered by Qt 6 WebEngine.
- **🛡️ Cybersecurity & Privacy Protection**: Built-in tracker and ad interceptor (`NetworkAdBlockInterceptor`), Do-Not-Track headers, and local sandbox isolation.
- **🔍 Omnibox Search & Direct Navigation**: Smart address bar supporting instant Google searches, HTTPS normalization, security indicators (`🔒`/`🌐`/`G`), and instant bookmarking.
- **⭐ Bookmarks & History Manager**: Built-in SQLite database tracking page visits, active search history, and persistent bookmarks.
- **📥 Download Manager**: Integrated download interceptor storing files cleanly in the user's Downloads folder with real-time notifications.
- **🖥️ Frameless & Standard OS Support**: Native OS titlebar controls, Taskbar icon binding (`SetCurrentProcessExplicitAppUserModelID`), and desktop shortcuts.

---

## 🛠️ Architecture & Tech Stack

- **Core Engine**: Qt 6 WebEngine (`QWebEngineView`, `QWebEngineProfile`, `QWebEnginePage`) & Chromium Core
- **GUI Framework**: PyQt6 / C++ Qt6
- **Database**: SQLite3 (`history.db`)
- **Config Storage**: JSON (`settings.json`, `bookmarks.json`)
- **OS Compatibility**: Windows 10 / 11, Linux, macOS

---

## 💻 Quick Start & Running Locally

### Prerequisites

Ensure you have Python 3.10+ installed along with `PyQt6` and `PyQt6-WebEngine`:

```bash
pip install PyQt6 PyQt6-WebEngine
```

### Launch Browser

Run the main application script:

```bash
python ktbrowser_qt6.py
```

To launch without a background command prompt on Windows:

```bash
pythonw ktbrowser_qt6.py
```

---

## 📦 Building Standalone Executable (Windows)

To package **KT Browser** into a standalone executable using PyInstaller:

```bash
pyinstaller --onedir --noconsole --name "ktbrowser" --icon "ktbrowser.ico" ktbrowser_qt6.py
```

The compiled binary will be placed inside `dist/ktbrowser/ktbrowser.exe`.

---

## 🏢 About Kawerify Tech

- **Official Website**: [https://kawerifytech.com](https://kawerifytech.com)
- **Social Media**: **@kawerifytech** (Twitter/X, LinkedIn, GitHub, Instagram, Facebook)
- **Support & Legal**: [kawerifytech.com/legal](https://kawerifytech.com)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Developed with ❤️ by **Kawerify Tech**.
