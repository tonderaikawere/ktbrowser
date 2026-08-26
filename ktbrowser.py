import sys
import os
import urllib.parse
from PySide6.QtCore import QUrl, Qt, QSize
from PySide6.QtGui import QIcon, QPixmap, QPainter, QColor, QRadialGradient, QFont
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLineEdit, QToolButton, QTabWidget, QTabBar, QLabel, QFrame,
    QDialog, QMessageBox, QPushButton, QSizePolicy
)
from PySide6.QtWebEngineWidgets import QWebEngineView
from PySide6.QtWebEngineCore import QWebEngineProfile, QWebEngineUrlRequestInterceptor

# --- High-Resolution Chrome-Style Icon Generator ---
def create_app_icon():
    pixmap = QPixmap(256, 256)
    pixmap.fill(Qt.transparent)
    painter = QPainter(pixmap)
    painter.setRenderHint(QPainter.Antialiasing)

    # Outer Dark Purple Gradient Circle
    grad = QRadialGradient(128, 128, 120)
    grad.setColorAt(0, QColor(74, 52, 97))
    grad.setColorAt(1, QColor(35, 26, 46))
    painter.setBrush(grad)
    painter.setPen(QColor(208, 188, 255))
    painter.drawEllipse(12, 12, 232, 232)

    # Inner Glowing Blue Core
    painter.setBrush(QColor(138, 180, 248))
    painter.setPen(Qt.NoPen)
    painter.drawEllipse(68, 68, 120, 120)

    # Center Deep Core
    painter.setBrush(QColor(35, 26, 46))
    painter.drawEllipse(96, 96, 64, 64)
    painter.end()

    return QIcon(pixmap)

# --- Chrome New Tab Page (NTP) HTML HTML/CSS Template ---
NTP_HTML = """
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>New Tab</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; }
        body { background-color: #2b2238; color: #ffffff; min-height: 100vh; display: flex; flex-direction: column; justify-content: space-between; }
        
        /* Top Navigation Header */
        .header { display: flex; justify-content: space-between; align-items: center; padding: 16px 24px; }
        .kt-badge { background: #4a3461; color: #d0bcff; padding: 6px 16px; border-radius: 16px; font-weight: 600; font-size: 13px; text-decoration: none; border: 1px solid #5c4278; transition: all 0.2s; }
        .kt-badge:hover { background: #5c4278; color: #ffffff; }
        .nav-links { display: flex; align-items: center; gap: 16px; }
        .nav-links a { color: #ffffff; text-decoration: none; font-size: 14px; opacity: 0.9; }
        .nav-links a:hover { opacity: 1; text-decoration: underline; }
        .grid-icon { font-size: 18px; font-weight: bold; opacity: 0.8; cursor: pointer; }
        .profile-icon { background: #4a3461; width: 34px; height: 34px; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 16px; }

        /* Main Content Container */
        .main { display: flex; flex-direction: column; align-items: center; margin-top: 20px; width: 100%; }
        .logo { font-size: 82px; font-weight: 700; color: #ffffff; margin-bottom: 24px; letter-spacing: -1px; }

        /* Search Pill Box */
        .search-container { background: #ffffff; width: 680px; height: 50px; border-radius: 25px; display: flex; align-items: center; padding: 0 16px; gap: 12px; box-shadow: 0 4px 12px rgba(0,0,0,0.3); }
        .search-plus { color: #5f6368; font-size: 20px; font-weight: bold; }
        .search-input { flex: 1; border: none; outline: none; font-size: 16px; color: #202124; background: transparent; }
        .search-actions { display: flex; align-items: center; gap: 10px; }
        .icon-btn { background: none; border: none; font-size: 18px; cursor: pointer; }
        .ai-pill { background: #f1f3f4; color: #3c4043; font-size: 13px; font-weight: 600; padding: 6px 14px; border-radius: 15px; border: 1px solid #dadce0; cursor: pointer; }

        /* Circular Shortcuts Row */
        .shortcuts { display: flex; gap: 20px; margin-top: 32px; }
        .shortcut-item { display: flex; flex-direction: column; align-items: center; text-decoration: none; width: 80px; }
        .shortcut-icon { width: 54px; height: 54px; border-radius: 50%; background: #382d47; display: flex; align-items: center; justify-content: center; font-size: 22px; transition: background 0.2s; }
        .shortcut-item:hover .shortcut-icon { background: #4a3c5d; }
        .shortcut-label { color: #d0bcff; font-size: 12px; margin-top: 8px; text-align: center; white-space: nowrap; overflow: hidden; text-overflow: ellipsis; max-width: 80px; }

        /* Continue Tabs Card */
        .continue-card { background: #362947; width: 680px; border-radius: 16px; padding: 16px 20px; margin-top: 28px; display: flex; justify-content: space-between; align-items: center; }
        .card-title { font-size: 15px; font-weight: 600; color: #ffffff; }

        /* Footer */
        .footer { display: flex; justify-content: space-between; align-items: center; padding: 16px 24px; font-size: 13px; color: #b3a0d9; }
        .customize-btn { background: #3b2c4e; color: #d0bcff; font-weight: 600; border-radius: 18px; padding: 8px 18px; border: 1px solid #4a3b60; cursor: pointer; }
        .customize-btn:hover { background: #4a3763; color: #ffffff; }
    </style>
</head>
<body>
    <div class="header">
        <a href="https://kawerifytech.com" class="kt-badge">🚀 Kawerify Tech</a>
        <div class="nav-links">
            <a href="https://mail.google.com">Gmail</a>
            <a href="https://images.google.com">Images</a>
            <span class="grid-icon">::</span>
            <div class="profile-icon">👤</div>
        </div>
    </div>

    <div class="main">
        <div class="logo">Google</div>
        
        <form action="https://www.google.com/search" method="get" class="search-container">
            <span class="search-plus">+</span>
            <input type="text" name="q" class="search-input" placeholder="Ask Google or type a URL" autofocus autocomplete="off">
            <div class="search-actions">
                <span class="icon-btn">🎤</span>
                <span class="icon-btn">📷</span>
                <button type="button" class="ai-pill">✨ AI Mode</button>
            </div>
        </form>

        <div class="shortcuts">
            <a href="https://chatgpt.com" class="shortcut-item">
                <div class="shortcut-icon">🤖</div>
                <div class="shortcut-label">ChatGPT</div>
            </a>
            <a href="https://github.com" class="shortcut-item">
                <div class="shortcut-icon">🐙</div>
                <div class="shortcut-label">GitHub</div>
            </a>
            <a href="https://hpanel.hostinger.com" class="shortcut-item">
                <div class="shortcut-icon">⚡</div>
                <div class="shortcut-label">hPanel</div>
            </a>
            <a href="https://gemini.google.com" class="shortcut-item">
                <div class="shortcut-icon">✨</div>
                <div class="shortcut-label">Gemini</div>
            </a>
            <a href="https://chat.deepseek.com" class="shortcut-item">
                <div class="shortcut-icon">🐳</div>
                <div class="shortcut-label">DeepSeek</div>
            </a>
            <a href="https://kawerifytech.com" class="shortcut-item">
                <div class="shortcut-icon">🌐</div>
                <div class="shortcut-label">Kawerify Tech</div>
            </a>
            <a href="#" class="shortcut-item">
                <div class="shortcut-icon">+</div>
                <div class="shortcut-label">Show more</div>
            </a>
        </div>

        <div class="continue-card">
            <div class="card-title">Continue with these tabs</div>
            <div style="color: #d0bcff; font-weight: bold; cursor: pointer;">⋮</div>
        </div>
    </div>

    <div class="footer">
        <div>Built by <b>Kawerify Tech</b> (<a href="https://kawerifytech.com" style="color:#d0bcff;">kawerifytech.com</a> | <b>@kawerifytech</b>)</div>
        <button class="customize-btn">✏️ Customize Chrome</button>
    </div>
</body>
</html>
"""

