#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageViewer.h"
//#include<QScrollArea>

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = Q_NULLPTR);
    //private slots:
    void loadFile();
    void saveAs(); //保存图像
    void zoomOut(); //缩小
    void zoomIn(); //放大
    void normalSize(); //还原
    void fitToWindow(); //适应窗体
private:
    //Ui_ImageViewerClass ui;
    Ui::ImageViewerClass ui;
    QImage image;
    double scaleFactor; //缩放系数
public:
};
