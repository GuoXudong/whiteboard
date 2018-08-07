#include "whiteboard.h"
#include "ui_whiteboard.h"

Whiteboard::Whiteboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Whiteboard)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground, true);

    scene = new Scene();                //add scene
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Whiteboard::Timer);
    timer->start(100);

    connect(scene, SIGNAL(clear_emit()),this, SLOT(clear_enable()));
    connect(scene, SIGNAL(redo_emit()),this, SLOT(redo_unable()));

    ui->graphicsView->raise();
}

Whiteboard::~Whiteboard()
{
    delete ui;
}

void Whiteboard::Timer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width(), ui->graphicsView->height());
}

void Whiteboard::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void Whiteboard::paintEvent(QPaintEvent *event)
{
    QColor color(255,255,255,0);
    QPainter painter(this);
    painter.setBrush(color);
    painter.drawRect(rect());
}

void Whiteboard::on_horizontalSlider_valueChanged(int value)
{
    scene->size = value;
    ui->spinBox->setValue(value);
}

void Whiteboard::on_spinBox_valueChanged(int value)
{
    scene->size = value;
    ui->horizontalSlider->setValue(value);
}

void Whiteboard::on_typeLine_currentIndexChanged(int index)
{
    scene->type = index;
}

void Whiteboard::on_clear_clicked()
{
    scene->clear();                 //undo,redo,clear set unable
    scene->undo_items.clear();
    scene->redo_items.clear();
    ui->undo->setEnabled(false);
    ui->redo->setEnabled(false);
    ui->clear->setEnabled(false);
    scene->update();
}

void Whiteboard::clear_enable()
{
    ui->clear->setEnabled(true);
    ui->undo->setEnabled(true);
}

void Whiteboard::redo_unable()
{
    ui->redo->setEnabled(false);
    scene->redo_items.clear();
}

void Whiteboard::on_undo_clicked()
{
    if (!scene->undo_items.isEmpty())       //just to be sure
    {
        scene->redo_items.push(scene->undo_items.top());
        scene->removeItem(scene->undo_items.top());
        scene->undo_items.pop();
        ui->redo->setEnabled(true);
    }

    if (scene->undo_items.isEmpty())    //set unable if it was last item
        ui->undo->setEnabled(false);
    scene->update();
}

void Whiteboard::on_redo_clicked()
{
    if (!scene->redo_items.isEmpty())       //just to be sure
    {
        scene->addItem(scene->redo_items.top());
        scene->undo_items.push(scene->redo_items.top());
        scene->redo_items.pop();
        ui->undo->setEnabled(true);
    }

    if (scene->redo_items.isEmpty())    //set unable if it was last item
        ui->redo->setEnabled(false);
    scene->update();
}

void Whiteboard::on_black_clicked()
{
    scene->color = ui->black->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 0, 0)");
}

void Whiteboard::on_l_grey_clicked()
{
    scene->color = ui->l_grey->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(191, 191, 191)");
}

void Whiteboard::on_blue_clicked()
{
    scene->color = ui->blue->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 5, 129)");
}

void Whiteboard::on_sea_clicked()
{
    scene->color = ui->sea->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 127, 131)");
}

void Whiteboard::on_green_clicked()
{
    scene->color = ui->green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 124, 0)");
}

void Whiteboard::on_d_green_clicked()
{
    scene->color = ui->d_green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 127, 0)");
}

void Whiteboard::on_d_red_clicked()
{
    scene->color = ui->d_red->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 4, 0)");
}

void Whiteboard::on_violet_clicked()
{
    scene->color = ui->violet->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(126, 10, 125)");
}

void Whiteboard::on_grey_clicked()
{
    scene->color = ui->grey->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 128, 128)");
}

void Whiteboard::on_white_clicked()
{
    scene->color = ui->white->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(255, 255, 255)");
}

void Whiteboard::on_l_blue_clicked()
{
    scene->color = ui->l_blue->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 7, 243)");
}

void Whiteboard::on_cyan_clicked()
{
    scene->color = ui->cyan->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(5, 226, 248)");
}

void Whiteboard::on_l_green_clicked()
{
    scene->color = ui->l_green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(1, 210, 0)");
}

void Whiteboard::on_yellow_clicked()
{
    scene->color = ui->yellow->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(249, 236, 9)");
}

void Whiteboard::on_red_clicked()
{
    scene->color = ui->red->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(239, 11, 0)");
}

void Whiteboard::on_pink_clicked()
{
    scene->color = ui->pink->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(243, 26, 239)");
}
