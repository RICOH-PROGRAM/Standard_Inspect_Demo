#include <QGraphicsview>

class MyGraphicsView : public QGraphicsView
{
	Q_OBJECT
private:
	bool isMousePressed = false;
	QPointF centerAnchor;
	QPoint posAnchor;
public:
	MyGraphicsView(QWidget* parent = Q_NULLPTR);
	~MyGraphicsView();
protected:
	void wheelEvent(QWheelEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
};