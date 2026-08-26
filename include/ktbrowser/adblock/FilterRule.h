#pragma once

#include <QString>
#include <QRegularExpression>
#include <QUrl>

namespace ktbrowser {

enum class RuleType {
    BlockDomain,
    BlockPattern,
    AllowDomain,
    AllowPattern,
    ElementHiding // Future expansion
};

enum class ResourceType {
    Any,
    Script,
    Image,
    StyleSheet,
    SubFrame,
    XmlHttpRequest,
    Media,
    Font,
    Other
};

class FilterRule {
public:
    FilterRule(RuleType type, const QString& pattern, bool isRegex = false);

    bool matches(const QUrl& requestUrl, const QUrl& firstPartyUrl = QUrl()) const;

    RuleType type() const { return m_type; }
    QString rawPattern() const { return m_rawPattern; }
    bool isException() const { return m_type == RuleType::AllowDomain || m_type == RuleType::AllowPattern; }

private:
    RuleType m_type;
    QString m_rawPattern;
    bool m_isRegex{false};
    QRegularExpression m_regex;
    QString m_domainMatch;
};

} // namespace ktbrowser
