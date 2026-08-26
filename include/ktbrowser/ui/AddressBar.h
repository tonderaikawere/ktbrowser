#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QUrl>

namespace ktbrowser {

class AddressBar : public QWidget {
    Q_OBJECT
public:
    explicit AddressBar(QWidget* parent = nullptr);

    void setUrl(const QUrl& url);
    QString text() const;

signals:
    void navigateRequested(const QString& input);

private:
    void setupUi();

    QLineEdit* m_lineEdit{nullptr};
    QLabel* m_searchIcon{nullptr};
};

} // namespace ktbrowser
