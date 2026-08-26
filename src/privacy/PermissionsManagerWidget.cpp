#include "ktbrowser/privacy/PermissionsManagerWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>

namespace ktbrowser {

PermissionsManagerWidget::PermissionsManagerWidget(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Site Permissions Manager");
    setMinimumSize(540, 360);
    setupUi();
    refreshPermissions();
}

void PermissionsManagerWidget::setupUi() {
    auto* mainLayout = new QVBoxLayout(this);

    auto* titleLabel = new QLabel("<h2>Site Permission Rules</h2>", this);
    titleLabel->setTextFormat(Qt::RichText);
    mainLayout->addWidget(titleLabel);

    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels({"Origin Domain", "Permission Feature", "State"});
    m_tableWidget->setColumnWidth(0, 240);
    m_tableWidget->setColumnWidth(1, 150);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);

    mainLayout->addWidget(m_tableWidget);

    auto* bottomBox = new QHBoxLayout();
    bottomBox->addStretch();
    auto* closeBtn = new QPushButton("Close", this);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    bottomBox->addWidget(closeBtn);

    mainLayout->addLayout(bottomBox);
}

void PermissionsManagerWidget::refreshPermissions() {
    m_tableWidget->setRowCount(0);
    // Populate permissions from PrivacyManager
}

} // namespace ktbrowser
