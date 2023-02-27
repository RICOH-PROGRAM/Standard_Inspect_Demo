#include "mygraphicsview.h"
#include <QWheelEvent>

MyGraphicsView::MyGraphicsView(QWidget* parent)
{
}

MyGraphicsView::~MyGraphicsView()
{
}

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
    int wheelValue = event->angleDelta().y();
    double ratio = (double)wheelValue / (double)1200 + 1;
    scale(ratio, ratio);
}
void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
    if (this->scene() == nullptr)
    {
        return;
    }
    // 记录鼠标按下时的中心点坐标
    centerAnchor = mapToScene(event->pos()) - event->pos() + QPointF(width() / 2, height() / 2);
    // 记录当前鼠标在view中的位置，用来在mouseMove事件中计算偏移
    // 此处不将view坐标转换成scene坐标的原因是优化性能，在move的过程中会产生抖动
    posAnchor = event->pos();
    isMousePressed = true;
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
    QPointF offsetPos = event->pos() - posAnchor;
    if (isMousePressed) {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        centerOn(centerAnchor - offsetPos);
    }
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    isMousePressed = false;
}