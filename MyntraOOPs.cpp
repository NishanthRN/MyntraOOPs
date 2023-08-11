#include <iostream>
#include <excpt.h>
#include <vector>
#include <utility>

using namespace std;

int order_count = 0;
int payId = 0;
int cust_count = 0;
int seller_count = 0;

class Error
{
    const char *message;

public:
    Error(const char *msg)
    {
        message = msg;
    }
    void what()
    {
        cout << message << endl;
    }
};

enum ItemType
{
    Men_Shoe,
    Men_Clothing,
    Women_Shoe,
    Women_Clothing,
    electronics
};

class Item
{
protected:
    int id, sellerID;
    double price;

public:
    Item(int a, int b, double c) : id(a), sellerID(b), price(c) {}
    double getPrice()
    {
        return price;
    }
    int getID()
    {
        return id;
    }
    static Item *createItem(ItemType type, int a, int b, double c, string d, int e, string f);
    virtual void printItem(){};
};

class MenShoe : public Item
{
private:
    string brand;
    int size;
    string type;

public:
    MenShoe(int a, int b, double c, string d, int e, string f) : Item(a, b, c)
    {
        brand = d;
        size = e;
        type = f;
    }
    void printItem()
    {
        cout << "Id : " << id << endl;
        cout << "Brand : " << brand << endl;
        cout << "Type : " << type << endl;
        cout << "Size : " << size << endl;
        cout << "Price : " << price << endl;
    }
};

class WomenShoe : public Item
{
private:
    string brand;
    int size;
    string type;

public:
    WomenShoe(int a, int b, double c, string d, int e, string f) : Item(a, b, c)
    {
        brand = d;
        size = e;
        type = f;
    }
    void printItem()
    {
        cout << "Id : " << id << endl;
        cout << "Brand : " << brand << endl;
        cout << "Type : " << type << endl;
        cout << "Size : " << size << endl;
        cout << "Price : " << price << endl;
    }
};

class MenClothing : public Item
{
private:
    string brand;
    int size;
    string type;

public:
    MenClothing(int a, int b, double c, string d, int e, string f) : Item(a, b, c)
    {
        brand = d;
        size = e;
        type = f;
    }
    void printItem()
    {
        cout << "ID : " << id << endl;
        cout << "Brand : " << brand << endl;
        cout << "Type : " << type << endl;
        cout << "Size : " << size << endl;
        cout << "Price : " << price << endl;
    }
};

class WomenClothing : public Item
{
private:
    string brand;
    int size;
    string type;

public:
    WomenClothing(int a, int b, double c, string d, int e, string f) : Item(a, b, c)
    {
        brand = d;
        size = e;
        type = f;
    }
    void printItem()
    {
        cout << "ID : " << id << endl;
        cout << "Brand : " << brand << endl;
        cout << "Type : " << type << endl;
        cout << "Size : " << size << endl;
        cout << "Price : " << price << endl;
    }
};

class Electronics : public Item
{
private:
    string company, description;

public:
    Electronics(int a, int b, double c, string d, string e) : Item(a, b, c)
    {
        company = d;
        description = e;
    }
    void printItem()
    {
        cout << "ID : " << id << endl;
        cout << "Price : " << price << endl;
        cout << "Company : " << company << endl;
        cout << "Description : " << description << endl;
    }
};

Item *Item::createItem(ItemType type, int a, int b, double c, string d, int e, string f)
{
    if (type == Men_Shoe)
        return new MenShoe(a, b, c, d, e, f);
    else if (type == Men_Clothing)
        return new MenClothing(a, b, c, d, e, f);
    else if (type == Women_Clothing)
        return new WomenClothing(a, b, c, d, e, f);
    else if (type == Women_Shoe)
        return new WomenShoe(a, b, c, d, e, f);
    else if (type == electronics)
        return new Electronics(a, b, c, d, f);
    return NULL;
}

enum PaymentType
{
    cod,
    Debit_Card,
    Credit_Card
};

class PaymentMethod
{
private:
    int paymentId;
    string status;

public:
    PaymentMethod(string a) : status(a)
    {
        payId++;
        paymentId = (payId);
    }
    static PaymentMethod *createPayment(PaymentType paytype, string statu, string loc, int acc, double bal, string barn, long long cardno, int cvv, double clim);
    virtual void printPayment() = 0;
    int getID()
    {
        return paymentId;
    }
    virtual void debitAmt(double amt) {}
};

class COD : public PaymentMethod
{
private:
    string location;

public:
    COD(string b, string loc) : PaymentMethod(b)
    {
        location = loc;
    }
    void printPayment()
    {
        cout << "Payment ID : " << getID() << endl;
        cout << "Location : " << location << endl;
    }
};

