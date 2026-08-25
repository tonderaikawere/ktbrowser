#pragma once

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

namespace codebrowser {

class PrivacyDashboard : public QDialog {
    Q_OBJECT
public:
    explicit PrivacyDashboard(QWidget* parent = nullptr);

    void refreshStatistics();

private:
    void setupUi();

    QLabel* m_adsBlockedLabel{nullptr};
    QLabel* m_trackersBlockedLabel{nullptr};
    QLabel* m_requestsBlockedLabel{nullptr};
    QLabel* m_httpsPercentageLabel{nullptr};
    QLabel* m_protectionStatusLabel{nullptr};
    QPushButton* m_toggleProtectionBtn{nullptr};
    QTableWidget* m_blockedTable{nullptr};
};

} // namespace codebrowser
