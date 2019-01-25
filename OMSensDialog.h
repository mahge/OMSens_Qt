#ifndef OMSENSDIALOG_H
#define OMSENSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include "model.h"
#include "dialogs/BaseRunSpecsDialog.h"

// Enum so we can pseudo-reference classes
enum RunType {Individual, Sweep, Vectorial};

class OMSensDialog : public QDialog
{
    Q_OBJECT
public:
    // Constructors
    OMSensDialog(Model model, QWidget *parent = nullptr);
    // Conventions
    QString helpTextPath          = "qrc:/OMSens/help/help.html";
    QString exp_specs_file_name   = "experiment_specs.json";
    QString model_specs_file_name = "model_specs.json";

    void showResultsDialog(RunType runType, QString resultsFolderPath);

private:
    // Data
    Model mActiveModel;
    QString mOMSensPath;
    QString mPythonBinPath;
    // GUI
    QLabel      *mpOMSensPathLabel;
    QLabel      *mpOMSensPathValue;
    QPushButton *mpOMSensPathBrowseButton;
    QLabel      *mpPythonBinLabel;
    QLabel      *mpPythonBinValue;
    QPushButton *mpPythonBinBrowseButton;
    QFrame      *mpHorizontalLineOne;
    QPushButton *mpIndivButton;
    QPushButton *mpSweepButton;
    QPushButton *mpVectButton;
    QFrame      *mpHorizontalLineTwo;
    QPushButton *mpHelpButton; // Not shown for now
    QPushButton *mpLoadExperimentButton;
    // Auxs
    QJsonDocument readJsonFile(QString resultsFolderPath);
    bool runProcessAndShowProgress(QString scriptDirPath, QString command);
    QString createTimestampDir(QString destFolderPath);
    QString writeJsonToDisk(QString file_path, QJsonDocument runSpecifications);
    QString createResultsFolder(QString timeStampFolderPath);
    QString dirPathForFilePath(QString scriptPath);
    QString commandCallFromPaths(QString scriptPath, QString pythonBinPath, QString jsonSpecsPath, QString resultsFolderPath);
    bool defineAndRunCommand(QString scriptDirPath, QString jsonSpecsPath, QString resultsFolderPath, QString scriptPath, QString pythonBinPath);
    void runNewOMSensAnalysis(RunType runType);
    QString progressDialogTextForCurrentTime();
    void runAnalysisAndShowResult(BaseRunSpecsDialog *runSpecsDialog, RunType runType, Model model);

signals:

public slots:
  void runIndivSensAnalysis();
  void runMultiParameterSweep();
  void runVectorialSensAnalysis();
  void openSensAnalysisResult();
  void openSensAnalysisImage();
  void launchOMSensBackendChooseFolderDialog();
  void launchPythonBinChooseFolderDialog();
  void helpDialog();
  void loadExperimentFileDialog();
};

#endif // OMSENSDIALOG_H
