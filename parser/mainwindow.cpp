#include "mainwindow.h"
#include "parserfunctions.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QToolBar>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/data/img/tree_structure.png"));
    this->init_main_window();
    this->init_graph_window();
    this->setCentralWidget(this->main_window);
}
void MainWindow::init_main_window()
{
    QLabel * main_label = new QLabel("Please Enter Tiny Code here");

    this->text_input = new QTextEdit;

    QPushButton * apply_parser = new QPushButton("Apply Parser");
    QHBoxLayout * h1 = new QHBoxLayout;
    h1->addStretch();
    h1->addWidget(apply_parser);
    QObject::connect(apply_parser, SIGNAL(clicked()),this, SLOT(show_graph_window()));

    QVBoxLayout * v1 = new QVBoxLayout;
    v1->addWidget(main_label);
    v1->addWidget(text_input);
    v1->addLayout(h1);

    this->main_window = new QWidget;
    main_window->setLayout(v1);
}

void MainWindow::show_main_window()
{
    input_vector.clear();
    this->graph_scene->clear();
    this->centralWidget()->setParent(nullptr);
    this->setCentralWidget(this->main_window);
}

void MainWindow::init_graph_window()
{
    QToolBar * bar = new QToolBar();
    bar->setStyleSheet("background: #1b1b1b");
    QAction * back_action = new QAction (QIcon(":/data/img/back.png"),"Back");
    bar->addAction(back_action);

    connect(back_action, SIGNAL(triggered()),this, SLOT(show_main_window()));


    QVBoxLayout * v1 = new QVBoxLayout;
    v1->addWidget(bar);

    this->graph = new View();
    this->graph_scene = new QGraphicsScene();
    this->graph->setScene(graph_scene);
    this->graph->setRenderHints(QPainter::Antialiasing);// make smooth line

    v1->addWidget(graph);

    this->graph_window = new QWidget;
    this->graph_window->setStyleSheet("background: #4e4e4e");
    this->graph_window->setLayout(v1);

}

void MainWindow::show_graph_window()
{
    this->input_function.reset_parser_error();
    this->input_vector.clear();
    string str_in = (this->text_input->toPlainText()).toStdString();
    Token t1;
    string type;
    string value;
    if(str_in.length() == 0)
    {
        this->print_error("Please enter list of tokens");
        this->show_main_window();
        return;
    }
    for(unsigned int i = 0; i< str_in.length(); i++)
    {
        type = "";
        value = "";
        while(str_in[i]!= ',')
        {
            if(str_in[i]!= ' ' && str_in[i]!= '\t')
            {
                value = value + str_in[i];
            }
            i++;
        }
        i++;
        while(str_in[i]!= '\n' && i< str_in.length())
        {
            if(str_in[i]!= ' ' && str_in[i]!= '\t')
            {
                type = type + str_in[i];
            }
            i++;
        }
        t1.set_token(value, type);
        input_vector.add_token(t1);
    }
    input_vector.print_vector();
    input_function.set_vector(input_vector);
    tree = input_function.program();
    if(input_function.get_parser_error())
    {
        this->print_error("Parser Error");
        this->show_main_window();
        return ;
    }
    tree.print_node();
    this->draw_node(&tree);

    this->centralWidget()->setParent(nullptr);
    this->setCentralWidget(this->graph_window);
}

MainWindow::~MainWindow()
{
    delete this->graph_window;
    delete this->main_window;
}

void MainWindow::draw_rectangle(int x, int y, QString type, QString value)
{
    QBrush redBrush(Qt::red);
    QBrush blackBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(3);
    this->graph_scene->addRect(x,y,100,70,blackPen,blackBrush);
    QGraphicsTextItem * text1 = graph_scene->addText(type);
    QGraphicsTextItem * text2 = graph_scene->addText(value);
    text1->setFont(QFont("Calibri", 14,75,false));
    text1->setPos(x + 15, y + 10);
    text2->setFont(QFont("Calibri", 14,50,false));
    text2->setPos(x + 15, y + 30);

}
void MainWindow::print_error(QString err)
{
    QMessageBox messageBox;
    messageBox.critical(this,"Error",err);
    messageBox.setFixedSize(500,200);
}
void MainWindow::draw_ellipse(int x, int y,QString type, QString value)
{
    QBrush redBrush(Qt::red);
    QBrush blackBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(3);
    this->graph_scene->addEllipse(x,y,100,70,blackPen,blackBrush);
    QGraphicsTextItem * text1 = graph_scene->addText(type);
    QGraphicsTextItem * text2 = graph_scene->addText(value);
    text1->setFont(QFont("Calibri", 14,75,false));
    text1->setPos(x + 20, y + 10);
    text2->setFont(QFont("Calibri", 14,50,false));
    text2->setPos(x + 20, y + 30);
}
void MainWindow::draw_link(int x1, int y1, int x2 , int y2)
{

    QPen blackPen(Qt::black);
    blackPen.setWidth(3);
    if(y1 == y2)
    {
        this->graph_scene->addLine(x1 + 100, y1 + 35, x2, y2 + 35, blackPen);
    }
    else
    {
        this->graph_scene->addLine(x1 + 50, y1 + 70, x2 + 50, y2, blackPen);
    }
}
void MainWindow::draw_node(TreeNode * tree)
{
    if(tree->get_token().get_type() == "READ"){
        this->draw_rectangle(tree->dim_x,tree->dim_y,"read","("+QString::fromStdString(tree->get_token().get_value())+")");
    } else if(tree->get_token().get_type() == "IF"){
        this->draw_rectangle(tree->dim_x,tree->dim_y,"if","");
    } else if(tree->get_token().get_type() == "ELSE"){
        this->draw_rectangle(tree->dim_x,tree->dim_y,"else","");
    } else if(tree->get_token().get_type() == "ASSIGN"){
        this->draw_rectangle(tree->dim_x,tree->dim_y,"assign","("+QString::fromStdString(tree->get_token().get_value())+")");
    } else if(tree->get_token().get_type() == "REPEAT"){
        this->draw_rectangle(tree->dim_x,tree->dim_y,"repeat","");
    } else if(tree->get_token().get_type() == "WRITE"){
        this->draw_rectangle(tree->dim_x,tree->dim_y,"write","");
    } else if(tree->get_token().get_type() == "OP"){
        this->draw_ellipse(tree->dim_x,tree->dim_y,"OP","("+QString::fromStdString(tree->get_token().get_value())+")");
    } else if(tree->get_token().get_type() == "IDENTIFIER"){
        this->draw_ellipse(tree->dim_x,tree->dim_y,"id","("+QString::fromStdString(tree->get_token().get_value())+")");
    } else if(tree->get_token().get_type() == "NUMBER"){
        this->draw_ellipse(tree->dim_x,tree->dim_y,"const","("+QString::fromStdString(tree->get_token().get_value())+")");
    }


    for (unsigned int i = 0; i < tree->children.size(); i++)
    {
        draw_link(tree->dim_x, tree->dim_y, tree->children[i]->dim_x , tree->children[i]->dim_y);
        draw_node(tree->children[i]);
    }
    if (tree->brother != nullptr)
    {
        draw_link(tree->dim_x, tree->dim_y, tree->brother->dim_x , tree->brother->dim_y);
        draw_node(tree->brother);
    }
}

