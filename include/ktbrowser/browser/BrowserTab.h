#pragma once

#include "ktbrowser/ui/NewTabPage.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QIcon>
#include <QUrl>

#ifdef KTBROWSER_HAS_WEBENGINE
#include <QWebEngineView>
#include <QWebEnginePage>
#endif

namespace ktbrowser {

class BrowserTab : public QWidget {
    Q_OBJECT
public:
    explicit BrowserTab(QWidget* parent = nullptr);
    ~BrowserTab() override = default;

#ifdef KTBROWSER_HAS_WEBENGINE
    QWebEngineView* webView() const { return m_webView; }
#else
    QTextBrowser* textBrowser() const { return m_textBrowser; }
#endif
    NewTabPage* newTabPage() const { return m_newTabPage; }

    QUrl url() const;
    QString title() const;
    QIcon icon() const;
    bool isLoading() const { return m_isLoading; }
    bool isNewTabPage() const { return m_isNtp; }

    void loadUrl(const QUrl& url);
    void loadNewTabPage();

    bool canGoBack() const;
    bool canGoForward() const;
    void back();
    void forward();
    void reload();
    void stop();

signals:
    void titleChanged(const QString& title);
    void iconChanged(const QIcon& icon);
    void urlChanged(const QUrl& url);
    void loadStarted();
    void loadFinished(bool success);
    void loadProgress(int progress);

private:
    void setupUi();

#ifdef KTBROWSER_HAS_WEBENGINE
    QWebEngineView* m_webView{nullptr};
#else
    QTextBrowser* m_textBrowser{nullptr};
#endif
    NewTabPage* m_newTabPage{nullptr};
    QVBoxLayout* m_layout{nullptr};

    bool m_isLoading{false};
    bool m_isNtp{true};
    QString m_title{"New Tab"};
    QIcon m_icon;
    QUrl m_url;
};

} // namespace ktbrowser
