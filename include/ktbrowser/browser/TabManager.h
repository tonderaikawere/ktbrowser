#pragma once

#include "ktbrowser/browser/BrowserTab.h"
#include "ktbrowser/ui/TabBar.h"
#include <QObject>
#include <QStackedWidget>
#include <QList>
#include <QStack>
#include <QUrl>

namespace ktbrowser {

struct ClosedTabInfo {
    QUrl url;
    QString title;
};

class TabManager : public QObject {
    Q_OBJECT
public:
    TabManager(TabBar* tabBar, QStackedWidget* stackedWidget, QObject* parent = nullptr);

    BrowserTab* createTab(const QUrl& url = QUrl(), bool makeCurrent = true);
    void closeTab(int index);
    void switchToTab(int index);
    void duplicateTab(int index);
    void restoreClosedTab();

    BrowserTab* currentTab() const;
    int currentIndex() const;
    int count() const;
    BrowserTab* tabAt(int index) const;

signals:
    void currentTabChanged(BrowserTab* tab);
    void tabCountChanged(int count);

private:
    void connectTabSignals(BrowserTab* tab, int index);

    TabBar* m_tabBar{nullptr};
    QStackedWidget* m_stackedWidget{nullptr};
    QList<BrowserTab*> m_tabs;
    QStack<ClosedTabInfo> m_closedTabsStack;
};

} // namespace ktbrowser
