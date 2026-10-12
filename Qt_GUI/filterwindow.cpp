#include "filterwindow.h"
#include "ui_filterwindow.h"
#include "filters.h"

#include <QFile>
#include <QDir>
#include <QShowEvent>
#include <QResizeEvent>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QToolButton>
#include <QStringList>
#include <cmath>

namespace {
const char *kOpenFilter = "Images (*.png *.jpg *.jpeg *.bmp *);;All files (*)";
const char *kSaveFilter = "PNG (*.png);;JPEG (*.jpg *.jpeg);;Bitmap (*.bmp)";
}

FilterWindow::FilterWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FilterWindow)
{
    ui->setupUi(this);

    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->imageLabel->setMinimumSize(1, 1);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    struct IconInfo { QToolButton *button; const char *file; };
    const IconInfo icons[] = {
        { ui->skewButton,      "skew.png" },
        { ui->oilButton,       "oil.png" },
        { ui->purpleButton,    "purple.png" },
        { ui->cropButton,      "crop.png" },
        { ui->edgesButton,     "edges.png" },
        { ui->frameButton,     "frame.png" },
        { ui->infraredButton,  "infrared.png" },
        { ui->blurButton,      "blur.png" },
        { ui->sunlightButton,  "sunlight.png" },
        { ui->mergeButton,     "merge.png" },
        { ui->resizeButton,    "resize.png" },
        { ui->bwButton,        "bw.png" },
        { ui->darkLightButton, "darkLight.png" },
        { ui->invertButton,    "invert.png" },
        { ui->tvButton,        "tv.png" },
        { ui->rotateButton,    "rotate.png" },
        { ui->flipButton,      "flip.png" },
        { ui->grayscaleButton, "grayscale.png" },
    };
    const QString srcDir = QFileInfo(QString(__FILE__)).absolutePath();
    const QStringList folders = {
        ":/",
        srcDir + "/filter_ui/",
        srcDir + "/filter_images/",
        "C:/C++/BabyPhoto/filter_ui/",
        "C:/C++/BabyPhoto/filter_images/",
        "C:/filter_ui/",
        "C:/filter_images/"
    };

    for (const IconInfo &i : icons) {
        for (const QString &folder : folders) {
            QString fullPath = folder + i.file;
            if (QFile::exists(fullPath)) {
                i.button->setIcon(QIcon(fullPath));
                break;
            }
        }
        i.button->setIconSize(QSize(80, 80));
        i.button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        i.button->setFixedSize(120, 130);
    }

    connect(ui->loadPushButton, &QAbstractButton::clicked, this, &FilterWindow::onLoadClicked);
    connect(ui->savePushButton, &QAbstractButton::clicked, this, &FilterWindow::onSaveClicked);
    connect(ui->undoPushButton, &QAbstractButton::clicked, this, &FilterWindow::onUndoClicked);
    connect(ui->exitPushButton, &QAbstractButton::clicked, this, &FilterWindow::onExitClicked);

    connect(ui->grayscaleButton, &QAbstractButton::clicked, this, &FilterWindow::onGrayscaleClicked);
    connect(ui->flipButton,      &QAbstractButton::clicked, this, &FilterWindow::onFlipClicked);
    connect(ui->rotateButton,    &QAbstractButton::clicked, this, &FilterWindow::onRotateClicked);
    connect(ui->tvButton,        &QAbstractButton::clicked, this, &FilterWindow::onTvClicked);
    connect(ui->invertButton,    &QAbstractButton::clicked, this, &FilterWindow::onInvertClicked);
    connect(ui->darkLightButton, &QAbstractButton::clicked, this, &FilterWindow::onDarkLightClicked);
    connect(ui->bwButton,        &QAbstractButton::clicked, this, &FilterWindow::onBwClicked);
    connect(ui->resizeButton,    &QAbstractButton::clicked, this, &FilterWindow::onResizeClicked);
    connect(ui->mergeButton,     &QAbstractButton::clicked, this, &FilterWindow::onMergeClicked);
    connect(ui->sunlightButton,  &QAbstractButton::clicked, this, &FilterWindow::onSunlightClicked);
    connect(ui->blurButton,      &QAbstractButton::clicked, this, &FilterWindow::onBlurClicked);
    connect(ui->infraredButton,  &QAbstractButton::clicked, this, &FilterWindow::onInfraredClicked);
    connect(ui->frameButton,     &QAbstractButton::clicked, this, &FilterWindow::onFrameClicked);
    connect(ui->edgesButton,     &QAbstractButton::clicked, this, &FilterWindow::onEdgesClicked);
    connect(ui->cropButton,      &QAbstractButton::clicked, this, &FilterWindow::onCropClicked);
    connect(ui->purpleButton,    &QAbstractButton::clicked, this, &FilterWindow::onPurpleClicked);
    connect(ui->oilButton,       &QAbstractButton::clicked, this, &FilterWindow::onOilClicked);
    connect(ui->skewButton,      &QAbstractButton::clicked, this, &FilterWindow::onSkewClicked);
}

