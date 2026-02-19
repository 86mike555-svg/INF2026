#ifndef ITEM_h
#define ITEM_h

#include "useful-types.h"

class IItem {
  protected:
    enum ItemType {
        NoType,
        Car,
    };
    virtual const ItemType type() = 0;

    Percent inflation_coefficient;
    RUB_Kopecks basic_price;

  public:
    virtual RUB_Kopecks pure_value() const = 0;
    RUB_Kopecks value() const { return pure_value() * inflation_coefficient; }

    virtual RUB_Kopecks tax() const = 0;
    virtual void inflate(Percent inflation) {
        inflation_coefficient += (inflation / 100.0);
    }

    virtual void use() = 0;
    virtual RUB_Kopecks restoring_price() const = 0;
    virtual void restore() = 0;

    virtual ~IItem() = 0;
};

class Car : public IItem {
    String name;
    Kilometers mileage;
    Months age;
    Percent wear;

  public:
    const ItemType type() { return ItemType::Car; }

    Car(String name, RUB_Kopecks price)
        : name(name), mileage(0), age(0), wear(0.0) {
        basic_price = price;
        inflation_coefficient = 0;
    }

    RUB_Kopecks pure_value() const {
        RUB_Kopecks disvalue = 1'750'000'00 * (mileage / 150'000) -
                               500'000'00 * (age / 15) -
                               (Integer)(2'000'000'00 * (wear / 100.0));

        return (basic_price < disvalue ? 0 : basic_price - disvalue);
    }

    RUB_Kopecks tax() const { return 750'00 * (wear / 10.0); }

    void use() {
        mileage += 100;
        age += 1;
        wear += 3.0 * (mileage / 100.0) + 2.75 * (age / 12.0);
    }

    RUB_Kopecks restoring_price() const {
        return (2'500'00 * (wear / 10.0) + 250'00 * (age / 12.0) +
                10'00 * (mileage)) *
               inflation_coefficient;
    }

    void restore() { wear = 0.0; }

    ~Car() {}
};

#endif
