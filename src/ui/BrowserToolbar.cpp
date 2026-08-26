#include "ktbrowser/ui/BrowserToolbar.h"
#include <QStyle>

namespace ktbrowser {

BrowserToolbar::BrowserToolbar(QWidget* parent)
    : QWidget(parent) {
    setupUi();
}

void BrowserToolbar::setupUi() {
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(10, 4, 10, 6);
    m_layout->setSpacing(6);

    setStyleSheet(R"(
        QWidget {
            background-color: #361f1c;
        }
        QToolButton {
            background-color: transparent;
            color: #d8a499;
            border: none;
            border-radius: 14px;
            padding: 4px;
            font-size: 14px;
            min-width: 28px;
            min-height: 28px;
        }
        QToolButton:hover {
            background-color: rgba(252, 232, 228, 0.15);
            color: #ffffff;
        }
        QToolButton:disabled {
            color: #5c3b37;
        }
    )");

    m_backBtn = new QToolButton(this);
    m_backBtn->setText("←");
    m_backBtn->setToolTip("Click to go back");

    m_forwardBtn = new QToolButton(this);
    m_forwardBtn->setText("→");
    m_forwardBtn->setToolTip("Click to go forward");

    m_reloadBtn = new QToolButton(this);
    m_reloadBtn->setText("↻");
    m_reloadBtn->setToolTip("Reload page");

    m_homeBtn = new QToolButton(this);
    m_homeBtn->setText("🏠");
    m_homeBtn->setToolTip("Open New Tab Page");

    m_addressBar = new AddressBar(this);

    m_shieldsBtn = new QToolButton(this);
    m_shieldsBtn->setText("🛡️ Shields");
    m_shieldsBtn->setToolTip("KT Browser Privacy Shield");
    m_shieldsBtn->setStyleSheet(R"(
        QToolButton {
            background-color: #1b5e20;
            color: #ffffff;
            font-weight: bold;
            border-radius: 14px;
            padding: 4px 12px;
            font-size: 12px;
        }
        QToolButton:hover {
            background-color: #2e7d32;
        }
    )");

    m_bookmarkBtn = new QToolButton(this);
    m_bookmarkBtn->setText("📁");
    m_bookmarkBtn->setToolTip("All Bookmarks (Ctrl+B)");

    m_historyBtn = new QToolButton(this);
    m_historyBtn->setText("🕒");
    m_historyBtn->setToolTip("Browsing History (Ctrl+H)");

    m_downloadsBtn = new QToolButton(this);
    m_downloadsBtn->setText("📥");
    m_downloadsBtn->setToolTip("Downloads Manager (Ctrl+J)");

    auto* profileBtn = new QToolButton(this);
    profileBtn->setText("👤");
    profileBtn->setToolTip("Kawerify Tech Profile");
    profileBtn->setStyleSheet(R"(
        QToolButton {
            background-color: #4a3461;
            color: #ffffff;
            border-radius: 15px;
            min-width: 30px;
            min-height: 30px;
        }
        QToolButton:hover {
            background-color: #5c4278;
        }
    )");

    m_settingsBtn = new QToolButton(this);
    m_settingsBtn->setText("⋮");
    m_settingsBtn->setToolTip("Customize and Control KT Browser");
    m_settingsBtn->setStyleSheet("font-size: 18px; font-weight: bold;");

    m_layout->addWidget(m_backBtn);
    m_layout->addWidget(m_forwardBtn);
    m_layout->addWidget(m_reloadBtn);
    m_layout->addWidget(m_homeBtn);
    m_layout->addWidget(m_addressBar, 1);
    m_layout->addWidget(m_shieldsBtn);
    m_layout->addWidget(m_bookmarkBtn);
    m_layout->addWidget(m_historyBtn);
    m_layout->addWidget(m_downloadsBtn);
    m_layout->addWidget(profileBtn);
    m_layout->addWidget(m_settingsBtn);

    connect(m_backBtn, &QToolButton::clicked, this, &BrowserToolbar::backRequested);
    connect(m_forwardBtn, &QToolButton::clicked, this, &BrowserToolbar::forwardRequested);
    connect(m_reloadBtn, &QToolButton::clicked, this, [this]() {
        if (m_isLoading) {
            emit stopRequested();
        } else {
            emit reloadRequested();
        }
    });
    connect(m_homeBtn, &QToolButton::clicked, this, &BrowserToolbar::homeRequested);
    connect(m_shieldsBtn, &QToolButton::clicked, this, &BrowserToolbar::privacyDashboardRequested);
    connect(m_bookmarkBtn, &QToolButton::clicked, this, &BrowserToolbar::bookmarkRequested);
    connect(m_historyBtn, &QToolButton::clicked, this, &BrowserToolbar::historyRequested);
    connect(m_downloadsBtn, &QToolButton::clicked, this, &BrowserToolbar::downloadsRequested);
    connect(m_settingsBtn, &QToolButton::clicked, this, &BrowserToolbar::settingsRequested);
}

void BrowserToolbar::setIsLoading(bool isLoading) {
    m_isLoading = isLoading;
    m_reloadBtn->setText(m_isLoading ? "✕" : "↻");
    m_reloadBtn->setToolTip(m_isLoading ? "Stop loading page" : "Reload page");
}

void BrowserToolbar::setCanGoBack(bool canGoBack) {
    m_backBtn->setEnabled(canGoBack);
}

void BrowserToolbar::setCanGoForward(bool canGoForward) {
    m_forwardBtn->setEnabled(canGoForward);
}

} // namespace ktbrowser
