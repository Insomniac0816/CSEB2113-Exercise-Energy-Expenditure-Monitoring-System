#include<iomanip>
#include<iostream>
#include<string>
using namespace std;

void displayMenu();
void addParticipant(int, string, int, double, int& count);
void displayRecord();
int searchParticipant(const int id[], int, int);
void exerciseSummary();

const int SIZE = 20;

void displayMenu(){
    cout << "---------------------------------------------" <<endl;
    cout << "Exercise Energy Expenditure Monitoring System" <<endl;
    cout << "---------------------------------------------" <<endl;
    cout << "1. Add Participant" <<endl;
    cout << "2. Display Records" <<endl;
    cout << "3. Search Participant" <<endl;
    cout << "4. Print Summary" <<endl;
    cout << "5. Exit" <<endl;
}

void addParticipant(int id[], string name[], int minute[], double energy[], int& i){
    while (i<SIZE){
        double rate;
        int tempID;
        cout << "\nEnter ID number (or -1 to stop): ";
        cin >> tempID;
        if (tempID == -1){
            break;
        }
        if (searchParticipant(id, i, tempID) != -1){
            cout << "Error: The ID already exists! Try a different one.\n";
            continue;
        }
        id[i] = tempID;
        cout << "Enter name: ";
        cin >> name[i];
        cout << "Enter exercise duration(minutes): ";
        cin >> minute[i];
        cout << "Enter estimated energy expenditure rate(kcl/m): ";
        cin >> rate;
        double expendedEnergy = rate * minute[i];
        energy[i] = expendedEnergy;
        i++;
        cout << "Participant " << i <<" Added to the system.";
    }
    if(i>=20){
        cout << "Maximum capacity of 20 reached\n";
    }
}

void displayRecord(){

}

int searchParticipant(const int id[], int SIZE, int target){
    for(int i = 0; i < SIZE; i++){
        if(id[i] == target){
            return i;
        }
    }
    return -1;
}

void exerciseSummary(){

}

int main(){
    int choice = 0, target, count = 0;
    int id[SIZE];
    string name[SIZE];
    int minute[SIZE];
    double energyExpended[SIZE];
    while (choice != 5){
        displayMenu();
        cout << "\nPlease select an operation(1-5): ";
        cin >> choice;
        switch(choice){
            case 1:
                addParticipant(id, name, minute, energyExpended, count);
                break;
            case 2:
                displayRecord();
                break;
            case 3:
                cout <<"Please enter the Participant's ID: ";
                cin >> target;
                searchParticipant(id, SIZE, target);
                break;
            case 4:
                exerciseSummary();
                break;
            case 5:
                cout <<"Thank you for using this program.";
                break;
            default:
                cout <<"Invalid selection: Please enter a value between 1-5.\n";
        }
    }
    return 0;
}