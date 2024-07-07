#ifndef REPORTS_H
#define REPORTS_H

#include <iostream>

#include "branch.h"
#include "product.h"
#include "people.h"
#include "helper.h"

// provisional

// Se accede asi (a la referencia del nodo): (*(*N)->data)

// abb generico
enum TYPE {
    T_BILL = 1,
    T_DETAIL = 2,
    T_PRODUCT = 3,
    T_BRANCH = 4,
    T_CLIENT = 5,
    T_UNDEFINED = 0
};


struct ABBgen {
    void *data;

    string axS;
    int axPr;
    int axAm;

    enum TYPE T;
    ABBgen *left;
    ABBgen *right;
};


//  ABB BRANCH
ABBgen *NG(branch *b) {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->T = T_BRANCH;
    r->left = NULL;
    r->right = NULL;

    return r;
}

// ABB BILL
ABBgen *NG(bill *b, string ax = "") {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->axS = ax;
    r->T = T_BILL;
    r->left = NULL;
    r->right = NULL;

    return r;
}

//  ABB CLIENT
ABBgen *NG(people *b, int am, int pr) {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->axAm = am;
    r->axPr = pr;

    r->T = T_CLIENT;
    r->left = NULL;
    r->right = NULL;

    return r;
}

// ABB DETAIL
ABBgen *NG(detail *b, int pr, int am) {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->axAm = am;
    r->axPr = pr;
    r->T = T_DETAIL;
    r->left = NULL;
    r->right = NULL;
    return r;
}

// ABB PRODUCT
ABBgen *NG(product *b) {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->axAm = b->amount;
    r->axPr = b->minAmount;
    r->T = T_PRODUCT;
    r->left = NULL;
    r->right = NULL;
    return r;
}



// MERCADEO 3.3
/*
    Dado un mes (y año) y un código de producto mostrar la cantidad total comprada
    (mayor a cero) de cada cliente en toda las tiendas ordenado por cantidad (de mayor
    a menor). Al final el total de producto comprados en todas las tiendas.

    multilista
    abb y volver a insertar en abb;
*/


struct clientContainer {
    string branchName;
    people *clients;
    int totalQty;
    int totalPrice; 
    clientContainer *next;
};

struct branchContainer {
    branch *selBranch;
    clientContainer *cont;
    branchContainer *next;

    ABBgen *clients;
};


void insert(branchContainer *b, branchContainer *h) {
    if (h) {
        h->next = b;
        b = h;
    }

}

void insert(clientContainer *b, clientContainer *h) {
    if (h) {
        h->next = b;
        b = h;
    }
}


/*
RESUMEN DE CAFE:

---------------------------------------
FARMA:
    30906652 Carlos      20       5042
------------------------------------
.
.
.

*/




int compareGen(ABBgen *a, ABBgen *b) {
    if (a->T == b->T) {
        switch (a->T) {
            case T_BILL:
                return compare(((bill*) a->data)->code,  ((bill*) b->data)->code);
                break;
            case T_DETAIL:
                return compare(((detail*) a->data)->code,  ((detail*) b->data)->code);
                break;
            case T_PRODUCT:
                return (((product*) a->data)->amount > ((product*) b->data)->amount);
                break;
            case T_UNDEFINED:
                return 0;
                break;
        }
    }
    return 0;
}

void tableData(ABBgen *t) {
    if (t) {
        switch (t->T) {
            case T_BILL:
                printFmt(((bill*) t->data)->code, 15);
                printFmt(((bill*) t->data)->date, 15);
                printFmt(to_string( ((bill*) t->data)->total ), 15);  
                printFmt(t->axS, 15);  
                break;
            case T_DETAIL:
                printFmt(((detail*) t->data)->code, 15);
                printFmt(((detail*) t->data)->name, 25);
                printFmt(to_string(t->axAm), 15);
                printFmt(to_string(t->axPr), 15);
                break;
            case T_PRODUCT:
                printFmt(((product*) t->data)->code, 15);
                printFmt(((product*) t->data)->name, 25);
                printFmt(to_string(t->axAm), 15);
                printFmt(to_string(t->axPr), 15);
                break;
            case T_CLIENT:
                printFmt(((people*) t->data)->ID, 15);
                printFmt(((people*) t->data)->name, 25);
                printFmt(to_string(t->axAm), 15);
                printFmt(to_string(t->axPr), 15);
                break;
            default:
                cout << "<Undefined type object>";
                break;
        }
    }
}

