#ifndef BARTABSONG_H
#define BARTABSONG_H


#include <QWidget>
#include <QFileDialog>
#include <QVector>
#include <QColor>


namespace Ui {
class BARTabSong;
}

class BARTabSong : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARTabSong(QWidget *parent = 0);
    ~BARTabSong();
    
private slots:


    void on_buttonAddPatternBar_clicked();

private:
    Ui::BARTabSong *ui;
    QVector<QColor> patternBarColorList;
    int nbPatternCreated;
};

#endif // BARTABSONG_H
