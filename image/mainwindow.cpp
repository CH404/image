#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QRegExp>
#include "bmp.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createPage();


   // this->setFixedSize(800,500);
}

MainWindow::~MainWindow()
{
    delete ui;
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

    spinBoxLayout = new QHBoxLayout;
    configureLayout = new QVBoxLayout;
    widgetInit<QLabel>(figureLabel,this,"图形");
    widgetInit<QPushButton>(okButton,this,"OK");
    okButton->setMinimumHeight(50);
    widgetInit<>(formatLabel,this,"输出数据类型");
    widgetInit<>(spinBoxlabel,this,"边长");

    figureSpinBox1 = new QSpinBox(this);
    figureSpinBox1->setMaximum(1000);
    figureSpinBox1->setValue(0);

    figureSpinBox2 = new QSpinBox(this);
    figureSpinBox2->setMaximum(1000);
    figureSpinBox2->setValue(0);

   //两个SpinBox水平布局
    spinBoxLayout->addWidget(figureSpinBox1);
    spinBoxLayout->addWidget(figureSpinBox2);

    formatBox = new QComboBox(this);
    formatBox->addItem("C语言数据(*.c)");
    formatBox->addItem("二进制(*.bin)");

    figureBox = new QComboBox(this);
    figureBox->addItem("圆");
    figureBox->addItem("正方形");
    figureBox->addItem("长方形");


   // configureLayout->addStretch(1);

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
}

void MainWindow::createImageBar()
{
    widgetInit<>(imageLabelS,this,"");
  //  widgetInit<>(imageLabelD,this,"345678");
    imageLabelS->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    imageLabelS->setAlignment(Qt::AlignCenter);
    //mageLabelS->setFixedSize(500,500);
/*
    QImage images(":/resource/openFile.jpeg");
    QPixmap pixmap;
    pixmap.convertFromImage(images);
    imageLabelS->setPixmap(pixmap);*/
   // imageLabelD->setFixedSize(500,500);

}
void MainWindow::createPage()
{
    belowLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    createToolBar();
    createConfigBar();
    createImageBar();
    belowLayout->addWidget(configWidget);
    belowLayout->addWidget(imageLabelS);

     mainLayout->addLayout(barLayout);
     mainLayout->addLayout(belowLayout);
     mainWidget->setLayout(mainLayout);
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
    imageLabelS->setPixmap(QPixmap::fromImage(image));
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
    QString filePathTmp = formatBox->currentText();
    qDebug() << filePathTmp;
    QRegExp rx1("^(.*)(\\()(\\*)(\\.[a-z]*)(\\))$");
    bool match = rx1.exactMatch(filePathTmp);
    if(match)
    {
        QString saveFileFormat = rx1.cap(4);
        qDebug() << saveFileFormat;


        QString savefileName = QFileDialog::getSaveFileName(this,"save file",".",saveFileFormat);
        if ( !savefileName.isNull() )
        {
            qDebug() << savefileName;
            newSaveFilePath.append(savefileName);
            newSaveFilePath.append(saveFileFormat);
            qDebug() << newSaveFilePath;
        }
    }
}

void MainWindow::getImageData()
{
    int ret;
    imageDecode = new Bmp;
    imageDecode->DecodeImageInformation(openfilePath);
    imageDecode->GetImageinformation(imageWidth,imageHight,imagebitCount,imageSize,palette_size);
//    imageDecode->GetImageHW(imageWidth,imageHight);
//    imageDecode->GetImageBitCount(imagebitCount);
    if(palette_size != 0)
    {

    }
    pimageDate = new uint8_t[imageSize];
   ret = imageDecode->GetImageData(pimageDate,imageSize);
    qDebug() <<"ret"<< ret;

  //  delete imageDecode;
  //  imageDecode = nullptr;
}
#if 1
void MainWindow::testShowinfo()
{
    qDebug() <<"imageWidth" << imageWidth;
    qDebug() << "imageHight" << imageHight;
    qDebug() << "imagebitCount" << imagebitCount;
    qDebug() << "palette_size" <<palette_size;
    qDebug() << "imageSize" << imageSize;
    for (int i=0;i<10;i++) {
             qDebug("bfType %x",*(pimageDate+i));
        }


}
#endif
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

template<typename T>
void MainWindow::widgetInit(T *&widgettmp, QWidget *parent, QString text, int width, int height, int x, int y)
{
    widgettmp = new T;
    widgettmp->setParent(parent);
    widgettmp->setText(text);
    widgettmp->resize(width,height);
    widgettmp->move(x,y);
}