void insertABBgen(ABBgen**N, bill *data, string ax = "") {
    ABBgen *temp = NG(data, ax);
    if (*N) {
        if (compareGen(*N, temp)) {
            insertABBgen(&(*N)->left, data, ax);
        }
        else if (compareGen(temp, *N )) {
            insertABBgen(&(*N)->right, data, ax);
        }
        else return;
    } else *N = temp;
}

// DETAIL AVBB
void insertABBgen(ABBgen**N, detail *data) {
    if (*N) {
        if (compare( ((detail*)(*N)->data)->code, data->code)) {
            insertABBgen(&(*N)->left, data);
        }
        else if (compare(data->code, ((detail*)(*N)->data)->code )) {
            insertABBgen(&(*N)->right, data);
        }
        else {
            (*N)->axAm += data->amount;
            (*N)->axPr += data->price;
        };
    } else *N = NG(data, data->price, data->amount);
}

// INSERT ABB PRODUCTS 
void insertABBgen(ABBgen**N, product *data) {
    if (*N) {
        if (((product*)(*N)->data)->amount > data->amount) {
            insertABBgen(&(*N)->left, data);
        }
        else if (((product*)(*N)->data)->amount < data->amount) {
            insertABBgen(&(*N)->right, data);
        }
        else return;
    } else *N = NG(data);
}

// INSERT ABB BRANCHS
void insertABBgen(ABBgen**N, branch *data) {
    if (*N) {
        if (compare(((branch*)(*N)->data)->code, data->code)) {
            insertABBgen(&(*N)->left, data);
        }
        else if (compare(data->code, ((branch*)(*N)->data)->code)) {
            insertABBgen(&(*N)->right, data);
        }
        else return;
    } else *N = NG(data);
}

// INSERT ABB CLIENTS
void insertABBgen(ABBgen**N, people *data, int am, int pr) {
    if (*N) {
        if ( compare( ((people*)(*N)->data)->ID, data->ID ) ) {
            insertABBgen(&(*N)->left, data, am, pr);
        }
        else if ( compare(data->ID, ((people*)(*N)->data)->ID) ) {
            insertABBgen(&(*N)->left, data, am, pr);
        } else {
            (*N)->axAm += am;
            (*N)->axPr += pr;
        }
    }else *N = NG(data, am, pr);
}


void inorderGen(ABBgen**N) {
    if (*N)
    {
        inorderGen(&(*N)->left);
        if ((*N)->data) {
            tableData(*N);
            cout << "\n"; 
        }
        inorderGen(&(*N)->right);
        
        ABBgen *t = *N;
        *N = NULL;
        delete t;
    }
}

void showArr(ABBgen*arr, int len) {
    for (int i = 0; i < len; i++) {
        tableData(arr);
        cout << "\n";
    }
}

int lenAbb(ABBgen*N) {
    if (N) {
        return lenAbb(N->left) + lenAbb(N->right) + 1;
    }
    return 0;
}

void abbToARrr(ABBgen *N, ABBgen **arr, int *i) {
    if (N) {
        abbToARrr(N->left, arr, i);
        arr[*i] = N;
        (*i)++;
        abbToARrr(N->right, arr, i);
    }
}

ABBgen *convertToArr(ABBgen*N, int *size) {
    *size = lenAbb(N);
    ABBgen *arr = (ABBgen*)calloc(*size, sizeof(ABBgen*));
    int pos = 0;
    abbToARrr(N, &arr, &pos);
    return arr;
}

void sortAnddShow(ABBgen*N) {
    int size = 0;
    ABBgen *arr = convertToArr(N, &size);
    showArr(arr, size);
    
    system("pause");
    delete arr;
}



/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

void billsClientResume(branch *branches, people *client) {
    bill *ax = NULL;
    ABBgen *resume = NULL;

    while (branches) {
        ax = branches->bills->first;
        while (ax) {
            if (ax->clientId == client->ID) insertABBgen(&resume, ax, branches->name);
            ax = ax->next;
        }
        branches = branches->next;
    }
    if (resume) {
        cout << "\n\t3.1 Resumen de facturas\n\n\tCliente: [ "<<client->name<<"]\n";
        cout << "\n----------------------------------------------------------------------------\n\t\tRESUMEN DE FACTURAS \n----------------------------------------------------------------------------\n";
        printFmt("Factura ", 15);
        printFmt("Fecha ", 15);
        printFmt("Monto (Bs.) ", 15);
        printFmt("Tienda ", 15);
        cout << "\n----------------------------------------------------------------------------\n";
        inorderGen(&resume);
        cout << "\n----------------------------------------------------------------------------\n\n\t";
    }
}

