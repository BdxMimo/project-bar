#include "barexportdialog.h"
#include "ui_barexportdialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QCloseEvent>

/**
 * @brief This class allows the final export of the song (conversion into standard audio format).
 * When clicking the export button in the "song" tab, dialog pops up to set parameters for exportation of the song.
 */

/**
 * @brief Default constructor.
 * @param[in] parent widget
 * @param[in] window flag
 */
BARExportDialog::BARExportDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent,f),
    ui(new Ui::barexportdialog)
{
    ui->setupUi(this);
    initialSetup();
}

/**
 * @brief Default destructor.
 */
BARExportDialog::~BARExportDialog()
{
    delete ui;
}

/**
 * @brief Overrides the standard QCloseEvent function and uses this one instead.
 * @param[in] the CloseEvent event
 */
void BARExportDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    closeCleanUp();
    event->accept();
}

/**
 * @brief Sets up the gui with appropriate buttons and labels. Also creates a signal connecting
 * the lineEdit with the function textChangedSlot().
 */
void BARExportDialog::initialSetup()
{
    ui->fileNameLineEdit->setText("");
    ui->fileNameLineEdit->setFocus();
    QObject::connect(ui->fileNameLineEdit,SIGNAL(textChanged(QString)),this,SLOT(textChangedSlot(QString)));
    ui->savedLabel->setText("File not yet saved...");
    ui->saveButton->setEnabled(false);
    this->isModal();
    this->setWindowTitle("Save File Dialog");
}

/**
 * @brief Enables or disables the save button according to the appropriateness of the text in the lineEdit field.
 * @param[in] the text entered in the lineEdit.
 */
void BARExportDialog::textChangedSlot(QString text)
{
    if(text!="") {
        ui->saveButton->setEnabled(true);
        return;
    }
    ui->saveButton->setEnabled(false);
}

/**
 * @brief Resets each field in order to close the dialog.
 */
void BARExportDialog::closeCleanUp()
{
    ui->fileNameLineEdit->setEnabled(true);
    ui->saveButton->setEnabled(false);
    ui->fileTypeComboBox->setEnabled(true);
    ui->fileNameLineEdit->setText("");
    ui->savedLabel->setText("File not yet saved...");
}

/**
 * @brief Activates when the user clicks the "Back" button.
 */
void BARExportDialog::on_backButton_clicked()
{
    closeCleanUp();
    this->close();
}

/**
 * @brief Activates when the user clicks the "Save" button. Saves the filename and the filetype in the variables
 * fileName and fileType which are to be used in the saving process.
 */
void BARExportDialog::on_saveButton_clicked()
{
    fileName=ui->fileNameLineEdit->text();
    fileType=ui->fileTypeComboBox->currentText();
    ui->fileNameLineEdit->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->fileTypeComboBox->setEnabled(false);
    ui->savedLabel->setText("File saved: " + fileName + fileType);
}
