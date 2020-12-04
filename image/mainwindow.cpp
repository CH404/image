#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QRegExp>
#include <QStatusBar>
#include <QVector>
#include "bmp.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 //   ui(new Ui::MainWindow)
{
  //  ui->setupUi(this);
#if 0
    setWindowTitle(QStringLiteral("鼠标事件"));
    setWindowIcon(QIcon("icon.png"));

    //显示鼠标当前实时位置
    statusLabel = new QLabel;
    statusLabel->setText(QStringLiteral("当前位置:"));
    statusLabel->setFixedWidth(100);

    //显示鼠标按下或释放时的实时位置
    MousePosLabel = new QLabel;
    MousePosLabel->setText(QStringLiteral(""));
    MousePosLabel->setFixedWidth(100);

    //添加控件
    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->addPermanentWidget(MousePosLabel);

    //开启鼠标追踪
    this->setMouseTracking(true);

    resize(600,400);
#endif
    createPage();
    resize(600,400);
    //鼠标移动的捕捉一层套一层
    this->setMouseTracking(true);     //开启整个窗口
    mainWidget->setMouseTracking(true); //开启 mainWidger,其他控件都在这里面
}

MainWindow::~MainWindow()
{
   // delete ui;
}

void MainWindow::createToolBar()
{
   barLayout = new QHBoxLayout;
   openAction = new QAction("&Open");
   saveAction = new QAction("&Save");
   helpAction = new QAction("&Help");
   toolBar =new QToolBar(this);
   mainWidget = new QWidget(this);
   //绘制图标
   openAction->setIcon(QIcon(":/resource/openFile.jpeg"));
   saveAction->setIcon(QIcon(":/resource/saveFile.jpeg"));
   helpAction->setIcon(QIcon(":/resource/help.jpg"));
   //添加分割线

   toolBar->addSeparator();
   //添加 Action
   toolBar->addAction(openAction);
   toolBar->addAction(saveAction);
   toolBar->addAction(helpAction);
   toolBar->addSeparator();
   //禁止移动
   toolBar->setMovable(false);
   //文本显示在图标下
   toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   //将toolbar添加到水平布局
   barLayout->addWidget(toolBar);
   //链接open的信号与槽
   connect(openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
   connect(saveAction,SIGNAL(triggered()),this,SLOT(saveFileSlot()));

}

void MainWindow::createConfigBar()
{

   // spinBoxLayout = new QHBoxLayout;
     spinBoxLayout = new QGridLayout;
    configureLayout = new QVBoxLayout;
    widgetInit<QLabel>(figureLabel,this,"图形");
    widgetInit<QPushButton>(okButton,this,"OK");
    okButton->setMinimumHeight(50);
    widgetInit<>(formatLabel,this,"输出数据类型");
    widgetInit<>(spinBoxlabel,this,"圆心");
    widgetInit<>(spinBoxlable2,this,"半径");


   SpinBox1 = new QSpinBox(this);
    SpinBox1->setMaximum(9999);
    SpinBox1->setValue(0);

   SpinBox2 = new QSpinBox(this);
    SpinBox2->setMaximum(9999);
    SpinBox2->setValue(0);

    spinBox3 = new QSpinBox(this);
    spinBox3->setMaximum(9999);
    spinBox3->setValue(0);
    spinBox3->setVisible(true);

    spinBox4 = new QSpinBox(this);
    spinBox4->setMaximum(9999);
    spinBox4->setValue(0);
    spinBox4->setVisible(false);

   //两个SpinBox水平布局
    spinBoxLayout->addWidget(SpinBox1,0,0,1,1);
    spinBoxLayout->addWidget(SpinBox2,0,1,1,1);
    spinBoxLayout->addWidget(spinBoxlable2,1,0,1,1);
    spinBoxLayout->addWidget(spinBox3,2,0,1,1);
    spinBoxLayout->addWidget(spinBox4,2,1,1,1);

    formatBox = new QComboBox(this);
    formatBox->addItem("C语言数据(*.c)");
    formatBox->addItem("二进制(*.bin)");

    figureBox = new QComboBox(this);
    figureBox->addItem("圆");
    figureBox->addItem("矩形");


   // configureLayoutimageLabelS->setMouseTracking(true);->addStretch(1);

    configureLayout->addWidget(figureLabel);
    configureLayout->addWidget(figureBox);
    configureLayout->addWidget(spinBoxlabel);
    configureLayout->addLayout(spinBoxLayout);
    configureLayout->addWidget(formatLabel);
    configureLayout->addWidget(formatBox);
    //加弹簧
    configureLayout->addStretch(1);
    configureLayout->addWidget(okButton);

    //为了固定大小不随mainwindows变化而变化，将布局添加到QWidget
    configWidget = new QWidget;
    configWidget->setLayout(configureLayout);
    configWidget->setFixedWidth(150);//固定width 150

    connect(figureBox,SIGNAL(currentIndexChanged(int)),this,SLOT(changedfigure(int)));
    connect(okButton,SIGNAL(pressed()),this,SLOT(buttonPress()));
    connect(SpinBox1,SIGNAL(valueChanged(int)),this,SLOT(changedfigure(int)));
     connect(SpinBox2,SIGNAL(valueChanged(int)),this,SLOT(changedfigure(int)));
      connect(spinBox3,SIGNAL(valueChanged(int)),this,SLOT(changedfigure(int)));
       connect(spinBox4,SIGNAL(valueChanged(int)),this,SLOT(changedfigure(int)));

}

void MainWindow::createImageBar()
{
    gridLayout0 = new QGridLayout;
    horizontalSpacer0 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    verticalSpacer0 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalSpacer1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    widgetInit<mylabel>(imageLabelS,this);
   // imageLabelS->setFixedSize(QSize(240, 240));
    imageLabelS->setVisible(false);
  //  imageLabelS->setText("sssssssssssssssss");
    imageLabelS->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    imageLabelS->setAlignment(Qt::AlignCenter);
    gridLayout0->addItem(horizontalSpacer0,1,0,1,1);
    gridLayout0->addItem(horizontalSpacer1,1,2,1,1);
    gridLayout0->addItem(verticalSpacer0,0,2,1,1);
    gridLayout0->addItem(verticalSpacer1,2,2,1,1);
    gridLayout0->addWidget(imageLabelS,1,1,1,1);


   // imageLayout->addWidget(imageLabelS);

}

void MainWindow::createStatusBar()
{
    //显示鼠标当前实时位置
    statusLabel = new QLabel;
    statusLabel->setText(QStringLiteral("当前位置:"));
    statusLabel->setFixedWidth(100);

    //显示鼠标按下或释放时的实时位置
    MousePosLabel = new QLabel;
    MousePosLabel->setText(QStringLiteral(""));
    MousePosLabel->setFixedWidth(100);
    statusBar = new QStatusBar;
    //添加控件
    statusBar->addPermanentWidget(statusLabel);
    statusBar->addPermanentWidget(MousePosLabel);
}
void MainWindow::createPage()
{
    belowLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    createToolBar();
    createConfigBar();
    createImageBar();
    createStatusBar();
    belowLayout->addWidget(configWidget);
    belowLayout->addLayout(gridLayout0);
//    belowLayout->addWidget(imageLabelS);
    mainLayout->addLayout(barLayout);
    mainLayout->addLayout(belowLayout);
    mainLayout->addWidget(statusBar);
    mainWidget->setLayout(mainLayout);
    mainWidget->setMouseTracking(true);
   this->setCentralWidget(mainWidget);

}

void MainWindow::openFile()
{
    //新建可以文件对话框
    QFileDialog *fileDialog = new QFileDialog(this);
    //窗口标题名
    fileDialog->setWindowTitle("Opne image");
    //设置默认目录
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter("Image(*.png *.jpg *.jpeg *.bmp)");
    //设置单选
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //阻塞，show是非阻塞
    if(fileDialog->exec() == QDialog::Accepted)
    {
        openfilePath = fileDialog->selectedFiles()[0];
        qDebug() << openfilePath;
        getImageData();
        testShowinfo();       
    }
    delete fileDialog;
    // fileDialog->getOpenFileName();
}

void MainWindow::displayImage()
{
    QImage image(openfilePath);
#if 0
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    imageLabelS->setPixmap(pixmap);
#else
   // imageLabelS->setPixmap(QPixmap::fromImage(image));
    imageLabelS->setVisible(true);
    imageLabelS->setImage(image);
    imageLabelS->resize(image.size());
    //开启imageLables 的鼠标捕捉
    imageLabelS->setMouseTracking(true);
    qDebug() << image.size();

#endif
}

void MainWindow::saveFile()
{

    /*一个（）有一个cap,rx.cap(0)表示""内的整个表达式
     * 从左往右，从外往里，cap(1)捕捉(.*)
     * cap(2)((\\*)\\.[a-z]*)
     * cap(3)(\\*)
     * .* 不能匹配中文
     */
         //读formatBox
    QString newSaveFilePath;
    QString filePathTmp = formatBox->currentText();
    qDebug() << filePathTmp;
    QRegExp rx1("^(.*)(\\()(\\*)(\\.[a-z]*)(\\))$");
    bool match = rx1.exactMatch(filePathTmp);
    if(match)
    {
        QString saveFileFormat = rx1.cap(4);
        qDebug() <<"saveFileFormat"<< saveFileFormat;

        QString savefileName = QFileDialog::getSaveFileName(this,"save file",".",saveFileFormat);
        if ( !savefileName.isNull() )
        {
            qDebug() << "savefileName"<<savefileName;
            newSaveFilePath.append(savefileName);
            newSaveFilePath.append(saveFileFormat);

            qDebug() <<"newSaveFilePath" <<newSaveFilePath;
            saveFigureImage(newSaveFilePath);
        }
    }
}

void MainWindow::changedSpinBox(int index)
{
    if(index == 0)
    {
        spinBoxlabel->setText("圆心");
        spinBoxlable2->setText("半径");
        spinBox4->setVisible(false);
    }
    else if(index == 1)
    {
        spinBoxlabel->setText("起点");
        spinBoxlable2->setText("边长");
        spinBox4->setVisible(true);

    }
}

void MainWindow::drawCutFigure()
{
   imageLabelS->getCirclePointPos();
   cutImagePosition.swap(imageLabelS->position);
}

void MainWindow::getImageData()
{
    int ret;
    uint32_t offset;
    imageDecode = new Bmp;
    imageDecode->DecodeImageInformation(openfilePath);
    imageDecode->GetImageinformation(imageWidth,imageHight,biCompression,imagebitCount,imageSize,palette_size);
    imageDecode->GetImageOffset(offset);
    if(palette_size != 0)
    {

    }
    pimageDate = new uint8_t[imageSize];
   ret = imageDecode->GetImageData(pimageDate,imageSize);
}

void MainWindow::saveFigureImage(QString file)
{
    int skip=4-((imageWidth*imagebitCount)>>3)&3;
    qDebug() << skip;
    QFile savefile(file);
    savefile.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate);
    QTextStream out;
    out.setDevice(&savefile);

    getFigureInportantPoint();
    testVector();

    int minx,maxx,height;
    int offset = imagebitCount/8;
    QVector<QPoint>::iterator it = cutImagePosition.begin();

    out << "uint8_t imageArray[]={" << endl;
    for (;it!=cutImagePosition.end();){
        minx = it->x();
        maxx = (it+1)->x();
        height = it->y();
        for (int i=minx;i<=maxx;i++) {
            for(int j=offset-1;j>=0;j--)
            {
              out << "0x" <<hex <<pimageDate[imageSize-((imageWidth*height+i)*offset+j)]<<",";
            }
        }
        out << "// (x,y)(" <<dec<<minx<<","<<height<<")";
        out << "(" <<dec<<maxx<<","<<height<<")";
       out << endl;
        it+=2;
    }
    out << "}" << endl;

    out << "uint16_t position["+QString::number(cutImagePosition.count())+"][2] = {"<<endl;
    for (it=cutImagePosition.begin();it!=cutImagePosition.end();it++) {
        out<< "{"+QString::number(it->x())+","+QString::number(it->y())+"}," << endl;
    }
    out << "}"<< endl;
}

