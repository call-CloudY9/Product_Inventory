#include "../include/Inventory.h"

void Inventory::addProduct(const Product &product) {
    for (const Product &p : m_products) {
        if (p.getId() == product.getId())
            return;
    }
    m_products.append(product);
}

bool Inventory::removeProduct(int id) {
    for (int i = 0; i < m_products.size(); ++i) {
        if (m_products[i].getId() == id) {
            m_products.removeAt(i);
            return true;
        }
    }
    return false;
}

bool Inventory::updateProduct(int id, const Product &newProduct) {
    for (int i = 0; i < m_products.size(); ++i) {
        if (m_products[i].getId() == id) {
            m_products[i] = newProduct;
            return true;
        }
    }
    return false;
}

QList<Product> Inventory::getProducts() const {
    return m_products;
}

double Inventory::totalValue() const {
    double total = 0.0;
    for (const Product &p : m_products) {
        total += p.getPrice() * p.getQuantity();
    }
    return total;
}