FilterWindow::~FilterWindow()
{
    delete ui;
}


bool FilterWindow::hasImage() const
{
    return currentImage.width > 0 && currentImage.height > 0;
}

bool FilterWindow::requireImage()
{
    if (hasImage()) return true;
    QMessageBox::information(this, "No image", "Load an image first.");
    return false;
}

void FilterWindow::refreshDisplay()
{
    if (!hasImage()) return;

    QImage qimg(currentImage.imageData, currentImage.width, currentImage.height,
                currentImage.width * 3, QImage::Format_RGB888);

    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg).scaled(
        ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void FilterWindow::backupBeforeFilter()
{
    previousImage = currentImage;
    hasBackup = true;
}

void FilterWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    refreshDisplay();
}

void FilterWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    refreshDisplay();
}

void FilterWindow::closeEvent(QCloseEvent *event)
{
    if (askSaveIfModified()) event->accept();
    else event->ignore();
}

bool FilterWindow::askSaveIfModified()
{
    if (!modified || !hasImage()) return true;

    auto answer = QMessageBox::question(
        this, "Unsaved changes", "Do you want to save the current image first?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Save);

    if (answer == QMessageBox::Save) {
        onSaveClicked();
        return !modified;
    }
    return answer == QMessageBox::Discard;
}

bool FilterWindow::loadImageFromPath(const QString& path)
{
    try {
        currentImage.loadNewImage(path.toStdString());
        hasBackup = false;
        modified = false;
        lastPath = path;
        refreshDisplay();
        return true;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Load failed", e.what());
        return false;
    }
}

void FilterWindow::onLoadClicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select an image", "", kOpenFilter);
    if (path.isEmpty()) return;
    if (!askSaveIfModified()) return;
    loadImageFromPath(path);
}

void FilterWindow::onSaveClicked()
{
    if (!requireImage()) return;

    QString startPath;
    if (!lastPath.isEmpty()) {
        QFileInfo fi(lastPath);
        startPath = fi.absolutePath() + "/" + fi.completeBaseName() + "_edited.png";
    }

    QString path = QFileDialog::getSaveFileName(this, "Save image as", startPath, kSaveFilter);
    if (path.isEmpty()) return;

    try {
        currentImage.saveImage(path.toStdString());
        lastPath = path;
        modified = false;
        QMessageBox::information(this, "Saved", "Image saved successfully.");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Save failed", e.what());
    }
}

void FilterWindow::onUndoClicked()
{
    if (!hasBackup) {
        QMessageBox::information(this, "Undo", "Nothing to undo.");
        return;
    }
    currentImage = previousImage;
    hasBackup = false;
    modified = true;
    refreshDisplay();
}

void FilterWindow::onExitClicked()
{
    close();
}

