#include "codebrowser/browser/BrowserWindow.h"
#include "codebrowser/database/Database.h"
#include "codebrowser/adblock/AdBlockEngine.h"
#include "codebrowser/adblock/WebEngineUrlRequestInterceptor.h"

#include <QApplication>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QRadialGradient>

#ifdef CODEBROWSER_HAS_WEBENGINE
#include <QWebEngineProfile>
#endif
#include <QDebug>

QIcon createApplicationIcon() {
    QPixmap iconPixmap(256, 256);
    iconPixmap.fill(Qt::transparent);
    {
        QPainter painter(&iconPixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // Outer Terracotta Brown Gradient Circle
        QRadialGradient grad(128, 128, 120);
        grad.setColorAt(0, QColor(110, 61, 55));
        grad.setColorAt(1, QColor(56, 32, 29));
        painter.setBrush(grad);
        painter.setPen(QPen(QColor(243, 180, 162), 6));
        painter.drawEllipse(12, 12, 232, 232);

        // Inner Glowing Coral Core
        painter.setBrush(QColor(245, 182, 167));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(68, 68, 120, 120);

        // Center Deep Core
        painter.setBrush(QColor(72, 45, 42));
        painter.drawEllipse(96, 96, 64, 64);
    }
    return QIcon(iconPixmap);
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    app.setApplicationName("KT Browser");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Kawerify Tech");
    app.setOrganizationDomain("kawerifytech.com");

    // Set Application & Taskbar Icon
    QIcon appIcon = createApplicationIcon();
    app.setWindowIcon(appIcon);

    // Initialize Database
    if (!codebrowser::Database::instance().initialize()) {
        qCritical() << "Failed to initialize SQLite Database!";
        return 1;
    }

    // Initialize Network AdBlock & Tracker Protection Engine
    if (!codebrowser::AdBlockEngine::instance().initialize()) {
        qWarning() << "AdBlock Engine failed to initialize completely.";
    }

#ifdef CODEBROWSER_HAS_WEBENGINE
    // Attach Request Interceptor to WebEngine Profile
    auto* interceptor = new codebrowser::WebEngineUrlRequestInterceptor(&app);
    QWebEngineProfile::defaultProfile()->setUrlRequestInterceptor(interceptor);
#endif

    // Show Native BrowserWindow
    codebrowser::BrowserWindow window;
    window.setWindowTitle("KT Browser by Kawerify Tech");
    window.setWindowIcon(appIcon);
    window.show();

    return app.exec();
}
