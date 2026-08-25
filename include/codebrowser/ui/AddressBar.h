#pragma once

#include <QLineEdit>
#include <QAction>
#include <QLabel>

namespace codebrowser {

class AddressBar : public QLineEdit {
    Q_OBJECT
public:
    explicit AddressBar(QWidget* parent = nullptr);

    void setSecurityStatus(bool isHttps, bool isSecure);
    void setUrl(const QUrl& url);

signals:
    void navigateRequested(const QString& input);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;

private:
    QAction* m_securityAction{nullptr};
    QAction* m_bookmarkAction{nullptr};
    bool m_isHttps{false};
};

} // namespace codebrowser
