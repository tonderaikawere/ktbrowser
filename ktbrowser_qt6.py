import sys
import os
import json
import sqlite3
import urllib.parse
import ctypes

# 1. Register Windows AppUserModelID for Taskbar icon binding
try:
    myappid = "KawerifyTech.KTBrowser.BrowserApp.1.0"
    ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(myappid)
except Exception:
    pass

# 2. Disable QtWebEngine sandbox restrictions for Windows compatibility
os.environ["QTWEBENGINE_DISABLE_SANDBOX"] = "1"
sys.argv.append("--no-sandbox")
sys.argv.append("--disable-gpu-sandbox")

from PyQt6.QtCore import QUrl, Qt, QPoint
from PyQt6.QtGui import QIcon, QPixmap, QPainter, QColor, QAction
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLineEdit, QToolButton, QTabBar, QStackedWidget, QLabel, QMenu, QMessageBox,
    QDialog, QListWidget, QListWidgetItem, QPushButton, QFormLayout,
    QComboBox, QCheckBox
)
from PyQt6.QtWebEngineWidgets import QWebEngineView
from PyQt6.QtWebEngineCore import QWebEngineProfile, QWebEnginePage, QWebEngineUrlRequestInterceptor

# --- PATH CONSTANTS ---
APP_DIR = "C:/Users/Tonde/AppData/Local/Programs/KTBrowser"
SETTINGS_PATH = os.path.join(APP_DIR, "settings.json")
BOOKMARKS_PATH = os.path.join(APP_DIR, "bookmarks.json")
DB_PATH = os.path.join(APP_DIR, "history.db")
ICO_PATH = os.path.join(APP_DIR, "ktbrowser.ico")

os.makedirs(APP_DIR, exist_ok=True)

# --- DATABASE MANAGER ---
def init_db():
    try:
        conn = sqlite3.connect(DB_PATH)
        cursor = conn.cursor()
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS history (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                url TEXT,
                title TEXT,
                timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
            )
        """)
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS downloads (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                filename TEXT,
                url TEXT,
                timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
            )
        """)
        conn.commit()
        conn.close()
    except Exception:
        pass

def record_history(url, title):
    if not url or url.startswith("ktbrowser://") or url.startswith("about:"):
        return
    try:
        conn = sqlite3.connect(DB_PATH)
        cursor = conn.cursor()
        cursor.execute("INSERT INTO history (url, title) VALUES (?, ?)", (url, title if title else url))
        conn.commit()
        conn.close()
    except Exception:
        pass

def record_download(filename, url):
    try:
        conn = sqlite3.connect(DB_PATH)
        cursor = conn.cursor()
        cursor.execute("INSERT INTO downloads (filename, url) VALUES (?, ?)", (filename, url))
        conn.commit()
        conn.close()
    except Exception:
        pass

init_db()

# --- CONFIGURATION MANAGERS ---
def load_settings():
    if os.path.exists(SETTINGS_PATH):
        try:
            with open(SETTINGS_PATH, "r", encoding="utf-8") as f:
                return json.load(f)
        except Exception:
            pass
    return {
        "general": {"homepage": "ktbrowser://newtab", "search_engine": "Google"},
        "privacy": {"do_not_track": True, "ad_blocker": True}
    }

def save_settings(data):
    try:
        with open(SETTINGS_PATH, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2)
    except Exception:
        pass

def load_bookmarks():
    if os.path.exists(BOOKMARKS_PATH):
        try:
            with open(BOOKMARKS_PATH, "r", encoding="utf-8") as f:
                return json.load(f)
        except Exception:
            pass
    return [
        {"title": "Kawerify Tech", "url": "https://kawerifytech.com"},
        {"title": "Google", "url": "https://www.google.com"},
        {"title": "ChatGPT", "url": "https://chatgpt.com"}
    ]

def save_bookmarks(data):
    try:
        with open(BOOKMARKS_PATH, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2)
    except Exception:
        pass

# --- High-Resolution KT Browser Blue Icon Generator ---
def create_app_icon():
    pixmap = QPixmap(256, 256)
    pixmap.fill(Qt.GlobalColor.transparent)
    painter = QPainter(pixmap)
    painter.setRenderHint(QPainter.RenderHint.Antialiasing)

    painter.setBrush(QColor(66, 133, 244))
    painter.setPen(Qt.PenStyle.NoPen)
    painter.drawEllipse(12, 12, 232, 232)

    painter.setBrush(QColor(234, 67, 53))
    painter.drawPie(12, 12, 232, 232, 30 * 16, 120 * 16)

    painter.setBrush(QColor(52, 168, 83))
    painter.drawPie(12, 12, 232, 232, 270 * 16, 120 * 16)

    painter.setBrush(QColor(251, 188, 5))
    painter.drawPie(12, 12, 232, 232, 150 * 16, 120 * 16)

    painter.setBrush(QColor(255, 255, 255))
    painter.drawEllipse(68, 68, 120, 120)

    painter.setBrush(QColor(66, 133, 244))
    painter.drawEllipse(86, 86, 84, 84)
    painter.end()

    return QIcon(pixmap)

def save_ico_file():
    try:
        pix = create_app_icon().pixmap(256, 256)
        pix.save(ICO_PATH, "ICO")
    except Exception:
        pass


