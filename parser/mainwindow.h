#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGraphicsView>
#include "treenode.h"
#include <QTextEdit>
#include "parserfunctions.h"
#include "vectoroftokens.h"
#include "view.h"
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void init_main_window();
    void init_graph_window();
    void draw_rectangle(int x, int y, QString type, QString value);
    void print_error(QString err);
    void draw_ellipse(int x, int y,QString type, QString value);
    void draw_link(int x1, int y1, int x2 , int y2);
    void draw_node(TreeNode * tree);
    ~MainWindow();

public slots:
    void show_graph_window();
    void show_main_window();

private:
    QWidget * main_window;
    QWidget * graph_window;
    View * graph;
    QGraphicsScene * graph_scene;
    TreeNode tree;
    QTextEdit * text_input;
    VectorOfTokens input_vector;
    ParserFunctions input_function;
};

#endif // MAINWINDOW_H
