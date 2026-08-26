#include "ktbrowser/settings/SettingsWindow.h"
#include "ktbrowser/database/SettingsRepository.h"
#include "ktbrowser/adblock/AdBlockEngine.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

namespace ktbrowser {

SettingsWindow::SettingsWindow(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("KT Browser Settings");
    setMinimumSize(540, 420);
    setWindowModality(Qt::ApplicationModal);

    setupUi();
    loadSettings();
}

void SettingsWindow::setupUi() {
    auto* mainLayout = new QVBoxLayout(this);
    
    m_tabWidget = new QTabWidget(this);

    // General Tab
    auto* generalTab = new QWidget(this);
    auto* generalLayout = new QFormLayout(generalTab);
    
    m_searchEngineCombo = new QComboBox(generalTab);
    m_searchEngineCombo->addItems({"DuckDuckGo", "Google", "Bing", "Brave Search", "Custom"});
    generalLayout->addRow("Default Search Engine:", m_searchEngineCombo);

    m_customSearchEdit = new QLineEdit(generalTab);
    m_customSearchEdit->setPlaceholderText("https://search.example.com/search?q=%s");
    generalLayout->addRow("Custom Search Engine URL:", m_customSearchEdit);

    m_tabWidget->addTab(generalTab, "General");

    // Privacy & Ad Blocking Tab
    auto* privacyTab = new QWidget(this);
    auto* privacyLayout = new QVBoxLayout(privacyTab);

    m_adBlockCheckBox = new QCheckBox("Enable Ad and Network Tracker Blocking", privacyTab);
    m_trackerProtectionCheckBox = new QCheckBox("Enable Fingerprinting & Analytics Protection", privacyTab);
    m_thirdPartyCookiesCheckBox = new QCheckBox("Block Third-Party Cookies", privacyTab);

    privacyLayout->addWidget(m_adBlockCheckBox);
    privacyLayout->addWidget(m_trackerProtectionCheckBox);
    privacyLayout->addWidget(m_thirdPartyCookiesCheckBox);
    privacyLayout->addStretch();

    m_tabWidget->addTab(privacyTab, "Privacy & Ad Blocking");

    // Appearance Tab
    auto* appearanceTab = new QWidget(this);
    auto* appearanceLayout = new QFormLayout(appearanceTab);

    m_themeCombo = new QComboBox(appearanceTab);
    m_themeCombo->addItems({"System", "Light", "Dark"});
    appearanceLayout->addRow("Browser Theme Mode:", m_themeCombo);

    m_tabWidget->addTab(appearanceTab, "Appearance");

    mainLayout->addWidget(m_tabWidget);

    // Buttons
    auto* buttonBox = new QHBoxLayout();
    buttonBox->addStretch();

    auto* cancelBtn = new QPushButton("Cancel", this);
    auto* saveBtn = new QPushButton("Save & Apply", this);
    saveBtn->setDefault(true);

    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(saveBtn, &QPushButton::clicked, this, [this]() {
        saveSettings();
        accept();
    });

    buttonBox->addWidget(cancelBtn);
    buttonBox->addWidget(saveBtn);

    mainLayout->addLayout(buttonBox);
}

void SettingsWindow::loadSettings() {
    SettingsRepository repo;
    
    QString engine = repo.defaultSearchEngine();
    int idx = m_searchEngineCombo->findText(engine);
    if (idx != -1) m_searchEngineCombo->setCurrentIndex(idx);

    m_customSearchEdit->setText(repo.customSearchEngineUrl());
    m_adBlockCheckBox->setChecked(repo.isAdBlockEnabled());
    m_trackerProtectionCheckBox->setChecked(repo.isTrackerProtectionEnabled());

    QString theme = repo.theme();
    if (theme == "dark") m_themeCombo->setCurrentText("Dark");
    else if (theme == "light") m_themeCombo->setCurrentText("Light");
    else m_themeCombo->setCurrentText("System");
}

void SettingsWindow::saveSettings() {
    SettingsRepository repo;
    repo.setDefaultSearchEngine(m_searchEngineCombo->currentText());
    repo.setCustomSearchEngineUrl(m_customSearchEdit->text());
    
    bool adblock = m_adBlockCheckBox->isChecked();
    repo.setAdBlockEnabled(adblock);
    AdBlockEngine::instance().setEnabled(adblock);

    repo.setTrackerProtectionEnabled(m_trackerProtectionCheckBox->isChecked());
    repo.setTheme(m_themeCombo->currentText().toLower());
}

} // namespace ktbrowser
