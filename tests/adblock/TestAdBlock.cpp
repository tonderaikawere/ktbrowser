#include "codebrowser/adblock/AdBlockEngine.h"
#include "codebrowser/adblock/FilterParser.h"
#include "codebrowser/adblock/FilterRule.h"
#include <iostream>
#include <cassert>

using namespace codebrowser;

void testFilterRuleMatching() {
    FilterRule rule(RuleType::BlockDomain, "||doubleclick.net^");
    assert(rule.matches(QUrl("https://ad.doubleclick.net/ad.js")));
    assert(rule.matches(QUrl("https://doubleclick.net/track")));
    assert(!rule.matches(QUrl("https://google.com/search")));

    std::cout << "[PASS] FilterRule matching test passed.\n";
}

void testAdBlockEngine() {
    AdBlockEngine& engine = AdBlockEngine::instance();
    engine.initialize();

    QString reason;
    bool blocked = engine.shouldBlockRequest(QUrl("https://analytics.google.com/collect"), QUrl("https://example.com"), &reason);
    assert(blocked);

    bool allowed = engine.shouldBlockRequest(QUrl("https://wikipedia.org/wiki/Main_Page"), QUrl("https://wikipedia.org"), &reason);
    assert(!allowed);

    std::cout << "[PASS] AdBlockEngine core test passed.\n";
}

int main() {
    testFilterRuleMatching();
    testAdBlockEngine();
    std::cout << "All AdBlock Unit Tests PASSED Successfully!\n";
    return 0;
}
