/* Program name: main.cpp
* Author: Dalila Ait fella
* Date last updated: 4/22/2026
* Purpose: Read product data from a file, store it in linked lists, and sort using merge sort with function pointers.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "unorderedLinkedList.h"
#include "Product.h"

int compareByName(Product &, Product &);
int compareByPrice(Product &, Product &);
int compareByRating(Product &, Product &);

int main()
{
    std::ifstream infile("products.txt");

    unorderedLinkedList<Product> listName;
    unorderedLinkedList<Product> listPrice;
    unorderedLinkedList<Product> listRating;

    double price;
    std::string description;
    int productNumber;
    double rating;

    while (infile >> price)
    {
        infile.ignore();
        std::getline(infile, description);
        infile >> productNumber;
        infile >> rating;
        infile.ignore();

        Product p(price, description, productNumber, rating);

        listName.insert(p);
        listPrice.insert(p);
        listRating.insert(p);
    }

    infile.close();

    listName.mergeSort(compareByName);
    listPrice.mergeSort(compareByPrice);
    listRating.mergeSort(compareByRating);

    std::cout << "Sorted by Name:\n";
    listName.print();

    std::cout << "\nSorted by Price:\n";
    listPrice.print();

    std::cout << "\nSorted by Rating:\n";
    listRating.print();

    return 0;
}

/ comparison functions /

int compareByName(Product &p1, Product &p2)
{
    if (p1.getName() < p2.getName()) return -1;
    if (p1.getName() > p2.getName()) return 1;
    return 0;
}

int compareByPrice(Product &p1, Product &p2)
{
    if (p1.getPrice() < p2.getPrice()) return -1;
    if (p1.getPrice() > p2.getPrice()) return 1;
    return 0;
}

int compareByRating(Product &p1, Product &p2)
{
    if (p1.getRating() < p2.getRating()) return -1;
    if (p1.getRating() > p2.getRating()) return 1;
    return 0;
}