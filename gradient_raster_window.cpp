#include "gradient_raster_window.hpp"
#include "playingfield.hpp"

GradientRasterWindow::GradientRasterWindow(QGradient gradient, Game* game, QWindow *parent)
    : QWindow{parent},
      backingStore_{new QBackingStore{this}},
      gradient_{gradient},
      game_{game} {
    setGeometry(100, 100, FLIELD_WIDTH, FIELD_HEIGHT);
}

void GradientRasterWindow::exposeEvent(QExposeEvent *) {
    if (isExposed()) renderNow();
}

void GradientRasterWindow::resizeEvent(QResizeEvent *resizeEvent) {
    backingStore_->resize(resizeEvent->size());
}

void GradientRasterWindow::renderNow() {
    if (!isExposed()) return;

    QRect rect(0, 0, width(), height());
    backingStore_->beginPaint(rect);
    QPaintDevice* device = backingStore_->paintDevice();
    QPainter painter{device};

    painter.fillRect(0, 0, width(), height(), gradient_);
    /****************************  original start  **********************************/
    render(&painter);
    /****************************   original end   **********************************/

    painter.end();
    backingStore_->endPaint();
    backingStore_->flush(rect); // flushes onto the screen
}

void GradientRasterWindow::render(QPainter* painter) {
    const Field field = game_->playingField().field();
    const QColor occupied{BLOCK_COLOR};
    const int centerLeftBorder = (width() - FLIELD_WIDTH)/2;
    const int centerUpperBorder = (height() - FIELD_HEIGHT)/2;

    for(int rows{}; rows < F_HEIGHT; ++rows) {
        for(int column{}; column < F_WIDTH; ++column) {
            QRectF rectangle{centerLeftBorder+BLOCK_SIZE*column, centerUpperBorder+BLOCK_SIZE*rows, BLOCK_SIZE, BLOCK_SIZE};
            if(field[rows][column]) {
                painter->fillRect(rectangle, occupied);
            }
            painter->drawRect(rectangle);
        }
    }
}

void GradientRasterWindow::renderLater() {
    requestUpdate();
}

bool GradientRasterWindow::event(QEvent *event) {
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

