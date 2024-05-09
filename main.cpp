#include "product.h"
#include "order.h"
#include <iostream>

using namespace std;


Product mainProduct;
order mainOrder;
int main() {



    int choice;
    string  entered_product_id, entered_order_id;

    while (true) {
        cout << "1. Add new product" << endl;
        cout << "2. see product info & edit" << endl;
        cout << "3. add new order" << endl;
        cout << "4. see order" << endl;
        cout << "5. see finance report" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                mainProduct.add_new_product();
                break;

            case 2:
                cout<<"enter id: ";
                cin>>entered_product_id;
                mainProduct.print_product_info_by_id(entered_product_id);

                break;
            case 3:
                mainOrder.add_new_order();

                break;
            case 4:
                cout<<"enter order id: ";
                cin >> entered_order_id;

                mainOrder.print_order_by_id(entered_order_id);


                break;
            case 5:
                mainOrder.see_finance();

                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }


}
