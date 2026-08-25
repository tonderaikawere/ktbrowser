#pragma once

#include <QString>
#include <QUrl>

namespace codebrowser {

class NavigationController {
public:
    static QUrl parseInput(const QString& input, const QString& defaultEngine = "DuckDuckGo", const QString& customEngineUrl = QString());
    static bool isUrl(const QString& input);
    static QString buildSearchUrl(const QString& query, const QString& defaultEngine, const QString& customEngineUrl);
};

} // namespace codebrowser
