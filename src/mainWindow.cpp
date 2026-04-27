#include "../include/MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    refreshTable();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    m_table = new QTableWidget(0, 3, this);
    m_table->setHorizontalHeaderLabels({"ID", "Цена", "Количество"});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_table, &QTableWidget::itemSelectionChanged,
            this, &MainWindow::onTableSelectionChanged);
    mainLayout->addWidget(m_table);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    m_idEdit = new QLineEdit(this);
    m_idEdit->setPlaceholderText("ID (уникальный)");
    m_priceEdit = new QLineEdit(this);
    m_priceEdit->setPlaceholderText("Цена");
    m_quantityEdit = new QLineEdit(this);
    m_quantityEdit->setPlaceholderText("Количество");
    inputLayout->addWidget(m_idEdit);
    inputLayout->addWidget(m_priceEdit);
    inputLayout->addWidget(m_quantityEdit);
    mainLayout->addLayout(inputLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_addButton = new QPushButton("Добавить", this);
    m_removeButton = new QPushButton("Удалить", this);
    m_updateButton = new QPushButton("Изменить", this);
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_removeButton);
    buttonLayout->addWidget(m_updateButton);
    mainLayout->addLayout(buttonLayout);

    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(m_removeButton, &QPushButton::clicked, this, &MainWindow::removeProduct);
    connect(m_updateButton, &QPushButton::clicked, this, &MainWindow::updateProduct);

    m_totalLabel = new QLabel("Общая стоимость: 0.00", this);
    QFont font = m_totalLabel->font();
    font.setBold(true);
    m_totalLabel->setFont(font);
    mainLayout->addWidget(m_totalLabel);

    m_removeButton->setEnabled(false);
    m_updateButton->setEnabled(false);
}

void MainWindow::refreshTable() {
    m_table->setRowCount(0);
    QList<Product> products = m_inventory.getProducts();
    for (const Product &p : products) {
        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row, 0, new QTableWidgetItem(QString::number(p.getId())));
        m_table->setItem(row, 1, new QTableWidgetItem(QString::number(p.getPrice(), 'f', 2)));
        m_table->setItem(row, 2, new QTableWidgetItem(QString::number(p.getQuantity())));
    }
    updateTotalLabel();
}

void MainWindow::updateTotalLabel() {
    double total = m_inventory.totalValue();
    m_totalLabel->setText(QString("Общая стоимость: %1").arg(total, 0, 'f', 2));
}

void MainWindow::onTableSelectionChanged() {
    bool hasSelection = !m_table->selectedItems().isEmpty();
    m_removeButton->setEnabled(hasSelection);
    m_updateButton->setEnabled(hasSelection);

    if (hasSelection) {
        int row = m_table->currentRow();
        m_idEdit->setText(m_table->item(row, 0)->text());
        m_priceEdit->setText(m_table->item(row, 1)->text());
        m_quantityEdit->setText(m_table->item(row, 2)->text());
    } else {
        m_idEdit->clear();
        m_priceEdit->clear();
        m_quantityEdit->clear();
    }
}

void MainWindow::addProduct() {
    bool ok;
    int id = m_idEdit->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный положительный ID.");
        return;
    }

    double price = m_priceEdit->text().toDouble(&ok);
    if (!ok || price < 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректную цену (неотрицательное число).");
        return;
    }

    int quantity = m_quantityEdit->text().toInt(&ok);
    if (!ok || quantity < 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректное количество (неотрицательное целое).");
        return;
    }

    for (const Product &p : m_inventory.getProducts()) {
        if (p.getId() == id) {
            QMessageBox::warning(this, "Ошибка", "Продукт с таким ID уже существует.");
            return;
        }
    }

    Product newProduct(id, price, quantity);
    m_inventory.addProduct(newProduct);
    refreshTable();

    m_idEdit->clear();
    m_priceEdit->clear();
    m_quantityEdit->clear();
}

void MainWindow::removeProduct() {
    int row = m_table->currentRow();
    if (row < 0) return;

    int id = m_table->item(row, 0)->text().toInt();
    m_inventory.removeProduct(id);
    refreshTable();
}

void MainWindow::updateProduct() {
    int row = m_table->currentRow();
    if (row < 0) return;

    int oldId = m_table->item(row, 0)->text().toInt();

    bool ok;
    int newId = m_idEdit->text().toInt(&ok);
    if (!ok || newId <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный положительный ID.");
        return;
    }

    double price = m_priceEdit->text().toDouble(&ok);
    if (!ok || price < 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректную цену (неотрицательное число).");
        return;
    }

    int quantity = m_quantityEdit->text().toInt(&ok);
    if (!ok || quantity < 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректное количество (неотрицательное целое).");
        return;
    }

    if (newId != oldId) {
        for (const Product &p : m_inventory.getProducts()) {
            if (p.getId() == newId) {
                QMessageBox::warning(this, "Ошибка", "Продукт с таким ID уже существует.");
                return;
            }
        }
    }

    Product updatedProduct(newId, price, quantity);
    if (m_inventory.updateProduct(oldId, updatedProduct)) {
        refreshTable();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить продукт.");
    }
}