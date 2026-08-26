#include "ktbrowser/database/Database.h"
#include "ktbrowser/database/SettingsRepository.h"
#include <QCoreApplication>
#include <iostream>
#include <cassert>

using namespace ktbrowser;

void testSettingsRepository() {
    bool ok = Database::instance().initialize(":memory:");
    assert(ok);
    
    SettingsRepository repo;
    
    // Default search engine
    QString defaultEngine = repo.defaultSearchEngine();
    assert(!defaultEngine.isEmpty());
    
    // Custom search engine modification
    repo.setDefaultSearchEngine("DuckDuckGo");
    assert(repo.defaultSearchEngine() == "DuckDuckGo");
    
    // Theme setting
    repo.setTheme("dark");
    assert(repo.theme() == "dark");
    
    std::cout << "[PASS] SettingsRepository test passed.\n";
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    testSettingsRepository();
    std::cout << "All Settings Unit Tests PASSED Successfully!\n";
    return 0;
}
