#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Inscription;
}
QT_END_NAMESPACE

class Inscription : public QMainWindow
{
    Q_OBJECT

public:
    Inscription(QWidget *parent = nullptr);
    ~Inscription();

private slots:
    void on_actionS_inscrire_triggered();

    void on_actionChercher_triggered();

    void on_actionLister_triggered();

    void on_pushButton_clicked();

    void on_actionSe_desabonner_triggered();

    void on_pushButton_5_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::Inscription *ui;
};
#endif // INSCRIPTION_H
