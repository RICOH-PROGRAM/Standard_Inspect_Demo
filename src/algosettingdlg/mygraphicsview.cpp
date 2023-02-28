#include "mygraphicsview.h"
#include "logger.h"
#include <QWheelEvent>

MyGraphicsView::MyGraphicsView(QWidget* parent) :
	m_scene(new QGraphicsScene()),
	m_imageItem(new QGraphicsPixmapItem())
{
	m_scene->addItem(m_imageItem);
	setScene(m_scene);
	//setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	//setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   //����ˮƽ��
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //��������
}

MyGraphicsView::~MyGraphicsView()
{
	m_scene->deleteLater();
	delete m_imageItem;
}

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
	// ���ֵĹ�����
	QPoint scrollAmount = event->angleDelta();
	// ��ֵ��ʾ����Զ��ʹ���߷Ŵ�ֵ��ʾ����ʹ������С
	scrollAmount.y() > 0 ? ZoomIn() : ZoomOut();

}

void MyGraphicsView::ZoomIn()
{
	Zoom(1.1);
}

void MyGraphicsView::ZoomOut()
{
	Zoom(0.9);
}

void MyGraphicsView::Zoom(float scaleFactor)
{
	// ��ֹ��С�����
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
}


void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isTranslate = true;
		m_lastMousePos = event->pos();
	}
	else if (event->button() == Qt::RightButton)
	{
		QPointF point = mapToScene(event->pos());
		//ֻ�е��ͼƬʱ�ŷ���
		if (scene()->itemAt(point, transform()) != NULL)
		{
			//emit m_imageBox->ImageClick(point.x(), point.y());
		}
	}

	QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	{
		if (m_isTranslate)
		{
			//��ȡ
			QPointF mouseDelta = event->pos() - m_lastMousePos;
			Translate(mouseDelta);
		}
		m_lastMousePos = event->pos();
	}

	QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
		m_isTranslate = false;



	QGraphicsView::mouseReleaseEvent(event);
}


void MyGraphicsView::Translate(QPointF delta)
{
	int w = viewport()->rect().width();
	int h = viewport()->rect().height();
	QPoint newCenter(w / 2. - delta.x() + 0.5, h / 2. - delta.y() + 0.5);
	centerOn(mapToScene(newCenter));
}
void MyGraphicsView::SetImage(const QImage& image)
{
	m_imageItem->setPixmap(QPixmap::fromImage(image));

	//QPoint newCenter(image.width() / 2, image.height() / 2);

	////����scene���ĵ�ͼ���е�
	//centerOn(newCenter);

	show();
}