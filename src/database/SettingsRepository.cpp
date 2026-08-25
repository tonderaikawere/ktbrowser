#include "codebrowser/database/SettingsRepository.h"
#include "codebrowser/database/Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

namespace codebrowser {

bool SettingsRepository::setSetting(const QString& key, const QString& value) {
    auto db = Database::instance().database();
    QSqlQuery query(db);

    query.prepare("INSERT OR REPLACE INTO settings (key, value) VALUES (:key, :value)");
    query.bindValue(":key", key);
    query.bindValue(":value", value);

    if (!query.exec()) {
        qWarning() << "Failed to set setting:" << query.lastError().text();
        return false;
    }
    return true;
}

QString SettingsRepository::setting(const QString& key, const QString& defaultValue) const {
    auto db = Database::instance().database();
    QSqlQuery query(db);

    query.prepare("SELECT value FROM settings WHERE key = :key");
    query.bindValue(":key", key);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return defaultValue;
}

QString SettingsRepository::defaultSearchEngine() const {
    return setting("search_engine", "Google");
}

void SettingsRepository::setDefaultSearchEngine(const QString& engine) {
    setSetting("search_engine", engine);
}

QString SettingsRepository::customSearchEngineUrl() const {
    return setting("custom_search_url", "https://www.google.com/search?q=%1");
}

void SettingsRepository::setCustomSearchEngineUrl(const QString& url) {
    setSetting("custom_search_url", url);
}

QString SettingsRepository::theme() const {
    return setting("theme", "dark");
}

void SettingsRepository::setTheme(const QString& themeName) {
    setSetting("theme", themeName);
}

} // namespace codebrowser
