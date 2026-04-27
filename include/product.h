#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product {
public:
    Product();
    Product(int id, double price, int quantity);

    int getId() const;
    void setId(int id);

    double getPrice() const;
    void setPrice(double price);

    int getQuantity() const;
    void setQuantity(int quantity);

private:
    int m_id;
    double m_price;
    int m_quantity;
};

#endif