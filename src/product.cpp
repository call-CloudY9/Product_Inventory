#include "../include/Product.h"

Product::Product() : m_id(0), m_price(0.0), m_quantity(0) {}

Product::Product(int id, double price, int quantity)
    : m_id(id), m_price(price), m_quantity(quantity) {}

int Product::getId() const { return m_id; }
void Product::setId(int id) { m_id = id; }

double Product::getPrice() const { return m_price; }
void Product::setPrice(double price) { m_price = price; }

int Product::getQuantity() const { return m_quantity; }
void Product::setQuantity(int quantity) { m_quantity = quantity; }