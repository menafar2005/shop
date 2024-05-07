//
// Created by QHS on 3/31/2024.
//

#ifndef SHOP_PROJECT_PRODUCT_H
#define SHOP_PROJECT_PRODUCT_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <filesystem>


using namespace std;


class Product {

public:
    string product_name;
    int product_number, product_id;
    long product_price;

    void add_new_product() {
        int new_product_id;

        // Get product information from the user
        cout << "Enter product name: ";
        cin >> product_name;
        cout << "Enter product quantity: ";
        cin >> product_number;
        cout << "Enter product price: ";
        cin >> product_price;


        //set id for new product
        fstream productId;
        productId.open("product_id.txt", ios::in);
        productId>>product_id;
        productId.close();

        //creating new id for next product
        productId.open("product_id.txt", ios::out);
        new_product_id= (product_id+1);
        productId<<new_product_id;
        productId.close();


        // Save information to a CSV file
        fstream file1;
        file1.open("Product.csv", ios::app);
        file1 << product_name << "," << product_number << "," << product_price << "," <<product_id<<endl;
        file1.close();

        cout<<"your product id is: "<<product_id<<'\n';

    }


    //printing product info by entering product id
    void print_product_info_by_id(string entered_id)
    {
        string name1, price1, id1, num1, temp;
        fstream file2("Product.csv");
        bool found = false;
        int choice;
        //system("cls")
        while (!file2.eof()) {
            getline(file2, name1, ',');
            getline(file2, num1, ',');
            getline(file2, price1, ',');
            getline(file2, id1);

            if (id1 == entered_id) {
                found = true;
                cout << "____________________________________________________________" << '\n';
                cout << name1 << setw(10) << num1 << setw(10) << price1 << '\n';
                cout << "____________________________________________________________" << '\n';

                // Display edit menu
                while (true) {
                    cout << "1. Edit price" << endl;
                    cout << "2. Edit quantity" << endl;
                    cout << "3. Back to main menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    file2.seekp(0);
                    fstream temp_file;
                    temp_file.open("temp.csv", ios::app);


                    switch (choice) {
                        case 1:
                        {
                            // Edit price
                            string new_price;
                            cout << "enter new price: ";
                            cin >> new_price;
                            while (true)
                            {
                                getline(file2, name1, ',');
                                getline(file2, num1, ',');
                                getline(file2, price1, ',');
                                getline(file2, id1);
                                if(file2.eof())
                                    break;
                                if (id1==entered_id)
                                {
                                    temp_file<<name1<<","<<num1<<","<<new_price<<","<<id1<<endl;
                                }
                                else
                                {
                                        temp_file << name1 << "," << num1 << "," << price1 << "," << id1 << endl;
                                }
                            }

                            //delete Product.csv file
                            file2.close();
                            temp_file.close();
                            remove("Product.csv");

                            //rename temp.csv to Product.csv
                            //rename("temp_file.csv", "Product.csv");
                            rename("temp.csv", "Product.csv");
                        }

                        // Continue reading the rest of the line
                            break;

                        case 2:
                            // Edit quantity
                        {
                            string new_quantity;
                            bool edited= false;
                            cout << "enter new quantity: ";
                            cin >> new_quantity;
                            while (!file2.eof())
                            {
                                getline(file2, name1, ',');
                                getline(file2, num1, ',');
                                getline(file2, price1, ',');
                                getline(file2, id1);

                                if (id1==entered_id)
                                {
                                    temp_file<<name1<<","<<new_quantity<<","<<price1<<","<<id1<<endl;
                                    edited= true;
                                }
                                else
                                {
                                    if (!edited)
                                    {
                                        temp_file << name1 << "," << num1 << "," << price1 << "," << id1 << endl;
                                    }
                                }
                            }

                            //delete Product.csv file
                            file2.close();
                            temp_file.close();
                            remove("Product.csv");

                            //rename temp.csv to Product.csv
                            //rename("temp_file.csv", "Product.csv");
                            rename("temp.csv", "Product.csv");
                        }
                            break;
                        case 3:
                            // Go back to main menu
                            break;

                        default:
                            cout << "Invalid choice." << endl;
                    }

                    if (choice == 3) {
                        break; // Exit edit menu
                    }
                }
                break;
            }
        }

        if (!found)
        {
            cout << "this id is not available!" << '\n';
        }


    }
};


#endif //SHOP_PROJECT_PRODUCT_H
