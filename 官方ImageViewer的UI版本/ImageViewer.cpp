#include "ImageViewer.h"
#include<QFileDialog>
#include<QScrollBar>
#include<QImageWriter>
//#include<QScrollArea> //滚动区域，当图像过大时，会自动出现滚动条

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionOpen, &QAction::triggered, this, &ImageViewer::loadFile); //自定义函数
    connect(ui.actionExit, &QAction::triggered, this, &QWidget::close); //系统函数
    connect(ui.actionSaveAs, &QAction::triggered, this, &ImageViewer::saveAs); 
    connect(ui.pushButton, &QPushButton::clicked, this, &ImageViewer::zoomOut);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &ImageViewer::zoomIn);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &ImageViewer::normalSize);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &ImageViewer::fitToWindow);
}

//ui界面属性设置说明
//scrollArea不勾选widgetResizable，sizeAdjustPolicy改为AdjustToContents，alignment改为AlignHCenter、AlignVCenter
//label，不勾选scaledContents

void ImageViewer::loadFile()
{
    QFileDialog dialog(this, "打开图片",NULL, "Image Files (*.bmp) \n Image Files (*.png *.jpg)"); //优先bmp格式
    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }
    
    QString fullPath = dialog.selectedFiles().first(); //获取图片全路径
    image.load(fullPath);
    //窗口标题“文件名 - 窗体名”
    QFileInfo fi(fullPath); //fi.fileName()获取文件名
    const QString title = QString("%1 - %2").arg(fi.fileName()).arg(windowTitle());
    setWindowTitle(title);
    //状态栏显示图片信息
    const QString msg = QString("分辨率：%1×%2 ，位深度：%3").arg(image.width()).arg(image.height()).arg(image.depth());
    ui.statusBar->showMessage(msg); //状态栏显示图片信息
    //显示图片
    ui.label->setPixmap(QPixmap::fromImage(image));
    ui.label->adjustSize(); //控件适应图片
    ui.scrollArea->setWidget(ui.label); //让label显示在scrollArea控件。注意窗体上label控件与scrollArea控件并列关系，而非嵌套。label大小设置为0以不占空间。alignment设置为水平、垂直居中，这样图片会居中显示。
    
    scaleFactor = 1.0; //缩放系数

    return;
}

void ImageViewer::saveAs()
{
    QFileDialog dialog(this, "保存图片", NULL, "Image Files (*.bmp) \n Image Files (*.png *.jpg)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }
    QImageWriter writer(dialog.selectedFiles().first());
    writer.write(image);
}

//缩小
void ImageViewer::zoomOut()
{
    scaleFactor *= 0.8; //每次缩小0.8
    ui.label->setScaledContents(true); //图片适应控件
    ui.label->resize(scaleFactor * ui.label->pixmap(Qt::ReturnByValue).size()); //注意，图片大小未变，而是label改变

}

//放大
void ImageViewer::zoomIn()
{
    scaleFactor *= 1.2; //每次放大1.2
    ui.label->setScaledContents(true); //图片适应控件
    ui.label->resize(scaleFactor * ui.label->pixmap(Qt::ReturnByValue).size()); //注意，图片大小未变，而是label改变

}

//还原
void ImageViewer::normalSize()
{
    ui.label->adjustSize(); //控件适应图片。或者用以下三行
    scaleFactor = 1.0;
    //ui.label->setScaledContents(true); //图片适应控件
    //ui.label->resize(scaleFactor * ui.label->pixmap(Qt::ReturnByValue).size()); //注意，图片大小未变，而是label改变

}

//还原
void ImageViewer::fitToWindow()
{
    ui.label->setScaledContents(true); //图片适应控件
    ui.label->resize(ui.scrollArea->width()-1,ui.scrollArea->height()-1);
}