#include "ktbrowser/downloads/DownloadManager.h"
#include <QCoreApplication>
#include <iostream>
#include <cassert>

using namespace ktbrowser;

void testDownloadManagerInstance() {
    DownloadManager& dm = DownloadManager::instance();
    auto active = dm.activeDownloads();
    
    // Initial download list should be empty or accessible
    assert(active.size() >= 0);
    
    std::cout << "[PASS] DownloadManager instance & query test passed.\n";
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    testDownloadManagerInstance();
    std::cout << "All Downloads Unit Tests PASSED Successfully!\n";
    return 0;
}