void productClientResume(branch *branches, people *client) {
    bill *ax;
    detail *dt;
    ABBgen *resume = NULL;

    while (branches)
    {
        ax = branches->bills->first;
        while (ax) {
            dt = ax->detailBill;
            
            while (dt) {
                if (ax->clientId == client->ID) insertABBgen(&resume, dt);
                dt = dt->next;
            }    
            ax = ax->next;
        }
        branches = branches->next;
    }
    if (resume) {
        
        cout << "\n\t3.1 Resumen de facturas\n\n\tCliente: [ "<<client->name<<"]\n";
        cout << "\n----------------------------------------------------------------------------\n\tRESUMEN DE FACTURAS \n----------------------------------------------------------------------------\n";
        printFmt("CODIGO ", 15);
        printFmt("DESCRIPCION ", 25);
        printFmt("CANTIDAD ", 15);
        printFmt("PRECIO (Bs.) ", 15);
        cout << "\n----------------------------------------------------------------------------\n";
        inorderGen(&resume);
        cout << "\n----------------------------------------------------------------------------\n\n\t";
    }
}

void branchUnitsResume(branch *selected) {
    ABBgen *resume = NULL;
    bill *ax = selected->bills->first;
    int totalSelled = 0;
    float cost = 0;
    float totalBills = 0; 
    float i = 0;
    while (ax) {
        detail *bx = ax->detailBill;
        cost = 0;
        while (bx) {
            insertABBgen(&resume, bx);
            totalSelled += bx->amount;
            cost += bx->price;
            cout << cost << "," << bx->amount << "," << bx->price << endl; 
            bx = bx->next;
        }
        i++;
        
        totalBills += cost;
        ax = ax->next;
    }
    
    if (resume) {
        cout << "\n\t3.2.1 Resumen de [ " << selected->name << " ]\n";
        cout << "\n----------------------------------------------------------------------------\n\tRESUMEN DE FACTURAS \n----------------------------------------------------------------------------\n";
        printFmt("CODIGO ", 15);
        printFmt("DESCRIPCION ", 25);
        printFmt("VENDIDOS ", 15);
        printFmt("GENERADO ", 15);
        cout << "\n----------------------------------------------------------------------------\n";
        inorderGen(&resume);
        cout << "\n----------------------------------------------------------------------------\n\n";
        cout << "\tCANTIDAD VENDIDA: " << totalSelled << "\n";
        cout << "\tCOSTO TOTAL: " << totalBills << "Bs.\n";
        cout << "\tPROMEDIO DE GASTO POR COMPRA: " << totalBills/i << "Bs.\n";
        cout << "\n----------------------------------------------------------------------------\n\n\n";
    }
}

void branchInventoryResume(branch *selected) {
    ABBgen *resume = NULL;
    product *ax = selected->products;
    while (ax) {
        insertABBgen(&resume, ax);
        ax = ax->next;
    }
    if (resume) {
        cout << "\n\t\tResumen Inventario de [ " << selected->name << " ]\n";
        cout << "\n----------------------------------------------------------------------------\n\tRESUMEN DE FACTURAS \n----------------------------------------------------------------------------\n";
        printFmt("CODIGO ", 15);
        printFmt("NOMBRE ", 25);
        printFmt("EXISTENCIA ", 15);
        printFmt("MIN. EXISTENCIA ", 15);
        cout << "\n----------------------------------------------------------------------------\n";
        inorderGen(&resume);
        cout << "\n----------------------------------------------------------------------------\n\n\n";

    }
}

