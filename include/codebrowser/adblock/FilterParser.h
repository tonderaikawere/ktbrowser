#pragma once

#include "codebrowser/adblock/FilterRule.h"
#include <QString>
#include <QList>
#include <memory>

namespace codebrowser {

class FilterParser {
public:
    static QList<std::shared_ptr<FilterRule>> parseLines(const QStringList& lines);
    static std::shared_ptr<FilterRule> parseLine(const QString& line);
};

} // namespace codebrowser