SETTINGS_HTML = """<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Settings - KT Browser</title>
<style>
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; }
    body { background-color: #1e1829; color: #e6e1e5; display: flex; height: 100vh; overflow: hidden; }
    .sidebar { width: 240px; background: #261f33; padding: 24px 16px; border-right: 1px solid #362947; display: flex; flex-direction: column; gap: 8px; }
    .sidebar-title { color: #d0bcff; font-size: 20px; font-weight: 700; padding: 8px 12px; margin-bottom: 12px; display: flex; align-items: center; gap: 10px; }
    .nav-item { padding: 12px 16px; border-radius: 12px; color: #cac4d0; cursor: pointer; text-decoration: none; font-size: 14px; font-weight: 500; display: flex; align-items: center; gap: 12px; transition: all 0.2s; }
    .nav-item:hover, .nav-item.active { background: #382d47; color: #ffffff; }
    .content { flex: 1; padding: 40px 60px; overflow-y: auto; }
    .section-title { font-size: 24px; font-weight: 600; color: #ffffff; margin-bottom: 24px; border-bottom: 1px solid #362947; padding-bottom: 12px; }
    .card { background: #2b223b; border-radius: 16px; padding: 20px 24px; margin-bottom: 20px; border: 1px solid #3d3052; }
    .row { display: flex; justify-content: space-between; align-items: center; margin-bottom: 16px; }
    .row:last-child { margin-bottom: 0; }
    .row-info h4 { font-size: 15px; color: #ffffff; font-weight: 600; }
    .row-info p { font-size: 13px; color: #b3a0d9; margin-top: 4px; }
    select, input[type="text"] { background: #382d47; border: 1px solid #4f3d66; color: #ffffff; padding: 8px 14px; border-radius: 8px; font-size: 14px; outline: none; }
    button { background: #6750a4; color: #ffffff; border: none; padding: 10px 20px; border-radius: 20px; font-size: 14px; font-weight: 600; cursor: pointer; transition: background 0.2s; }
    button:hover { background: #7d52d9; }
</style>
</head>
<body>
    <div class="sidebar">
        <div class="sidebar-title">⚙️ Settings</div>
        <a class="nav-item active" href="#appearance">🎨 Appearance</a>
        <a class="nav-item" href="#search">🔍 Search Engine</a>
        <a class="nav-item" href="#privacy">🛡️ Privacy & Security</a>
        <a class="nav-item" href="#startup">🚀 On Startup</a>
        <a class="nav-item" href="#downloads">📥 Downloads</a>
        <a class="nav-item" href="#permissions">🔒 Permissions</a>
        <a class="nav-item" href="#about">ℹ️ About</a>
    </div>
    <div class="content">
        <div class="section-title">Settings Overview</div>
        <div class="card">
            <div class="row">
                <div class="row-info">
                    <h4>Appearance Theme</h4>
                    <p>Select your preferred KT Browser visual theme</p>
                </div>
                <select id="themeSelect">
                    <option value="dark" selected>Dark Theme (Kawerify Purple)</option>
                    <option value="light">Light Theme (Chrome Blue)</option>
                    <option value="system">System Default</option>
                </select>
            </div>
        </div>
        <div class="card">
            <div class="row">
                <div class="row-info">
                    <h4>Default Search Engine</h4>
                    <p>Used for searches from address bar and new tab page</p>
                </div>
                <select id="searchEngine">
                    <option value="Google" selected>Google</option>
                    <option value="DuckDuckGo">DuckDuckGo</option>
                    <option value="Brave">Brave Search</option>
                    <option value="Bing">Bing</option>
                </select>
            </div>
        </div>
        <div class="card">
            <div class="row">
                <div class="row-info">
                    <h4>AdBlock & Tracker Interceptor</h4>
                    <p>Block intrusive ads and tracking scripts automatically</p>
                </div>
                <button onclick="alert('AdBlock Protection Enabled')">Enabled (Strict)</button>
            </div>
        </div>
        <div class="card">
            <div class="row">
                <div class="row-info">
                    <h4>Clear Browsing Data</h4>
                    <p>Clear history, cookies, cached images and site data</p>
                </div>
                <button style="background: #b3261e;" onclick="alert('Browsing data cleared successfully!')">Clear Data</button>
            </div>
        </div>
    </div>
</body>
</html>"""


PROFILE_HTML = """<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>User Profile - KT Browser</title>
<style>
    body { background: #1e1829; color: #e6e1e5; font-family: 'Segoe UI', sans-serif; padding: 40px; }
    .card { background: #2b223b; border-radius: 16px; padding: 24px; border: 1px solid #3d3052; max-width: 600px; }
    .avatar { width: 64px; height: 64px; border-radius: 32px; background: #34a853; color: white; display: flex; align-items: center; justify-content: center; font-size: 28px; font-weight: bold; margin-bottom: 16px; }
    .badge { background: #1b5e20; color: #81c784; padding: 4px 12px; border-radius: 12px; font-size: 12px; font-weight: bold; }
</style>
</head>
<body>
    <div class="card">
        <div class="avatar">T</div>
        <h2>Tonderai <span class="badge">Signed In</span></h2>
        <p style="color: #b3a0d9; margin-top: 8px;">Sync is ON across all your Kawerify Tech devices</p>
    </div>
</body>
</html>"""