class DebitCard : public PaymentMethod
{
private:
    int accNo;
    double accBal;
    string branch;
    long long cardNo;
    int cvv;

public:
    DebitCard(string statu, int acc, double bal, string bran, long long card, int cv) : PaymentMethod(statu)
    {
        accNo = acc;
        accBal = bal;
        branch = bran;
        cardNo = card;
        cvv = cv;
    }
    void debitAmt(double amt)
    {
        if ((accBal - amt) < 1000)
            throw new Error("Insufficient balance");
        else
            accBal -= amt;
    }
    void printPayment()
    {
        cout << "Payment ID : " << getID() << endl;
        cout << "Account Number : " << accNo << endl;
        cout << "Account Balance : " << accBal << endl;
        cout << "Branch : " << branch << endl;
        cout << "Card no : " << cardNo << endl;
    }
};

class CreditCard : public PaymentMethod
{
private:
    int accNo;
    double accBal;
    string branch;
    long long cardNo;
    int cvv;
    double credit_limit;

public:
    CreditCard(string statu, int acc, double bal, string bran, long long card, int cv, double clim) : PaymentMethod(statu)
    {
        accNo = acc;
        accBal = bal;
        branch = bran;
        cardNo = card;
        cvv = cv;
        credit_limit = clim;
    }
    void debitAmt(double amt)
    {
        cout << "In credit" << endl;
        if ((accBal - amt) < 0 && (accBal - amt) < (0 - credit_limit))
            throw new Error("Credit Limit exceeded");
        else
            accBal -= amt;
    }
    void printPayment()
    {
        cout << "Payment ID : " << getID() << endl;
        cout << "Account Number : " << accNo << endl;
        cout << "Account Balance : " << accBal << endl;
        cout << "Branch : " << branch << endl;
        cout << "Credit limit : " << credit_limit << endl;
    }
};

PaymentMethod *PaymentMethod::createPayment(PaymentType paytype, string statu, string loc, int acc, double bal, string barn, long long cardno, int cvv, double clim)
{
    if (paytype == cod)
        return new COD(statu, loc);
    else if (paytype == Debit_Card)
        return new DebitCard(statu, acc, bal, barn, cardno, cvv);
    else if (paytype == Credit_Card)
        return new CreditCard(statu, acc, bal, barn, cardno, cvv, clim);
    else
        return NULL;
}

class Cart
{
    vector<Item *> items;
    friend class Order;
    double virtualTotal;

public:
    Cart()
    {
        virtualTotal = 0;
    }
    void addItem(Item *i1)
    {
        items.push_back(i1);
        virtualTotal += i1->getPrice();
        cout << "Item added to cart successfully" << endl;
    }
    void deleteItem(int id)
    {
        for (int i = 0; i < items.size(); i++)
            if ((items.at(i)->getID()) == id)
            {
                items.erase(items.begin() + i);
                cout << "Item removed from cart successfully" << endl;
            }
    }
    void printCart()
    {
        for (int i = 0; i < items.size(); i++)
            items.at(i)->printItem();
    }
    void clearCart()
    {
        items.clear();
        cout << "Cart cleared" << endl;
    }
};

class Order
{
private:
    int custId;
    int orderId;
    vector<Item *> items;
    double total;
    PaymentMethod *pay;

public:
    Order(int a)
    {
        custId = a;
        order_count++;
        orderId = order_count;
        total = 0;
    }
    int getOrderId()
    {
        return orderId;
    }

    int buy(Cart c1)
    {
        items = c1.items;
        if (items.empty())
        {
            cout << "Cart is empty" << endl;
            return 1;
        }
        for (int i = 0; i < items.size(); i++)
        {
            total += items.at(i)->getPrice();
        }
        cout << "Your total : " << total << endl;
        int method = 0;
        do
        {
            cout << "Enter the payment method" << endl;
            cout << "1.Credit card" << endl;
            cout << "2.Debit card" << endl;
            cout << "3.COD" << endl;
            cin >> method;
        } while (method > 4 || method < 1);
        string branch, loc;
        int acc, cvv;
        long long cardNo;
        double bal, creditLimit;
        PaymentType type;
        if (method == 1 || method == 2)
        {
            cout << "Bank account number" << endl;
            cin >> acc;
            cout << "Enter balance" << endl;
            cin >> bal;
            cout << "Enter branch" << endl;
            cin >> branch;
            cout << "Enter card no" << endl;
            cin >> cardNo;
            cout << "Enter cvv" << endl;
            cin >> cvv;
            if (method == 1)
            {
                type = Credit_Card;
                cout << "Enter credit limit" << endl;
                cin >> creditLimit;
                pay = pay->createPayment(type, "Processing", "", acc, bal, branch, cardNo, cvv, creditLimit);
            }
            else if (method == 2)
            {
                type = Debit_Card;
                pay = pay->createPayment(type, "Processing", "", acc, bal, branch, cardNo, cvv, 0);
            }
            try
            {
                pay->debitAmt(total);
            }
            catch (Error &e1)
            {
                e1.what();
                return 1;
            }
        }
        else if (method == 3)
        {
            type = cod;
            cout << "Enter location" << endl;
            cin >> loc;
            pay = pay->createPayment(type, "Processing", loc, 0, 0.0, "", 0, 0, 0);
        }

        cout << "Order added" << endl;
        return 0;
    }
    void printOrder()
    {
        cout << "Order Id : " << orderId << endl;
        for (int i = 0; i < items.size(); i++)
            items.at(i)->printItem();
        cout << "Total : " << total << endl;
        pay->printPayment();
    }
    ~Order()
    {
        order_count--;
    }
};