void MainWindow::getFigureInportantPoint()
{
    int tmpy = -1;
    int maxx;
    QVector<QPoint>::iterator it = cutImagePosition.begin();
    QPoint lastPoint = cutImagePosition.last();
     for(;it!=cutImagePosition.end();)
     {
         if(tmpy == -1)
         {
               tmpy = it->y();
               it++;
               continue;
         }
         if(tmpy == it->y())
         {
             maxx = it->x();
             it = cutImagePosition.erase(it);
         }
         else if(tmpy != it->y())
         {
             it = cutImagePosition.insert(it,QPoint(maxx,tmpy));
             it+=2;
              tmpy = it->y();
         }
     }
     it = cutImagePosition.insert(cutImagePosition.end(),lastPoint);
}

#if 1
void MainWindow::testShowinfo()
{
    qDebug() <<"imageWidth" << imageWidth;
    qDebug() << "imageHight" << imageHight;
    qDebug() << "imagebitCount" << imagebitCount;
    qDebug() << "palette_size" <<palette_size;
    qDebug() << "imageSize" << imageSize;
}

void MainWindow::testVector()
{
    QVector<QPoint>::iterator it = cutImagePosition.begin();
    for (;it!=cutImagePosition.end();it++) {
        qDebug() <<"position"<<*it;
    }
}
#endif
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if((event->x()>=imageLabelS->x() && event->x()<= (imageWidth+imageLabelS->x()) )&& \
      ( event->y()>=imageLabelS->y() && event->y()<= (imageHight+imageLabelS->y())))
    {
        QString str = "("+QString::number(event->x()-imageLabelS->x())+","+QString::number(event->y()-imageLabelS->y())+")";
        if(event->button()==Qt::LeftButton){//左键按下
            QPoint offset(event->x()-imageLabelS->x(),event->y()-imageLabelS->y());
         imageLabelS->mousePress(offset,figureBox->currentIndex());
            statusBar->showMessage(QStringLiteral("左键:")+str);
        }else if(event->button()==Qt::RightButton){//右键按下
            statusBar->showMessage(QStringLiteral("右键:")+str);
        }else if(event->button()==Qt::MidButton){//中间键按下
            statusBar->showMessage(QStringLiteral("中间键:")+str);
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if((event->x()>=imageLabelS->x() && (event->x()<= imageWidth+imageLabelS->x())) && \
       (event->y()>=imageLabelS->y() && (event->y()<= imageHight+imageLabelS->y())))
    {
        MousePosLabel->setText("("+QString::number(event->x()-imageLabelS->x())+","+QString::number(event->y()-imageLabelS->y())+")");

        QPoint offset(event->x()-imageLabelS->x(),event->y()-imageLabelS->y());

        imageLabelS->mouseMove(offset);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if((event->x()>=imageLabelS->x() && (event->x()<= imageWidth+imageLabelS->x())) && \
       (event->y()>=imageLabelS->y() && (event->y()<= imageHight+imageLabelS->y())))
    {
         QPoint offset(event->x()-imageLabelS->x(),event->y()-imageLabelS->y());
         qDebug() << "offset" << offset;
       imageLabelS->mouseRelease(offset);
    }
}

void MainWindow::openFileSlot()
{
    qDebug() << "openFileSlot";
    openFile();
    displayImage();
}

void MainWindow::saveFileSlot()
{
    qDebug() << "saveFileSlot";
    saveFile();
}

void MainWindow::buttonPress()
{
    qDebug() << "buttonPress";
    drawCutFigure();
}

void MainWindow::changedfigure(int)
{
    qDebug() << "figureSpinBox1"<<SpinBox1->value();
     qDebug() << "figureSpinBox2"<<SpinBox2->value();
      qDebug() << "spinBox3"<<spinBox3->value();
       qDebug() << "spinBox4"<<spinBox4->value();
       changedSpinBox(figureBox->currentIndex());
       imageLabelS->mousePress(QPoint(SpinBox1->value(),SpinBox2->value()),figureBox->currentIndex());
       if(figureBox->currentIndex() == CRICLE)
       {
           imageLabelS->mouseRelease(QPoint(SpinBox1->value()+spinBox3->value(),SpinBox2->value()));
        }
       else{
       imageLabelS->mouseRelease(QPoint(SpinBox1->value()+spinBox3->value(),SpinBox2->value()+spinBox4->value()));
       }
}

template<typename T>
void MainWindow::widgetInit(T *&widgettmp, QWidget *parent, QString text, int width, int height, int x, int y)
{
    widgettmp = new T;
    widgettmp->setParent(parent);
    widgettmp->setText(text);
    widgettmp->resize(width,height);
    widgettmp->move(x,y);
}
