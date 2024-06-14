// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>

#include "libs/branch.h"
#include "libs/menu.h"
#include "libs/helper.h"
using namespace std;

/*
int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
	int op;
    branch* branchs = NULL;

    product* products = NULL;
    // READ PRODUCTS
    //readProducts(&products);
    // READ BRANCHS
    //readBranchs(&branchs);
    // READ PRODUCTS INSIDE BRANCHS
    readProductsOfBranch(branchs , products);
	do
	{
		menu();
		cin >> op;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            op = -1;
        }
        fflush(stdin);
		switch (op)
		{
			case 1: // Mantenimiento
				do
				{
					menuMant();
					cin >> op;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        op = -1;
                    }
					switch (op)
					{
						case 1: // Mantenimiento Productos
                            do
                            {
                                menuMantProds();
                                cin >> op;
                                if (cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore();
                                    op = -1;
                                }
                                switch (op)
                                {
                                    case 1: // Add Product
                                        createProduct(&products);
                                        break;
                                    case 2: // MODIFY A PRODUCT
                                        menuModProduct(products);
                                        break;
                                    case 3: // DELETE A PRODUCT
                                        menuDelProduct(&products);
                                        break;
                                    case 4: // CONSULT A PRODUCT BY CODE
                                        menuConsultProductByCode(products);
                                        break;
                                    case 5:
                                        menuConsultProductByDesc(products);
                                        break;
                                    case 6:
                                        //showAllProducts(products);
                                        tableProducts(products);
                                        system("pause");
                                        break;
                                }
                            } while (op != 0);
                            op = -1;
							break;
						case 2: // Mantenimiento Sucursales
							do
                            {
                                fflush(stdin);
                                menuMantBranchs();
                                cin >> op;
                                if (cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore();
                                    op = -1;
                                }
                                switch (op)
                                {
                                    case 1: // Add Branch
                                        createBranch(&branchs);
                                        break;
                                    case 2: // Modify Branch
                                        menuModBranch(branchs);
                                        break;
                                    case 3: // Delete Branch
                                        menuDeleBranch(&branchs );
                                        break;
                                    case 4: // Consult By Code
                                        menuConsultBranchByCode(branchs);
                                        break;
                                    case 5: // Consult By Description
                                        menuConsultBranchByDesc(branchs);
                                        break;
                                    case 6: // Show All Branchs  
                                        //printBranchs(branchs);
                                        tableBranchs(branchs);
                                        system("pause");
                                        break;
                                    case 7: // INVENTORY
                                        menuInventory(branchs , products);
                                        break;
                                }
                            } while (op != 0);
                            op = -1;
							break;
					}
					// ---------- FIN MANTENIMIENTO ---------- 
				} while (op != 0);
				op = -1;
				break;
            case 2:
            {
                // No available
                break;
            }
			case 3:
				// No available
				break;
		}
	} while (op != 0);
    saveProducts(products);
	saveBranchs(branchs);
    saveProductsOfBranch(branchs);
    return EXIT_SUCCESS;
}
*/


int main() {
    run();

}