void FilterWindow::onGrayscaleClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    grayscaleFilter(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onTvClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    den(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onInvertClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    invertImage(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onBwClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    Black_and_White(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onSunlightClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    sunlightFilter(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onInfraredClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    Infrared_Images(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onEdgesClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    edges(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onPurpleClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    PurpleImage(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onOilClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    oilImage(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onBlurClicked()
{
    if (!requireImage()) return;
    backupBeforeFilter();
    Image blurred(currentImage.width, currentImage.height);
    Blur_Images(currentImage, blurred);
    currentImage = blurred;
    modified = true;
    refreshDisplay();
}

void FilterWindow::onFlipClicked()
{
    if (!requireImage()) return;

    QStringList options;
    options << "Horizontal" << "Vertical";
    bool ok = false;
    QString choice = QInputDialog::getItem(this, "Flip Direction", "Choose direction:",
                                            options, 0, false, &ok);
    if (!ok) return;

    backupBeforeFilter();
    currentImage = flipFilter(currentImage, (choice == "Horizontal") ? "h" : "v");
    modified = true;
    refreshDisplay();
}

void FilterWindow::onRotateClicked()
{
    if (!requireImage()) return;

    QStringList options;
    options << "90" << "180" << "270";
    bool ok = false;
    QString choice = QInputDialog::getItem(this, "Rotate", "Choose degree:",
                                            options, 0, false, &ok);
    if (!ok) return;

    int code = options.indexOf(choice) + 1;

    backupBeforeFilter();
    rotation(currentImage, code);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onDarkLightClicked()
{
    if (!requireImage()) return;

    QStringList options;
    options << "Darken (50%)" << "Lighten (50%)";
    bool ok = false;
    QString choice = QInputDialog::getItem(this, "Darken / Lighten", "Choose option:",
                                            options, 0, false, &ok);
    if (!ok) return;

    backupBeforeFilter();
    if (choice == options.at(0)) darkenImage(currentImage);
    else                         lightenImage(currentImage);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onFrameClicked()
{
    if (!requireImage()) return;

    QStringList typeOptions;
    typeOptions << "Simple" << "Fancy";
    bool ok = false;
    QString typeChoice = QInputDialog::getItem(this, "Frame Type", "Choose frame type:",
                                                typeOptions, 0, false, &ok);
    if (!ok) return;

    QStringList colorOptions;
    colorOptions << "Beige" << "Red" << "Blue" << "Green";
    QString colorChoice = QInputDialog::getItem(this, "Frame Color", "Choose frame color:",
                                                colorOptions, 0, false, &ok);
    if (!ok) return;

    int n = (typeChoice == "Simple") ? 1 : 2;
    int color = colorOptions.indexOf(colorChoice) + 1;

    if (n == 2 && std::min(currentImage.width, currentImage.height) < 50) {
        QMessageBox::warning(this, "Image too small",
                                "The fancy frame needs an image of at least 50x50 pixels.");
        return;
    }

    backupBeforeFilter();
    makeframe(currentImage, n, color);
    modified = true;
    refreshDisplay();
}

void FilterWindow::onResizeClicked()
{
    if (!requireImage()) return;

    bool ok = false;
    int newW = QInputDialog::getInt(this, "Resize", "New width:", currentImage.width, 1, 5000, 1, &ok);
    if (!ok) return;
    int newH = QInputDialog::getInt(this, "Resize", "New height:", currentImage.height, 1, 5000, 1, &ok);
    if (!ok) return;

    backupBeforeFilter();
    Image resized(newW, newH);
    Resizing_Images(currentImage, resized, newW, newH);
    currentImage = resized;
    modified = true;
    refreshDisplay();
}

void FilterWindow::onCropClicked()
{
    if (!requireImage()) return;

    int W = currentImage.width;
    int H = currentImage.height;
    bool ok = false;

    int x = QInputDialog::getInt(this, "Crop", QString("Start X (0-%1):").arg(W - 1), 0, 0, W - 1, 1, &ok);
    if (!ok) return;
    int y = QInputDialog::getInt(this, "Crop", QString("Start Y (0-%1):").arg(H - 1), 0, 0, H - 1, 1, &ok);
    if (!ok) return;
    int w = QInputDialog::getInt(this, "Crop", QString("Width (1-%1):").arg(W - x), W - x, 1, W - x, 1, &ok);
    if (!ok) return;
    int h = QInputDialog::getInt(this, "Crop", QString("Height (1-%1):").arg(H - y), H - y, 1, H - y, 1, &ok);
    if (!ok) return;

    backupBeforeFilter();
    bool success = cropImage(currentImage, x, y, w, h);
    if (!success) {
        currentImage = previousImage;
        QMessageBox::warning(this, "Invalid crop", "Those dimensions don't fit inside the image.");
        return;
    }
    modified = true;
    refreshDisplay();
}

void FilterWindow::onSkewClicked()
{
    if (!requireImage()) return;

    bool ok = false;
    double angle = QInputDialog::getDouble(this, "Skew", "Skew angle (degrees):",
                                            20.0, -80.0, 80.0, 1, &ok);
    if (!ok) return;

    double skewFactor = std::tan(angle * 3.14159265 / 180.0);
    int orgWidth = currentImage.width;
    int orgHeight = currentImage.height;
    int maxShift = std::abs((int)(skewFactor * orgHeight));
    int newWidth = orgWidth + maxShift;

    if (newWidth > 20000) {
        QMessageBox::warning(this, "Skew", "The result would be too wide. Use a smaller angle.");
        return;
    }

    backupBeforeFilter();
    Image skewed(newWidth, orgHeight);
    Skewed_Images(currentImage, skewed, orgWidth, orgHeight, newWidth, skewFactor);
    currentImage = skewed;
    modified = true;
    refreshDisplay();
}

void FilterWindow::onMergeClicked()
{
    if (!requireImage()) return;

    QString secondPath = QFileDialog::getOpenFileName(
        this, "Select the second image to merge", "", kOpenFilter);
    if (secondPath.isEmpty()) return;

    Image secondImage;
    try {
        secondImage.loadNewImage(secondPath.toStdString());
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Load failed", e.what());
        return;
    }

    bool ok = false;
    int option = QInputDialog::getInt(
        this, "Merge", "1 = Resize to biggest, 2 = Crop common area:",
        1, 1, 2, 1, &ok);
    if (!ok) return;

    double blend = QInputDialog::getDouble(
        this, "Merge", "Blend factor (0 = second image only, 1 = current image only):",
        0.5, 0.0, 1.0, 2, &ok);
    if (!ok) return;

    backupBeforeFilter();
    currentImage = mergeFilter(currentImage, secondImage, option, (float)blend);
    modified = true;
    refreshDisplay();
}