#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================= ENUMS =================

enum Category {
    ELECTRONICS,
    CLOTHING,
    FOOD,
    BOOKS
};

enum OrderStatus {
    PENDING,
    CONFIRMED,
    DELIVERED,
    CANCELLED
};

enum PaymentStatus {
    PAYMENT_PENDING,
    PAYMENT_SUCCESS,
    PAYMENT_FAILED
};

enum PaymentMethod {
    CREDIT_CARD,
    UPI,
    CASH
};

// ================= UNION =================

union PaymentInfo {
    char lastFourDigits[5];
    char upiID[50];

    PaymentInfo() {}
    ~PaymentInfo() {}
};

// ================= PRODUCT CLASS =================

class Product {
private:
    int productID;
    string name;
    double price;
    int stock;
    Category category;

public:
    // Constructor
    Product(int id, string n, double p, int s, Category c) {
        productID = id;
        name = n;
        price = p;
        stock = s;
        category = c;
    }

    int getProductID() {
        return productID;
    }

    double getPrice() {
        return price;
    }

    void displayProduct() {
        cout << "\nProduct ID: " << productID;
        cout << "\nName: " << name;
        cout << "\nPrice: Rs. " << price;
        cout << "\nStock: " << stock;

        cout << "\nCategory: ";

        switch (category) {
            case ELECTRONICS:
                cout << "Electronics";
                break;

            case CLOTHING:
                cout << "Clothing";
                break;

            case FOOD:
                cout << "Food";
                break;

            case BOOKS:
                cout << "Books";
                break;
        }

        cout << "\n";
    }

    void updateStock(int quantity) {
        if (stock + quantity < 0) {
            cout << "Error: Insufficient stock!\n";
            return;
        }

        stock += quantity;
        cout << "Stock updated successfully.\n";
    }

    bool checkAvailability(int quantity) {
        return stock >= quantity;
    }
};

// ================= CUSTOMER CLASS =================

class Customer {
private:
    int customerID;
    string name;
    string email;
    string phone;
    string address;

public:
    // Constructor
    Customer(int id, string n, string e, string p, string a) {
        customerID = id;
        name = n;
        email = e;
        phone = p;
        address = a;
    }

    int getCustomerID() {
        return customerID;
    }

    void displayCustomer() {
        cout << "\nCustomer ID: " << customerID;
        cout << "\nName: " << name;
        cout << "\nEmail: " << email;
        cout << "\nPhone: " << phone;
        cout << "\nAddress: " << address << "\n";
    }

    void updateCustomer(string n, string e, string p, string a) {
        name = n;
        email = e;
        phone = p;
        address = a;

        cout << "Customer details updated successfully.\n";
    }
};

// ================= ORDER STRUCT =================

struct Order {
    int orderID;
    int customerID;
    double totalAmount;
    OrderStatus orderStatus;
    PaymentStatus paymentStatus;

    Order(int oid, int cid, double amount) {
        orderID = oid;
        customerID = cid;
        totalAmount = amount;
        orderStatus = PENDING;
        paymentStatus = PAYMENT_PENDING;
    }
};

// ================= HELPER FUNCTIONS =================

string getOrderStatus(OrderStatus status) {
    switch (status) {
        case PENDING:
            return "Pending";

        case CONFIRMED:
            return "Confirmed";

        case DELIVERED:
            return "Delivered";

        case CANCELLED:
            return "Cancelled";
    }

    return "Unknown";
}

string getPaymentStatus(PaymentStatus status) {
    switch (status) {
        case PAYMENT_PENDING:
            return "Payment Pending";

        case PAYMENT_SUCCESS:
            return "Payment Successful";

        case PAYMENT_FAILED:
            return "Payment Failed";
    }

    return "Unknown";
}

// ================= MAIN =================

