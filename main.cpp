#include <iostream>
#include "B_Star_Tree.h"
#include <fstream>
void printMenu() {
    std::cout<<"=======================\n";
    std::cout << "Pretraga po primarnom kljucu(1)\n";
    std::cout << "Ispis stabla(2)\n";
    std::cout << "Dodavanje zapisa(3)\n" ;
    std::cout << "Brisanje zapisa(4)\n" ;
    std::cout << "Pretraga po imenu(5)\n" ;
    std::cout << "Pretraga k kljuceva(6)\n" ;
    std::cout << "Izlaz(0)\n" ;
}

int main() {
    int m=1;
    std::cout<<"=======================\n";
    std::cout<<"Napisite red B* stabla(red mora biti =<10 i >=3 \n";
    while(m<3||m>=10)
        std::cin>>m;
    auto* stablo =new BStarTree(m);
    std::cout<<"=======================\n";
    std::cout<<"Napisite ime fajla: \n";
    std::string ime_fila;
    std::cin>>ime_fila;
    std::ifstream file;
    file.open(ime_fila);
    if(!file.is_open())
    {
        std::cout<<"File ne postoji!\n";
        return 0;
    }
    stablo->parser(file);
    stablo->Print_keys();
    file.close();
    int decison=-1;
    while(decison!=0)
    {
        decison=-1;
        printMenu();
        while(decison<0||decison>6) {
            std::cin >> decison;
        }
        switch(decison){
            case 1: stablo->find_key_call();break;
            case 2: stablo->Print_keys();   break;
            case 3: stablo->insert_one();   break;
            case 4: stablo->delete_one();   break;
            case 5: stablo->find_name();    break;
            case 6: stablo->k_search();     break;
            case 0: break;
        }

    }
    stablo->~BStarTree();
    return 0;
}
