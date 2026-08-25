#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QRadialGradient>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QPixmap pixmap(256, 256);
    pixmap.fill(Qt::transparent);
    {
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        QRadialGradient grad(128, 128, 120);
        grad.setColorAt(0, QColor(74, 52, 97));
        grad.setColorAt(1, QColor(35, 26, 46));
        painter.setBrush(grad);
        painter.setPen(QPen(QColor(208, 188, 255), 6));
        painter.drawEllipse(12, 12, 232, 232);
        painter.setBrush(QColor(138, 180, 248));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(68, 68, 120, 120);
        painter.setBrush(QColor(35, 26, 46));
        painter.drawEllipse(96, 96, 64, 64);
    }
    pixmap.save("C:/Users/Tonde/AppData/Local/Programs/CodeBrowser/codebrowser.ico");
    pixmap.save("C:/Users/Tonde/AppData/Local/Programs/CodeBrowser/codebrowser.png");
    return 0;
}
