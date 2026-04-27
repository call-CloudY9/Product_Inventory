#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "Inventory.h"

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addProduct();
    void removeProduct();
    void updateProduct();
    void onTableSelectionChanged();

private:
    void setupUI();
    void refreshTable();
    void updateTotalLabel();

    Inventory m_inventory;

    QTableWidget *m_table;
    QLineEdit *m_idEdit;
    QLineEdit *m_priceEdit;
    QLineEdit *m_quantityEdit;
    QLabel *m_totalLabel;
    QPushButton *m_addButton;
    QPushButton *m_removeButton;
    QPushButton *m_updateButton;
};

#endif