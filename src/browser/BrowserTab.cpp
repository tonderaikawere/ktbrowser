#include "codebrowser/browser/BrowserTab.h"
#include "codebrowser/adblock/AdBlockEngine.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace codebrowser {

BrowserTab::BrowserTab(QWidget* parent)
    : QWidget(parent) {
    setupUi();
}

void BrowserTab::setupUi() {
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    m_newTabPage = new NewTabPage(this);
    m_layout->addWidget(m_newTabPage);

#ifdef CODEBROWSER_HAS_WEBENGINE
    m_webView = new QWebEngineView(this);
    m_layout->addWidget(m_webView);
    m_webView->hide();

    connect(m_webView, &QWebEngineView::titleChanged, this, [this](const QString& title) {
        if (!m_isNtp) {
            m_title = title;
            emit titleChanged(m_title);
        }
    });

    connect(m_webView, &QWebEngineView::iconChanged, this, [this](const QIcon& icon) {
        if (!m_isNtp) {
            m_icon = icon;
            emit iconChanged(m_icon);
        }
    });

    connect(m_webView, &QWebEngineView::urlChanged, this, [this](const QUrl& url) {
        if (!m_isNtp) {
            m_url = url;
            emit urlChanged(m_url);
        }
    });

    connect(m_webView, &QWebEngineView::loadStarted, this, [this]() {
        m_isLoading = true;
        emit loadStarted();
    });

    connect(m_webView, &QWebEngineView::loadFinished, this, [this](bool success) {
        m_isLoading = false;
        emit loadFinished(success);
    });

    connect(m_webView, &QWebEngineView::loadProgress, this, &BrowserTab::loadProgress);
#else
    m_textBrowser = new QTextBrowser(this);
    m_textBrowser->setOpenExternalLinks(false);
    m_layout->addWidget(m_textBrowser);
    m_textBrowser->hide();

    connect(m_textBrowser, &QTextBrowser::anchorClicked, this, [this](const QUrl& link) {
        loadUrl(link);
    });
#endif
}

QUrl BrowserTab::url() const {
    return m_isNtp ? QUrl("codebrowser://newtab") : m_url;
}

QString BrowserTab::title() const {
    return m_isNtp ? "New Tab" : (m_title.isEmpty() ? m_url.toString() : m_title);
}

QIcon BrowserTab::icon() const {
    return m_icon;
}

void BrowserTab::loadUrl(const QUrl& url) {
    if (!url.isValid()) return;

    if (url.toString() == "codebrowser://newtab") {
        loadNewTabPage();
        return;
    }

    m_isNtp = false;
    m_url = url;
    m_newTabPage->hide();

#ifdef CODEBROWSER_HAS_WEBENGINE
    m_webView->show();
    m_webView->load(url);
#else
    m_textBrowser->show();
    m_isLoading = true;
    emit loadStarted();

    // Perform native HTTP request with privacy request interception
    auto* manager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    
    QString reason;
    if (AdBlockEngine::instance().shouldBlockRequest(url, url, &reason)) {
        m_textBrowser->setHtml("<h2 style='color:#e74c3c;'>🛡️ Network Request Blocked by CodeBrowser Privacy Shield</h2>"
                               "<p>Target URL: " + url.toString() + "</p>"
                               "<p>Reason: " + reason + "</p>");
        m_isLoading = false;
        emit loadFinished(false);
        return;
    }

    QNetworkReply* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        m_isLoading = false;
        if (reply->error() == QNetworkReply::NoError) {
            m_textBrowser->setHtml(QString::fromUtf8(reply->readAll()));
            emit loadFinished(true);
        } else {
            m_textBrowser->setHtml("<h2>Failed to load " + m_url.toString() + "</h2><p>" + reply->errorString() + "</p>");
            emit loadFinished(false);
        }
        reply->deleteLater();
    });
#endif

    emit urlChanged(m_url);
}

void BrowserTab::loadNewTabPage() {
    m_isNtp = true;
    m_url = QUrl("codebrowser://newtab");
    m_title = "New Tab";

#ifdef CODEBROWSER_HAS_WEBENGINE
    if (m_webView) m_webView->hide();
#else
    if (m_textBrowser) m_textBrowser->hide();
#endif

    m_newTabPage->show();
    emit titleChanged(m_title);
    emit urlChanged(m_url);
}

bool BrowserTab::canGoBack() const {
#ifdef CODEBROWSER_HAS_WEBENGINE
    return m_webView && m_webView->history() ? m_webView->history()->canGoBack() : false;
#else
    return m_textBrowser ? m_textBrowser->historyTitle(-1).length() > 0 : false;
#endif
}

bool BrowserTab::canGoForward() const {
#ifdef CODEBROWSER_HAS_WEBENGINE
    return m_webView && m_webView->history() ? m_webView->history()->canGoForward() : false;
#else
    return m_textBrowser ? m_textBrowser->historyTitle(1).length() > 0 : false;
#endif
}

void BrowserTab::back() {
#ifdef CODEBROWSER_HAS_WEBENGINE
    if (m_webView) m_webView->back();
#else
    if (m_textBrowser) m_textBrowser->backward();
#endif
}

void BrowserTab::forward() {
#ifdef CODEBROWSER_HAS_WEBENGINE
    if (m_webView) m_webView->forward();
#else
    if (m_textBrowser) m_textBrowser->forward();
#endif
}

void BrowserTab::reload() {
#ifdef CODEBROWSER_HAS_WEBENGINE
    if (m_webView) m_webView->reload();
#else
    if (!m_url.isEmpty()) loadUrl(m_url);
#endif
}

void BrowserTab::stop() {
#ifdef CODEBROWSER_HAS_WEBENGINE
    if (m_webView) m_webView->stop();
#endif
}

} // namespace codebrowser
