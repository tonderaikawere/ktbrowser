#include "ktbrowser/adblock/FilterRule.h"
#include <QDebug>

namespace ktbrowser {

FilterRule::FilterRule(RuleType type, const QString& pattern, bool isRegex)
    : m_type(type), m_rawPattern(pattern), m_isRegex(isRegex) {
    
    if (m_isRegex) {
        m_regex = QRegularExpression(pattern, QRegularExpression::CaseInsensitiveOption);
    } else {
        // Handle EasyList domain match style: ||example.com^
        QString clean = pattern;
        if (clean.startsWith("||")) {
            clean = clean.mid(2);
            int endIdx = clean.indexOf('^');
            if (endIdx != -1) {
                clean = clean.left(endIdx);
            }
            int slashIdx = clean.indexOf('/');
            if (slashIdx != -1) {
                clean = clean.left(slashIdx);
            }
            m_domainMatch = clean.toLower();
        } else if (clean.startsWith("|")) {
            clean = clean.mid(1);
            if (clean.endsWith("|")) {
                clean.chop(1);
            }
            m_rawPattern = clean.toLower();
        } else {
            m_rawPattern = clean.toLower();
        }
    }
}

bool FilterRule::matches(const QUrl& requestUrl, const QUrl& firstPartyUrl) const {
    Q_UNUSED(firstPartyUrl);
    QString host = requestUrl.host().toLower();
    QString fullUrl = requestUrl.toString().toLower();

    if (!m_domainMatch.isEmpty()) {
        if (host == m_domainMatch || host.endsWith("." + m_domainMatch)) {
            return true;
        }
        return false;
    }

    if (m_isRegex && m_regex.isValid()) {
        return m_regex.match(fullUrl).hasMatch();
    }

    if (!m_rawPattern.isEmpty()) {
        return fullUrl.contains(m_rawPattern);
    }

    return false;
}

} // namespace ktbrowser
