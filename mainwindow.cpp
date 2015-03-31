#include "boardWidget.h"
#include "mainwindow.h"
#include <qmenu.h>
#include <qmenubar.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qslider.h>
#include <qbuttongroup.h>
#include <qcolordialog.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qfiledialog.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
	buildMenus();
	buildWidgets();
}

MainWindow::~MainWindow()
{

}

void MainWindow::buildWidgets()
{
	main_widget = new QWidget();
	tool_widget = new QWidget();
	board_widget = new boardWidget();

	v_layout = new QVBoxLayout();
	h_layout = new QHBoxLayout();
	grid_layout = new QGridLayout();

	groupBox = new QGroupBox("Shapes");
	lblSliderValue = new QLabel();
	lblSlider = new QLabel("Brush Size");
	brushSlider = new QSlider(Qt::Horizontal);

	btn_group = new QButtonGroup(main_widget);

	btn_square = new QPushButton("Square");
	btn_triangle = new QPushButton("Triangle");
	btn_circle = new QPushButton("Circle");
	btn_text = new QPushButton("Text");
	btn_fill = new QPushButton("Fill");
	btn_brush = new QPushButton("Brush");
	btn_pen = new QPushButton("Pen");
	btn_erase = new QPushButton("Erase");
	
	btn_selectcolor = new QPushButton("Select Color");
	color_label = new QLabel();
	lbl_color = new QLabel("Current Color");

	groupBox->setStyleSheet("QGroupBox {font: bold normal 13px \"Arial\";}");
	groupBox->setAlignment(Qt::AlignHCenter);

	lblSliderValue->setText(" 1                 4                 7                10");

	brushSlider->setMinimum(1);
	brushSlider->setMaximum(10);
	brushSlider->setFocusPolicy(Qt::StrongFocus);
	brushSlider->setTickPosition(QSlider::TicksBothSides);
	brushSlider->setTickInterval(3);
	brushSlider->setSingleStep(1);

	btn_group->addButton(btn_circle);
	btn_group->addButton(btn_square);
	btn_group->addButton(btn_triangle);
	btn_group->addButton(btn_brush);
	btn_group->addButton(btn_fill);
	btn_group->addButton(btn_text);
	btn_group->addButton(btn_pen);
	btn_group->addButton(btn_erase);

	QAbstractButton* btn;

	foreach(btn, btn_group->buttons())
	{
		btn->setCheckable(true);
		connect(btn, SIGNAL(toggled(bool)), this, SLOT(draw_shape()));
	}
	

	connect(btn_selectcolor, &QPushButton::clicked, this, &MainWindow::select_color);
	connect(brushSlider, &QSlider::valueChanged, this, &MainWindow::set_brush_value);

	grid_layout->setSpacing(15);

	grid_layout->addWidget(btn_square, 0, 0);
	grid_layout->addWidget(btn_triangle, 0, 1);
	grid_layout->addWidget(btn_circle, 1, 0);
	grid_layout->addWidget(btn_text, 1, 1);
	grid_layout->addWidget(btn_fill, 2, 0);
	grid_layout->addWidget(btn_brush, 2, 1);
	grid_layout->addWidget(btn_pen, 3, 0);
	grid_layout->addWidget(btn_erase, 3, 1);

	QWidget* top_filler = new QWidget();
	QWidget* bottom_filler = new QWidget();

	v_layout->addWidget(groupBox, 0, Qt::AlignVCenter);
	v_layout->addWidget(top_filler, 1, Qt::AlignVCenter);
	v_layout->addWidget(lblSlider, 0, Qt::AlignCenter);
	v_layout->addWidget(lblSliderValue, 0, Qt::AlignVCenter);
	v_layout->addWidget(brushSlider, 0, Qt::AlignVCenter);
	v_layout->addWidget(bottom_filler, 1, Qt::AlignVCenter);
	v_layout->addWidget(lbl_color, 0, Qt::AlignCenter);
	v_layout->addWidget(color_label, 0, Qt::AlignCenter);
	v_layout->addWidget(btn_selectcolor, 0, Qt::AlignCenter);

	h_layout->addWidget(tool_widget);
	h_layout->addWidget(board_widget);

	board_widget->setMinimumSize(800, 600);
	tool_widget->setFixedSize(200, 450);

	QFont font;
	font.setBold(true);
	font.setFamily("Arial");
	font.setPointSize(10);

	lblSlider->setFont(font);
	lbl_color->setFont(font);

	color_label->setFixedSize(25, 25);
	btn_selectcolor->setFixedSize(80, 30);

	color_label->setFrameStyle(QFrame::Sunken | QFrame::Panel);

	color_label->setPalette(QPalette(Qt::black));
    color_label->setAutoFillBackground(true);

	groupBox->setLayout(grid_layout);
	tool_widget->setLayout(v_layout);
	main_widget->setLayout(h_layout);


	setCentralWidget(main_widget);
}

void MainWindow::select_color()
{
	QColor color = QColorDialog::getColor(Qt::black);

    if (color.isValid())
    {	
        color_label->setPalette(QPalette(color));
        color_label->setAutoFillBackground(true);
    }

	board_widget->set_color(color);
}

void MainWindow::set_brush_value(int value)
{
	board_widget->set_brush_size(value);
}

void MainWindow::buildMenus()
{
	QMenu *fileMenu = menuBar()->addMenu("File");
	QMenu *editMenu = menuBar()->addMenu("Edit");
	QMenu *image = menuBar()->addMenu("Image");
	QMenu *color = menuBar()->addMenu("Color");
	QMenu *help = menuBar()->addMenu("Help");

	QAction *save = fileMenu->addAction("Save");
	connect(save, SIGNAL(toggled(bool)), this, SLOT(saveLayout));
}

void MainWindow::buildToolbar()
{

}

void MainWindow::draw_shape()
{
	if (btn_circle->isChecked())
	{
		board_widget->set_cur_object(CIRCLE);
	}
	else if (btn_triangle->isChecked())
	{
		board_widget->set_cur_object(TRIANGLE);
	}
	else if (btn_square->isChecked())
	{
		board_widget->set_cur_object(SQUARE);
	}
	else if (btn_text->isChecked())
	{
		board_widget->set_cur_object(NONE);
	}
	else if (btn_pen->isChecked())
	{
		board_widget->set_cur_object(PEN);
	}
	else if (btn_erase->isChecked())
	{
		board_widget->set_cur_object(NONE);
	}
	else if (btn_fill->isChecked())
	{
		board_widget->set_cur_object(FILL);
	}
	else
	{
		board_widget->set_cur_object(NONE);
	}
}
void MainWindow::saveLayout()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save layout"));
	if (fileName.isEmpty())
		return;
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly)) {
		QString msg = tr("Failed to open %1\n%2")
			.arg(fileName)
			.arg(file.errorString());
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}

	QByteArray geo_data = saveGeometry();
	QByteArray layout_data = saveState();

	bool ok = file.putChar((uchar)geo_data.size());
	if (ok)
		ok = file.write(geo_data) == geo_data.size();
	if (ok)
		ok = file.write(layout_data) == layout_data.size();

	if (!ok) {
		QString msg = tr("Error writing to %1\n%2")
			.arg(fileName)
			.arg(file.errorString());
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}
}
void MainWindow::actionTriggered(QAction *action)
{
	qDebug("action '%s' triggered", action->text().toLocal8Bit().data());
}
