/*
Задание:
4.Создать родительский класс «Товар», а также дочерние классы «Холодильник» и «Чайник», придумать им соответствующие поля,
хранящие информацию о типе товара (для дочерних классов), стоимости единицы товара, количества товара на складе.
Добавить метод info(), выводящий полную информацию о товаре. Корректно реализовать конструкторы для всех классов.
Перегрузить оператор сложения так, чтобы к любому товару можно было прибавлять целое число, в результате чего должно
увеличиваться поле, соответствующее количеству товара. Сделать классы шаблонными чтобы стоимость единицы товара могла
быть любым подходящим типом данных.
5.Дополнить предыдущее задание. Создать вектор указателей на «Товар», поместить туда
экземпляр «Холодильника» и экземпляр «Чайника». Сделать так, чтобы при обходе вектора и вызове метода info() вызывались
методы дочерних классов. Добавить к дочерним классам динамическое поле (указатель на int), хранящее информацию об объёме,
который товар занимает на складе. В конструкторе выделить память под это поле и задать стартовое значение (очевидно,
что холодильник должен занимать больше места, чем чайник). Корректно реализовать деструкторы для всей иерархии классов.
Протестировать корректную работу классов в основной программе.

*/
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Product {
public:
   T unitPrice;
   int quantity;
   int* storageVolume;

   Product(T price, int qty, int volume) : unitPrice(price), quantity(qty) {
      storageVolume = new int(volume);
   }

   virtual void info() {
      cout << "Unit Price: " << unitPrice << ", Quantity: " << quantity << ", Storage Volume: " << *storageVolume << endl;
   }

   Product<T> operator+(int qty) {
      quantity += qty;
      return *this;
   }

   virtual ~Product() {
      delete storageVolume;
   }
};

class Fridge : public Product<double> {
public:
   Fridge(double price, int qty, int volume) : Product(price, qty, volume) {}

   void info() override {
      cout << "Fridge - ";
      Product::info();
   }
};

class Kettle : public Product<double> {
public:
   Kettle(double price, int qty, int volume) : Product(price, qty, volume) {}

   void info() override {
      cout << "Kettle - ";
      Product::info();
   }
};

int main() {
   vector<Product<double>*> products;
   products.push_back(new Fridge(1500.0, 5, 20));
   products.push_back(new Kettle(50.5, 10, 5));

   for (const auto& product : products) {
      product->info();
   }

   for (auto& product : products) {
      delete product;
   }

   return 0;
}