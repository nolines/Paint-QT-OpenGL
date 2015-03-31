#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class boardWidget;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QGroupBox;
class QLabel;
class QSlider;
class QButtonGroup;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void actionTriggered(QAction *action);
	void saveLayout();

private:
	void buildWidgets();
	void buildMenus();
	void buildToolbar();
	
private:
	QWidget* main_widget;
	QWidget* tool_widget;
	boardWidget* board_widget;
	

	QVBoxLayout* v_layout;
	QHBoxLayout* h_layout;
	QGridLayout* grid_layout;

	QButtonGroup* btn_group;
	QPushButton* btn_square;
	QPushButton* btn_triangle;
	QPushButton* btn_circle;
	QPushButton* btn_text;
	QPushButton* btn_fill;
	QPushButton* btn_brush;
	QPushButton* btn_pen;
	QPushButton* btn_erase;
	
	
	QGroupBox* groupBox;
	QLabel* lblSlider;
	QLabel* lblSliderValue;
	QSlider* brushSlider;

	QLabel* lbl_color;
	QLabel*	color_label;
	QPushButton* btn_selectcolor;

private slots:
	void draw_shape();
	void select_color();
	void set_brush_value(int value);
};

#endif // MAINWINDOW_H
