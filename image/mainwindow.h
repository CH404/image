#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QMouseEvent>
#include <QStatusBar>
#include <QGridLayout>

#include "mylabel.h"
#include "bmp.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QAction *openAction;
    QAction *saveAction;
    QAction *helpAction;
    QToolBar *toolBar;
    QLabel *figureLabel;
    QComboBox *figureBox;       //剪切图形选择box
    QLabel * spinBoxlabel;

    QSpinBox *SpinBox1;
    QSpinBox *SpinBox2;   //剪切图形大小选择box

    QLabel *spinBoxlable2;
    QSpinBox *spinBox3;
    QSpinBox *spinBox4;

    QLabel *formatLabel;
    QComboBox *formatBox;       //选择输出格式box
    QPushButton *okButton;

    QLabel *mousePoslabel;       //鼠标位置显示
    mylabel *imageLabelS;        //图片显示label
    QGridLayout *gridLayout0;
    QGridLayout *gridLayout1;
    QSpacerItem *horizontalSpacer0;
    QSpacerItem *horizontalSpacer1;
    QSpacerItem *verticalSpacer0;
    QSpacerItem *verticalSpacer1;

    QGridLayout *spinBoxLayout;
   // QHBoxLayout *spinBoxLayout;     //剪切图形大小选择box布局
    QHBoxLayout *barLayout;         //工具条布局
    QVBoxLayout *configureLayout;   //左侧设置布局
    QHBoxLayout *belowLayout;
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;
    QWidget *configWidget;


    QString openfilePath;
  //  Ui::MainWindow *ui;
    Bmp *imageDecode;

    uint32_t imageWidth =0;         //图像宽单位像素
    uint32_t imageHight = 0;
    uint32_t biCompression;
    uint16_t imagebitCount = 0;     //图片深度
    uint32_t palette_size =0;       //调色版大小 16位图以下的图片才有
    uint32_t imageSize = 0;         //真个图片数据大小

    uint8_t *pimageDate = nullptr;      //接收图片数据buff
    uint8_t *pimagePalette =nullptr;       //调色板buff

private:
    QLabel *statusLabel;
    QLabel *MousePosLabel;
    QStatusBar *statusBar;
    QVector<QPoint> cutImagePosition;

private:
    void createToolBar(void);
    void createConfigBar(void);
    void createImageBar(void);
    void createStatusBar(void);
    void createPage(void);
    void openFile(void);
    void displayImage(void);
    void saveFile(void);
    void changedSpinBox(int index);

    void drawCutFigure(void);
    template<typename T>
    void widgetInit(T *&widgettmp,QWidget *parent=nullptr,QString text="",int width=0,int height=0,int x=0,int y=0);
    void getImageData();
    void saveFigureImage(QString file);
    void getFigureInportantPoint(void);


    void testShowinfo(void);
    void testVector(void);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void openFileSlot();
    void saveFileSlot();
    void buttonPress(void);
    void changedfigure(int);
};


#endif // MAINWINDOW_H
