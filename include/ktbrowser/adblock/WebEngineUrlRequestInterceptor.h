#pragma once

#include <QObject>

#ifdef KTBROWSER_HAS_WEBENGINE
#include <QWebEngineUrlRequestInterceptor>

namespace ktbrowser {

class WebEngineUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor {
    Q_OBJECT
public:
    explicit WebEngineUrlRequestInterceptor(QObject* parent = nullptr);
    ~WebEngineUrlRequestInterceptor() override = default;

    void interceptRequest(QWebEngineUrlRequestInfo& info) override;
};

} // namespace ktbrowser
#else
namespace ktbrowser {
class WebEngineUrlRequestInterceptor : public QObject {
    Q_OBJECT
public:
    explicit WebEngineUrlRequestInterceptor(QObject* parent = nullptr) : QObject(parent) {}
};
} // namespace ktbrowser
#endif
