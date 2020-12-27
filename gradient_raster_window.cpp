#include "gradient_raster_window.hpp"
#include "playingfield.hpp"

GradientRasterWindow::GradientRasterWindow(QGradient gradient, QWindow *parent)
    : QWindow{parent},
      backingStore_{new QBackingStore{this}},
      gradient_{gradient} {
    setGeometry(100, 100, 300, 200);
}

void GradientRasterWindow::exposeEvent(QExposeEvent *) {
    if (isExposed()) renderNow();
}

void GradientRasterWindow::resizeEvent(QResizeEvent *resizeEvent) {
    backingStore_->resize(resizeEvent->size());
}

/**
 * @brief RasterWindow::renderNow
 * sets up what is needed for a QWindow to render its content using QPainter
 */
void GradientRasterWindow::renderNow() {
    if (!isExposed()) return;

    QRect rect(0, 0, width(), height());
    backingStore_->beginPaint(rect);

    QPaintDevice* device = backingStore_->paintDevice();
    QPainter painter{device};

    painter.fillRect(0, 0, width(), height(), gradient_);
    render(&painter);
    painter.end();

    backingStore_->endPaint();
    backingStore_->flush(rect); // flushes onto the screen
}

void GradientRasterWindow::updateText(const QString& text) {
    text_ = text;
    renderNow();
}

/**
 * @fn GradientRasterWindow::render(QPainter *painter)
 * @brief draw text onto rectanglea
 * @param painter
 */
void GradientRasterWindow::render(QPainter *painter) {
    painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, text_);
}

void GradientRasterWindow::renderGame(const Game& game) {
    if (!isExposed()) return;

    QRect rect(0, 0, width(), height());
    backingStore_->beginPaint(rect);

    QPaintDevice* device = backingStore_->paintDevice();
    QPainter painter{device};

    painter.fillRect(0, 0, width(), height(), gradient_);

    /****************************  original start  **********************************/

    const Field field = game.playingField().field();
    constexpr qreal blockSize = 20.0;
    const QColor occupied = QColor{"red"};


    for(int rows{}; rows < F_HEIGHT; ++rows) {
        for(int column{}; column < F_WIDTH; ++column) {
            QRectF rectangle{0+blockSize*column, 0+blockSize*rows, blockSize, blockSize};
            if(field[rows][column]) {
                painter.fillRect(rectangle, occupied);
            }
            painter.drawRect(rectangle);
        }
    }

    /****************************   original end   **********************************/

    painter.end();

    backingStore_->endPaint();
    backingStore_->flush(rect); // flushes onto the screen
    requestUpdate();
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

