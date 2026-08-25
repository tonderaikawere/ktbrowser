#include "codebrowser/privacy/PrivacyDashboard.h"
#include "codebrowser/adblock/AdBlockEngine.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QStyle>
#include <QDebug>

namespace codebrowser {

PrivacyDashboard::PrivacyDashboard(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("CodeBrowser Privacy Protection Dashboard");
    setMinimumSize(540, 520);
    setWindowModality(Qt::ApplicationModal);
    
    setupUi();
    refreshStatistics();

    connect(&AdBlockEngine::instance().statistics(), &BlockStatistics::statisticsUpdated,
            this, &PrivacyDashboard::refreshStatistics);

    connect(&AdBlockEngine::instance(), &AdBlockEngine::requestBlocked,
            this, &PrivacyDashboard::refreshStatistics);
}

void PrivacyDashboard::setupUi() {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Header
    auto* headerLabel = new QLabel("<h2>Privacy Protection Dashboard</h2>", this);
    headerLabel->setTextFormat(Qt::RichText);
    mainLayout->addWidget(headerLabel);

    // Stats Box
    auto* statsGroup = new QGroupBox("Session Shield Statistics", this);
    auto* formLayout = new QFormLayout(statsGroup);
    formLayout->setSpacing(10);

    m_adsBlockedLabel = new QLabel("0", this);
    m_adsBlockedLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #2ecc71;");
    formLayout->addRow("Ads blocked:", m_adsBlockedLabel);

    m_trackersBlockedLabel = new QLabel("0", this);
    m_trackersBlockedLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #3498db;");
    formLayout->addRow("Trackers blocked:", m_trackersBlockedLabel);

    m_requestsBlockedLabel = new QLabel("0", this);
    m_requestsBlockedLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #9b59b6;");
    formLayout->addRow("Total requests blocked:", m_requestsBlockedLabel);

    m_httpsPercentageLabel = new QLabel("100%", this);
    m_httpsPercentageLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #e67e22;");
    formLayout->addRow("HTTPS connections:", m_httpsPercentageLabel);

    mainLayout->addWidget(statsGroup);

    // Recent Blocked Requests Log
    auto* blockedGroup = new QGroupBox("Recently Blocked Requests & Trackers", this);
    auto* blockedLayout = new QVBoxLayout(blockedGroup);
    
    m_blockedTable = new QTableWidget(this);
    m_blockedTable->setColumnCount(3);
    m_blockedTable->setHorizontalHeaderLabels({"Time", "Blocked Target URL", "Filter Reason"});
    m_blockedTable->setColumnWidth(0, 80);
    m_blockedTable->setColumnWidth(1, 240);
    m_blockedTable->horizontalHeader()->setStretchLastSection(true);
    blockedLayout->addWidget(m_blockedTable);

    mainLayout->addWidget(blockedGroup);

    // Status Box
    auto* statusGroup = new QGroupBox("Global Protection Status", this);
    auto* statusLayout = new QHBoxLayout(statusGroup);

    m_protectionStatusLabel = new QLabel("Protection: ON", this);
    m_protectionStatusLabel->setStyleSheet("font-weight: bold; font-size: 15px; color: #27ae60;");
    statusLayout->addWidget(m_protectionStatusLabel);

    m_toggleProtectionBtn = new QPushButton("Pause Protection", this);
    statusLayout->addWidget(m_toggleProtectionBtn);

    connect(m_toggleProtectionBtn, &QPushButton::clicked, this, [this]() {
        bool current = AdBlockEngine::instance().isEnabled();
        bool newState = !current;
        AdBlockEngine::instance().setEnabled(newState);
        
        if (newState) {
            m_protectionStatusLabel->setText("Protection: ON");
            m_protectionStatusLabel->setStyleSheet("font-weight: bold; font-size: 15px; color: #27ae60;");
            m_toggleProtectionBtn->setText("Pause Protection");
        } else {
            m_protectionStatusLabel->setText("Protection: OFF");
            m_protectionStatusLabel->setStyleSheet("font-weight: bold; font-size: 15px; color: #e74c3c;");
            m_toggleProtectionBtn->setText("Enable Protection");
        }
    });

    mainLayout->addWidget(statusGroup);

    // Close button
    auto* closeBtn = new QPushButton("Close", this);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeBtn, 0, Qt::AlignRight);
}

void PrivacyDashboard::refreshStatistics() {
    auto& stats = AdBlockEngine::instance().statistics();
    m_adsBlockedLabel->setText(QString::number(stats.adsBlocked()));
    m_trackersBlockedLabel->setText(QString::number(stats.trackersBlocked()));
    m_requestsBlockedLabel->setText(QString::number(stats.requestsBlocked()));
    m_httpsPercentageLabel->setText(QString::number(stats.httpsPercentage(), 'f', 1) + "%");

    // Populate live blocked requests table
    auto logs = AdBlockEngine::instance().recentBlockedLogs();
    m_blockedTable->setRowCount(0);

    for (const auto& log : logs) {
        int r = m_blockedTable->rowCount();
        m_blockedTable->insertRow(r);
        m_blockedTable->setItem(r, 0, new QTableWidgetItem(log.timestamp.toString("hh:mm:ss")));
        m_blockedTable->setItem(r, 1, new QTableWidgetItem(log.url));
        m_blockedTable->setItem(r, 2, new QTableWidgetItem(log.reason));
    }
}

} // namespace codebrowser
