#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

namespace codebrowser {

class NewTabPage : public QWidget {
    Q_OBJECT
public:
    explicit NewTabPage(QWidget* parent = nullptr);

    void refreshStats();

signals:
    void navigateRequested(const QString& urlOrSearch);

private:
    void setupUi();

    QLineEdit* m_searchEdit{nullptr};
    QLabel* m_adsBlockedLabel{nullptr};
    QLabel* m_trackersBlockedLabel{nullptr};
};

} // namespace codebrowser
