#ifndef APPLICGARAGEWINDOW_H
#define APPLICGARAGEWINDOW_H

#include <QMainWindow>
#include <string>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class ApplicGarageWindow; }
QT_END_NAMESPACE

class ApplicGarageWindow : public QMainWindow
{
    Q_OBJECT

public:
    ApplicGarageWindow(QWidget *parent = nullptr);
    ~ApplicGarageWindow();

    
    void setTitle(string titre);
    void setRole(int val = 3);
    void closeEvent(QCloseEvent *event);

    
    void setTableOption(int index, string code = "", string label = "", float price = -1.0);
    void clearTableOption();
    int  getIndexOptionSelectionTable() const;

    
    void addAvailableModel(string name, float basePrice);
    void clearComboBoxAvailableModels();
    int  getIndexModelSelectionCombobox() const;

    
    void addAvailableOption(string intitule, float price);
    void clearComboBoxAvailableOptions();
    int  getIndexOptionSelectionCombobox() const;

    
    void   setCurrentProjectName(string name);
    string getCurrentProjectName() const;
    void   setModel(string name, int power, int engine, float basePrice,string image);
    void   setPrice(float price);

    
    void addTupleTableEmployees(string tuple);
    void clearTableEmployees();
    int  getIndexEmployeeSelectionTable();

    
    void addTupleTableClients(string tuple);
    void clearTableClients();
    int  getIndexClientSelectionTable();

    
    void addTupleTableContracts(string tuple);
    void clearTableContracts();
    int  getIndexContractSelectionTable();

    
    void   dialogMessage(const char *title, const char *message);
    void   dialogError(const char *title, const char *message);
    string dialogPromptText(const char *title, const char *question);
    int    dialogPromptInt(const char *title, const char *question);
    float  dialogPromptFloat(const char *title, const char *question);

private slots:
    void on_actionLogout_triggered();
    void on_actionResetPassword_triggered();
    void on_pushButtonNewContract_clicked();
    void on_pushButtonDeleteContract_clicked();
    void on_pushButtonShowCar_clicked();
    void on_actionNewModel_triggered();
    void on_actionNewOption_triggered();
    void on_pushButtonSelectModel_clicked();
    void on_pushButtonAddOption_clicked();
    void on_pushButtonRemoveOption_clicked();
    void on_pushButtonReduction_clicked();
    void on_actionAddEmployee_triggered();
    void on_actionDeleteEmployeeById_triggered();
    void on_actionDeleteEmployeeByIndex_triggered();
    void on_actionAddClient_triggered();
    void on_actionDeleteClientById_triggered();
    void on_actionDeleteClientByIndex_triggered();
    void on_actionLogin_triggered();
    void on_actionQuit_triggered();
    void on_pushButtonNewProject_clicked();
    void on_pushButtonOpenProject_clicked();
    void on_pushButtonSaveProject_clicked();

private:
    Ui::ApplicGarageWindow *ui;
};
#endif 
