#ifndef RASTERWINDOW_HPP
#define RASTERWINDOW_HPP

#include "game.hpp"

#include <QtGui>

class GradientRasterWindow : public QWindow
{
    Q_OBJECT

    QBackingStore* backingStore_; // used to manage the window's back buffer for QPainter based graphics
    QGradient gradient_;
    QString text_ = QStringLiteral("Drücke eine Taste.");

public:
    explicit GradientRasterWindow(QGradient gradient, QWindow* parent = 0);

    virtual void render(QPainter* painter);
    void renderGame(const Game& game);
public slots:
    void renderLater();
    void renderNow();
    void updateText(const QString& text);

protected:
    bool event(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;
};

#endif // RASTERWINDOW_HPP
