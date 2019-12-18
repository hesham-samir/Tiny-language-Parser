#include "view.h"

View::View(QWidget *parent):
  QGraphicsView(parent)
{
  setDragMode(QGraphicsView::ScrollHandDrag);

  QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap("D:/collage.png"));
  pixmapItem->setTransformationMode(Qt::SmoothTransformation);

  QGraphicsScene *scene = new QGraphicsScene();
  scene->addItem(pixmapItem);
  setScene(scene);
}

void View::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        scale(1.25, 1.25);
    else
        scale(0.8, 0.8);
}

void View::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        rotate(1);
    else if(event->key() == Qt::Key_Right)
        rotate(-1);
}
