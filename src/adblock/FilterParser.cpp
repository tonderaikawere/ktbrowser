#include "ktbrowser/adblock/FilterParser.h"
#include <QDebug>

namespace ktbrowser {

QList<std::shared_ptr<FilterRule>> FilterParser::parseLines(const QStringList& lines) {
    QList<std::shared_ptr<FilterRule>> rules;
    rules.reserve(lines.size());

    for (const auto& line : lines) {
        auto rule = parseLine(line);
        if (rule) {
            rules.append(rule);
        }
    }
    return rules;
}

std::shared_ptr<FilterRule> FilterParser::parseLine(const QString& rawLine) {
    QString line = rawLine.trimmed();

    // Skip empty lines, comments (!), and HTML element hiding rules (##)
    if (line.isEmpty() || line.startsWith("!") || line.startsWith("[Adblock") || line.contains("##")) {
        return nullptr;
    }

    bool isException = line.startsWith("@@");
    if (isException) {
        line = line.mid(2);
    }

    // Strip options after $ if present (e.g. $script,third-party)
    int dollarIdx = line.indexOf('$');
    if (dollarIdx != -1) {
        line = line.left(dollarIdx);
    }

    if (line.isEmpty()) return nullptr;

    bool isRegex = line.startsWith('/') && line.endsWith('/') && line.length() > 2;
    if (isRegex) {
        line = line.mid(1, line.length() - 2);
    }

    RuleType type = isException ? RuleType::AllowDomain : RuleType::BlockDomain;
    return std::make_shared<FilterRule>(type, line, isRegex);
}

} // namespace ktbrowser
