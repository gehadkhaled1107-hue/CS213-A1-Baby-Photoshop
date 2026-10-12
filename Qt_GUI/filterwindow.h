#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QWidget>
#include <QString>
#include <QImage>
#include <QPixmap>

#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#include "Image_Class.h"
#undef pixel
#undef ll

namespace Ui {
class FilterWindow;
}

class FilterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FilterWindow(QWidget *parent = nullptr);
    ~FilterWindow();

    bool loadImageFromPath(const QString& path);

protected:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onLoadClicked();
    void onSaveClicked();
    void onUndoClicked();
    void onExitClicked();

    void onGrayscaleClicked();
    void onTvClicked();
    void onInvertClicked();
    void onBwClicked();
    void onSunlightClicked();
    void onInfraredClicked();
    void onEdgesClicked();
    void onPurpleClicked();
    void onOilClicked();
    void onBlurClicked();

    void onFlipClicked();
    void onRotateClicked();
    void onDarkLightClicked();
    void onFrameClicked();
    void onResizeClicked();
    void onCropClicked();
    void onSkewClicked();
    void onMergeClicked();

private:
    void refreshDisplay();
    bool hasImage() const;
    bool requireImage();
    void backupBeforeFilter();
    bool askSaveIfModified();

    Ui::FilterWindow *ui;

    Image currentImage;
    Image previousImage;
    bool hasBackup = false;
    bool modified = false;
    QString lastPath;
};

#endif