# --- Network Ad & Tracker Interceptor ---
class NetworkAdBlockInterceptor(QWebEngineUrlRequestInterceptor):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.blocked_domains = ["doubleclick.net", "googlesyndication.com", "adservice.google.com", "adnxs.com"]

    def interceptRequest(self, info):
        url_str = info.requestUrl().toString()
        for domain in self.blocked_domains:
            if domain in url_str:
                info.block(True)
                return

# --- Main Window ---
class KTBrowserWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("KT Browser by Kawerify Tech")
        self.setWindowIcon(create_app_icon())
        self.resize(1280, 800)
        self.setMinimumSize(800, 600)

        self.setup_ui()

    def setup_ui(self):
        central = QWidget(self)
        self.setCentralWidget(central)
        main_layout = QVBoxLayout(central)
        main_layout.setContentsMargins(0, 0, 0, 0)
        main_layout.setSpacing(0)

        # Apply Chrome Dark Purple Palette
        self.setStyleSheet("""
            QMainWindow { background-color: #2b2238; }
            QTabWidget::pane { border: none; background: #2b2238; }
            QTabBar::tab {
                background: #2f233f;
                color: #b3a0d9;
                border-top-left-radius: 10px;
                border-top-right-radius: 10px;
                padding: 8px 16px;
                margin-right: 3px;
                min-width: 140px;
                font-size: 13px;
                font-weight: 500;
            }
            QTabBar::tab:selected {
                background: #3b2c4e;
                color: #ffffff;
                font-weight: bold;
                border-bottom: 2px solid #d0bcff;
            }
            QTabBar::tab:hover:!selected {
                background: #36284a;
                color: #ffffff;
            }
        """)

        # Navigation Bar
        nav_bar = QWidget(self)
        nav_bar.setStyleSheet("background-color: #2b2238; padding: 4px 8px;")
        nav_layout = QHBoxLayout(nav_bar)
        nav_layout.setContentsMargins(8, 4, 8, 4)
        nav_layout.setSpacing(6)

        btn_style = """
            QToolButton {
                background: transparent; color: #d0bcff; border: none;
                border-radius: 15px; font-size: 15px; min-width: 30px; min-height: 30px;
            }
            QToolButton:hover { background: rgba(208, 188, 255, 0.18); color: #ffffff; }
        """

        self.back_btn = QToolButton(self)
        self.back_btn.setText("←")
        self.back_btn.setStyleSheet(btn_style)

        self.forward_btn = QToolButton(self)
        self.forward_btn.setText("→")
        self.forward_btn.setStyleSheet(btn_style)

        self.reload_btn = QToolButton(self)
        self.reload_btn.setText("↻")
        self.reload_btn.setStyleSheet(btn_style)

        self.home_btn = QToolButton(self)
        self.home_btn.setText("🏠")
        self.home_btn.setStyleSheet(btn_style)

        # Omnibox Address Bar
        self.address_bar = QLineEdit(self)
        self.address_bar.setPlaceholderText("Ask Google or type a URL")
        self.address_bar.setStyleSheet("""
            QLineEdit {
                background-color: #362947;
                color: #ffffff;
                border: 1px solid #4a3861;
                border-radius: 18px;
                padding: 6px 16px;
                font-size: 14px;
            }
            QLineEdit:focus { background-color: #3f3053; border: 1px solid #d0bcff; }
        """)

        shields_btn = QToolButton(self)
        shields_btn.setText("🛡️ Shields")
        shields_btn.setStyleSheet("""
            QToolButton {
                background-color: #1b5e20; color: #ffffff; font-weight: bold;
                border-radius: 14px; padding: 4px 12px; font-size: 12px;
            }
            QToolButton:hover { background-color: #2e7d32; }
        """)

        gemini_btn = QToolButton(self)
        gemini_btn.setText("✨ Ask Gemini")
        gemini_btn.setStyleSheet("""
            QToolButton {
                background-color: #4a3461; color: #ffffff; font-weight: bold;
                border-radius: 14px; padding: 4px 14px; font-size: 12px;
            }
            QToolButton:hover { background-color: #5c4278; }
        """)

        menu_btn = QToolButton(self)
        menu_btn.setText("⋮")
        menu_btn.setStyleSheet("font-size: 18px; font-weight: bold; color: #d0bcff; background: transparent; border: none;")

        nav_layout.addWidget(self.back_btn)
        nav_layout.addWidget(self.forward_btn)
        nav_layout.addWidget(self.reload_btn)
        nav_layout.addWidget(self.home_btn)
        nav_layout.addWidget(self.address_bar, 1)
        nav_layout.addWidget(shields_btn)
        nav_layout.addWidget(gemini_btn)
        nav_layout.addWidget(menu_btn)

        # Tab Widget
        self.tabs = QTabWidget(self)
        self.tabs.setTabsClosable(True)
        self.tabs.setMovable(True)
        self.tabs.tabCloseRequested.connect(self.close_tab)

        main_layout.addWidget(nav_bar)
        main_layout.addWidget(self.tabs)

        # Connect Navigation Actions
        self.address_bar.returnPressed.connect(self.navigate_to_url)
        self.back_btn.clicked.connect(lambda: self.current_view().back() if self.current_view() else None)
        self.forward_btn.clicked.connect(lambda: self.current_view().forward() if self.current_view() else None)
        self.reload_btn.clicked.connect(lambda: self.current_view().reload() if self.current_view() else None)
        self.home_btn.clicked.connect(self.add_new_tab)

        # Create Initial Tab
        self.add_new_tab()

    def current_view(self):
        return self.tabs.currentWidget()

    def add_new_tab(self, url=None):
        view = QWebEngineView(self)
        if url:
            view.setUrl(QUrl(url))
        else:
            view.setHtml(NTP_HTML, QUrl("ktbrowser://newtab"))

        index = self.tabs.addTab(view, "New Tab")
        self.tabs.setCurrentIndex(index)

        view.urlChanged.connect(lambda qurl, v=view: self.on_url_changed(qurl, v))
        view.titleChanged.connect(lambda title, v=view: self.on_title_changed(title, v))

    def close_tab(self, index):
        if self.tabs.count() > 1:
            self.tabs.removeTab(index)

    def on_url_changed(self, url, view):
        if view == self.current_view():
            url_str = url.toString()
            if url_str == "ktbrowser://newtab" or url_str == "about:blank":
                self.address_bar.setText("")
            else:
                self.address_bar.setText(url_str)

    def on_title_changed(self, title, view):
        index = self.tabs.indexOf(view)
        if index != -1:
            self.tabs.setTabText(index, title if title else "New Tab")

    def navigate_to_url(self):
        text = self.address_bar.text().strip()
        if not text:
            return

        if "." not in text and ":" not in text and not text.startswith("localhost"):
            url = QUrl(f"https://www.google.com/search?q={urllib.parse.quote(text)}")
        elif not text.startswith("http://") and not text.startswith("https://"):
            url = QUrl(f"https://{text}")
        else:
            url = QUrl(text)

        if self.current_view():
            self.current_view().setUrl(url)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setApplicationName("KT Browser by Kawerify Tech")

    # Attach Interceptor
    interceptor = NetworkAdBlockInterceptor(app)
    QWebEngineProfile.defaultProfile().setUrlRequestInterceptor(interceptor)

    window = KTBrowserWindow()
    window.show()
    sys.exit(app.exec())
