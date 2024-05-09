//
// Created by QHS on 4/5/2024.
//

#ifndef SHOP_PROJECT_ORDER_H
#define SHOP_PROJECT_ORDER_H
#include "product.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <filesystem>

class order {

public:
    string customer_first_name,customer_last_name,customer_phone, order_final_price, order_total_price,order_discount,orderPack[100], order_year, order_month, order_day;
    int order_id, orderPack_num[100];

    void add_new_order()
    {

        fstream product_file("Product.csv");
        ofstream temp_file;
        string name2,id2,price2, num2;
        int i=0, new_order_id;
        int order_product_number;


        // Get order information from the user
        cout << "Enter customer first name: ";
        cin >> customer_first_name;
        cout<<"Enter customer last name: ";
        cin>>customer_last_name;
        cout<<"Enter customer phone number:(like 09127442356) ";
        cin>>customer_phone;
        cout<<"enter year: ";
        cin>>order_year;
        cout<<"enetr month: ";
        cin>>order_month;
        cout<<"enter day: ";
        cin>>order_day;
        cout<<"how many products: (kind of product)";
        cin>>order_product_number;

        //long order_total_price_long = stol(order_total_price);
        stringstream ss3(order_total_price);
        long order_total_price_long;
        ss3 >> order_total_price_long;
        order_total_price_long = 0;

        for (; i < order_product_number; )
        {
            product_file.seekp(0);
            string order_product_id;
            bool productfound= false;
            bool quantity_enough= false;
            cout<<"enter product id: ";
            cin>>order_product_id;
            while (product_file.good())
            {
                getline(product_file, name2, ',');

                getline(product_file, num2, ',');
                stringstream ss4(num2);
                int num2_int;
                ss4 >> num2_int;

                getline(product_file, price2, ',');
                //int price2_int = stoi(price2);
                stringstream ss5(price2);
                long price2_long;
                ss5 >> price2_long;

                getline(product_file, id2);

                if (id2 == order_product_id)
                {
                    int each_product_quantity;
                    productfound= true;

                    cout<<"enter quantity of this product: ";
                    cin>>each_product_quantity;

                    //check if the quantity of product is enough
                    if (num2_int==0)
                    {
                        cout<<"the quantity of this product is 0";
                        break;
                    }
                    else if ((num2_int - each_product_quantity) >= 0)
                    {
                        order_total_price_long += (price2_long * each_product_quantity);
                        quantity_enough= true;
                        //string each_product_quantity_string = to_string(each_product_quantity);
                        orderPack[i]= order_product_id;
                        orderPack_num[i]= each_product_quantity;
                        i++;

                        break;
                    }
                    else
                    {


                        while ( quantity_enough= true)
                        {
                            cout<<"the product is not enough! enter another quantity: ";
                            cin>>each_product_quantity;
                            if ((num2_int - each_product_quantity) >= 0)
                            {
                                order_total_price_long += (price2_long * each_product_quantity);
                                quantity_enough= true;
                                string each_product_quantity_string = to_string(each_product_quantity);
                                orderPack[i]= order_product_id;
                                orderPack_num[i]= each_product_quantity;
                                i++;

                                break;

                            }
                            else
                            {
                                continue;
                            }
                        }

                    }

                    break;
                }
            }

            if (!productfound)
            {
                cout << "this id is not available!" << '\n';
            }

        }

        int is_discount;
        cout<<"total price is: "<<order_total_price_long<<'\n';
        cout<<"do you want to give any discount? "<<'\n'<<"1. yes"<<'\n'<<"2. no"<<'\n';
        cin>>is_discount;

        if (is_discount== 1)
        {
            //set order discount
            cout<<"enter discount price: ";
            cin>>order_discount;
        }
        else if(is_discount== 2)
        {
            order_discount= "0";
        }
        else
        {
            cout<<"invalid choice!";
        }

        //long order_final_price_long = stol(order_final_price);
        stringstream ss1(order_final_price);
        long order_final_price_long;
        ss1 >> order_final_price_long;

        //long order_discount_long = stol(order_discount);
        stringstream ss2(order_discount);
        long order_discount_long;
        ss2 >> order_discount_long;

        order_final_price_long = (order_total_price_long - order_discount_long);
        string order_final_price_string = to_string(order_final_price_long);

        //set order final price
        order_final_price=order_final_price_string;

        //set order total price
        string order_total_price_string = to_string(order_total_price_long);
        order_total_price = order_total_price_string;

        //set order discount
        string order_discount_string = to_string(order_discount_long);
        order_discount = order_discount_string;

        //set id for new order
        fstream orderId("order_id.txt");

        if(orderId.good())
        {
            orderId.open("order_id.txt", ios::in);
            orderId>>order_id;
            orderId.close();
        }
        else
        {
            order_id=1000;
        }



        //creating new id for next order
        orderId.open("order_id.txt", ios::out);
        new_order_id= (order_id+1);
        orderId<<new_order_id;
        orderId.close();


        ofstream order_file;
        order_file.open("Order.csv", ios::app);
        order_file<<order_id<<","<<customer_first_name<<","<<customer_last_name<<","<<customer_phone<<","<<order_day<<","<<order_month<<","<<order_year<<",";


        for (int k = 0; k < order_product_number; k++)
        {
            order_file<< orderPack[k] <<" * "<< orderPack_num[k]<<" | ";
        }

        order_file<<","<<order_total_price<<","<<order_discount<<","<<order_final_price<<endl;
        order_file.close();

    }