void branchMonthlyResume(branch *selected, string month) {
    ABBgen *resume = NULL;

    bill *ax = selected->bills->first;
    detail *bx = NULL;
    int earned = 0;
    int totalProducts = 0;
    while (ax) {
        if (getMonth(ax->date) == month) {
            bx = ax->detailBill;
            while (bx) {
                insertABBgen(&resume, bx);
                earned += bx->price;
                totalProducts += bx->amount;
                bx = bx->next;
            }
        }
        ax = ax->next;
    }

    if (resume) {
        cout << "\n\t\tResumen Inventario de [ " << selected->name << " ("<<selected->code<<") ]\n";
        cout << "\n----------------------------------------------------------------------------\n\tRESUMEN DE FACTURAS \n----------------------------------------------------------------------------\n";
        printFmt("CODIGO ", 15);
        printFmt("NOMBRE ", 25);
        printFmt("TOTAL VENDIDO ", 15);
        printFmt("MIN. EXISTENCIA ", 15);
        cout << "\n----------------------------------------------------------------------------\n";
        inorderGen(&resume);
        cout << "\n----------------------------------------------------------------------------\n";
        cout << "\tTotal ingresado: " << earned;
        cout << "\n\tProductos vendidos: " << totalProducts;
        cout << "\n----------------------------------------------------------------------------\n\n\n";
    }
}



// MERCADERO 3.1
void statsMarketingByCode(branch *branchs, string month) {
    ABBgen *resume = NULL;

    bill *ax = NULL;
    detail *bx = NULL;
    int earned = 0;
    int totalProducts = 0;

    while (branchs) {
        ax = branchs->bills->first;
        while (ax) {
            if (getMonth(ax->date) == month) {
                bx = ax->detailBill;
                while (bx) {
                    insertABBgen(&resume, bx);
                    earned += bx->price;
                    totalProducts += bx->amount;
                    bx = bx->next;
                }
            }
            ax = ax->next;
        }
        branchs = branchs->next;
    }

    if (resume) {
        cout << "\n\tRESUMEN VENTAS GLOBALES ";
        cout << "\n----------------------------------------------------------------------------\n\tRESUMEN DE FACTURAS \n----------------------------------------------------------------------------\n";
        printFmt("CODIGO ", 15);
        printFmt("NOMBRE ", 25);
        printFmt("TOTAL VENDIDO ", 15);
        printFmt("GANANCIA ", 15);
        cout << "\n----------------------------------------------------------------------------\n";
        inorderGen(&resume);
        cout << "\n----------------------------------------------------------------------------\n";
        cout << "\tTotal ingresado: " << earned;
        cout << "\n\tProductos vendidos: " << totalProducts;
        cout << "\n----------------------------------------------------------------------------\n\n\n";
    }
}




// MERCADERO 3.2
void resumeByBranch(ABBgen *resume, string month) {
    if (resume) {
        resumeByBranch(resume->left, month);
        branchMonthlyResume( ((branch*)resume->data), month);
        resumeByBranch(resume->right, month);
    }
}

void statsMarketingByBranch(branch *branchs, string month) {
    ABBgen *resume = NULL;
    while (branchs) {
        insertABBgen(&resume, branchs);
        branchs = branchs->next;
    }
    resumeByBranch(resume, month);
}




// MERCADEO 3.4
void statsMarketingByClientBill(branch *branchs, people *clients, product *prod,string month) {
    bill *ax = NULL;
    detail *bx = NULL;
    people *cl = clients;
    ABBgen *resume = NULL;
    
    
    while (branchs) {
        ax = branchs->bills->first;
        while (ax) {
            if (getMonth(ax->date) == month) {
                bx = ax->detailBill;
                cl = searchPeopleByID(cl, ax->clientId);
                if (cl) {
                    while (bx) {
                        if (bx->code == prod->code) insertABBgen(&resume, cl, bx->amount, bx->price);
                        bx = bx->next;
                    }
                }
            }
            ax = ax->next;
        }
        branchs = branchs->next;
    }
    sortAnddShow(resume);
    /*
    if (resume) {
        cout << "\n\tRESUMEN VENTAS DE [ " << prod->name << " ] por cliente";
        cout << "\n----------------------------------------------------------------------------\n\tRESUMEN\n----------------------------------------------------------------------------\n";
        printFmt("C.I. ", 15);
        printFmt("NOMBRE ", 25);
        printFmt("COMPRADOS ", 15);
        printFmt("GANANCIA ", 15);
        cout << "\n----------------------------------------------------------------------------\n";
        inorderGen(&resume);
        cout << "\n----------------------------------------------------------------------------\n";
        //cout << "\tTotal ingresado: " << earned;
        //cout << "\n\tProductos vendidos: " << totalProducts;
        //cout << "\n----------------------------------------------------------------------------\n\n\n";
    }*/
}


#endif //REPORTS_H