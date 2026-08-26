#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include "ktbrowser/database/SettingsRepository.h"

namespace ktbrowser {

class SettingsPage : public QWidget {
    Q_OBJECT
public:
    explicit SettingsPage(QWidget* parent = nullptr);

    void loadSettings();
    void saveSettings();

signals:
    void settingsChanged();

private:
    void setupUi();

    QTabWidget* m_tabWidget{nullptr};

    // Appearance
    QComboBox* m_themeCombo{nullptr};
    
    // Search Engine
    QComboBox* m_searchEngineCombo{nullptr};
    QLineEdit* m_customSearchEdit{nullptr};

    // Privacy & Security
    QCheckBox* m_adBlockCheckBox{nullptr};
    QCheckBox* m_trackerProtectionCheckBox{nullptr};
    QCheckBox* m_dntCheckBox{nullptr};
    QPushButton* m_clearDataBtn{nullptr};

    // Downloads
    QLineEdit* m_downloadPathEdit{nullptr};
    QCheckBox* m_askSavePathCheckBox{nullptr};

    SettingsRepository m_repo;
};

} // namespace ktbrowser
