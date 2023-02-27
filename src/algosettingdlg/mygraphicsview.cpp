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
    // ��¼��갴��ʱ�����ĵ�����
    centerAnchor = mapToScene(event->pos()) - event->pos() + QPointF(width() / 2, height() / 2);
    // ��¼��ǰ�����view�е�λ�ã�������mouseMove�¼��м���ƫ��
    // �˴�����view����ת����scene�����ԭ�����Ż����ܣ���move�Ĺ����л��������
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