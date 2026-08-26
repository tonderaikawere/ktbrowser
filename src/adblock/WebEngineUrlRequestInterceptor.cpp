#include "ktbrowser/adblock/WebEngineUrlRequestInterceptor.h"
#include "ktbrowser/adblock/AdBlockEngine.h"
#include <QDebug>

namespace ktbrowser {

#ifdef KTBROWSER_HAS_WEBENGINE
WebEngineUrlRequestInterceptor::WebEngineUrlRequestInterceptor(QObject* parent)
    : QWebEngineUrlRequestInterceptor(parent) {
}

void WebEngineUrlRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo& info) {
    QUrl requestUrl = info.requestUrl();
    QUrl firstPartyUrl = info.firstPartyUrl();

    QString reason;
    if (AdBlockEngine::instance().shouldBlockRequest(requestUrl, firstPartyUrl, &reason)) {
        info.block(true);
        qDebug() << "[AdBlock Interceptor] BLOCKED:" << requestUrl.toString() << "(" << reason << ")";
    }
}
#endif

} // namespace ktbrowser
