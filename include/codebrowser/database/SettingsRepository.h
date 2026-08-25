#pragma once

#include <QString>
#include <QVariant>
#include <unordered_map>

namespace codebrowser {

class SettingsRepository {
public:
    SettingsRepository() = default;

    void setSetting(const QString& key, const QVariant& value);
    QVariant getSetting(const QString& key, const QVariant& defaultValue = QVariant());
    
    // Quick helpers
    QString defaultSearchEngine();
    void setDefaultSearchEngine(const QString& engineName);
    
    QString customSearchEngineUrl();
    void setCustomSearchEngineUrl(const QString& url);

    bool isAdBlockEnabled();
    void setAdBlockEnabled(bool enabled);

    bool isTrackerProtectionEnabled();
    void setTrackerProtectionEnabled(bool enabled);

    QString theme(); // "light", "dark", "system"
    void setTheme(const QString& theme);
};

} // namespace codebrowser
