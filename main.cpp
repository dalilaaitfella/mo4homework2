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

// function prototypes for merge sort comparison functions
int compareByName(Product &, Product &);
int compareByPrice(Product &, Product &);
int compareByRating(Product &, Product &);

int main()
{
    std::ifstream infile("products.txt"); // open input file

    if (!infile) // check if file opened correctly
    {
        std::cout << "Error opening file" << std::endl;
        return 1; // stop program if file cannot be read
    }

    unorderedLinkedList<Product> listName;   // list sorted by product name
    unorderedLinkedList<Product> listPrice;  // list sorted by product price
    unorderedLinkedList<Product> listRating; // list sorted by product rating

    double price;                // stores price from file
    std::string description;     // stores product description
    int productNumber;           // stores product number
    double rating;               // stores product rating

    // read file until no more data
    while (infile >> price) // first value is price
    {
        infile.ignore(); // clear leftover newline

        std::getline(infile, description); // read full description line

        infile >> productNumber; // read product number
        infile >> rating;        // read rating value

        infile.ignore(); // clear newline before next product

        Product p(price, description, productNumber, rating); // create product object

        listName.insert(p);   // insert into name-sorted list
        listPrice.insert(p);  // insert into price-sorted list
        listRating.insert(p); // insert into rating-sorted list
    }

    infile.close(); // close file after reading all products

    listName.mergeSort(compareByName);   // sort list by name
    listPrice.mergeSort(compareByPrice); // sort list by price
    listRating.mergeSort(compareByRating); // sort list by rating

    std::cout << "Sorted by Name:\n";
    listName.print(); // display sorted-by-name list

    std::cout << "\nSorted by Price:\n";
    listPrice.print(); // display sorted-by-price list

    std::cout << "\nSorted by Rating:\n";
    listRating.print(); // display sorted-by-rating list

    return 0; // program ends successfully
}

/* compare products by name (alphabetical order) */
int compareByName(Product &p1, Product &p2)
{
    if (p1.getName() < p2.getName())
        return -1; // p1 comes before p2
    else if (p1.getName() > p2.getName())
        return 1;  // p1 comes after p2
    else
        return 0;  // equal names
}

/* compare products by price (low to high) */
int compareByPrice(Product &p1, Product &p2)
{
    if (p1.getPrice() < p2.getPrice())
        return -1; // cheaper product comes first
    else if (p1.getPrice() > p2.getPrice())
        return 1;  // more expensive product comes later
    else
        return 0;  // equal price
}

/* compare products by rating (low to high) */
int compareByRating(Product &p1, Product &p2)
{
    if (p1.getRating() < p2.getRating())
        return -1; // lower rating first
    else if (p1.getRating() > p2.getRating())
        return 1;  // higher rating later
    else
        return 0;  // equal rating
}