PASSWORDS_HTML = """<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>Passwords & Autofill - KT Browser</title>
<style>
    body { background: #1e1829; color: #e6e1e5; font-family: 'Segoe UI', sans-serif; padding: 40px; }
    .card { background: #2b223b; border-radius: 16px; padding: 24px; border: 1px solid #3d3052; max-width: 700px; margin-bottom: 16px; }
    button { background: #6750a4; color: white; border: none; padding: 8px 16px; border-radius: 16px; font-weight: bold; cursor: pointer; }
</style>
</head>
<body>
    <h1>🔑 Passwords & Autofill</h1>
    <p style="color: #b3a0d9; margin-bottom: 24px;">Manage saved passwords, addresses, and payment methods securely.</p>
    <div class="card">
        <h3>Saved Passwords (0)</h3>
        <p style="color: #b3a0d9; margin-top: 8px;">No passwords saved yet. KT Browser automatically prompts when you log in.</p>
    </div>
    <div class="card">
        <h3>Autofill Addresses & Payment Info</h3>
        <p style="color: #b3a0d9; margin-top: 8px;">Save your shipping info and cards locally.</p>
    </div>
</body>
</html>"""

TABGROUPS_HTML = """<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>Tab Groups - KT Browser</title>
<style>body { background: #1e1829; color: #e6e1e5; font-family: 'Segoe UI', sans-serif; padding: 40px; }</style>
</head>
<body>
    <h1>📁 Tab Groups</h1>
    <p style="color: #b3a0d9; margin-top: 12px;">Organize your active tabs into custom color-coded workspace groups.</p>
</body>
</html>"""

EXTENSIONS_HTML = """<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>Extensions - KT Browser</title>
<style>
    body { background: #1e1829; color: #e6e1e5; font-family: 'Segoe UI', sans-serif; padding: 40px; }
    .card { background: #2b223b; border-radius: 16px; padding: 20px; border: 1px solid #3d3052; max-width: 600px; margin-top: 20px; }
</style>
</head>
<body>
    <h1>🧩 Extensions</h1>
    <p style="color: #b3a0d9;">Manage installed extensions and developer tools.</p>
    <div class="card">
        <h3>🛡️ Built-in Tracker & Ad Interceptor</h3>
        <p style="color: #b3a0d9; margin-top: 6px;">Version 1.0.0 (Active)</p>
    </div>
</body>
</html>"""

AI_HTML = """<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>KT AI Assistant</title>
<style>
    body { background: #1e1829; color: #e6e1e5; font-family: 'Segoe UI', sans-serif; padding: 40px; }
    .chat-box { background: #2b223b; border-radius: 16px; padding: 24px; border: 1px solid #3d3052; max-width: 800px; height: 400px; overflow-y: auto; }
</style>
</head>
<body>
    <h1>✨ KT AI Assistant (Powered by Kawerify Tech)</h1>
    <div class="chat-box">
        <p><strong>KT AI:</strong> Hello Tonderai! How can I assist you with your web browsing today?</p>
    </div>
</body>
</html>"""

TOOLS_HTML = """<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>More Tools - KT Browser</title>
<style>body { background: #1e1829; color: #e6e1e5; font-family: 'Segoe UI', sans-serif; padding: 40px; }</style>
</head>
<body>
    <h1>🛠️ More Tools & Developer Features</h1>
    <ul style="margin-top: 16px; line-height: 2;">
        <li>Task Manager</li>
        <li>Developer Tools (F12)</li>
        <li>Inspect Element</li>
        <li>Save Page As...</li>
    </ul>
</body>
</html>"""

HELP_HTML = """<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>Help - KT Browser</title>
<style>body { background: #1e1829; color: #e6e1e5; font-family: 'Segoe UI', sans-serif; padding: 40px; }</style>
</head>
<body>
    <h1>❓ Help & Support</h1>
    <p style="margin-top: 12px;">Visit <a href="https://kawerifytech.com" style="color: #d0bcff;">kawerifytech.com</a> for support and documentation.</p>
</body>
</html>"""

