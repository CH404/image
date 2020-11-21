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
#include <bmp.h>
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
    QComboBox *figureBox;
    QLabel * spinBoxlabel;
    QSpinBox *figureSpinBox1;
    QSpinBox *figureSpinBox2;
    QLabel *formatLabel;
    QComboBox *formatBox;
    QPushButton *okButton;

    QLabel *imageLabelS;

    QHBoxLayout *spinBoxLayout;
    QHBoxLayout *barLayout;
    QVBoxLayout *configureLayout;
    QHBoxLayout *belowLayout;
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;
    QWidget *configWidget;

    QString newSaveFilePath;
    QString openfilePath;
    Ui::MainWindow *ui;
    Bmp *imageDecode;

    uint32_t imageWidth =0;
    uint32_t imageHight = 0;

    uint16_t imagebitCount = 0;
    uint32_t palette_size =0;
    uint32_t imageSize = 0;

    uint8_t *pimageDate = nullptr;
    uint8_t *pimagePalette =nullptr;

private:
    void createToolBar(void);
    void createConfigBar(void);
    void createImageBar(void);
    void createPage(void);
    void openFile(void);
    void displayImage(void);
    void saveFile(void);
    template<typename T>
    void widgetInit(T *&widgettmp,QWidget *parent=nullptr,QString text="",int width=0,int height=0,int x=0,int y=0);
    void getImageData();
    void testShowinfo(void);
private slots:
    void openFileSlot();
    void saveFileSlot();
};

#endif // MAINWINDOW_H
