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
    /*
    * @brief Display system title and each operations
    */
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
    /*
    * @details Add new participant's record, make sure there are no duplicates in id[].
    *
    * @param id The array of participant's IDs
    * @param name The array of participant's names
    * @param minute The array of exercise duration
    * @param energy The array of expended energy
    * @param i Counter for the function, used & to indicate pass-by-reference
    *          for the function to modify the counter in main
    */
    while (i<SIZE){
        //loop while there are less than 20 records
        double rate;
        int tempID;
        cout << "\nEnter ID number (or -1 to stop): ";
        //using tempID before actually append to id[] array 
        //tempID need to be verified to be added when no duplicate is found.
        cin >> tempID;
        if (tempID == -1){
            //terminate the process with an anchor value
            break;
        }
        if (searchParticipant(id, i, tempID) != -1){
            //reusing function searchParticipant() to check for duplicate
            cout << "Error: The ID already exists! Try a different one.\n";
            //skips the rest of the processes if there are duplicate
            continue;
        }
        id[i] = tempID;
        cout << "Enter name: ";
        //cleanup any leftover \n from the previous cin in prep for getline()
        cin.ignore();
        getline(cin, name[i]);
        cout << "Enter exercise duration(minutes): ";
        cin >> minute[i];
        cout << "Enter estimated energy expenditure rate(kcal/m): ";
        cin >> rate;
        //formula for the expended energy
        double expendedEnergy = rate * minute[i];
        energy[i] = expendedEnergy;
        i++;
        cout << "Participant " << i << " Added to the system.";
        cout <<endl;
    }
    //have another check outside the while loop because the operation might be access after the capacity is full
    if(i>=20){
        cout << "Maximum capacity of 20 reached\n";
    }
}

void displayRecord(int id[], string name[], int minute[], double energy[], int count){
    /*
    * @brief Display all records available.
    *
    * @param id The array of participant's IDs
    * @param name The array of participant's names
    * @param minute The array of exercise duration
    * @param energy The array of expended energy
    * @param count The length of each array 
    */
    if(count == 0){
        //make sure there are records in array
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
    /*
    * @brief Linear search to find the target id's index value
    *
    * @param id The array of participant's IDs
    * @param SIZE Constant of 20, indicating the high boundary
    * @param target The value that needs to be find
    * 
    * @return Index of the target
    */
    for(int i = 0; i < SIZE; i++){
        if(id[i] == target){
            //iterate through each items in id
            return i;
        }
    }
    //if the loop ended without triggering the return statement, return -1
    //-1 is specifically return because 0 is still an index in array
    return -1;
}

void exerciseSummary(string name[], int minute[], double energy[], int count){
    /*
    * @brief print a summary table with totalDuration, totalEnergy as well as maxEnergy across records
    *
    * @param id The array of participant's IDs
    * @param name The array of participant's names
    * @param minute The array of exercise duration
    * @param energy The array of expended energy
    * @param count The length of each array
    */
    if (count == 0){
        //make sure there are record in array
        cout <<"Insufficient record\n";
    }else{
        int totalDuration = 0, energyIndex = 0;
        double totalEnergy = 0, maxEnergy = energy[0];
        for (int i = 0; i <count; i++){
            //reusing i for each processes
            totalDuration += minute[i];
            totalEnergy += energy[i];
            if (energy[i] > maxEnergy){
                //update value for maxEnergy
                maxEnergy = energy[i];
                //update the index of maxEnergy
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
    //initialising variables and arrays
    int choice = 0, target, count = 0;
    int id[SIZE];
    string name[SIZE];
    int minute[SIZE];
    double energyExpended[SIZE];
    //loop whilst user did not choose 5 (exit)
    while (choice != 5){
        displayMenu();
        cout << "\nPlease select an operation(1-5): ";
        cin >> choice;
        //using switch case for data validation in value 1-5
        switch(choice){
            case 1:
                addParticipant(id, name, minute, energyExpended, count);
                break;
            case 2:
                displayRecord(id, name, minute, energyExpended, count);
                break;
            case 3:{
                //precheck if there are records in the array
                if (count != 0){
                    cout <<"Please enter the Participant's ID: ";
                    cin >> target;
                }else{
                    cout << "Error: no value available in record.\n";
                    break;
                }
                int index = searchParticipant(id, SIZE, target);
                if(index != -1){
                    //print the table if index is found
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