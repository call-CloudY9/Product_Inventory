#ifndef INVENTORY_H
#define INVENTORY_H

#include <QList>
#include "Product.h"

class Inventory {
public:
    void addProduct(const Product &product);
    bool removeProduct(int id);
    bool updateProduct(int id, const Product &newProduct);
    QList<Product> getProducts() const;
    double totalValue() const;

private:
    QList<Product> m_products;
};

#endif