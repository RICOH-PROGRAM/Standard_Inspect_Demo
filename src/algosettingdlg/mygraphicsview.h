#include <QGraphicsview>

class MyGraphicsView : public QGraphicsView
{
	Q_OBJECT
private:
	bool m_isTranslate = false;
	double m_qrScaledNum = 1;
	QPointF centerAnchor;
	QPoint m_lastMousePos;

	void Translate(QPointF delta);
	void ZoomIn();
	void ZoomOut();
	void Zoom(float scaleFactor);
public:
	MyGraphicsView(QWidget* parent = Q_NULLPTR);
	~MyGraphicsView();
protected:
	void wheelEvent(QWheelEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
};