int main() {

    vector<Product> products;
    vector<Customer> customers;
    vector<Order> orders;

    int nextOrderID = 1;

    // Sample Products
    products.push_back(
        Product(101, "Laptop", 55000, 5, ELECTRONICS)
    );

    products.push_back(
        Product(102, "T-Shirt", 999, 10, CLOTHING)
    );

    products.push_back(
        Product(103, "C++ Book", 599, 7, BOOKS)
    );

    // Sample Customer
    customers.push_back(
        Customer(
            1,
            "Prashant",
            "prashant@gmail.com",
            "9876543210",
            "Punjab"
        )
    );

    int choice;

    do {

        cout << "\n========================================";
        cout << "\n E-COMMERCE ORDER MANAGEMENT SYSTEM";
        cout << "\n========================================";

        cout << "\n1. Display Products";
        cout << "\n2. Display Customers";
        cout << "\n3. Add Product";
        cout << "\n4. Add Customer";
        cout << "\n5. Create Order";
        cout << "\n6. Make Payment";
        cout << "\n7. Confirm Order";
        cout << "\n8. Cancel Order";
        cout << "\n9. Deliver Order";
        cout << "\n10. Display Orders";
        cout << "\n0. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        // ================= DISPLAY PRODUCTS =================

        if (choice == 1) {

            if (products.empty()) {
                cout << "\nNo products available.\n";
            }
            else {
                for (auto &p : products) {
                    p.displayProduct();
                }
            }
        }

        // ================= DISPLAY CUSTOMERS =================

        else if (choice == 2) {

            if (customers.empty()) {
                cout << "\nNo customers available.\n";
            }
            else {
                for (auto &c : customers) {
                    c.displayCustomer();
                }
            }
        }

        // ================= ADD PRODUCT =================

        else if (choice == 3) {

            int id, stock, category;
            string name;
            double price;

            cout << "\nEnter Product ID: ";
            cin >> id;

            cout << "Enter Product Name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter Price: ";
            cin >> price;

            cout << "Enter Stock: ";
            cin >> stock;

            cout << "Category:";
            cout << "\n0. Electronics";
            cout << "\n1. Clothing";
            cout << "\n2. Food";
            cout << "\n3. Books";

            cout << "\nEnter Category: ";
            cin >> category;

            if (category < 0 || category > 3) {
                cout << "Invalid category!\n";
                continue;
            }

            products.push_back(
                Product(
                    id,
                    name,
                    price,
                    stock,
                    static_cast<Category>(category)
                )
            );

            cout << "Product added successfully.\n";
        }

        // ================= ADD CUSTOMER =================

        else if (choice == 4) {

            int id;
            string name, email, phone, address;

            cout << "\nEnter Customer ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter Email: ";
            getline(cin, email);

            cout << "Enter Phone: ";
            getline(cin, phone);

            cout << "Enter Address: ";
            getline(cin, address);

            customers.push_back(
                Customer(id, name, email, phone, address)
            );

            cout << "Customer added successfully.\n";
        }

        // ================= CREATE ORDER =================

        else if (choice == 5) {

            int customerID;
            int productID;
            int quantity;

            cout << "\nEnter Customer ID: ";
            cin >> customerID;

            bool customerFound = false;

            for (auto &c : customers) {
                if (c.getCustomerID() == customerID) {
                    customerFound = true;
                    break;
                }
            }

            // Invalid customer ID
            if (!customerFound) {
                cout << "Error: Invalid Customer ID!\n";
                continue;
            }

            cout << "Enter Product ID: ";
            cin >> productID;

            bool productFound = false;

            for (auto &p : products) {

                if (p.getProductID() == productID) {

                    productFound = true;

                    cout << "Enter Quantity: ";
                    cin >> quantity;

                    // Invalid quantity
                    if (quantity <= 0) {
                        cout << "Error: Invalid quantity!\n";
                        break;
                    }

                    // Product out of stock
                    if (!p.checkAvailability(quantity)) {
                        cout << "Error: Product out of stock!\n";
                        break;
                    }

                    double total = p.getPrice() * quantity;

                    p.updateStock(-quantity);

                    orders.push_back(
                        Order(
                            nextOrderID,
                            customerID,
                            total
                        )
                    );

                    cout << "\nOrder created successfully!";
                    cout << "\nOrder ID: " << nextOrderID;
                    cout << "\nTotal Amount: Rs. " << total << "\n";

                    nextOrderID++;

                    break;
                }
            }

            // Invalid product ID
            if (!productFound) {
                cout << "Error: Invalid Product ID!\n";
            }
        }

        // ================= MAKE PAYMENT =================

        else if (choice == 6) {

            int orderID;
            int method;

            cout << "\nEnter Order ID: ";
            cin >> orderID;

            Order *selectedOrder = nullptr;

            for (auto &o : orders) {
                if (o.orderID == orderID) {
                    selectedOrder = &o;
                    break;
                }
            }

            // Invalid order ID
            if (selectedOrder == nullptr) {
                cout << "Error: Invalid Order ID!\n";
                continue;
            }

            // Payment for cancelled order
            if (selectedOrder->orderStatus == CANCELLED) {
                cout << "Error: Cannot make payment for a cancelled order!\n";
                continue;
            }

            cout << "\nSelect Payment Method:";
            cout << "\n0. Credit Card";
            cout << "\n1. UPI";
            cout << "\n2. Cash";

            cout << "\nEnter choice: ";
            cin >> method;

            if (method < 0 || method > 2) {
                cout << "Error: Invalid payment method!\n";
                continue;
            }

            PaymentInfo payment;

            if (method == CREDIT_CARD) {

                string card;

                cout << "Enter last 4 digits of card: ";
                cin >> card;

                if (card.length() != 4) {
                    cout << "Error: Invalid card digits!\n";
                    selectedOrder->paymentStatus = PAYMENT_FAILED;
                    continue;
                }

                for (int i = 0; i < 4; i++) {
                    payment.lastFourDigits[i] = card[i];
                }

                payment.lastFourDigits[4] = '\0';

                selectedOrder->paymentStatus = PAYMENT_SUCCESS;

                cout << "Credit Card payment successful.\n";
            }

            else if (method == UPI) {

                string upi;

                cout << "Enter UPI ID: ";
                cin >> upi;

                if (upi.find("@") == string::npos) {

                    cout << "Error: Invalid UPI ID!\n";

                    selectedOrder->paymentStatus =
                        PAYMENT_FAILED;

                    continue;
                }

                int i;

                for (i = 0; i < (int)upi.length() && i < 49; i++) {
                    payment.upiID[i] = upi[i];
                }

                payment.upiID[i] = '\0';

                selectedOrder->paymentStatus =
                    PAYMENT_SUCCESS;

                cout << "UPI payment successful.\n";
            }

            else if (method == CASH) {

                selectedOrder->paymentStatus =
                    PAYMENT_SUCCESS;

                cout << "Cash payment recorded successfully.\n";
            }
        }

        // ================= CONFIRM ORDER =================

        else if (choice == 7) {

            int orderID;

            cout << "\nEnter Order ID: ";
            cin >> orderID;

            bool found = false;

            for (auto &o : orders) {

                if (o.orderID == orderID) {

                    found = true;

                    if (o.orderStatus == CANCELLED) {
                        cout << "Error: Cannot confirm a cancelled order!\n";
                    }

                    else if (o.orderStatus == DELIVERED) {
                        cout << "Error: Order already delivered!\n";
                    }

                    else if (o.paymentStatus != PAYMENT_SUCCESS) {
                        cout << "Error: Cannot confirm order because payment failed or is pending!\n";
                    }

                    else {
                        o.orderStatus = CONFIRMED;
                        cout << "Order confirmed successfully.\n";
                    }

                    break;
                }
            }

            if (!found) {
                cout << "Error: Invalid Order ID!\n";
            }
        }

        // ================= CANCEL ORDER =================

        else if (choice == 8) {

            int orderID;

            cout << "\nEnter Order ID: ";
            cin >> orderID;

            bool found = false;

            for (auto &o : orders) {

                if (o.orderID == orderID) {

                    found = true;

                    // Cannot cancel delivered order
                    if (o.orderStatus == DELIVERED) {
                        cout << "Error: Cannot cancel a delivered order!\n";
                    }

                    // Already cancelled
                    else if (o.orderStatus == CANCELLED) {
                        cout << "Error: Order is already cancelled!\n";
                    }

                    else {
                        o.orderStatus = CANCELLED;
                        cout << "Order cancelled successfully.\n";
                    }

                    break;
                }
            }

            if (!found) {
                cout << "Error: Invalid Order ID!\n";
            }
        }

        // ================= DELIVER ORDER =================

        else if (choice == 9) {

            int orderID;

            cout << "\nEnter Order ID: ";
            cin >> orderID;

            bool found = false;

            for (auto &o : orders) {

                if (o.orderID == orderID) {

                    found = true;

                    if (o.orderStatus != CONFIRMED) {
                        cout << "Error: Only confirmed orders can be delivered!\n";
                    }

                    else {
                        o.orderStatus = DELIVERED;
                        cout << "Order delivered successfully.\n";
                    }

                    break;
                }
            }

            if (!found) {
                cout << "Error: Invalid Order ID!\n";
            }
        }

        // ================= DISPLAY ORDERS =================

        else if (choice == 10) {

            if (orders.empty()) {
                cout << "\nNo orders available.\n";
            }

            for (auto &o : orders) {

                cout << "\n-----------------------------";
                cout << "\nOrder ID: " << o.orderID;
                cout << "\nCustomer ID: " << o.customerID;
                cout << "\nTotal Amount: Rs. "
                     << o.totalAmount;

                cout << "\nOrder Status: "
                     << getOrderStatus(o.orderStatus);

                cout << "\nPayment Status: "
                     << getPaymentStatus(o.paymentStatus);

                cout << "\n-----------------------------\n";
            }
        }

        // ================= EXIT =================

        else if (choice == 0) {
            cout << "\nThank you for using the system!\n";
        }

        else {
            cout << "\nError: Invalid menu choice!\n";
        }

    } while (choice != 0);

    return 0;
}
