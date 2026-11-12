#include<iomanip>
#include<iostream>
#include<string>
using namespace std;

void displayMenu();
void addParticipant(int, string, int, double, int& count);
void displayRecord(int, string, int, double, int);
int searchParticipant(const int id[], int, int);
void exerciseSummary(string, int, double, int);

const int SIZE = 20;

void displayMenu(){
    cout << "\n---------------------------------------------" <<endl;
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
        cin.ignore();
        getline(cin, name[i]);
        cout << "Enter exercise duration(minutes): ";
        cin >> minute[i];
        cout << "Enter estimated energy expenditure rate(kcal/m): ";
        cin >> rate;
        double expendedEnergy = rate * minute[i];
        energy[i] = expendedEnergy;
        i++;
        cout << "Participant " << i << " Added to the system.";
        cout <<endl;
    }
    if(i>=20){
        cout << "Maximum capacity of 20 reached\n";
    }
}

void displayRecord(int id[], string name[], int minute[], double energy[], int count){
    if(count == 0){
        cout <<"No Record to show\n";
    }else{
        cout << "\n-----------------------------" <<endl;
        cout << "Report of energy Expenditure" <<endl;
        cout << "-----------------------------" <<endl;
        for (int i = 0; i <count; i++){
            cout <<fixed <<setprecision(2);
            cout << "Participant " <<i+1 <<":" <<endl;
            cout <<left <<setw(30) <<"Participant ID"
                 <<right <<setw(50) <<id[i] <<endl;
            cout <<left <<setw(30) <<"Name of Participant"
                 <<right <<setw(50) <<name[i] <<endl;
            cout <<left <<setw(30) <<"Exercise duration(minutes)"
                 <<right <<setw(50) <<minute[i] <<endl;
            cout <<left <<setw(30) <<"Estimated energy expended(kcal)"
                 <<right <<setw(50) <<energy[i] <<endl;
            cout <<endl;
        }
    }
}

int searchParticipant(const int id[], int SIZE, int target){
    for(int i = 0; i < SIZE; i++){
        if(id[i] == target){
            return i;
        }
    }
    return -1;
}

void exerciseSummary(string name[], int minute[], double energy[], int count){
    if (count == 0){
        cout <<"Insufficient record\n";
    }else{
        int totalDuration = 0, energyIndex = 0;
        double totalEnergy = 0, maxEnergy = energy[0];
        for (int i = 0; i <count; i++){
            totalDuration += minute[i];
            totalEnergy += energy[i];
            if (energy[i] > maxEnergy){
                maxEnergy = energy[i];
                energyIndex = i;
            }
        }
        cout <<fixed<<setprecision(2);
        cout <<"\n----------------" <<endl;
        cout <<"Exercise Summary" <<endl;
        cout <<"----------------" <<endl;
        cout <<left <<setw(30) <<"Total Duration(minutes)"
             <<right <<setw(50) <<totalDuration <<endl;
        cout <<left <<setw(30) <<"Total Energy Expended(kcal)"
             <<right <<setw(50) <<totalEnergy <<endl;
        cout <<left <<setw(30) <<"Highest Energy Expended"
             <<right <<setw(50) <<name[energyIndex] <<endl;
        cout <<endl;
    }
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
                displayRecord(id, name, minute, energyExpended, count);
                break;
            case 3:{
                if (count != 0){
                    cout <<"Please enter the Participant's ID: ";
                    cin >> target;
                }else{
                    cout << "Error: no value available in record.\n";
                    break;
                }
                int index = searchParticipant(id, SIZE, target);
                if(index != -1){
                    cout <<"\nParticipant ID found at index ["<<index<<"]\n"<<endl;
                    cout <<fixed <<setprecision(2);
                    cout <<left <<setw(30) <<"Participant ID"
                         <<right <<setw(50) <<id[index] <<endl;
                    cout <<left <<setw(30) <<"Name of Participant"
                         <<right <<setw(50) <<name[index] <<endl;
                    cout <<left <<setw(30) <<"Exercise duration(minutes)"
                         <<right <<setw(50) <<minute[index] <<endl;
                    cout <<left <<setw(30) <<"Estimated energy expended(kcal)"
                         <<right <<setw(50) <<energyExpended[index] <<endl;
                    cout <<endl;
                }else{
                    cout <<"Participant ID not found in system.";
                }
                break;
            }
            case 4:
                exerciseSummary(name, minute, energyExpended, count);
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