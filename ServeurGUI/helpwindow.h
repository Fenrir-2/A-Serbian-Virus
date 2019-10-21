#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
    ~HelpWindow();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::HelpWindow *ui;
};

#endif // HELPWINDOW_H
