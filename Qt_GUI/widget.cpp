#include "widget.h"
#include "ui_widget.h"
#include "filterwindow.h"
#include <QFileDialog>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, &Widget::onStartClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onStartClicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select image to load",
        "",
        "Images (*.png *.jpg *.jpeg *.bmp );;All files (*)"
    );

    // if not loaded file then return
    if (filePath.isEmpty()) {
        return;
    }

    FilterWindow *filterWin = new FilterWindow();
    filterWin->setAttribute(Qt::WA_DeleteOnClose);

    if (!filterWin->loadImageFromPath(filePath)) {
        delete filterWin;
        return;
    }


    filterWin->show();
    this->close();
}
