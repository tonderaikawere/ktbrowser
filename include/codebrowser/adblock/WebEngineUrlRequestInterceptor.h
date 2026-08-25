#pragma once

#include <QObject>

#ifdef CODEBROWSER_HAS_WEBENGINE
#include <QWebEngineUrlRequestInterceptor>

namespace codebrowser {

class WebEngineUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor {
    Q_OBJECT
public:
    explicit WebEngineUrlRequestInterceptor(QObject* parent = nullptr);
    ~WebEngineUrlRequestInterceptor() override = default;

    void interceptRequest(QWebEngineUrlRequestInfo& info) override;
};

} // namespace codebrowser
#else
namespace codebrowser {
class WebEngineUrlRequestInterceptor : public QObject {
    Q_OBJECT
public:
    explicit WebEngineUrlRequestInterceptor(QObject* parent = nullptr) : QObject(parent) {}
};
} // namespace codebrowser
#endif
