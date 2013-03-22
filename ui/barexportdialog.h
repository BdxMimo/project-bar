#ifndef BAREXPORTDIALOG_H
#define BAREXPORTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QCloseEvent>

/**
 * @brief This class allows the final export of the song (conversion into standard audio format).
 * When clicking the export button in the "song" tab, dialog pops up to set parameters for exportation of the song.
 */

namespace Ui {
class barexportdialog;
}

class BARExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BARExportDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~BARExportDialog();

private slots:
    void on_backButton_clicked();
    void on_saveButton_clicked();
    void closeCleanUp();
    void textChangedSlot(QString text);
    void initialSetup();
    void closeEvent(QCloseEvent *event);

private:
    Ui::barexportdialog *ui;
    QPushButton* saveButton; /**< button that triggers the exportation procedure itself (creation of the file). */
    QPushButton* backButton; /**< button to leave the dialog box and return to the main window. */
    QComboBox* fileTypeComboBox; /**< list in which the user select the desired format to export the song. */
    QString fileName; /**< desired name for the file (selected by the user). */
    QString fileType; /**< stores the type of the file selected in the list by the user. */
};

#endif // BAREXPORTDIALOG_H
