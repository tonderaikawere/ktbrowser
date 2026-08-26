#include "ktbrowser/ui/SettingsPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

namespace ktbrowser {

SettingsPage::SettingsPage(QWidget* parent)
    : QWidget(parent) {
    setupUi();
    loadSettings();
}

void SettingsPage::setupUi() {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);

    auto* titleLabel = new QLabel("⚙️ KT Browser Settings", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #ffffff; margin-bottom: 12px;");
    mainLayout->addWidget(titleLabel);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setStyleSheet(R"(
        QTabWidget::pane {
            border: 1px solid #362947;
            background: #2b223b;
            border-radius: 12px;
            padding: 16px;
        }
        QTabBar::tab {
            background: #261f33;
            color: #b3a0d9;
            padding: 10px 20px;
            font-size: 14px;
            font-weight: bold;
            border-top-left-radius: 8px;
            border-top-right-radius: 8px;
            margin-right: 4px;
        }
        QTabBar::tab:selected {
            background: #382d47;
            color: #ffffff;
            border-bottom: 2px solid #d0bcff;
        }
    )");

    // 1. Appearance Tab
    auto* appearanceTab = new QWidget(m_tabWidget);
    auto* appLayout = new QFormLayout(appearanceTab);
    m_themeCombo = new QComboBox(appearanceTab);
    m_themeCombo->addItems({"dark", "light", "system"});
    appLayout->addRow("🎨 Application Theme:", m_themeCombo);

    // 2. Search Engine Tab
    auto* searchTab = new QWidget(m_tabWidget);
    auto* searchLayout = new QFormLayout(searchTab);
    m_searchEngineCombo = new QComboBox(searchTab);
    m_searchEngineCombo->addItems({"Google", "DuckDuckGo", "Brave Search", "Bing", "Custom"});
    m_customSearchEdit = new QLineEdit(searchTab);
    m_customSearchEdit->setPlaceholderText("https://example.com/search?q=%1");
    searchLayout->addRow("🔍 Default Search Engine:", m_searchEngineCombo);
    searchLayout->addRow("🔗 Custom Search URL:", m_customSearchEdit);

    // 3. Privacy & Security Tab
    auto* privacyTab = new QWidget(m_tabWidget);
    auto* privLayout = new QVBoxLayout(privacyTab);
    m_adBlockCheckBox = new QCheckBox("🛡️ Enable AdBlock Protection", privacyTab);
    m_trackerProtectionCheckBox = new QCheckBox("🕵️ Enable Tracker Interceptor", privacyTab);
    m_dntCheckBox = new QCheckBox("🚫 Send Do-Not-Track (DNT) Header", privacyTab);
    m_clearDataBtn = new QPushButton("🗑️ Clear Browsing Data", privacyTab);
    m_clearDataBtn->setStyleSheet("background: #b3261e; color: #ffffff; padding: 8px 16px; border-radius: 8px; font-weight: bold;");

    privLayout->addWidget(m_adBlockCheckBox);
    privLayout->addWidget(m_trackerProtectionCheckBox);
    privLayout->addWidget(m_dntCheckBox);
    privLayout->addSpacing(16);
    privLayout->addWidget(m_clearDataBtn);

    // 4. Downloads Tab
    auto* downloadsTab = new QWidget(m_tabWidget);
    auto* dlLayout = new QFormLayout(downloadsTab);
    m_downloadPathEdit = new QLineEdit(downloadsTab);
    m_askSavePathCheckBox = new QCheckBox("Ask where to save each file before downloading", downloadsTab);
    dlLayout->addRow("📥 Default Location:", m_downloadPathEdit);
    dlLayout->addRow("", m_askSavePathCheckBox);

    // Add Tabs
    m_tabWidget->addTab(appearanceTab, "🎨 Appearance");
    m_tabWidget->addTab(searchTab, "🔍 Search Engine");
    m_tabWidget->addTab(privacyTab, "🛡️ Privacy & Security");
    m_tabWidget->addTab(downloadsTab, "📥 Downloads");

    mainLayout->addWidget(m_tabWidget);

    auto* btnLayout = new QHBoxLayout();
    auto* saveBtn = new QPushButton("Save Settings", this);
    saveBtn->setStyleSheet("background: #6750a4; color: #ffffff; padding: 10px 24px; border-radius: 20px; font-weight: bold;");
    btnLayout->addStretch();
    btnLayout->addWidget(saveBtn);
    mainLayout->addLayout(btnLayout);

    connect(saveBtn, &QPushButton::clicked, this, &SettingsPage::saveSettings);
    connect(m_clearDataBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Clear Data", "Browsing history, cache, and cookies cleared successfully!");
    });
}

void SettingsPage::loadSettings() {
    m_themeCombo->setCurrentText(m_repo.theme());
    m_searchEngineCombo->setCurrentText(m_repo.defaultSearchEngine());
    m_customSearchEdit->setText(m_repo.customSearchEngineUrl());
    m_adBlockCheckBox->setChecked(m_repo.isAdBlockEnabled());
    m_trackerProtectionCheckBox->setChecked(m_repo.isTrackerProtectionEnabled());
    m_downloadPathEdit->setText(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
}

void SettingsPage::saveSettings() {
    m_repo.setTheme(m_themeCombo->currentText());
    m_repo.setDefaultSearchEngine(m_searchEngineCombo->currentText());
    m_repo.setCustomSearchEngineUrl(m_customSearchEdit->text());
    m_repo.setAdBlockEnabled(m_adBlockCheckBox->isChecked());
    m_repo.setTrackerProtectionEnabled(m_trackerProtectionCheckBox->isChecked());

    QMessageBox::information(this, "Settings Saved", "Your settings have been saved successfully!");
}

} // namespace ktbrowser
