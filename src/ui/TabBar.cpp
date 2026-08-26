#include "ktbrowser/ui/TabBar.h"
#include <QHBoxLayout>
#include <QStyle>

namespace ktbrowser {

TabBar::TabBar(QWidget* parent)
    : QWidget(parent) {
    setupUi();
}

void TabBar::setupUi() {
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(8, 6, 8, 0);
    mainLayout->setSpacing(6);

    setStyleSheet("background-color: #231a2e;");

    m_tabBar = new QTabBar(this);
    m_tabBar->setTabsClosable(true);
    m_tabBar->setMovable(true);
    m_tabBar->setExpanding(false);
    m_tabBar->setDocumentMode(true);

    m_tabBar->setStyleSheet(R"(
        QTabBar {
            background-color: #38201d;
            padding-top: 6px;
            padding-left: 8px;
        }
        QTabBar::tab {
            background: #38201d;
            color: #d8a499;
            border-top-left-radius: 10px;
            border-top-right-radius: 10px;
            padding: 8px 18px;
            margin-right: 3px;
            min-width: 150px;
            font-size: 13px;
            font-weight: 500;
        }
        QTabBar::tab:selected {
            background: #543431;
            color: #f3b4a2;
            font-weight: bold;
            border-bottom: 2px solid #f5b6a7;
        }
        QTabBar::tab:hover:!selected {
            background: #462925;
            color: #ffffff;
        }
        QTabBar::close-button {
            image: none;
            subcontrol-position: right;
            margin-left: 6px;
        }
        QTabBar::close-button:hover {
            background: rgba(255, 255, 255, 0.2);
            border-radius: 8px;
        }
    )");

    m_newTabBtn = new QToolButton(this);
    m_newTabBtn->setText("+");
    m_newTabBtn->setToolTip("Open New Tab (Ctrl+T)");
    m_newTabBtn->setStyleSheet(R"(
        QToolButton {
            background: transparent;
            color: #d0bcff;
            border: none;
            border-radius: 14px;
            font-size: 18px;
            font-weight: bold;
            min-width: 28px;
            min-height: 28px;
        }
        QToolButton:hover {
            background: rgba(208, 188, 255, 0.2);
            color: #ffffff;
        }
    )");

    // Top Right KT AI Assistant pill button
    auto* askGeminiBtn = new QToolButton(this);
    askGeminiBtn->setText("✨ KT AI Assistant");
    askGeminiBtn->setToolTip("KT Browser AI Assistant");
    askGeminiBtn->setStyleSheet(R"(
        QToolButton {
            background-color: #4a3461;
            color: #ffffff;
            font-size: 12px;
            font-weight: bold;
            border-radius: 14px;
            padding: 4px 14px;
            margin-bottom: 4px;
        }
        QToolButton:hover {
            background-color: #5c4278;
        }
    )");

    mainLayout->addWidget(m_tabBar);
    mainLayout->addWidget(m_newTabBtn);
    mainLayout->addStretch();
    mainLayout->addWidget(askGeminiBtn);

    connect(m_tabBar, &QTabBar::currentChanged, this, &TabBar::currentChanged);
    connect(m_tabBar, &QTabBar::tabCloseRequested, this, &TabBar::tabCloseRequested);
    connect(m_tabBar, &QTabBar::tabCloseRequested, this, &TabBar::closeTabRequested);
    connect(m_tabBar, &QTabBar::tabMoved, this, &TabBar::tabMoved);
    connect(m_newTabBtn, &QToolButton::clicked, this, &TabBar::newTabRequested);
}

int TabBar::addTab(const QString& text) {
    return m_tabBar->addTab(text);
}

void TabBar::insertTab(int index, const QString& text) {
    m_tabBar->insertTab(index, text);
}

void TabBar::removeTab(int index) {
    m_tabBar->removeTab(index);
}

void TabBar::setTabText(int index, const QString& text) {
    m_tabBar->setTabText(index, text);
}

void TabBar::setTabIcon(int index, const QIcon& icon) {
    m_tabBar->setTabIcon(index, icon);
}

void TabBar::setCurrentIndex(int index) {
    m_tabBar->setCurrentIndex(index);
}

int TabBar::currentIndex() const {
    return m_tabBar->currentIndex();
}

int TabBar::count() const {
    return m_tabBar->count();
}

} // namespace ktbrowser
