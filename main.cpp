// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>

#include "libs/product.h"
#include "libs/branch.h"
#include "libs/menu.h"
using namespace std;

/*               FUNCTIONS               */





/*---------------------------------------*/






int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
	int op;
    unordered_map<string, branch*> hashB;
    branch* branchs = NULL;
    branch* lastB = NULL;

    product* products = NULL;
    product* lastP = NULL;
    // READ PRODUCTS
    readProducts(&products, &lastP);
    // READ BRANCHS
    readBranchs(&branchs , &lastB , hashB);
    // READ PRODUCTS INSIDE BRANCHS
    readProductsOfBranch(branchs , products , hashB);
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
                                        createProduct(&products, &lastP);
                                        break;
                                    case 2: // MODIFY A PRODUCT
                                        menuModProduct(products);
                                        break;
                                    case 3: // DELETE A PRODUCT
                                        menuDelProduct(&products , &lastP);
                                        break;
                                    case 4:
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
                                        createBranch(&branchs , &lastB , hashB);
                                        break;
                                    case 2: // Modify Branch
                                        menuModBranch(branchs);
                                        break;
                                    case 3: // Delete Branch
                                        menuDeleBranch(&branchs , &lastB);
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
					/* ---------- FIN MANTENIMIENTO ---------- */
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
    return 0;
}

// Ahora si funciona
// Para el mas culon