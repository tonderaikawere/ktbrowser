#include "ktbrowser/browser/TabManager.h"
#include "ktbrowser/database/HistoryRepository.h"
#include "ktbrowser/downloads/DownloadManager.h"

#ifdef KTBROWSER_HAS_WEBENGINE
#include <QWebEngineProfile>
#endif
#include <QDebug>

namespace ktbrowser {

TabManager::TabManager(TabBar* tabBar, QStackedWidget* stackedWidget, QObject* parent)
    : QObject(parent), m_tabBar(tabBar), m_stackedWidget(stackedWidget) {

    connect(m_tabBar, &TabBar::currentChanged, this, &TabManager::switchToTab);
    connect(m_tabBar, &TabBar::closeTabRequested, this, &TabManager::closeTab);
    connect(m_tabBar, &TabBar::newTabRequested, this, [this]() {
        createTab(QUrl("ktbrowser://newtab"), true);
    });

#ifdef KTBROWSER_HAS_WEBENGINE
    // Wire global WebEngine profile downloads
    connect(QWebEngineProfile::defaultProfile(), &QWebEngineProfile::downloadRequested,
            &DownloadManager::instance(), &DownloadManager::manageDownload);
#endif
}

BrowserTab* TabManager::createTab(const QUrl& url, bool makeCurrent) {
    auto* tab = new BrowserTab(m_stackedWidget);
    int index = m_tabs.size();

    m_tabs.append(tab);
    m_stackedWidget->addWidget(tab);

    int tabIndex = m_tabBar->addTab(tab->title());

    connectTabSignals(tab, tabIndex);

    if (url.isValid() && url.toString() != "ktbrowser://newtab") {
        tab->loadUrl(url);
    } else {
        tab->loadNewTabPage();
    }

    if (makeCurrent) {
        switchToTab(tabIndex);
    }

    emit tabCountChanged(count());
    return tab;
}

void TabManager::connectTabSignals(BrowserTab* tab, int index) {
    connect(tab, &BrowserTab::titleChanged, this, [this, tab](const QString& title) {
        int idx = m_tabs.indexOf(tab);
        if (idx != -1) {
            m_tabBar->setTabText(idx, title);
        }
    });

    connect(tab, &BrowserTab::iconChanged, this, [this, tab](const QIcon& icon) {
        int idx = m_tabs.indexOf(tab);
        if (idx != -1) {
            m_tabBar->setTabIcon(idx, icon);
        }
    });

    connect(tab, &BrowserTab::urlChanged, this, [tab](const QUrl& url) {
        if (!url.isEmpty() && url.scheme() != "codebrowser") {
            HistoryRepository repo;
            repo.addOrUpdateHistory(url.toString(), tab->title());
        }
    });
}

void TabManager::closeTab(int index) {
    if (index < 0 || index >= m_tabs.size()) return;

    BrowserTab* tab = m_tabs.at(index);

    ClosedTabInfo info;
    info.url = tab->url();
    info.title = tab->title();
    m_closedTabsStack.push(info);

    m_tabBar->removeTab(index);
    m_stackedWidget->removeWidget(tab);
    m_tabs.removeAt(index);

    delete tab;

    if (m_tabs.isEmpty()) {
        createTab(QUrl("ktbrowser://newtab"), true);
    } else {
        int newIdx = qMin(index, m_tabs.size() - 1);
        switchToTab(newIdx);
    }

    emit tabCountChanged(count());
}

void TabManager::switchToTab(int index) {
    if (index < 0 || index >= m_tabs.size()) return;

    m_tabBar->setCurrentIndex(index);
    m_stackedWidget->setCurrentIndex(index);
    emit currentTabChanged(m_tabs.at(index));
}

void TabManager::duplicateTab(int index) {
    if (index < 0 || index >= m_tabs.size()) return;
    BrowserTab* tab = m_tabs.at(index);
    createTab(tab->url(), true);
}

void TabManager::restoreClosedTab() {
    if (!m_closedTabsStack.isEmpty()) {
        ClosedTabInfo info = m_closedTabsStack.pop();
        createTab(info.url, true);
    }
}

BrowserTab* TabManager::currentTab() const {
    int idx = currentIndex();
    return (idx >= 0 && idx < m_tabs.size()) ? m_tabs.at(idx) : nullptr;
}

int TabManager::currentIndex() const {
    return m_stackedWidget->currentIndex();
}

int TabManager::count() const {
    return m_tabs.size();
}

BrowserTab* TabManager::tabAt(int index) const {
    return (index >= 0 && index < m_tabs.size()) ? m_tabs.at(index) : nullptr;
}

} // namespace ktbrowser
