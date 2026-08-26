#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

namespace ktbrowser {

class NewTabPage : public QWidget {
    Q_OBJECT
public:
    explicit NewTabPage(QWidget* parent = nullptr);

    void refreshStats();

signals:
    void navigateRequested(const QString& urlOrSearch);
    void searchRequested(const QString& query);

private:
    void setupUi();

    QLineEdit* m_searchEdit{nullptr};
    QLabel* m_adsBlockedLabel{nullptr};
    QLabel* m_trackersBlockedLabel{nullptr};
};

} // namespace ktbrowser
