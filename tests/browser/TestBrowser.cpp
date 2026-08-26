#include "ktbrowser/browser/NavigationController.h"
#include <QCoreApplication>
#include <iostream>
#include <cassert>

using namespace ktbrowser;

void testNavigationController() {
    // Test URL check
    assert(NavigationController::isUrl("https://example.com"));
    assert(NavigationController::isUrl("http://localhost:8080"));
    assert(NavigationController::isUrl("google.com"));
    assert(!NavigationController::isUrl("what is quantum computing"));
    
    // Test parseInput
    QUrl urlDirect = NavigationController::parseInput("https://kawerifytech.com");
    assert(urlDirect.toString() == "https://kawerifytech.com");
    
    QUrl urlSearch = NavigationController::parseInput("c++ qt6 webengine", "Google");
    assert(urlSearch.toString().contains("google.com/search"));
    assert(urlSearch.toString().contains("c%2B%2B") || urlSearch.toString().contains("qt6"));
    
    std::cout << "[PASS] NavigationController parsing test passed.\n";
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    testNavigationController();
    std::cout << "All Browser Core Unit Tests PASSED Successfully!\n";
    return 0;
}