    void print_order_by_id(string enteredID)
    {
        string fname, lname, phone_num, oday, omonth, oyear, products, total_price, discount_price, final_price, orderId;
        ifstream orderFile;
        bool is_order_found = false;

        orderFile.open("Order.csv");
        orderFile.seekg(0);

        while (orderFile.good())
        {

            getline(orderFile, orderId, ',');
            getline(orderFile, fname, ',');
            getline(orderFile, lname, ',');
            getline(orderFile, phone_num, ',');
            getline(orderFile, oday, ',');
            getline(orderFile, omonth, ',');
            getline(orderFile, oyear, ',');
            getline(orderFile, products, ',');
            getline(orderFile, total_price, ',');
            getline(orderFile, discount_price, ',');
            getline(orderFile, final_price);


            if (enteredID == orderId)
            {
                is_order_found = true;
                cout << "_______________________________________________________________________________________________________" << '\n';
                cout << fname << "     " << lname << "     " << phone_num << "     " <<  oyear << "/" << omonth << "/" << oday << "     " << products << "     " << total_price << "     " << discount_price << "     " << final_price << '\n';
                cout << "_______________________________________________________________________________________________________" << '\n';
                break;
            }
        }

        if (!is_order_found)
        {
            cout << "this id is not available!" << '\n';
        }

    }

    void see_finance()
    {
        int finance_choice;
        ifstream order_file("Order.csv", ios::app);
        while (true) {
            cout<<"1. see default finance report"<<'\n';
            cout<<"2. see custom finance report"<<'\n';
            cout<<"3. back to main menu"<<'\n';
            cout<<"enter your choice: ";
            cin>>finance_choice;
            order_file.seekg(0);

            switch (finance_choice)
            {
                case 1:
                {
                    string order_info, day, month, year, salary;
                    long final_salary = 0;
                    static bool is_order_calculated = false;

                    time_t now = time(0);
                    tm *ltm = localtime(&now);

                    // finding today's date
                    int end_day = ltm->tm_mday;
                    int end_month = 1 + ltm->tm_mon;
                    int end_year = 1900 + ltm->tm_year;


                    long end_date_num = ((end_year * 12 * 30) + (end_month * 30) + (end_day));
                    long start_date_num = end_date_num - 30;




                    while (!order_file.eof())
                    {
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, day, ',');
                        getline(order_file, month, ',');
                        getline(order_file, year, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, salary);

                        stringstream ss5(day);
                        int day_int;
                        ss5 >> day_int;

                        stringstream ss6(month);
                        int month_int;
                        ss6 >> month_int;

                        stringstream ss7(year);
                        int year_int;
                        ss7 >> year_int;

                        stringstream ss10(salary);
                        long salary_long;
                        ss10 >> salary_long;

                        long order_date_num = ((year_int * 12 * 30) + (month_int * 30) + (day_int));
                        is_order_calculated = false;

                        if (order_date_num >= start_date_num && order_date_num <= end_date_num && !is_order_calculated)
                        {
                            final_salary = salary_long + final_salary;
                            is_order_calculated= true;
                        }
                        else
                        {
                            final_salary = final_salary + 0;
                        }
                    }

                    stringstream ss11(salary);
                    long salary_long;
                    ss11 >> salary_long;

                    if (is_order_calculated)
                    {
                        final_salary= final_salary-salary_long;
                    }

                    cout << "you've earned " << final_salary << " at this period of time." << '\n';
                }

                    break;

                case 2:
                {
                    string order_info, day, month, year, salary;
                    long final_salary = 0;
                    static bool is_order_calculated = false;

                    int start_day, start_month, start_year, end_day, end_month, end_year;

                    cout<<"enter start year: "<<'\n';
                    cin>>start_year;
                    cout<<"enter start month: "<<'\n';
                    cin>>start_month;
                    cout<<"enter start day: "<<'\n';
                    cin>>start_day;
                    cout<<"enter end year: "<<'\n';
                    cin>>end_year;
                    cout<<"enter end month: "<<'\n';
                    cin>>end_month;
                    cout<<"enter end day: "<<'\n';
                    cin>>end_day;


                    long end_date_num = ((end_year * 12 * 30) + (end_month * 30) + (end_day));
                    long start_date_num = ((start_year * 12 * 30) + (start_month * 30) + (start_day));


                    while (!order_file.eof())
                    {
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, day, ',');
                        getline(order_file, month, ',');
                        getline(order_file, year, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, order_info, ',');
                        getline(order_file, salary);

                        stringstream ss5(day);
                        int day_int;
                        ss5 >> day_int;

                        stringstream ss6(month);
                        int month_int;
                        ss6 >> month_int;

                        stringstream ss7(year);
                        int year_int;
                        ss7 >> year_int;

                        stringstream ss10(salary);
                        long salary_long;
                        ss10 >> salary_long;

                        long order_date_num = ((year_int * 12 * 30) + (month_int * 30) + (day_int));
                        is_order_calculated = false;

                        if (order_date_num >= start_date_num && order_date_num <= end_date_num && !is_order_calculated)
                        {
                            final_salary = salary_long + final_salary;
                            is_order_calculated= true;
                        }
                        else
                        {
                            final_salary = final_salary + 0;
                        }
                    }

                    stringstream ss11(salary);
                    long salary_long;
                    ss11 >> salary_long;

                    if (is_order_calculated)
                    {
                        final_salary= final_salary-salary_long;
                    }

                    cout << "you've earned " << final_salary << " at this period of time." << '\n';
                }
                    break;

                case 3:
                {
                    //back to main menu
                    break;
                }

                default:
                    cout << "Invalid choice." << endl;
            }

            if (finance_choice == 3)
            {
                break; // Exit edit menu
            }
        }


    }

};


#endif //SHOP_PROJECT_ORDER_H