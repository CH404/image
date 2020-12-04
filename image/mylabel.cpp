#include "mylabel.h"
#include <QPainter>



mylabel::mylabel()
{
    qDebug() << "mylabel";
}

mylabel::~mylabel()
{
     qDebug() << "~mylabel";
}

void mylabel::mousePress(QPoint startPoint, int index)
{
    _startPoint =startPoint;
    _endPoint = startPoint;
    _figureIndex = index;
    _isPaint = true;
    update();
}

void mylabel::mouseMove(QPoint endPoint)
{
    if(_isPaint)
    {
        _endPoint = endPoint;
    }
    update();
}

void mylabel::mouseRelease(QPoint endPoint)
{
    if(_isPaint)
    {
        _isPaint = false;
        _endPoint = endPoint;
    }
    update();
}
#if 1
void mylabel::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent";
    QLabel::paintEvent(event);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    if(_figureIndex == CRICLE)
    {
        saveFigurePoint(_startPoint,_endPoint);
        QVector<QPoint>::iterator it = position.begin();
        for (;it!=position.end();it++) {
            painter.drawPoint(*it);
        }
    }
    else if(_figureIndex == RECT)
    {

       int w = _endPoint.x()-_startPoint.x();
       int h = _endPoint.y()-_startPoint.y();
       int startX=_startPoint.x(),startY=_startPoint.y();
       if(startX+w > _imageWidth || startX+w<0|| startY+h >_imageHeight || startY+h < 0)
       {
           painter.drawRect(QRect(position.first(),position.last()));
           return;
       }
       saveFigurePoint(_startPoint,_endPoint);
       painter.drawRect(_startPoint.x(),_startPoint.y(),w,h);
    }
}
#endif
void mylabel::setImage(QImage &image)
{
    qDebug() << "setImage"<< image.size();
    _imageWidth = image.width();
    _imageHeight = image.height();
    this->setPixmap(QPixmap::fromImage(image));

}

void mylabel::getCirclePointPos()
{
    QVector<QPoint>::iterator it;
     it = position.begin()+1;
    for(;it<position.end();it++)
    {
       QVector<QPoint>::iterator pre=it-1;
       int current = (*it).y();
       QPoint tmp = *it;
       while(pre>=position.begin() && current < pre->y())
       {
           *(pre+1) = *pre;
           pre--;
       }
       *(pre+1) = tmp;

       QVector<QPoint>::iterator currentIt = pre+1;
       QVector<QPoint>::iterator prex = currentIt-1;
       while(prex>=position.begin() && (tmp.y() == (*prex).y()) &&
             tmp.x() < prex->x())
       {
            *(prex+1) = *prex;
            prex--;
       }
       *(prex+1) = tmp;


    }
}

void mylabel::saveFigurePoint(QPoint startPoint, QPoint endPoint)
{
    qDebug() << "startpoint" << startPoint;
    qDebug() << "endpoint" << endPoint;

    if(_figureIndex ==CRICLE)
    {
    int tmpx = startPoint.x();
    int tmpy = startPoint.y();
    int tmpx1 = endPoint.x();
    int tmpy1 = endPoint.y();

    int r = sqrt(pow(tmpx1-tmpx,2)+pow(tmpy1-tmpy,2));
    qDebug() << "r" << r << "x" << tmpx;
    qDebug() << "r+tmpx" << r+tmpx << "tmpx-r" << tmpx-r;
    if(r+tmpx > _imageWidth || tmpx-r < 0 || r+tmpy > _imageHeight || tmpy-r < 0){
    return;
    }
      position.clear();
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;
    position.append(QPoint(tmpx,tmpy+r));
    position.append(QPoint(tmpx,tmpy-r));
    position.append(QPoint(tmpx+r,tmpy));
    position.append(QPoint(tmpx-r,tmpy));

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

         position.append(QPoint(tmpx+x,tmpy+y));
         position.append(QPoint(tmpx-x,tmpy+y));
         position.append(QPoint(tmpx+x,tmpy-y));
         position.append(QPoint(tmpx-x,tmpy-y));

         position.append(QPoint(tmpx+y,tmpy+x));
         position.append(QPoint(tmpx-y,tmpy+x));
         position.append(QPoint(tmpx+y,tmpy-x));
         position.append(QPoint(tmpx-y,tmpy-x));
    }
    }
    else if(_figureIndex == RECT)
    {

        int endX=endPoint.x(),endY= endPoint.y();
        int startX=startPoint.x(),startY=startPoint.y();
        int h = endY < startY ? startY-endY:endY-startY;
        position.clear();
        for(;h>=0;h--){
            position.append(QPoint(startX,startY+h));
            position.append(QPoint(endX,startY+h));
        }
    }
}
