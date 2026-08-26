#include "ktbrowser/database/Database.h"
#include "ktbrowser/database/HistoryRepository.h"
#include "ktbrowser/database/BookmarkRepository.h"
#include "ktbrowser/database/SettingsRepository.h"
#include <QCoreApplication>
#include <iostream>
#include <cassert>

using namespace ktbrowser;

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // Test Database init
    bool ok = Database::instance().initialize(":memory:");
    assert(ok);

    // Test History
    HistoryRepository historyRepo;
    historyRepo.addOrUpdateHistory("https://example.com", "Example Domain");
    auto recent = historyRepo.getRecentHistory(10);
    assert(recent.size() == 1);
    assert(recent[0].url == "https://example.com");

    // Test Bookmarks
    BookmarkRepository bookmarkRepo;
    int64_t bId = bookmarkRepo.addBookmark("Example", "https://example.com");
    assert(bId > 0);
    assert(bookmarkRepo.isBookmarked("https://example.com"));

    // Test Settings
    SettingsRepository settingsRepo;
    settingsRepo.setDefaultSearchEngine("Brave Search");
    assert(settingsRepo.defaultSearchEngine() == "Brave Search");

    std::cout << "All Database & Repository Unit Tests PASSED Successfully!\n";
    return 0;
}
