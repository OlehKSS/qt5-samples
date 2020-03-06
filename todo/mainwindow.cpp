#include <QDebug>
#include <QInputDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTasks()
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);

    updateStatus();
}

void MainWindow::addTask()
{
    bool ok;
    // blocking function to display a dialog
    QString name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         tr("Untitled task"),
                                         &ok);

    if (ok && !name.isEmpty())
    {
        qDebug() << "Adding new task" << "\t" << name;
        Task* task = new Task(name);
        // for the task removal (signal, slot)
        connect(task, &Task::removed, this, &MainWindow::removeTask);
        connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);
        mTasks.append(task);
        ui->tasksLayout->addWidget(task);
        updateStatus();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// slot must match the signal signature
void MainWindow::removeTask(Task* task)
{
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(0);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task*)
{
    updateStatus();
}

void MainWindow::updateStatus()
{
    int completedCount = 0;

    for (const auto& t : mTasks)
    {
        if (t->isCompleted())
        {
            completedCount++;
        }
    }
    int todoCount = mTasks.size() - completedCount;

    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completed")
                .arg(todoCount)
                .arg(completedCount));
}

