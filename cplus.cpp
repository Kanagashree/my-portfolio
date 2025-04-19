#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Product {
    int id;
    string name;
    double price;
};

class Cart {
    vector<Product> cart;
    double totalPrice = 0;

public:
    void addProduct(Product p) {
        cart.push_back(p);
        totalPrice += p.price;
        cout << p.name << " added to cart!\n";
    }

    void viewCart() {
        if (cart.empty()) {
            cout << "Cart is empty!\n";
            return;
        }
        cout << "\nYour Cart:\n";
        for (const auto &p : cart) {
            cout << "- " << p.name << " - ₹" << p.price << "\n";
        }
        cout << "Total: ₹" << totalPrice << "\n";
    }

    void checkout() {
        if (cart.empty()) {
            cout << "Cart is empty! Add items before checkout.\n";
            return;
        }
        cout << "Order Placed Successfully! Total Bill: ₹" << totalPrice << "\n";
        cart.clear();
        totalPrice = 0;
    }
};

bool login() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    
    if (username == "user" && password == "1234") {
        cout << "Login Successful!\n";
        return true;
    } else {
        cout << "Invalid Credentials! Try Again.\n";
        return false;
    }
}

int main() {
    vector<Product> products = {
        {1, "Laptop", 55000},
        {2, "Smartphone", 20000},
        {3, "Headphones", 3000},
        {4, "Smartwatch", 5000}
    };

    Cart myCart;
    
    cout << "Welcome to Online Shopping System!\n";
    if (!login()) return 0;

    int choice;
    while (true) {
        cout << "\nMenu:\n1. View Products\n2. Add to Cart\n3. View Cart\n4. Checkout\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nAvailable Products:\n";
            for (const auto &p : products) {
                cout << p.id << ". " << p.name << " - ₹" << p.price << "\n";
            }
        } 
        else if (choice == 2) {
            int productID;
            cout << "Enter Product ID to add: ";
            cin >> productID;
            if (productID > 0 && productID <= products.size()) {
                myCart.addProduct(products[productID - 1]);
            } else {
                cout << "Invalid Product ID!\n";
            }
        } 
        else if (choice == 3) {
            myCart.viewCart();
        } 
        else if (choice == 4) {
            myCart.checkout();
        } 
        else if (choice == 5) {
            cout << "Exiting... Thank you for shopping!\n";
            break;
        } 
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

 return 0;
}