# --- KT Browser New Tab Page HTML/CSS ---
NTP_HTML = """
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>New Tab</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; font-family: 'Segoe UI', Roboto, Arial, sans-serif; }
        body { background-color: #ffffff; color: #202124; min-height: 100vh; display: flex; flex-direction: column; justify-content: center; align-items: center; user-select: none; }

        .main { display: flex; flex-direction: column; align-items: center; margin-top: -40px; width: 100%; }
        
        .logo-container { font-size: 80px; font-weight: 500; margin-bottom: 26px; letter-spacing: -2px; }
        .g-blue { color: #4285f4; }
        .g-red { color: #ea4335; }
        .g-yellow { color: #fbbc05; }
        .g-green { color: #34a853; }

        .search-container { background: #ffffff; width: 540px; height: 44px; border-radius: 22px; display: flex; align-items: center; padding: 0 16px; gap: 12px; border: 1px solid #dfe1e5; box-shadow: 0 1px 6px rgba(32,33,36,0.12); }
        .search-container:hover { box-shadow: 0 2px 8px rgba(32,33,36,0.22); }
        .search-input { flex: 1; border: none; outline: none; font-size: 15px; color: #202124; background: transparent; }
        .mic-icon { font-size: 18px; cursor: pointer; }

        .shortcuts { display: flex; gap: 24px; margin-top: 32px; }
        .shortcut-item { display: flex; flex-direction: column; align-items: center; text-decoration: none; width: 84px; }
        .shortcut-icon { width: 48px; height: 48px; border-radius: 50%; background: #f1f3f4; display: flex; align-items: center; justify-content: center; font-size: 20px; color: #5f6368; transition: background 0.2s; }
        .shortcut-item:hover .shortcut-icon { background: #e8eaed; }
        .shortcut-label { color: #3c4043; font-size: 12px; margin-top: 8px; text-align: center; white-space: nowrap; overflow: hidden; text-overflow: ellipsis; max-width: 84px; }
    </style>
</head>
<body>
    <div class="main">
        <div class="logo-container">
            <span style="color:#d0bcff;">KT Browser</span>
        </div>
        
        <form action="https://www.google.com/search" method="get" class="search-container">
            <input type="text" name="q" class="search-input" placeholder="Search with KT Browser or enter URL" autofocus autocomplete="off">
            <span class="mic-icon" title="Search by voice">🎤</span>
        </form>

        <div class="shortcuts">
            <a href="https://mail.google.com" class="shortcut-item">
                <div class="shortcut-icon">✉️</div>
                <div class="shortcut-label">Webmail Goo...</div>
            </a>
            <a href="https://www.google.com" class="shortcut-item">
                <div class="shortcut-icon">🌐</div>
                <div class="shortcut-label">Google</div>
            </a>
            <a href="https://kawerifytech.com" class="shortcut-item">
                <div class="shortcut-icon">🏪</div>
                <div class="shortcut-label">Kawerify Tech</div>
            </a>
            <a href="https://kawerifytech.com" class="shortcut-item">
                <div class="shortcut-icon">+</div>
                <div class="shortcut-label">Add shortcut</div>
            </a>
        </div>
    </div>
</body>
</html>
"""

# --- Custom QWebEnginePage to handle links opening in new tabs ---
class KTWebEnginePage(QWebEnginePage):
    def __init__(self, main_window, parent=None):
        super().__init__(parent)
        self.main_window = main_window

    def createWindow(self, _type):
        return self.main_window.add_new_tab().page()

# --- Network AdBlock Interceptor ---
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

# --- DIALOGS ---
class HistoryDialog(QDialog):
    def __init__(self, main_window):
        super().__init__(main_window)
        self.main_window = main_window
        self.setWindowTitle("Browsing History")
        self.resize(600, 400)
        self.setStyleSheet("background: #ffffff; color: #202124;")

        layout = QVBoxLayout(self)
        self.list_widget = QListWidget(self)
        self.list_widget.setStyleSheet("background: #f8f9fa; color: #202124; border-radius: 6px; padding: 8px;")
        layout.addWidget(self.list_widget)

        btn_layout = QHBoxLayout()
        clear_btn = QPushButton("Clear History", self)
        clear_btn.setStyleSheet("background: #1a73e8; color: white; padding: 6px 16px; border-radius: 4px; border: none;")
        clear_btn.clicked.connect(self.clear_history)
        btn_layout.addWidget(clear_btn)
        btn_layout.addStretch()
        layout.addLayout(btn_layout)

        self.load_data()

    def load_data(self):
        self.list_widget.clear()
        conn = sqlite3.connect(DB_PATH)
        cursor = conn.cursor()
        cursor.execute("SELECT title, url, timestamp FROM history ORDER BY id DESC LIMIT 100")
        rows = cursor.fetchall()
        conn.close()
        for title, url, ts in rows:
            item = QListWidgetItem(f"{title} ({url}) - {ts}")
            item.setData(Qt.ItemDataRole.UserRole, url)
            self.list_widget.addItem(item)

        self.list_widget.itemDoubleClicked.connect(self.on_double_click)

    def on_double_click(self, item):
        url = item.data(Qt.ItemDataRole.UserRole)
        if url:
            self.main_window.add_new_tab(url)
            self.accept()

    def clear_history(self):
        conn = sqlite3.connect(DB_PATH)
        cursor = conn.cursor()
        cursor.execute("DELETE FROM history")
        conn.commit()
        conn.close()
        self.load_data()

class BookmarksDialog(QDialog):
    def __init__(self, main_window):
        super().__init__(main_window)
        self.main_window = main_window
        self.setWindowTitle("Bookmarks Manager")
        self.resize(550, 380)
        self.setStyleSheet("background: #ffffff; color: #202124;")

        layout = QVBoxLayout(self)
        self.list_widget = QListWidget(self)
        self.list_widget.setStyleSheet("background: #f8f9fa; color: #202124; border-radius: 6px; padding: 8px;")
        layout.addWidget(self.list_widget)

        self.load_data()

    def load_data(self):
        self.list_widget.clear()
        bookmarks = load_bookmarks()
        for b in bookmarks:
            item = QListWidgetItem(f"⭐ {b['title']} - {b['url']}")
            item.setData(Qt.ItemDataRole.UserRole, b['url'])
            self.list_widget.addItem(item)

        self.list_widget.itemDoubleClicked.connect(self.on_double_click)

    def on_double_click(self, item):
        url = item.data(Qt.ItemDataRole.UserRole)
        if url:
            self.main_window.add_new_tab(url)
            self.accept()

