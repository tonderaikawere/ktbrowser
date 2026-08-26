#include "ktbrowser/ui/AddressBar.h"
#include "ktbrowser/ui/BrowserToolbar.h"
#include "ktbrowser/ui/TabBar.h"
#include "ktbrowser/ui/NewTabPage.h"
#include <QApplication>
#include <iostream>
#include <cassert>

using namespace ktbrowser;

void testAddressBar() {
    AddressBar addr;
    addr.setUrl(QUrl("https://example.com"));
    assert(addr.text() == "https://example.com");

    addr.setUrl(QUrl("ktbrowser://newtab"));
    assert(addr.text().isEmpty());

    std::cout << "[PASS] AddressBar widget test passed.\n";
}

void testBrowserToolbar() {
    BrowserToolbar toolbar;
    assert(toolbar.addressBar() != nullptr);

    toolbar.setCanGoBack(true);
    toolbar.setCanGoForward(false);
    toolbar.setIsLoading(true);

    std::cout << "[PASS] BrowserToolbar widget test passed.\n";
}

void testTabBar() {
    TabBar tabWidget;
    int idx1 = tabWidget.addTab("New Tab");
    int idx2 = tabWidget.addTab("Google Search");

    assert(tabWidget.count() == 2);
    assert(tabWidget.currentIndex() == 0 || tabWidget.currentIndex() == 1);

    tabWidget.removeTab(idx1);
    assert(tabWidget.count() == 1);

    std::cout << "[PASS] TabBar widget test passed.\n";
}

void testNewTabPage() {
    NewTabPage ntp;
    ntp.refreshStats();

    std::cout << "[PASS] NewTabPage widget test passed.\n";
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    testAddressBar();
    testBrowserToolbar();
    testTabBar();
    testNewTabPage();

    std::cout << "All UI Widget Unit Tests PASSED Successfully!\n";
    return 0;
}
