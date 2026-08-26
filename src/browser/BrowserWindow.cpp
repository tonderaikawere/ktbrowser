#include "ktbrowser/browser/BrowserWindow.h"
#include "ktbrowser/browser/NavigationController.h"
#include "ktbrowser/adblock/AdBlockEngine.h"
#include "ktbrowser/database/SettingsRepository.h"
#include "ktbrowser/database/BookmarkRepository.h"
#include "ktbrowser/privacy/PrivacyDashboard.h"
#include "ktbrowser/settings/SettingsWindow.h"
#include "ktbrowser/ui/BookmarkManagerWidget.h"
#include "ktbrowser/ui/HistoryManagerWidget.h"
#include "ktbrowser/ui/DownloadsWidget.h"

#include <QVBoxLayout>
#include <QShortcut>
#include <QKeySequence>
#include <QApplication>
#include <QStyleFactory>
#include <QMessageBox>
#include <QDebug>

namespace ktbrowser {

BrowserWindow::BrowserWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("KT Browser by Kawerify Tech");
    resize(1280, 800);
    setMinimumSize(800, 600);

    setupUi();
    setupConnections();

    // Apply saved theme
    SettingsRepository repo;
    applyTheme(repo.theme());

    // Create default home tab
    m_tabManager->createTab(QUrl("ktbrowser://newtab"), true);
}

void BrowserWindow::setupUi() {
    setWindowIcon(qApp->windowIcon());

    auto* centralWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_tabBar = new TabBar(this);
    m_toolbar = new BrowserToolbar(this);
    m_stackedWidget = new QStackedWidget(this);

    mainLayout->addWidget(m_tabBar);
    mainLayout->addWidget(m_toolbar);
    mainLayout->addWidget(m_stackedWidget);

    setCentralWidget(centralWidget);

    m_tabManager = new TabManager(m_tabBar, m_stackedWidget, this);
}

void BrowserWindow::setupConnections() {
    // Toolbar navigation
    connect(m_toolbar, &BrowserToolbar::backRequested, this, [this]() {
        if (auto* tab = m_tabManager->currentTab()) {
            tab->back();
        }
    });

    connect(m_toolbar, &BrowserToolbar::forwardRequested, this, [this]() {
        if (auto* tab = m_tabManager->currentTab()) {
            tab->forward();
        }
    });

    connect(m_toolbar, &BrowserToolbar::reloadRequested, this, [this]() {
        if (auto* tab = m_tabManager->currentTab()) {
            tab->reload();
        }
    });

    connect(m_toolbar, &BrowserToolbar::stopRequested, this, [this]() {
        if (auto* tab = m_tabManager->currentTab()) {
            tab->stop();
        }
    });

    connect(m_toolbar, &BrowserToolbar::homeRequested, this, [this]() {
        if (auto* tab = m_tabManager->currentTab()) {
            tab->loadNewTabPage();
        }
    });

    connect(m_toolbar, &BrowserToolbar::privacyDashboardRequested, this, [this]() {
        PrivacyDashboard dialog(this);
        dialog.exec();
    });

    connect(m_toolbar, &BrowserToolbar::bookmarkRequested, this, [this]() {
        BookmarkManagerWidget bmWidget(this);
        connect(&bmWidget, &BookmarkManagerWidget::openUrlRequested, this, [this](const QString& url) {
            if (auto* tab = m_tabManager->currentTab()) {
                tab->loadUrl(QUrl(url));
            }
        });
        bmWidget.exec();
    });

    connect(m_toolbar, &BrowserToolbar::historyRequested, this, [this]() {
        HistoryManagerWidget histWidget(this);
        connect(&histWidget, &HistoryManagerWidget::openUrlRequested, this, [this](const QString& url) {
            if (auto* tab = m_tabManager->currentTab()) {
                tab->loadUrl(QUrl(url));
            }
        });
        histWidget.exec();
    });

    connect(m_toolbar, &BrowserToolbar::downloadsRequested, this, [this]() {
        DownloadsWidget dlWidget(this);
        dlWidget.exec();
    });

    connect(m_toolbar, &BrowserToolbar::settingsRequested, this, [this]() {
        SettingsWindow settings(this);
        if (settings.exec() == QDialog::Accepted) {
            SettingsRepository repo;
            applyTheme(repo.theme());
        }
    });

    // Address Bar input
    connect(m_toolbar->addressBar(), &AddressBar::navigateRequested, this, [this](const QString& input) {
        if (auto* tab = m_tabManager->currentTab()) {
            SettingsRepository repo;
            QUrl target = NavigationController::parseInput(input, repo.defaultSearchEngine(), repo.customSearchEngineUrl());
            tab->loadUrl(target);
        }
    });

    // Tab state updates to toolbar
    connect(m_tabManager, &TabManager::currentTabChanged, this, [this](BrowserTab* tab) {
        if (!tab) return;

        m_toolbar->addressBar()->setUrl(tab->url());
        m_toolbar->setCanGoBack(tab->canGoBack());
        m_toolbar->setCanGoForward(tab->canGoForward());
        m_toolbar->setIsLoading(tab->isLoading());
    });

    // Keyboard Shortcuts
    new QShortcut(QKeySequence("Ctrl+T"), this, [this]() {
        m_tabManager->createTab(QUrl("ktbrowser://newtab"), true);
    });

    new QShortcut(QKeySequence("Ctrl+W"), this, [this]() {
        m_tabManager->closeTab(m_tabManager->currentIndex());
    });

    new QShortcut(QKeySequence("Ctrl+Shift+T"), this, [this]() {
        m_tabManager->restoreClosedTab();
    });

    new QShortcut(QKeySequence("Ctrl+H"), this, [this]() {
        HistoryManagerWidget histWidget(this);
        connect(&histWidget, &HistoryManagerWidget::openUrlRequested, this, [this](const QString& url) {
            if (auto* tab = m_tabManager->currentTab()) {
                tab->loadUrl(QUrl(url));
            }
        });
        histWidget.exec();
    });

    new QShortcut(QKeySequence("Ctrl+B"), this, [this]() {
        BookmarkManagerWidget bmWidget(this);
        connect(&bmWidget, &BookmarkManagerWidget::openUrlRequested, this, [this](const QString& url) {
            if (auto* tab = m_tabManager->currentTab()) {
                tab->loadUrl(QUrl(url));
            }
        });
        bmWidget.exec();
    });

    new QShortcut(QKeySequence("Ctrl+J"), this, [this]() {
        DownloadsWidget dlWidget(this);
        dlWidget.exec();
    });
}

void BrowserWindow::applyTheme(const QString& themeName) {
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(35, 26, 46));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(43, 34, 56));
    darkPalette.setColor(QPalette::AlternateBase, QColor(35, 26, 46));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(43, 34, 56));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(208, 188, 255));
    darkPalette.setColor(QPalette::Highlight, QColor(208, 188, 255));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
}

void BrowserWindow::keyPressEvent(QKeyEvent* event) {
    QMainWindow::keyPressEvent(event);
}

} // namespace ktbrowser
