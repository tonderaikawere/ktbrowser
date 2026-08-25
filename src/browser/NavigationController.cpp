#include "codebrowser/browser/NavigationController.h"
#include <QUrlQuery>
#include <QRegularExpression>

namespace codebrowser {

QUrl NavigationController::parseInput(const QString& input, const QString& searchEngine, const QString& customSearchUrl) {
    QString trimmed = input.trimmed();
    if (trimmed.isEmpty()) return QUrl("codebrowser://newtab");

    // Explicit codebrowser:// protocol links
    if (trimmed.startsWith("codebrowser://")) {
        if (trimmed == "codebrowser://newtab" || trimmed == "codebrowser://home") {
            return QUrl("codebrowser://newtab");
        }
    }

    // If string contains no dot, contains spaces, or does not match domain rules, treat as SEARCH QUERY
    if (!trimmed.contains(".") && !trimmed.contains(":") && !trimmed.startsWith("localhost")) {
        return buildSearchUrl(trimmed, searchEngine, customSearchUrl);
    }

    // Match IP address or standard URL domain formats
    static QRegularExpression urlPattern(
        R"(^(https?:\/\/)?([a-zA-Z0-9\-]+\.)+[a-zA-Z]{2,}(:\d+)?(\/.*)?$)"
    );

    static QRegularExpression ipPattern(
        R"(^(https?:\/\/)?\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}(:\d+)?(\/.*)?$)"
    );

    static QRegularExpression localhostPattern(
        R"(^(https?:\/\/)?localhost(:\d+)?(\/.*)?$)"
    );

    if (urlPattern.match(trimmed).hasMatch() || ipPattern.match(trimmed).hasMatch() || localhostPattern.match(trimmed).hasMatch()) {
        if (!trimmed.startsWith("http://") && !trimmed.startsWith("https://")) {
            return QUrl("https://" + trimmed);
        }
        return QUrl(trimmed);
    }

    // Default search query fallback
    return buildSearchUrl(trimmed, searchEngine, customSearchUrl);
}

QUrl NavigationController::buildSearchUrl(const QString& query, const QString& engine, const QString& customSearchUrl) {
    QString encodedQuery = QUrl::toPercentEncoding(query);
    QString engineLower = engine.toLower();

    if (engineLower == "bing") {
        return QUrl("https://www.bing.com/search?q=" + encodedQuery);
    } else if (engineLower == "duckduckgo") {
        return QUrl("https://duckduckgo.com/?q=" + encodedQuery);
    } else if (engineLower == "brave") {
        return QUrl("https://search.brave.com/search?q=" + encodedQuery);
    } else if (engineLower == "yahoo") {
        return QUrl("https://search.yahoo.com/search?q=" + encodedQuery);
    } else if (engineLower == "custom" && !customSearchUrl.isEmpty()) {
        QString target = customSearchUrl;
        if (target.contains("%1")) {
            target.replace("%1", encodedQuery);
        } else {
            target += encodedQuery;
        }
        return QUrl(target);
    }

    // Default to Google
    return QUrl("https://www.google.com/search?q=" + encodedQuery);
}

} // namespace codebrowser
