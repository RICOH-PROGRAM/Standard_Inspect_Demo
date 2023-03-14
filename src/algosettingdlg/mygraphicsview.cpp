#include "mygraphicsview.h"
#include "logger.h"
#include <QWheelEvent>
#include <QScrollBar>

MyGraphicsView::MyGraphicsView(QWidget* parent) :
	m_scene(new QGraphicsScene()),
	m_imageItem(new QGraphicsPixmapItem())
{
	m_scene->addItem(m_imageItem);
	setScene(m_scene);
	//setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	//setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   //隐藏水平条
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //隐藏竖条
}

MyGraphicsView::~MyGraphicsView()
{
	m_scene->deleteLater();
	delete m_imageItem;
}

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
	// 滚轮的滚动量
	QPoint scrollAmount = event->angleDelta();
	// 正值表示滚轮远离使用者放大负值表示朝向使用者缩小
	scrollAmount.y() > 0 ? ZoomIn() : ZoomOut();

	//QPointF cursorPoint = event->pos();
	//QPointF scenePos = this->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));
	//QPointF viewPoint = this->matrix().map(scenePos);
	//// 通过滚动条控制view放大缩小后的展示scene的位置;
	//qreal viewWidth = this->viewport()->width();
	//qreal viewHeight = this->viewport()->height();
	//qreal hScale = cursorPoint.x() / viewWidth;
	//qreal vScale = cursorPoint.y() / viewHeight;

	//this->horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
	//this->verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));
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
	// 防止过小或过大
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
		//只有点击图片时才发送
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
			//获取
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
void MyGraphicsView::SetImage(const QImage& image, bool _first)
{
	m_imageItem->setPixmap(QPixmap::fromImage(image));

	QPoint newCenter(image.width() / 2, image.height() / 2);

	if (_first)
	{
		QRectF rectItem = scene()->itemsBoundingRect();

		fitInView(rectItem, Qt::KeepAspectRatio);
		////设置scene中心到图像中点
		centerOn(newCenter);
	};


	show();
}