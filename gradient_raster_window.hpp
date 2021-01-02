#ifndef RASTERWINDOW_HPP
#define RASTERWINDOW_HPP

#include "game.hpp"

#include <QtGui>

constexpr qreal BLOCK_SIZE = 20.0;
constexpr int FLIELD_WIDTH = BLOCK_SIZE*F_WIDTH;
constexpr int FIELD_HEIGHT = BLOCK_SIZE*F_HEIGHT;
constexpr char BLOCK_COLOR[] = "black";

class GradientRasterWindow : public QWindow
{
    Q_OBJECT

    QBackingStore* backingStore_; // used to manage the window's back buffer for QPainter based graphics
    QGradient gradient_;
    QString text_ = QStringLiteral("Drücke eine Taste.");
    Game* game_;

public:
    explicit GradientRasterWindow(QGradient gradient, Game* game, QWindow* parent = 0);

    virtual void render(QPainter* painter);
public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;
};

#endif // RASTERWINDOW_HPP
