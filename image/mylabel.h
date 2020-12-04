#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>
#include <QVector>
#include <QImage>
#include <QDebug>

#define CRICLE 0
#define RECT 1

class mylabel : public QLabel
{
    Q_OBJECT
    int _figureIndex;
    QPoint _startPoint;
    QPoint _endPoint;
    bool _isPaint;

    int _imageWidth;
    int _imageHeight;

public:
     QVector<QPoint> position;
    mylabel();
    ~mylabel();
    void mousePress(QPoint startPoint,int index);
    void mouseMove(QPoint endPoint);
    void mouseRelease(QPoint endPoint);
    virtual void paintEvent(QPaintEvent *event) override;
    void getCirclePos();
    void setImage(QImage &image);
    void getCirclePointPos(void);
private:
     void saveFigurePoint(QPoint startPoint, QPoint endPoint);
public slots:





};


#endif // MYLABEL_H