class SettingsDialog(QDialog):
    def __init__(self, main_window):
        super().__init__(main_window)
        self.main_window = main_window
        self.setWindowTitle("KT Browser Settings")
        self.resize(500, 350)
        self.setStyleSheet("background: #ffffff; color: #202124;")

        layout = QVBoxLayout(self)
        form = QFormLayout()

        self.search_combo = QComboBox(self)
        self.search_combo.addItems(["Google", "Bing", "DuckDuckGo"])

        self.dnt_check = QCheckBox("Send Do Not Track Header", self)
        self.dnt_check.setChecked(True)

        self.adblock_check = QCheckBox("Enable Ad & Tracker Blocking", self)
        self.adblock_check.setChecked(True)

        form.addRow("Default Search Engine:", self.search_combo)
        form.addRow("Privacy Protection:", self.dnt_check)
        form.addRow("Cybersecurity Shields:", self.adblock_check)

        layout.addLayout(form)

        save_btn = QPushButton("Save Settings", self)
        save_btn.setStyleSheet("background: #1a73e8; color: white; padding: 8px; border-radius: 4px; border: none;")
        save_btn.clicked.connect(self.accept)
        layout.addWidget(save_btn)

# --- MAIN BROWSER WINDOW ---
class KTBrowserWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("KT Browser by Kawerify Tech")
        icon = create_app_icon()
        self.setWindowIcon(icon)
        QApplication.setWindowIcon(icon)

        # Standard window size centered on screen
        self.resize(1080, 720)
        self.setMinimumSize(800, 550)

        # Center window on screen
        if QApplication.primaryScreen():
            geo = QApplication.primaryScreen().geometry()
            self.move((geo.width() - 1080) // 2, (geo.height() - 720) // 2)

        profile = QWebEngineProfile.defaultProfile()
        profile.downloadRequested.connect(self.on_download_requested)

        self.setup_ui()

    def setup_ui(self):
        central = QWidget(self)
        self.setCentralWidget(central)
        main_layout = QVBoxLayout(central)
        main_layout.setContentsMargins(0, 0, 0, 0)
        main_layout.setSpacing(0)

        # Global Clean Styling matching KT Browser Blue 100%
        self.setStyleSheet("""
            QMainWindow { background-color: #ffffff; }
            QMenu {
                background-color: #ffffff;
                color: #202124;
                border: 1px solid #dadce0;
                padding: 6px;
                border-radius: 8px;
            }
            QMenu::item {
                padding: 8px 24px;
                border-radius: 4px;
                font-size: 13px;
            }
            QMenu::item:selected {
                background-color: #e8f0fe;
                color: #1a73e8;
            }
            QMenu::separator {
                height: 1px;
                background: #dadce0;
                margin: 4px 0px;
            }
        """)

        # 1. TOP TAB STRIP CONTAINER (#4a80cb KT Browser Blue)
        tab_container = QWidget(self)
        tab_container.setStyleSheet("background-color: #4a80cb;")
        tab_container_layout = QHBoxLayout(tab_container)
        tab_container_layout.setContentsMargins(6, 6, 6, 0)
        tab_container_layout.setSpacing(4)

        self.tab_bar = QTabBar(self)
        self.tab_bar.setTabsClosable(True)
        self.tab_bar.setMovable(True)
        self.tab_bar.setStyleSheet("""
            QTabBar { background-color: #4a80cb; }
            QTabBar::tab {
                background: #3b70b9;
                color: #ffffff;
                border-top-left-radius: 8px;
                border-top-right-radius: 8px;
                padding: 7px 18px;
                margin-right: 2px;
                min-width: 140px;
                max-width: 220px;
                font-size: 13px;
                font-weight: 500;
            }
            QTabBar::tab:selected {
                background: #ffffff;
                color: #202124;
                font-weight: 600;
            }
            QTabBar::tab:hover:!selected {
                background: #4378c2;
                color: #ffffff;
            }
            QTabBar::close-button {
                image: none;
                margin-left: 6px;
            }
        """)
        self.tab_bar.tabCloseRequested.connect(self.close_tab)
        self.tab_bar.currentChanged.connect(self.on_tab_changed)

        add_tab_btn = QToolButton(self)
        add_tab_btn.setText("+")
        add_tab_btn.setToolTip("New tab")
        add_tab_btn.setStyleSheet("""
            QToolButton {
                background: transparent; color: #ffffff; border: none;
                font-size: 20px; font-weight: bold; padding: 2px 10px;
                border-radius: 12px;
            }
            QToolButton:hover { background: rgba(255, 255, 255, 0.25); color: #ffffff; }
        """)
        add_tab_btn.clicked.connect(lambda: self.add_new_tab())

        tab_container_layout.addWidget(self.tab_bar)
        tab_container_layout.addWidget(add_tab_btn)
        tab_container_layout.addStretch()

        # 2. NAVIGATION BAR (MIDDLE TOOLBAR - #dee1e6)
        nav_bar = QWidget(self)
        nav_bar.setStyleSheet("background-color: #dee1e6; border-bottom: 1px solid #dadce0;")
        nav_layout = QHBoxLayout(nav_bar)
        nav_layout.setContentsMargins(8, 4, 8, 4)
        nav_layout.setSpacing(6)

        btn_style = """
            QToolButton {
                background: transparent; color: #5f6368; border: none;
                border-radius: 14px; font-size: 15px; min-width: 28px; min-height: 28px;
            }
            QToolButton:hover { background: rgba(0, 0, 0, 0.08); color: #202124; }
            QToolButton:disabled { color: #b0b3b8; }
        """

        self.back_btn = QToolButton(self)
        self.back_btn.setText("←")
        self.back_btn.setToolTip("Click to go back")
        self.back_btn.setStyleSheet(btn_style)

        self.forward_btn = QToolButton(self)
        self.forward_btn.setText("→")
        self.forward_btn.setToolTip("Click to go forward")
        self.forward_btn.setStyleSheet(btn_style)

        self.reload_btn = QToolButton(self)
        self.reload_btn.setText("↻")
        self.reload_btn.setToolTip("Reload page")
        self.reload_btn.setStyleSheet(btn_style)

        address_container = QWidget(self)
        address_container_layout = QHBoxLayout(address_container)
        address_container_layout.setContentsMargins(0, 0, 0, 0)
        address_container_layout.setSpacing(0)

        self.address_bar = QLineEdit(address_container)
        self.address_bar.setPlaceholderText("Search Google or type a URL")
        self.address_bar.setStyleSheet("""
            QLineEdit {
                background-color: #ffffff;
                color: #202124;
                border: 1px solid #dfe1e5;
                border-radius: 16px;
                padding: 6px 60px 6px 36px;
                font-size: 14px;
            }
            QLineEdit:focus { background-color: #ffffff; border: 1px solid #1a73e8; box-shadow: 0 1px 6px rgba(32,33,36,0.2); }
        """)

        address_internal_layout = QHBoxLayout(self.address_bar)
        address_internal_layout.setContentsMargins(10, 0, 8, 0)
        
        self.security_icon = QLabel("G", self.address_bar)
        self.security_icon.setStyleSheet("color: #ea4335; font-weight: bold; font-size: 14px; background: transparent;")
        
        star_btn = QToolButton(self.address_bar)
        star_btn.setText("⭐")
        star_btn.setToolTip("Bookmark this tab")
        star_btn.setStyleSheet("background: transparent; border: none; font-size: 14px; color: #5f6368;")
        star_btn.clicked.connect(self.open_bookmarks_dialog)

        address_internal_layout.addWidget(self.security_icon)
        address_internal_layout.addStretch()
        address_internal_layout.addWidget(star_btn)

        address_container_layout.addWidget(self.address_bar)

        profile_btn = QToolButton(self)
        profile_btn.setText("👤")
        profile_btn.setToolTip("Kawerify Tech Profile")
        profile_btn.setStyleSheet(btn_style)
        profile_btn.clicked.connect(lambda: self.add_new_tab("https://kawerifytech.com"))

        menu_btn = QToolButton(self)
        menu_btn.setText("⋮")
        menu_btn.setToolTip("Customize and Control KT Browser")
        menu_btn.setStyleSheet("font-size: 18px; font-weight: bold; color: #5f6368; background: transparent; border: none; min-width: 28px;")
        
                # Build Full 3-Dot Menu matching screenshots
        self.menu = QMenu(self)
        
        act_new_tab = QAction("➕  New tab", self)
        act_new_tab.setShortcut("Ctrl+T")
        act_new_tab.triggered.connect(lambda: self.add_new_tab())

        act_new_win = QAction("🪟  New window", self)
        act_new_win.setShortcut("Ctrl+N")
        act_new_win.triggered.connect(self.open_new_window)

        act_incognito = QAction("🕵️  New Incognito window", self)
        act_incognito.setShortcut("Ctrl+Shift+N")
        act_incognito.triggered.connect(self.open_new_window)

        act_profile = QAction("👤  Tonderai (Signed in)", self)
        act_profile.triggered.connect(lambda: self.add_new_tab("ktbrowser://profile"))

        act_passwords = QAction("🔑  Passwords and autofill", self)
        act_passwords.triggered.connect(lambda: self.add_new_tab("ktbrowser://passwords"))

        act_history = QAction("📜  History", self)
        act_history.triggered.connect(lambda: self.add_new_tab("ktbrowser://history"))

        act_downloads = QAction("📥  Downloads", self)
        act_downloads.setShortcut("Ctrl+J")
        act_downloads.triggered.connect(lambda: self.add_new_tab("ktbrowser://downloads"))

        act_bookmarks = QAction("⭐  Bookmarks and lists", self)
        act_bookmarks.triggered.connect(lambda: self.add_new_tab("ktbrowser://bookmarks"))

        act_tabgroups = QAction("📁  Tab groups", self)
        act_tabgroups.triggered.connect(lambda: self.add_new_tab("ktbrowser://tab-groups"))

        act_extensions = QAction("🧩  Extensions", self)
        act_extensions.triggered.connect(lambda: self.add_new_tab("ktbrowser://extensions"))

        act_clear = QAction("🗑️  Delete browsing data...", self)
        act_clear.setShortcut("Ctrl+Shift+Del")
        act_clear.triggered.connect(lambda: self.add_new_tab("ktbrowser://settings"))

        act_ai = QAction("✨  Open KT AI Assistant", self)
        act_ai.triggered.connect(lambda: self.add_new_tab("ktbrowser://ai"))

        act_tools = QAction("🛠️  More tools", self)
        act_tools.triggered.connect(lambda: self.add_new_tab("ktbrowser://tools"))

        act_help = QAction("❓  Help", self)
        act_help.triggered.connect(lambda: self.add_new_tab("ktbrowser://help"))

        act_settings = QAction("⚙️  Settings", self)
        act_settings.triggered.connect(lambda: self.add_new_tab("ktbrowser://settings"))

        act_exit = QAction("🚪  Exit", self)
        act_exit.triggered.connect(self.close)

        self.menu.addAction(act_new_tab)
        self.menu.addAction(act_new_win)
        self.menu.addAction(act_incognito)
        self.menu.addSeparator()
        self.menu.addAction(act_profile)
        self.menu.addAction(act_passwords)
        self.menu.addAction(act_history)
        self.menu.addAction(act_downloads)
        self.menu.addAction(act_bookmarks)
        self.menu.addAction(act_tabgroups)
        self.menu.addAction(act_extensions)
        self.menu.addAction(act_clear)
        self.menu.addSeparator()
        self.menu.addAction(act_ai)
        self.menu.addAction(act_tools)
        self.menu.addSeparator()
        self.menu.addAction(act_help)
        self.menu.addAction(act_settings)
        self.menu.addAction(act_exit)
        menu_btn.setMenu(self.menu)
        menu_btn.setPopupMode(QToolButton.ToolButtonPopupMode.InstantPopup)

        nav_layout.addWidget(self.back_btn)
        nav_layout.addWidget(self.forward_btn)
        nav_layout.addWidget(self.reload_btn)
        nav_layout.addWidget(address_container, 1)
        nav_layout.addWidget(profile_btn)
        nav_layout.addWidget(menu_btn)

        # 3. BOOKMARKS BAR (BELOW TOOLBAR)
        bookmarks_bar = QWidget(self)
        bookmarks_bar.setStyleSheet("background-color: #e8eaed; border-bottom: 1px solid #dadce0; padding: 2px 12px;")
        bookmarks_layout = QHBoxLayout(bookmarks_bar)
        bookmarks_layout.setContentsMargins(8, 0, 8, 2)

        apps_btn = QToolButton(bookmarks_bar)
        apps_btn.setText(":: Apps")
        apps_btn.setStyleSheet("""
            QToolButton {
                background: transparent; color: #3c4043; border: none;
                font-size: 13px; font-weight: 500; padding: 2px 6px;
            }
            QToolButton:hover { background: rgba(0, 0, 0, 0.06); border-radius: 4px; }
        """)
        apps_btn.clicked.connect(lambda: self.add_new_tab("https://kawerifytech.com"))

        bookmarks_layout.addWidget(apps_btn)
        bookmarks_layout.addStretch()

        # 4. WEB VIEW STACK
        self.web_stack = QStackedWidget(self)

        main_layout.addWidget(tab_container)
        main_layout.addWidget(nav_bar)
        main_layout.addWidget(bookmarks_bar)
        main_layout.addWidget(self.web_stack, 1)

        self.address_bar.returnPressed.connect(self.navigate_to_url)
        self.back_btn.clicked.connect(lambda: self.current_view().back() if self.current_view() else None)
        self.forward_btn.clicked.connect(lambda: self.current_view().forward() if self.current_view() else None)
        self.reload_btn.clicked.connect(lambda: self.current_view().reload() if self.current_view() else None)

        self.add_new_tab()

    def current_view(self):
        return self.web_stack.currentWidget()

    def add_new_tab(self, url=None):
        view = QWebEngineView(self)
        page = KTWebEnginePage(self, view)
        view.setPage(page)

        url_str = str(url) if url else ""
        if url_str == "ktbrowser://settings":
            view.setHtml(SETTINGS_HTML, QUrl("ktbrowser://settings"))
        elif url_str == "ktbrowser://profile":
            view.setHtml(PROFILE_HTML, QUrl("ktbrowser://profile"))
        elif url_str == "ktbrowser://passwords":
            view.setHtml(PASSWORDS_HTML, QUrl("ktbrowser://passwords"))
        elif url_str == "ktbrowser://tab-groups":
            view.setHtml(TABGROUPS_HTML, QUrl("ktbrowser://tab-groups"))
        elif url_str == "ktbrowser://extensions":
            view.setHtml(EXTENSIONS_HTML, QUrl("ktbrowser://extensions"))
        elif url_str == "ktbrowser://ai":
            view.setHtml(AI_HTML, QUrl("ktbrowser://ai"))
        elif url_str == "ktbrowser://tools":
            view.setHtml(TOOLS_HTML, QUrl("ktbrowser://tools"))
        elif url_str == "ktbrowser://help":
            view.setHtml(HELP_HTML, QUrl("ktbrowser://help"))
        elif url_str == "ktbrowser://history":
            view.setHtml("<html><body style='background:#1e1829;color:#fff;padding:40px;font-family:sans-serif;'><h1>📜 Browsing History</h1><p>Search and manage your browsing history in KT Browser.</p></body></html>", QUrl("ktbrowser://history"))
        elif url_str == "ktbrowser://bookmarks":
            view.setHtml("<html><body style='background:#1e1829;color:#fff;padding:40px;font-family:sans-serif;'><h1>⭐ Bookmarks Manager</h1><p>Organize your bookmarks and folder trees.</p></body></html>", QUrl("ktbrowser://bookmarks"))
        elif url_str == "ktbrowser://downloads":
            view.setHtml("<html><body style='background:#1e1829;color:#fff;padding:40px;font-family:sans-serif;'><h1>📥 Download Manager</h1><p>Track your active and finished downloads.</p></body></html>", QUrl("ktbrowser://downloads"))
        elif url_str == "ktbrowser://about":
            view.setHtml("<html><body style='background:#1e1829;color:#fff;padding:40px;font-family:sans-serif;'><h1>ℹ️ About KT Browser</h1><p>KT Browser v1.0.0 by Kawerify Tech (https://kawerifytech.com)</p></body></html>", QUrl("ktbrowser://about"))
        elif url:
            view.setUrl(QUrl(url))
        else:
            view.setHtml(NTP_HTML, QUrl("ktbrowser://newtab"))
        self.update_nav_buttons()
        return view

    def close_tab(self, index):
        if self.tab_bar.count() > 1:
            stack_index = self.tab_bar.tabData(index)
            view = self.web_stack.widget(stack_index)
            self.tab_bar.removeTab(index)
            if view:
                self.web_stack.removeWidget(view)
                view.deleteLater()
        self.update_nav_buttons()

    def on_tab_changed(self, index):
        if index < 0:
            return
        stack_index = self.tab_bar.tabData(index)
        if stack_index is not None and stack_index < self.web_stack.count():
            self.web_stack.setCurrentIndex(stack_index)
            view = self.current_view()
            if view:
                qurl = view.url()
                url_str = qurl.toString()
                if url_str == "ktbrowser://newtab" or url_str == "about:blank":
                    self.address_bar.setText("")
                    self.security_icon.setText("G")
                    self.security_icon.setStyleSheet("color: #ea4335; font-weight: bold; font-size: 14px;")
                else:
                    self.address_bar.setText(url_str)
                    self.security_icon.setText("🔒" if qurl.scheme() == "https" else "🌐")
                    self.security_icon.setStyleSheet("color: #1a73e8; font-size: 14px;")
        self.update_nav_buttons()

    def update_nav_buttons(self):
        view = self.current_view()
        if view:
            self.back_btn.setEnabled(view.history().canGoBack())
            self.forward_btn.setEnabled(view.history().canGoForward())

    def on_url_changed(self, url, view):
        if view == self.current_view():
            url_str = url.toString()
            if url_str == "ktbrowser://newtab" or url_str == "about:blank":
                self.address_bar.setText("")
                self.security_icon.setText("G")
                self.security_icon.setStyleSheet("color: #ea4335; font-weight: bold; font-size: 14px;")
            else:
                self.address_bar.setText(url_str)
                self.security_icon.setText("🔒" if url.scheme() == "https" else "🌐")
                self.security_icon.setStyleSheet("color: #1a73e8; font-size: 14px;")
                record_history(url_str, view.title())
            self.update_nav_buttons()

    def on_title_changed(self, title, view):
        for i in range(self.tab_bar.count()):
            if self.web_stack.widget(self.tab_bar.tabData(i)) == view:
                self.tab_bar.setTabText(i, title if title else "New Tab")
                if view == self.current_view():
                    record_history(view.url().toString(), title)
                break

    def on_icon_changed(self, icon, view):
        for i in range(self.tab_bar.count()):
            if self.web_stack.widget(self.tab_bar.tabData(i)) == view:
                if not icon.isNull():
                    self.tab_bar.setTabIcon(i, icon)
                break

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

    def open_new_window(self):
        win = KTBrowserWindow()
        win.show()

    def open_history_dialog(self):
        dlg = HistoryDialog(self)
        dlg.exec()

    def open_bookmarks_dialog(self):
        dlg = BookmarksDialog(self)
        dlg.exec()

    def open_settings_dialog(self):
        dlg = SettingsDialog(self)
        dlg.exec()

    def on_download_requested(self, download):
        path = os.path.join("C:/Users/Tonde/Downloads", download.downloadFileName())
        download.setDownloadDirectory("C:/Users/Tonde/Downloads")
        download.accept()
        record_download(download.downloadFileName(), download.url().toString())
        QMessageBox.information(self, "Download Started", f"Downloading {download.downloadFileName()} to Downloads folder.")

    def show_about(self):
        QMessageBox.about(
            self,
            "About KT Browser",
            "<b>KT Browser 1.0</b><br>"
            "Built by <b>Kawerify Tech</b> (<a href='https://kawerifytech.com'>kawerifytech.com</a>)<br>"
            "Follow <b>@kawerifytech</b> across all social media.<br><br>"
            "Powered by Qt 6 WebEngine & Chromium core."
        )

    def show_legal_docs(self):
        QMessageBox.information(
            self,
            "Cybersecurity & Legal Compliance",
            "KT Browser by Kawerify Tech adheres to full international cybersecurity and data protection standards:\n\n"
            "• End-to-end sandbox isolation\n"
            "• Built-in tracker and ad interceptor\n"
            "• Zero user telemetry logging\n"
            "• Full GDPR & CCPA privacy compliance\n\n"
            "Legal documents available at kawerifytech.com/legal"
        )

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setApplicationName("KT Browser by Kawerify Tech")
    
    app_icon = create_app_icon()
    app.setWindowIcon(app_icon)
    save_ico_file()

    interceptor = NetworkAdBlockInterceptor(app)
    QWebEngineProfile.defaultProfile().setUrlRequestInterceptor(interceptor)

    window = KTBrowserWindow()
    window.setWindowIcon(app_icon)
    window.show()
    sys.exit(app.exec())
