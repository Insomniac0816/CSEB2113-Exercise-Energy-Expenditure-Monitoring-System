#include<iomanip>
#include<iostream>
#include<string>
using namespace std;

int ID[20], MINUTE[20];
string NAME[20];


void displayMenu(){
    cout << "========================" <<endl;
    cout << "Exercise Energy Expenditure Monitoring System" <<endl;
    cout << "========================" <<endl;
    cout << "1. Add Participant" <<endl;
    cout << "2. Display Records" <<endl;
    cout << "3. Search Participant" <<endl;
    cout << "4. Print Summary" <<endl;
    cout << "5. Exit" <<endl;
}

int addParticipant(){
    cout << "Enter your ID number: ";
    cout << "Enter your name: ";
    cout << "Enter exercise duration(minutes): ";
    cout << "Enter estimated energy expenditure rate(kcl/m): ";
}

void displayRecord(){

}

int searchParticipant(){

}

void exerciseSummary(){

}

int main(){
    int choice = 0;
    while (choice != 5){
        displayMenu();
        cout << "\nPlease select an operation(1-5): ";
        cin >> choice;
        switch(choice){
            case 1:
                addParticipant();
                break;
            case 2:
                displayRecord();
                break;
            case 3:
                searchParticipant();
                break;
            case 4:
                exerciseSummary();
                break;
            case 5:
                cout <<"Thank you for using this program.";
            default:
                cout <<"Invalid selection: Please enter a value between 1-5.\n";
        }
    }
    return 0;
}