class Myntra
{
    vector<Item *> items;
    vector<Order *> orders;
    static Myntra *inst;
    Myntra() {}

public:
    Myntra *getMyntra()
    {
        if (inst == NULL)
        {
            inst = new Myntra;
        }
        return inst;
    }
    void addItemMyntra(Item *i1)
    {
        items.push_back(i1);
        cout << "Item added to Myntra" << endl;
    }
    void printAllItem()
    {
        if (items.empty())
        {
            cout << "Empty Items" << endl;
            return;
        }
        for (int i = 0; i < items.size(); i++)
            items.at(i)->printItem();
    }
    Item *getItem(int ID)
    {
        for (int i = 0; i < items.size(); i++)
            if ((items.at(i)->getID()) == ID)
                return items.at(i);
        return NULL;
    }
    void addOrder(Order *o1)
    {
        orders.push_back(o1);
        cout << "Order added to myntra" << endl;
    }

    void printOrder(int orderID)
    {
        for (int i = 0; i < orders.size(); i++)
            if ((orders.at(i)->getOrderId()) == orderID)
            {
                orders.at(i)->printOrder();
                return;
            }
        cout << "Invalid order ID" << endl;
    }
};

Myntra *Myntra::inst = NULL;

class Customer
{
    int custId;
    string name, location, email;
    long long phone;
    Cart cart;
    Item *item;
    Myntra *myntra;

public:
    Customer(string a, string b, string c, long long d)
    {
        custId = (++cust_count);
        name = a;
        location = b;
        email = c;
        phone = d;
        myntra = myntra->getMyntra();
    }
    void addItemToCart(int ID)
    {
        item = myntra->getItem(ID);
        if (item == NULL)
        {
            cout << "Invalid Item ID" << endl;
            return;
        }
        cart.addItem(item);
    }
    void removeItemCart(int ID)
    {
        cart.deleteItem(ID);
    }

    int getCustId()
    {
        return custId;
    }

    void clearCart()
    {
        cart.clearCart();
    }

    void printCart()
    {
        cart.printCart();
    }

    void buy()
    {
        Order *o1 = new Order(custId);
        int status;
        status = o1->buy(cart);
        if (status)
        {
            delete o1;
            return;
        }
        cart.clearCart();
        myntra->addOrder(o1);
    }
};

class Seller
{
    int sellerID;
    string name, location, email;
    long long phone;
    Item *item;
    Myntra *myntra;

public:
    Seller(string a, string b, string c, long long d)
    {
        sellerID = (++seller_count);
        name = a;
        location = b;
        email = c;
        phone = d;
        myntra = myntra->getMyntra();
    }
    int getSellId()
    {
        return sellerID;
    }

    void addItem()
    {
        int itemId, choice = 6;
        double price;
        ItemType type;
        string brand, type2;
        int size = 0;
        cout << "Enter item Id : ";
        cin >> itemId;
        cout << "Enter price : ";
        cin >> price;
        do
        {
            cout << "Enter item type : " << endl;
            cout << "1. Men_Shoe : " << endl;
            cout << "2. Men_Clothing : " << endl;
            cout << "3. Women_Shoe : " << endl;
            cout << "4. Women_Clothing : " << endl;
            cout << "5. Electronics : " << endl;
            cin >> choice;
        } while (choice > 5 || choice < 1);
        if (choice == 1)
            type = Men_Shoe;
        if (choice == 2)
            type = Men_Clothing;
        if (choice == 3)
            type = Women_Shoe;
        if (choice == 4)
            type = Women_Clothing;
        if (choice == 5)
            type = electronics;
        cout << "Enter brand : ";
        cin >> brand;
        if (choice != 5)
        {
            cout << "Enter size : ";
            cin >> size;
        }
        cout << "Enter description : ";
        cin >> type2;
        Item *item1 = item->createItem(type, itemId, sellerID, price, brand, size, type2);
        myntra->addItemMyntra(item1);
    }
};

