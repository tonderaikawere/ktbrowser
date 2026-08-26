#pragma once

#include <QDialog>
#include <QTabWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

namespace ktbrowser {

class SettingsWindow : public QDialog {
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget* parent = nullptr);

private:
    void setupUi();
    void loadSettings();
    void saveSettings();

    QTabWidget* m_tabWidget{nullptr};
    
    // Controls
    QComboBox* m_searchEngineCombo{nullptr};
    QLineEdit* m_customSearchEdit{nullptr};
    QCheckBox* m_adBlockCheckBox{nullptr};
    QCheckBox* m_trackerProtectionCheckBox{nullptr};
    QCheckBox* m_thirdPartyCookiesCheckBox{nullptr};
    QComboBox* m_themeCombo{nullptr};
    QLineEdit* m_downloadLocationEdit{nullptr};
};

} // namespace ktbrowser
