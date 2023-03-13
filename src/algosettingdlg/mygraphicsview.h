#include <QGraphicsview>
#include <QGraphicsPixmapItem>

class MyGraphicsView : public QGraphicsView
{
	Q_OBJECT
private:
	bool m_isTranslate = false;
	double m_qrScaledNum = 1;
	QPointF centerAnchor;
	QPoint m_lastMousePos;
	QGraphicsScene* m_scene;
	QGraphicsPixmapItem* m_imageItem;

	void Translate(QPointF delta);
	void ZoomIn();
	void ZoomOut();
	void Zoom(float scaleFactor);
public:
	MyGraphicsView(QWidget* parent = Q_NULLPTR);
	~MyGraphicsView();
	void SetImage(const QImage& image, bool _first = false);
protected:
	void wheelEvent(QWheelEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
};