int main()
{
    Myntra *bin = bin->getMyntra();
    vector<Customer> customers;
    vector<Seller> sellers;
    int userID, itemID, orderID, choice, flag;
    string name, loc, email;
    long long phone;
    while (1)
    {
        cout << endl
             << endl;
        cout << "1. New customer" << endl;
        cout << "2. New seller" << endl;
        cout << "3. Add item" << endl;
        cout << "4. Add item to cart" << endl;
        cout << "5. Remove item from cart" << endl;
        cout << "6. Clear cart" << endl;
        cout << "7. Buy items in cart" << endl;
        cout << "8. Order history" << endl;
        cout << "9. Print all items" << endl;
        cout << "10. Print item in cart" << endl;
        cout << "11. Exit" << endl;
        cin >> choice;
        cout << endl
             << endl;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter name " << endl;
            cin >> name;
            cout << "Enter email" << endl;
            cin >> email;
            cout << "Enter phone number" << endl;
            cin >> phone;
            cout << "Enter location " << endl;
            cin >> loc;
            Customer obj(name, email, loc, phone);
            customers.push_back(obj);
            cout << "Your customer ID is : " << cust_count << endl;
            break;
        }
        case 2:
        {
            cout << "Enter name " << endl;
            cin >> name;
            cout << "Enter email" << endl;
            cin >> email;
            cout << "Enter phone number" << endl;
            cin >> phone;
            cout << "Enter location " << endl;
            cin >> loc;
            Seller obj(name, email, loc, phone);
            sellers.push_back(obj);
            cout << "Your seller ID is : " << seller_count << endl;
            break;
        }
        case 3:
        {
            cout << "Enter seller ID : ";
            cin >> userID;
            flag = 1;
            for (int i = 0; i < sellers.size(); i++)
                if ((sellers[i].getSellId()) == userID)
                {
                    sellers[i].addItem();
                    flag = 0;
                }
            if (flag)
                cout << "Invalid seller ID" << endl;
            break;
        }
        case 4:
        {
            cout << "Enter customer ID : ";
            cin >> userID;
            flag = 1;
            for (int i = 0; i < customers.size(); i++)
                if ((customers[i].getCustId()) == userID)
                {
                    cout << "Enter item ID : ";
                    cin >> itemID;
                    customers[i].addItemToCart(itemID);
                    flag = 0;
                }
            if (flag)
                cout << "Customer not found" << endl;
            break;
        }
        case 5:
        {
            cout << "Enter customer ID : ";
            cin >> userID;
            flag = 1;
            for (int i = 0; i < customers.size(); i++)
                if ((customers[i].getCustId()) == userID)
                {
                    cout << "Enter item ID : ";
                    cin >> itemID;
                    customers[i].removeItemCart(itemID);
                    flag = 0;
                }
            if (flag)
                cout << "Customer not found" << endl;
            break;
        }
        case 6:
        {
            cout << "Enter customer ID : ";
            cin >> userID;
            flag = 1;
            for (int i = 0; i < customers.size(); i++)
                if ((customers[i].getCustId()) == userID)
                {
                    customers[i].clearCart();
                    flag = 0;
                }
            if (flag)
                cout << "Customer not found" << endl;
            break;
        }
        case 7:
        {
            cout << "Enter customer ID : ";
            cin >> userID;
            flag = 1;
            for (int i = 0; i < customers.size(); i++)
                if ((customers[i].getCustId()) == userID)
                {
                    customers[i].buy();
                    flag = 0;
                }
            if (flag)
                cout << "Customer not found" << endl;
            break;
        }
        case 8:
        {
            cout << "Enter customer ID : ";
            cin >> userID;
            flag = 1;
            for (int i = 0; i < customers.size(); i++)
                if ((customers[i].getCustId()) == userID)
                {
                    cout << "Enter order ID : ";
                    cin >> orderID;
                    bin->printOrder(orderID);
                    flag = 0;
                }
            if (flag)
                cout << "Customer not found" << endl;
            break;
        }
        case 9:
        {
            bin->printAllItem();
            break;
        }
        case 10:
        {
            cout << "Enter customer ID : ";
            cin >> userID;
            flag = 1;
            for (int i = 0; i < customers.size(); i++)
                if ((customers[i].getCustId()) == userID)
                {
                    customers[i].printCart();
                    flag = 0;
                }
            if (flag)
                cout << "Customer not found" << endl;
            break;
        }
        case 11:
            exit(0);
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
    return 0;
}

/*
int main()
{
    PaymentType type=Credit_Card;
    PaymentMethod *pay;
    pay->createPayment(type,"processing","",123,4500,"Navanagar",12345,233,10000);
    pay->printPayment();
}
*/
/*
int main()
{
    PaymentMethod *pay;
    CreditCard c1("processing",123,4500,"Navanager",12345,233,10000);
    pay=&c1;
    pay->printPayment();
}
*/
